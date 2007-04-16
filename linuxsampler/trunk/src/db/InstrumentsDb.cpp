/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2007 Grigor Iliev                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,                *
 *   MA  02110-1301  USA                                                   *
 ***************************************************************************/

#include "InstrumentsDb.h"

#if HAVE_SQLITE3

#include <iostream>
#include <sstream>
#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include "../common/Exception.h"

namespace LinuxSampler {

    void DbInstrument::Copy(const DbInstrument& Instr) {
        if (this == &Instr) return;

        InstrFile = Instr.InstrFile;
        InstrNr = Instr.InstrNr;
        FormatFamily = Instr.FormatFamily;
        FormatVersion = Instr.FormatVersion;
        Size = Instr.Size;
        Created = Instr.Created;
        Modified = Instr.Modified;
        Description = Instr.Description;
        IsDrum = Instr.IsDrum;
        Product = Instr.Product;
        Artists = Instr.Artists;
        Keywords = Instr.Keywords;
    }


    void DbDirectory::Copy(const DbDirectory& Dir) {
        if (this == &Dir) return;

        Created = Dir.Created;
        Modified = Dir.Modified;
        Description = Dir.Description;
    }


    InstrumentsDb* InstrumentsDb::pInstrumentsDb = new InstrumentsDb;

    InstrumentsDb::InstrumentsDb() {
        db = NULL;
        DbInstrumentsMutex = Mutex();
    }

    InstrumentsDb::~InstrumentsDb() {
        if (db != NULL) sqlite3_close(db);
    }
    
    void InstrumentsDb::Destroy() {
        if (pInstrumentsDb != NULL) {
            delete pInstrumentsDb;
            pInstrumentsDb = NULL;
        }
    }

    void InstrumentsDb::AddInstrumentsDbListener(InstrumentsDb::Listener* l) {
        llInstrumentsDbListeners.AddListener(l);
    }
    
    void InstrumentsDb::RemoveInstrumentsDbListener(InstrumentsDb::Listener* l) {
        llInstrumentsDbListeners.RemoveListener(l);
    }
    
    InstrumentsDb* InstrumentsDb::GetInstrumentsDb() {
        return pInstrumentsDb;
    }
    
    void InstrumentsDb::SetDbFile(String File) {
        DbInstrumentsMutex.Lock();
        if (File.empty() || DbFile.length() > 0) {
            DbInstrumentsMutex.Unlock();
            throw Exception("Failed to set the database file");
        }
        DbFile = File;
        DbInstrumentsMutex.Unlock();
    }

    sqlite3* InstrumentsDb::GetDb() {
        if ( db != NULL) return db;

        if (DbFile.empty()) DbFile = "/var/lib/linuxsampler/instruments.db";
        int rc = sqlite3_open(DbFile.c_str(), &db);
        if (rc) {
            sqlite3_close(db);
            db = NULL;
            throw Exception("Cannot open instruments database: " + DbFile);
        }
        
        return db;
    }
    
    int InstrumentsDb::GetDirectoryCount(int DirId) {
        dmsg(2,("InstrumentsDb: GetDirectoryCount(DirId=%d)\n", DirId));
        if(DirId == -1) return -1;

        std::stringstream sql;
        sql << "SELECT COUNT(*) FROM instr_dirs WHERE parent_dir_id=" <<  DirId;
        
        int count = ExecSqlInt(sql.str());

        // While the root dir has ID 0 and parent ID 0, the directory
        // count for the root dir will be incorrect, so we should fix it.
        if (count != -1 && DirId == 0) count--;
        return count;
    }

    int InstrumentsDb::GetDirectoryCount(String Dir) {
        dmsg(2,("InstrumentsDb: GetDirectoryCount(Dir=%s)\n", Dir.c_str()));
        int i;

        DbInstrumentsMutex.Lock();
        try { i = GetDirectoryCount(GetDirectoryId(Dir)); }
        catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        if (i == -1) throw Exception("Unkown DB directory: " + Dir);
        
        return i;
    }

    IntListPtr InstrumentsDb::GetDirectoryIDs(int DirId) {
        std::stringstream sql;
        sql << "SELECT dir_id FROM instr_dirs ";
        sql << "WHERE parent_dir_id=" << DirId << " AND dir_id!=0";

        return ExecSqlIntList(sql.str());
    }

    StringListPtr InstrumentsDb::GetDirectories(String Dir) {
        dmsg(2,("InstrumentsDb: GetDirectories(Dir=%s)\n", Dir.c_str()));

        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(Dir);
            if(dirId == -1) throw Exception("Unknown DB directory: " + Dir);

            std::stringstream sql;
            sql << "SELECT dir_name FROM instr_dirs ";
            sql << "WHERE parent_dir_id=" << dirId << " AND dir_id!=0";

            DbInstrumentsMutex.Unlock();
            return ExecSqlStringList(sql.str());
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
    }

    int InstrumentsDb::GetDirectoryId(String Dir) {
        dmsg(2,("InstrumentsDb: GetDirectoryId(Dir=%s)\n", Dir.c_str()));
        CheckPathName(Dir);
        
        if (Dir.empty() || Dir.at(0) != '/') {
            return -1;
        } else if (Dir.length() == 1) {
            // We expect the root directory id to be always 0.
            return 0;
        }
        
        int id = 0, i = 1;
        int j = Dir.find('/', i);

        while(j != std::string::npos) {
            id = GetDirectoryId(id, Dir.substr(i, j - i));
            i = j + 1;
            if (i >= Dir.length()) return id;
            j = Dir.find('/', i);
        }
        
        return GetDirectoryId(id, Dir.substr(i));
    }

    int InstrumentsDb::GetDirectoryId(int ParentDirId, String DirName) {
        dmsg(2,("InstrumentsDb: GetDirectoryId(ParentDirId=%d, DirName=%s)\n", ParentDirId, DirName.c_str()));
        std::stringstream sql;
        sql << "SELECT dir_id FROM instr_dirs WHERE parent_dir_id=";
        sql << ParentDirId << " AND dir_name=?";
        return ExecSqlInt(sql.str(), DirName);
    }

    void InstrumentsDb::AddDirectory(String Dir) {
        dmsg(2,("InstrumentsDb: AddDirectory(Dir=%s)\n", Dir.c_str()));
        CheckPathName(Dir);
        String ParentDir = GetParentDirectory(Dir);
        
        DbInstrumentsMutex.Lock();
        try {
            if (Dir.length() > 1) {
                if (Dir.at(Dir.length() - 1) == '/') Dir.erase(Dir.length() - 1);
            }

            String dirName = GetFileName(Dir);
            if(ParentDir.empty() || dirName.empty()) {
                throw Exception("Failed to add DB directory: " + Dir);
            }

            int id = GetDirectoryId(ParentDir);
            if (id == -1) throw Exception("DB directory doesn't exist: " + ParentDir);
            int id2 = GetDirectoryId(id, dirName);
            if (id2 != -1) throw Exception("DB directory already exist: " + Dir);

            std::stringstream sql;
            sql << "INSERT INTO instr_dirs (parent_dir_id, dir_name) VALUES (";
            sql << id << ", ?)";

            ExecSql(sql.str(), dirName);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();

        FireDirectoryCountChanged(ParentDir);
    }

    void InstrumentsDb::RemoveDirectory(String Dir, bool Force) {
        dmsg(2,("InstrumentsDb: RemoveDirectory(Dir=%s,Force=%d)\n", Dir.c_str(), Force));

        String ParentDir = GetParentDirectory(Dir);

        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(Dir);
            if (dirId == -1) throw Exception("Unknown DB directory: " + Dir);
            if (dirId == 0) throw Exception("Cannot delete the root directory: " + Dir);
            if(ParentDir.empty()) throw Exception("Unknown parent directory");
            if (Force) RemoveDirectoryContent(dirId);
            RemoveDirectory(dirId);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();
        FireDirectoryCountChanged(ParentDir);
    }

    void InstrumentsDb::RemoveDirectoryContent(int DirId, int Level) {
        dmsg(2,("InstrumentsDb: RemoveDirectoryContent(DirId=%d,Level=%d)\n", DirId, Level));
        if (Level > 1000) throw Exception("Directory level too deep: " + ToString(Level));
        IntListPtr dirIds = GetDirectoryIDs(DirId);

        for (int i = 0; i < dirIds->size(); i++) {
            RemoveDirectoryContent(dirIds->at(i), Level + 1);
        }

        RemoveAllDirectories(DirId);
        RemoveAllInstruments(DirId);
    }

    void InstrumentsDb::RemoveDirectory(int DirId) {
        dmsg(2,("InstrumentsDb: RemoveDirectory(DirId=%d)\n", DirId));
        if (GetInstrumentCount(DirId) > 0 || GetDirectoryCount(DirId) > 0) {
            throw Exception("The specified DB directory is not empty");
        }

        std::stringstream sql;
        sql << "DELETE FROM instr_dirs WHERE dir_id=" << DirId;

        ExecSql(sql.str());
    }

    void InstrumentsDb::RemoveAllDirectories(int DirId) {
        dmsg(2,("InstrumentsDb: RemoveAllDirectories(DirId=%d)\n", DirId));
        IntListPtr dirIds = GetDirectoryIDs(DirId);

        for (int i = 0; i < dirIds->size(); i++) {
            if (!IsDirectoryEmpty(dirIds->at(i))) {
                throw Exception("DB directory not empty!");
            }
        }
        std::stringstream sql;
        sql << "DELETE FROM instr_dirs WHERE parent_dir_id=" << DirId;
        sql << " AND dir_id!=0";

        ExecSql(sql.str());
    }

    bool InstrumentsDb::IsDirectoryEmpty(int DirId) {
        dmsg(2,("InstrumentsDb: IsDirectoryEmpty(DirId=%d)\n", DirId));
        int dirCount = GetDirectoryCount(DirId);
        int instrCount = GetInstrumentCount(DirId);
        dmsg(3,("InstrumentsDb: IsDirectoryEmpty: dirCount=%d,instrCount=%d\n", dirCount, instrCount));
        if (dirCount == -1 || instrCount == -1) return false;
        return dirCount == 0 && instrCount == 0;
    }

    bool InstrumentsDb::DirectoryExist(String Dir) {
        dmsg(2,("InstrumentsDb: DirectoryExist(Dir=%s)\n", Dir.c_str()));
        bool b;

        DbInstrumentsMutex.Lock();
        try { b = GetDirectoryId(Dir) != -1; }
        catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();

        return b;
    }

    DbDirectory InstrumentsDb::GetDirectoryInfo(String Dir) {
        dmsg(2,("InstrumentsDb: GetDirectoryInfo(Dir=%s)\n", Dir.c_str()));
        DbDirectory d;

        DbInstrumentsMutex.Lock();

        try {
            int id = GetDirectoryId(Dir);
            if(id == -1) throw Exception("Unknown DB directory: " + Dir);

            sqlite3_stmt *pStmt = NULL;
            std::stringstream sql;
            sql << "SELECT created,modified,description FROM instr_dirs ";
            sql << "WHERE dir_id=" << id;

            int res = sqlite3_prepare(GetDb(), sql.str().c_str(), -1, &pStmt, NULL);
            if (res != SQLITE_OK) {
                throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
            }

            res = sqlite3_step(pStmt);
            if(res == SQLITE_ROW) {
                d.Created = ToString(sqlite3_column_text(pStmt, 0));
                d.Modified = ToString(sqlite3_column_text(pStmt, 1));
                d.Description = ToString(sqlite3_column_text(pStmt, 2));
            } else {
                sqlite3_finalize(pStmt);

                if (res != SQLITE_DONE) {
                    throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
                } else {
                    throw Exception("Unknown DB directory: " + Dir);
                }
            }
            
            sqlite3_finalize(pStmt);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();
        return d;
    }

    void InstrumentsDb::RenameDirectory(String Dir, String Name) {
        dmsg(2,("InstrumentsDb: RenameDirectory(Dir=%s,Name=%s)\n", Dir.c_str(), Name.c_str()));
        CheckFileName(Name);

        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(Dir);
            if (dirId == -1) throw Exception("Unknown DB directory: " + Dir);

            std::stringstream sql;
            sql << "SELECT parent_dir_id FROM instr_dirs WHERE dir_id=" <<  dirId;

            int parent = ExecSqlInt(sql.str());
            if (parent == -1) throw Exception("Unknown parent directory: " + Dir);
            if (GetDirectoryId(parent, Name) != -1) {
                throw Exception("Cannot rename. Directory with that name already exists: " + Name);
            }

            sql.str("");
            sql << "UPDATE instr_dirs SET dir_name=? WHERE dir_id=" << dirId;
            ExecSql(sql.str(), Name);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();
        FireDirectoryNameChanged(Dir, Name);
    }

    void InstrumentsDb::MoveDirectory(String Dir, String Dst) {
        dmsg(2,("InstrumentsDb: MoveDirectory(Dir=%s,Dst=%s)\n", Dir.c_str(), Dst.c_str()));

        String ParentDir = GetParentDirectory(Dir);
        if(ParentDir.empty()) throw Exception("Unknown parent directory");

        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(Dir);
            if (dirId == -1) throw Exception("Unknown DB directory: " + Dir);
            int dstId = GetDirectoryId(Dst);
            if (dstId == -1) throw Exception("Unknown DB directory: " + Dst);
            if (dirId == dstId) {
                throw Exception("Cannot move directory to itself");
            }

            if (Dir.at(Dir.length() - 1) != '/') Dir.append("/");
            if (Dst.length() > Dir.length()) {
                if (Dir.compare(Dst.substr(0, Dir.length())) == 0) {
                    throw Exception("Cannot move a directory to a subdirectory of itself.");
                }
            }

            std::stringstream sql;
            sql << "UPDATE instr_dirs SET parent_dir_id=" << dstId;
            sql << " WHERE dir_id=" << dirId;
            ExecSql(sql.str());
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();
        FireDirectoryCountChanged(ParentDir);
        FireDirectoryCountChanged(Dst);
    }

    void InstrumentsDb::SetDirectoryDescription(String Dir, String Desc) {
        dmsg(2,("InstrumentsDb: SetDirectoryDescription(Dir=%s,Desc=%s)\n", Dir.c_str(), Desc.c_str()));
        
        DbInstrumentsMutex.Lock();
        try {
            int id = GetDirectoryId(Dir);
            if(id == -1) throw Exception("Unknown DB directory: " + Dir);

            std::stringstream sql;
            sql << "UPDATE instr_dirs SET description=?,modified=CURRENT_TIMESTAMP ";
            sql << "WHERE dir_id="<< id;
        
            ExecSql(sql.str(), Desc);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        
        FireDirectoryInfoChanged(Dir);
    }

    void InstrumentsDb::AddInstruments(String DbDir, String FilePath, int Index) {
        dmsg(2,("InstrumentsDb: AddInstruments(DbDir=%s,FilePath=%s,Index=%d)\n", DbDir.c_str(), FilePath.c_str(), Index));
        if (DbDir.empty() || FilePath.empty()) return;
        
        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(DbDir);
            if (dirId == -1) throw Exception("Invalid DB directory: " + DbDir);

            struct stat statBuf;
            int res = stat(FilePath.c_str(), &statBuf);
            if (res) {
                std::stringstream ss;
                ss << "Fail to stat `" << FilePath << "`: " << strerror(errno);
                throw Exception(ss.str());
            }

            if (S_ISREG(statBuf.st_mode)) {
                AddInstrumentsFromFile(DbDir, FilePath, Index);
                DbInstrumentsMutex.Unlock();
                return;
            }

            if (!S_ISDIR(statBuf.st_mode)) {
                DbInstrumentsMutex.Unlock();
                return;
            }
            
            if (Index != -1) {
                std::stringstream ss;
                ss << "`" << FilePath << "` is directory, not an instrument file";
                throw Exception(ss.str());
            }
        
            AddInstrumentsRecursive(DbDir, FilePath, false);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();
    }

    void InstrumentsDb::AddInstrumentsNonrecursive(String DbDir, String FsDir) {
        dmsg(2,("InstrumentsDb: AddInstrumentsNonrecursive(DbDir=%s,FsDir=%s)\n", DbDir.c_str(), FsDir.c_str()));
        if (DbDir.empty() || FsDir.empty()) return;
        
        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(DbDir);
            if (dirId == -1) throw Exception("Invalid DB directory: " + DbDir);

            struct stat statBuf;
            int res = stat(FsDir.c_str(), &statBuf);
            if (res) {
                std::stringstream ss;
                ss << "Fail to stat `" << FsDir << "`: " << strerror(errno);
                throw Exception(ss.str());
            }

            if (!S_ISDIR(statBuf.st_mode)) {
                throw Exception("Directory expected");
            }
            
            if (FsDir.at(FsDir.length() - 1) != '/') FsDir.append("/");

            DIR* pDir = opendir(FsDir.c_str());
            if (pDir == NULL) {
                std::stringstream ss;
                ss << "The scanning of directory `" << FsDir << "` failed: ";
                ss << strerror(errno);
                std::cout << ss.str();
                DbInstrumentsMutex.Unlock();
                return;
            }

            struct dirent* pEnt = readdir(pDir);
            while (pEnt != NULL) {
                if (pEnt->d_type != DT_REG) {
                    pEnt = readdir(pDir);
                    continue;
                }

                AddInstrumentsFromFile(DbDir, FsDir + String(pEnt->d_name));
                pEnt = readdir(pDir);
            }

            if (closedir(pDir)) {
                std::stringstream ss;
                ss << "Failed to close directory `" << FsDir << "`: ";
                ss << strerror(errno);
                std::cout << ss.str();
            }
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }

        DbInstrumentsMutex.Unlock();
    }

    void InstrumentsDb::AddInstrumentsRecursive(String DbDir, String FsDir, bool Flat) {
        dmsg(2,("InstrumentsDb: AddInstrumentsRecursive(DbDir=%s,FsDir=%s,Flat=%d)\n", DbDir.c_str(), FsDir.c_str(), Flat));
        DirectoryScanner::Scan(DbDir, FsDir, Flat);
    }

    int InstrumentsDb::GetInstrumentCount(int DirId) {
        dmsg(2,("InstrumentsDb: GetInstrumentCount(DirId=%d)\n", DirId));
        if(DirId == -1) return -1;
        
        std::stringstream sql;
        sql << "SELECT COUNT(*) FROM instruments WHERE dir_id=" <<  DirId;
        
        return ExecSqlInt(sql.str());
    }

    int InstrumentsDb::GetInstrumentCount(String Dir) {
        dmsg(2,("InstrumentsDb: GetInstrumentCount(Dir=%s)\n", Dir.c_str()));
        int i;
        
        DbInstrumentsMutex.Lock();
        try { i = GetInstrumentCount(GetDirectoryId(Dir)); }
        catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();

        if (i == -1) throw Exception("Unknown Db directory: " + Dir);
        return i;
    }

    IntListPtr InstrumentsDb::GetInstrumentIDs(int DirId) {
        std::stringstream sql;
        sql << "SELECT instr_id FROM instruments WHERE dir_id=" << DirId;

        return ExecSqlIntList(sql.str());
    }

    StringListPtr InstrumentsDb::GetInstruments(String Dir) {
        dmsg(2,("InstrumentsDb: GetInstruments(Dir=%s)\n", Dir.c_str()));
        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(Dir);
            if(dirId == -1) throw Exception("Unknown DB directory: " + Dir);

            std::stringstream sql;
            sql << "SELECT instr_name FROM instruments WHERE dir_id=" << dirId;

            StringListPtr instrs = ExecSqlStringList(sql.str());
            DbInstrumentsMutex.Unlock();
            return instrs;
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
    }

    int InstrumentsDb::GetInstrumentId(String Instr) {
        dmsg(2,("InstrumentsDb: GetInstrumentId(Instr=%s)\n", Instr.c_str()));
        String Dir = GetDirectoryPath(Instr);
        if (Dir.empty()) return -1;

        return GetInstrumentId(GetDirectoryId(Dir), GetFileName(Instr));
    }

    int InstrumentsDb::GetInstrumentId(int DirId, String InstrName) {
        dmsg(2,("InstrumentsDb: GetInstrumentId(DirId=%d,InstrName=%s)\n", DirId, InstrName.c_str()));
        if (DirId == -1 || InstrName.empty()) return -1;
        
        std::stringstream sql;
        sql << "SELECT instr_id FROM instruments WHERE dir_id=";
        sql << DirId << " AND instr_name=?";
        return ExecSqlInt(sql.str(), InstrName);
    }
    
    void InstrumentsDb::RemoveInstrument(String Instr) {
        dmsg(2,("InstrumentsDb: RemoveInstrument(Instr=%s)\n", Instr.c_str()));
        String ParentDir = GetDirectoryPath(Instr);
        if(ParentDir.empty()) throw Exception("Unknown parent directory");
        
        DbInstrumentsMutex.Lock();
        try {
            int instrId = GetInstrumentId(Instr);
            if(instrId == -1) {
                throw Exception("The specified instrument does not exist: " + Instr);
            }
            RemoveInstrument(instrId);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        FireInstrumentCountChanged(ParentDir);
    }

    void InstrumentsDb::RemoveInstrument(int InstrId) {
        dmsg(2,("InstrumentsDb: RemoveInstrument(InstrId=%d)\n", InstrId));

        std::stringstream sql;
        sql << "DELETE FROM instruments WHERE instr_id=" << InstrId;

        ExecSql(sql.str());
    }

    void InstrumentsDb::RemoveAllInstruments(int DirId) {
        dmsg(2,("InstrumentsDb: RemoveAllInstruments(DirId=%d)\n", DirId));

        std::stringstream sql;
        sql << "DELETE FROM instruments WHERE dir_id=" << DirId;
        ExecSql(sql.str());
    }

    DbInstrument InstrumentsDb::GetInstrumentInfo(String Instr) {
        dmsg(2,("InstrumentsDb: GetInstrumentInfo(Instr=%s)\n", Instr.c_str()));
        DbInstrument i;
        
        DbInstrumentsMutex.Lock();
        try {
            int id = GetInstrumentId(Instr);
            if(id == -1) throw Exception("Unknown DB instrument: " + Instr);
        
            sqlite3_stmt *pStmt = NULL;
            std::stringstream sql;
            sql << "SELECT instr_file,instr_nr,format_family,format_version,";
            sql << "instr_size,created,modified,description,is_drum,product,";
            sql << "artists,keywords FROM instruments WHERE instr_id=" << id;

            int res = sqlite3_prepare(GetDb(), sql.str().c_str(), -1, &pStmt, NULL);
            if (res != SQLITE_OK) {
                throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
            }

            res = sqlite3_step(pStmt);
            if(res == SQLITE_ROW) {
                i.InstrFile = ToString(sqlite3_column_text(pStmt, 0));
                i.InstrNr = sqlite3_column_int(pStmt, 1);
                i.FormatFamily = ToString(sqlite3_column_text(pStmt, 2));
                i.FormatVersion = ToString(sqlite3_column_text(pStmt, 3));
                i.Size = sqlite3_column_int64(pStmt, 4);
                i.Created = ToString(sqlite3_column_text(pStmt, 5));
                i.Modified = ToString(sqlite3_column_text(pStmt, 6));
                i.Description = ToString(sqlite3_column_text(pStmt, 7));
                i.IsDrum = sqlite3_column_int(pStmt, 8);
                i.Product = ToString(sqlite3_column_text(pStmt, 9));
                i.Artists = ToString(sqlite3_column_text(pStmt, 10));
                i.Keywords = ToString(sqlite3_column_text(pStmt, 11));
            } else {
                sqlite3_finalize(pStmt);
            
                if (res != SQLITE_DONE) {
                    throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
                } else {
                    throw Exception("Unknown DB instrument: " + Instr);
                }
            }

            sqlite3_finalize(pStmt);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        
        return i;
    }

    void InstrumentsDb::RenameInstrument(String Instr, String Name) {
        dmsg(2,("InstrumentsDb: RenameInstrument(Instr=%s,Name=%s)\n", Instr.c_str(), Name.c_str()));
        CheckFileName(Name);

        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(GetDirectoryPath(Instr));
            if (dirId == -1) throw Exception("Unknown DB instrument: " + Instr);

            int instrId = GetInstrumentId(dirId, GetFileName(Instr));
            if (instrId == -1) throw Exception("Unknown DB instrument: " + Instr);

            if (GetInstrumentId(dirId, Name) != -1) {
                throw Exception("Cannot rename. Instrument with that name already exists: " + Name);
            }

            std::stringstream sql;
            sql << "UPDATE instruments SET instr_name=? WHERE instr_id=" << instrId;
            ExecSql(sql.str(), Name);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        FireInstrumentNameChanged(Instr, Name);
    }

    void InstrumentsDb::MoveInstrument(String Instr, String Dst) {
        dmsg(2,("InstrumentsDb: MoveInstrument(Instr=%s,Dst=%s)\n", Instr.c_str(), Dst.c_str()));
        String ParentDir = GetDirectoryPath(Instr);
        if(ParentDir.empty()) throw Exception("Unknown parent directory");

        DbInstrumentsMutex.Lock();
        try {
            int dirId = GetDirectoryId(GetDirectoryPath(Instr));
            if (dirId == -1) throw Exception("Unknown DB instrument: " + Instr);

            String instrName = GetFileName(Instr);
            int instrId = GetInstrumentId(dirId, instrName);
            if (instrId == -1) throw Exception("Unknown DB instrument: " + Instr);

            int dstId = GetDirectoryId(Dst);
            if (dstId == -1) throw Exception("Unknown DB directory: " + Dst);
            if (dirId == dstId) {
                DbInstrumentsMutex.Unlock();
                return;
            }

            if (GetInstrumentId(dstId, instrName) != -1) {
                throw Exception("Cannot move. Instrument with that name already exists: " + instrName);
            }

            std::stringstream sql;
            sql << "UPDATE instruments SET dir_id=" << dstId;
            sql << " WHERE instr_id=" << instrId;
            ExecSql(sql.str());
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        FireInstrumentCountChanged(ParentDir);
        FireInstrumentCountChanged(Dst);
    }

    void InstrumentsDb::SetInstrumentDescription(String Instr, String Desc) {
        dmsg(2,("InstrumentsDb: SetInstrumentDescription(Instr=%s,Desc=%s)\n", Instr.c_str(), Desc.c_str()));

        DbInstrumentsMutex.Lock();
        try {
            int id = GetInstrumentId(Instr);
            if(id == -1) throw Exception("Unknown DB instrument: " + Instr);

            std::stringstream sql;
            sql << "UPDATE instruments SET description=?,modified=CURRENT_TIMESTAMP ";
            sql << "WHERE instr_id="<< id;

            ExecSql(sql.str(), Desc);
        } catch (Exception e) {
            DbInstrumentsMutex.Unlock();
            throw e;
        }
        DbInstrumentsMutex.Unlock();
        FireInstrumentInfoChanged(Instr);
    }

    void InstrumentsDb::AddInstrumentsFromFile(String DbDir, String File, int Index) {
        dmsg(2,("InstrumentsDb: AddInstrumentsFromFile(DbDir=%s,File=%s,Index=%d)\n", DbDir.c_str(), File.c_str(), Index));
        
        if(File.length() < 4) return;
        
        try {
            if(!strcasecmp(".gig", File.substr(File.length() - 4).c_str())) {
                AddGigInstruments(DbDir, File, Index);
            }
        } catch(Exception e) {
            std::cout << e.Message() << std::endl;
        }
    }

    void InstrumentsDb::AddGigInstruments(String DbDir, String File, int Index) {
        dmsg(2,("InstrumentsDb: AddGigInstruments(DbDir=%s,File=%s,Index=%d)\n", DbDir.c_str(), File.c_str(), Index));
        int dirId = GetDirectoryId(DbDir);
        if (dirId == -1) throw Exception("Invalid DB directory: " + DbDir);

        struct stat statBuf;
        int res = stat(File.c_str(), &statBuf);
        if (res) {
            std::stringstream ss;
            ss << "Fail to stat `" << File << "`: " << strerror(errno);
            throw Exception(ss.str());
        }

        if (!S_ISREG(statBuf.st_mode)) {
            std::stringstream ss;
            ss << "`" << File << "` is not a regular file";
            throw Exception(ss.str());
        }

        RIFF::File* riff = NULL;
        gig::File* gig = NULL;
        try {
            riff = new RIFF::File(File);
            gig::File* gig = new gig::File(riff);
            
            std::stringstream sql;
            sql << "INSERT INTO instruments (dir_id,instr_name,instr_file,";
            sql << "instr_nr,format_family,format_version,instr_size,";
            sql << "description,is_drum,product,artists,keywords) VALUES (";
            sql << dirId << ",?,?,?,'GIG',?," << statBuf.st_size << ",?,?,?,?,?)";

            sqlite3_stmt* pStmt = NULL;

            int res = sqlite3_prepare(GetDb(), sql.str().c_str(), -1, &pStmt, NULL);
            if (res != SQLITE_OK) {
                throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
            }

            BindTextParam(pStmt, 2, File);
            String ver = "";
            if (gig->pVersion != NULL) ver = ToString(gig->pVersion->major);
            BindTextParam(pStmt, 4, ver);

            if (Index == -1) {
                int instrIndex = 0;
                gig::Instrument* pInstrument = gig->GetFirstInstrument();
                while (pInstrument) {
                    BindTextParam(pStmt, 7, gig->pInfo->Product);
                    BindTextParam(pStmt, 8, gig->pInfo->Artists);
                    BindTextParam(pStmt, 9, gig->pInfo->Keywords);
                    AddGigInstrument(pStmt, DbDir, dirId, File, pInstrument, instrIndex);

                    instrIndex++;
                    pInstrument = gig->GetNextInstrument();
                }
            } else {
                gig::Instrument* pInstrument = gig->GetInstrument(Index);
                if (pInstrument != NULL) {
                    BindTextParam(pStmt, 7, gig->pInfo->Product);
                    BindTextParam(pStmt, 8, gig->pInfo->Artists);
                    BindTextParam(pStmt, 9, gig->pInfo->Keywords);
                    AddGigInstrument(pStmt, DbDir, dirId, File, pInstrument, Index);
                }
            }

            delete gig;
            delete riff;
        } catch (RIFF::Exception e) {
            if (gig != NULL) delete gig;
            if (riff != NULL) delete riff;
            std::stringstream ss;
            ss << "Failed to scan `" << File << "`: " << e.Message;
            
            throw Exception(ss.str());
        } catch (Exception e) {
            if (gig != NULL) delete gig;
            if (riff != NULL) delete riff;
            throw e;
        } catch (...) {
            if (gig != NULL) delete gig;
            if (riff != NULL) delete riff;
            throw Exception("Failed to scan `" + File + "`");
        }
    }

    void InstrumentsDb::AddGigInstrument (sqlite3_stmt* pStmt, String DbDir, int DirId, String File, gig::Instrument* pInstrument, int Index) {
        String name = pInstrument->pInfo->Name;
        if (name == "") return;
        name = GetUniqueInstrumentName(DirId, name);
        
        std::stringstream sql2;
        sql2 << "SELECT COUNT(*) FROM instruments WHERE instr_file=? AND ";
        sql2 << "instr_nr=" << Index;
        if (ExecSqlInt(sql2.str(), File) > 0) return;

        BindTextParam(pStmt, 1, name);
        BindIntParam(pStmt, 3, Index);

        BindTextParam(pStmt, 5, pInstrument->pInfo->Comments);
        BindIntParam(pStmt, 6, pInstrument->IsDrum);

        if (!pInstrument->pInfo->Product.empty()) {
            BindTextParam(pStmt, 7, pInstrument->pInfo->Product);
        }
        if (!pInstrument->pInfo->Artists.empty()) {
            BindTextParam(pStmt, 8, pInstrument->pInfo->Artists);
        }

        if (!pInstrument->pInfo->Keywords.empty()) {
            BindTextParam(pStmt, 9, pInstrument->pInfo->Keywords);
        }

        int res = sqlite3_step(pStmt);
        if(res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        res = sqlite3_reset(pStmt);
        FireInstrumentCountChanged(DbDir);
    }

    void InstrumentsDb::ExecSql(String Sql) {
        dmsg(2,("InstrumentsDb: ExecSql(Sql=%s)\n", Sql.c_str()));
        sqlite3_stmt *pStmt = NULL;
        
        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
        
        res = sqlite3_step(pStmt);
        if(res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
    }

    void InstrumentsDb::ExecSql(String Sql, String Param) {
        dmsg(2,("InstrumentsDb: ExecSql(Sql=%s,Param=%s)\n", Sql.c_str(), Param.c_str()));
        sqlite3_stmt *pStmt = NULL;
        
        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        BindTextParam(pStmt, 1, Param);

        res = sqlite3_step(pStmt);
        if (res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
    }

    int InstrumentsDb::ExecSqlInt(String Sql) {
        dmsg(2,("InstrumentsDb: ExecSqlInt(Sql=%s)\n", Sql.c_str()));
        sqlite3_stmt *pStmt = NULL;

        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
        
        int i = -1;
        res = sqlite3_step(pStmt);
        if(res == SQLITE_ROW) {
            i = sqlite3_column_int(pStmt, 0);
        } else if (res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
        
        return i;
    }

    int InstrumentsDb::ExecSqlInt(String Sql, String Param) {
        dmsg(2,("InstrumentsDb: ExecSqlInt(Sql=%s,Param=%s)\n", Sql.c_str(), Param.c_str()));
        sqlite3_stmt *pStmt = NULL;

        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        BindTextParam(pStmt, 1, Param);

        int i = -1;
        res = sqlite3_step(pStmt);
        if(res == SQLITE_ROW) {
            i = sqlite3_column_int(pStmt, 0);
        } else if (res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
        return i;
    }

    String InstrumentsDb::ExecSqlString(String Sql) {
        dmsg(2,("InstrumentsDb: ExecSqlString(Sql=%s)\n", Sql.c_str()));
        sqlite3_stmt *pStmt = NULL;

        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
        
        String s;
        res = sqlite3_step(pStmt);
        if(res == SQLITE_ROW) {
            s = ToString(sqlite3_column_text(pStmt, 0));
        } else if (res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
        
        return s;
    }

    IntListPtr InstrumentsDb::ExecSqlIntList(String Sql) {
        IntListPtr intList(new std::vector<int>);
        
        sqlite3_stmt *pStmt = NULL;

        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
        
        res = sqlite3_step(pStmt);
        while(res == SQLITE_ROW) {
            intList->push_back(sqlite3_column_int(pStmt, 0));
            res = sqlite3_step(pStmt);
        }
        
        if (res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
        
        return intList;
    }
    
    StringListPtr InstrumentsDb::ExecSqlStringList(String Sql) {
        StringListPtr stringList(new std::vector<String>);
        
        sqlite3_stmt *pStmt = NULL;

        int res = sqlite3_prepare(GetDb(), Sql.c_str(), -1, &pStmt, NULL);
        if (res != SQLITE_OK) {
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
        
        res = sqlite3_step(pStmt);
        while(res == SQLITE_ROW) {
            stringList->push_back(ToString(sqlite3_column_text(pStmt, 0)));
            res = sqlite3_step(pStmt);
        }
        
        if (res != SQLITE_DONE) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(pStmt);
        
        return stringList;
    }

    void InstrumentsDb::BindTextParam(sqlite3_stmt* pStmt, int Index, String Text) {
        if (pStmt == NULL) return;
        int res = sqlite3_bind_text(pStmt, Index, Text.c_str(), -1, SQLITE_STATIC);
        if (res != SQLITE_OK) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
    }

    void InstrumentsDb::BindIntParam(sqlite3_stmt* pStmt, int Index, int Param) {
        if (pStmt == NULL) return;
        int res = sqlite3_bind_int(pStmt, Index, Param);
        if (res != SQLITE_OK) {
            sqlite3_finalize(pStmt);
            throw Exception("DB error: " + ToString(sqlite3_errmsg(db)));
        }
    }

    String InstrumentsDb::GetDirectoryPath(String File) {
        if (File.empty()) return String("");
        if (File.at(0) != '/') String("");
        if (File.length() == 1) return File;
        if (File.at(File.length() - 1) == '/') return File.substr(0, File.length() - 1);
        int i = File.rfind('/', File.length() - 1);
        if(i == std::string::npos) return String("");
        if(i == 0) return String("/");
        return File.substr(0, i);
    }

    String InstrumentsDb::GetFileName(String Path) {
        if (Path.length() < 2) return String("");
        if (Path.at(0) != '/') String("");
        if (Path.at(Path.length() - 1) == '/') return String("");
        int i = Path.rfind('/', Path.length() - 1);
        return Path.substr(i + 1);
    }

    void InstrumentsDb::CheckPathName(String Path) {
        if (Path.empty()) return;

        int i = 0, j = Path.find('/', i);

        while(j != std::string::npos) {
            if (j + 1 >= Path.length()) return;
            if (Path.at(j + 1) == '/') throw Exception("Invalid path name: " + Path);
            
            i = j + 1;
            j = Path.find('/', i);
        }
    }
    
    String InstrumentsDb::GetParentDirectory(String Dir) {
        if (Dir.length() < 2) return String("");
        if (Dir.at(0) != '/') String("");
        int i = Dir.rfind('/', Dir.length() - 2);
        if (i == 0) return "/";
        return Dir.substr(0, i);
    }

    void InstrumentsDb::CheckFileName(String File) {
        if (File.empty()) throw Exception("Invalid file name: " + File);
        if (File.find('/') != std::string::npos) {
            throw Exception("Invalid file name: " + File);
        }
    }

    String InstrumentsDb::GetUniqueInstrumentName(int DirId, String Name) {
        dmsg(2,("InstrumentsDb: GetUniqueInstrumentName(DirId=%d,Name=%s)\n", DirId, Name.c_str()));
        std::stringstream sql;
        sql << "SELECT COUNT(*) FROM instruments WHERE dir_id=" << DirId;
        sql << " AND instr_name=?";

        if (ExecSqlInt(sql.str(), Name) == 0) return Name;
        std::stringstream ss;
        for(int i = 2; i < 1001; i++) {
            ss.str("");
            ss << Name << '[' << i << ']';
            if (ExecSqlInt(sql.str(), ss.str()) == 0) return ss.str();
        }

        throw Exception("Unable to find an unique name: " + Name);
    }
    
    void InstrumentsDb::FireDirectoryCountChanged(String Dir) {
        for (int i = 0; i < llInstrumentsDbListeners.GetListenerCount(); i++) {
            llInstrumentsDbListeners.GetListener(i)->DirectoryCountChanged(Dir);
        }
    }
    
    void InstrumentsDb::FireDirectoryInfoChanged(String Dir) {
        for (int i = 0; i < llInstrumentsDbListeners.GetListenerCount(); i++) {
            llInstrumentsDbListeners.GetListener(i)->DirectoryInfoChanged(Dir);
        }
    }
    
    void InstrumentsDb::FireDirectoryNameChanged(String Dir, String NewName) {
        for (int i = 0; i < llInstrumentsDbListeners.GetListenerCount(); i++) {
            llInstrumentsDbListeners.GetListener(i)->DirectoryNameChanged(Dir, NewName);
        }
    }
    
    void InstrumentsDb::FireInstrumentCountChanged(String Dir) {
        for (int i = 0; i < llInstrumentsDbListeners.GetListenerCount(); i++) {
            llInstrumentsDbListeners.GetListener(i)->InstrumentCountChanged(Dir);
        }
    }
    
    void InstrumentsDb::FireInstrumentInfoChanged(String Instr) {
        for (int i = 0; i < llInstrumentsDbListeners.GetListenerCount(); i++) {
            llInstrumentsDbListeners.GetListener(i)->InstrumentInfoChanged(Instr);
        }
    }
    
    void InstrumentsDb::FireInstrumentNameChanged(String Instr, String NewName) {
        for (int i = 0; i < llInstrumentsDbListeners.GetListenerCount(); i++) {
            llInstrumentsDbListeners.GetListener(i)->InstrumentNameChanged(Instr, NewName);
        }
    }
    

    String DirectoryScanner::DbDir;
    String DirectoryScanner::FsDir;
    bool DirectoryScanner::Flat;

    void DirectoryScanner::Scan(String DbDir, String FsDir, bool Flat) {
        dmsg(2,("DirectoryScanner: Scan(DbDir=%s,FsDir=%s,Flat=%d)\n", DbDir.c_str(), FsDir.c_str(), Flat));
        if (DbDir.empty() || FsDir.empty()) throw Exception("Directory expected");
        
        struct stat statBuf;
        int res = stat(FsDir.c_str(), &statBuf);
        if (res) {
            std::stringstream ss;
            ss << "Fail to stat `" << FsDir << "`: " << strerror(errno);
            throw Exception(ss.str());
        }

        if (!S_ISDIR(statBuf.st_mode)) {
            throw Exception("Directory expected");
        }
        
        DirectoryScanner::DbDir = DbDir;
        DirectoryScanner::FsDir = FsDir;
        if (DbDir.at(DbDir.length() - 1) != '/') {
            DirectoryScanner::DbDir.append("/");
        }
        if (FsDir.at(FsDir.length() - 1) != '/') {
            DirectoryScanner::FsDir.append("/");
        }
        DirectoryScanner::Flat = Flat;
        
        ftw(FsDir.c_str(), FtwCallback, 10);
    }

    int DirectoryScanner::FtwCallback(const char* fpath, const struct stat* sb, int typeflag) {
        dmsg(2,("DirectoryScanner: FtwCallback(fpath=%s)\n", fpath));
        if (typeflag != FTW_D) return 0;

        String dir = DbDir;
        if (!Flat) {
            String subdir = fpath;
            if(subdir.length() > FsDir.length()) {
                subdir = subdir.substr(FsDir.length());
                dir += subdir;
            }
        }
        
        InstrumentsDb* db = InstrumentsDb::GetInstrumentsDb();
        if (!db->DirectoryExist(dir)) db->AddDirectory(dir);

        db->AddInstrumentsNonrecursive(dir, String(fpath));

        return 0;
    };

} // namespace LinuxSampler

#endif // HAVE_SQLITE3
