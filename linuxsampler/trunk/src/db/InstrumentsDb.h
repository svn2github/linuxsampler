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

#include "../common/global.h"

#if HAVE_SQLITE3

#ifndef __LS_INSTRUMENTSDB_H__
#define __LS_INSTRUMENTSDB_H__

#include <sqlite3.h>
#include <vector>
#include <sys/stat.h>
#include <gig.h>
#include "../common/Mutex.h"
#include "../EventListeners.h"

namespace LinuxSampler {

    class DbInstrument {
        public:
            String InstrFile;
            int    InstrNr;
            String FormatFamily;
            String FormatVersion;
            long long int Size;
            String Created;
            String Modified;
            String Description;
            bool   IsDrum;
            String Product;
            String Artists;
            String Keywords;

            DbInstrument() { }
            DbInstrument(const DbInstrument& Instr) { Copy(Instr); }
            void operator=(const DbInstrument& Instr) { Copy(Instr); }
            void Copy(const DbInstrument&);
    };

    class DbDirectory {
        public:
            String Created;
            String Modified;
            String Description;

            DbDirectory() { }
            DbDirectory(const DbDirectory& Dir) { Copy(Dir); }
            void operator=(const DbDirectory& Dir) { Copy(Dir); }
            void Copy(const DbDirectory&);
    };
    
    typedef std::auto_ptr<std::vector<int> > IntListPtr;
    typedef std::auto_ptr<std::vector<String> > StringListPtr;

    /**
     * @brief Provides access to the instruments database.
     */
    class InstrumentsDb {
        public:

            /**
             * This class is used as a listener, which is notified when
             * changes to the instruments database are made.
             */
            class Listener {
                public:
                    /**
                     * Invoked when the number of instrument directories
                     * in a specific directory has changed.
                     * @param Dir The absolute pathname of the directory in
                     * which the number of directories is changed.
                     */
                    virtual void DirectoryCountChanged(String Dir) = 0;

                    /**
                     * Invoked when the settings of an instrument directory
                     * are changed.
                     * @param Dir The absolute pathname of the directory
                     * whose settings are changed.
                     */
                    virtual void DirectoryInfoChanged(String Dir) = 0;

                    /**
                     * Invoked when an instrument directory is renamed.
                     * @param Dir The old absolute pathname of the directory.
                     * @param NewName The new name of the directory.
                     */
                    virtual void DirectoryNameChanged(String Dir, String NewName) = 0;

                    /**
                     * Invoked when the number of instruments
                     * in a specific directory has changed.
                     * @param Dir The absolute pathname of the directory in
                     * which the number of instruments is changed.
                     */
                    virtual void InstrumentCountChanged(String Dir) = 0;

                    /**
                     * Invoked when the settings of an instrument are changed.
                     * @param Instr The absolute pathname of the instrument
                     * whose settings are changed.
                     */
                    virtual void InstrumentInfoChanged(String Instr) = 0;

                    /**
                     * Invoked when an instrument is renamed.
                     * @param Instr The old absolute pathname of the instrument.
                     * @param NewName The new name of the directory.
                     */
                    virtual void InstrumentNameChanged(String Instr, String NewName) = 0;
            };

            /**
             * Registers the specified listener to be notified
             * when changes to the instruments database are made.
             */
            void AddInstrumentsDbListener(InstrumentsDb::Listener* l);

            /**
             * Removes the specified listener.
             */
            void RemoveInstrumentsDbListener(InstrumentsDb::Listener* l);

            /**
             * This method is used to access the instruments database.
             */
            static InstrumentsDb* GetInstrumentsDb();

            /**
             * Sets the absolute path name of the instruments database file to use.
             * The instruments database file location should be set before
             * any attempt to access the database and once set could not be changed.
             * @throws Exception - if an empty string is provided or if
             * the method is called more than once.
             */
            void SetDbFile(String File);

            /**
             * Gets the number of directories in the specified directory.
             * @param Dir The absolute path name of the directory.
             * @throws Exception - if database error occurs, or
             * the specified path name is invalid.
             * @returns The number of directories in the specified directory
             * or -1 if the directory doesn't exist.
             */
            int GetDirectoryCount(String Dir);

            /**
             * Gets the list of directories in the specified directory.
             * @param Dir The absolute path name of the directory.
             * @throws Exception - if database error occurs, or
             * the specified path name is invalid.
             */
            StringListPtr GetDirectories(String Dir);

            /**
             * Adds the specified directory to the database.
             * @param Dir The absolute path name of the directory to add.
             * @throws Exception - if database error occurs, or the
             * specified path is invalid.
             */
            void AddDirectory(String Dir);

            /**
             * Removes the specified directory from the database.
             * @param Dir The absolute path name of the directory to remove.
             * @throws Exception - If the specified path is invalid, or 
             * Force is false and the specified directory is
             * not empty, or if database error occurs.
             */
            void RemoveDirectory(String Dir, bool Force = false);

            /**
             * Determines whether the specified directory exists in the database.
             * @throws Exception - If database error occurs.
             */
            bool DirectoryExist(String Dir);

            /**
             * Gets information about the specified directory.
             * @param Dir The absolute path name of the directory.
             * @throws Exception - if database error occurs, or if
             * the specified directory is not found.
             */
            DbDirectory GetDirectoryInfo(String Dir);

            /**
             * Renames the specified directory.
             * @param Dir The absolute path name of the directory to rename.
             * @param Name The new name for the directory.
             * @throws Exception - In case the given directory does not exists,
             * or the specified name is not a valid name,
             * or if a directory with name equal to the new name already
             * exists, or if database error occurs.
             */
            void RenameDirectory(String Dir, String Name);

            /**
             * Moves the specified directory into the specified location.
             * @param Dir The absolute path name of the directory to move.
             * @param Dst The location where the directory will be moved to.
             * @throws Exception - In case a given directory does not exists,
             * or if a directory with name equal to the directory name already
             * exists in the specified destination directory, or if database error
             * occurs. Error is also thrown when trying to move a directory to a
             * subdirectory of itself.
             */
            void MoveDirectory(String Dir, String Dst);

            /**
             * Changes the description of the specified directory.
             * @throws Exception - if database error occurs, or if
             * the specified directory is not found.
             */
            void SetDirectoryDescription(String Dir, String Desc);

            /**
             * Adds the instruments in the specified file or
             * directory to the specified instruments database directory.
             * @param DbDir The absolute path name of a directory in the
             * instruments database in which only the new instruments
             * (that are not already in the database) will be added.
             * @param FilePath The absolute path name of a file or
             * directory in the file system. In case a directory is
             * supplied, all supported instruments in the specified directory
             * will be added to the instruments database, including the
             * instruments in the subdirectories. The respective subdirectory
             * structure will be recreated in the supplied database directory.
             * @param Index The index of the instrument (in the given
             * instrument file) to add. If -1 is specified, all instruments in
             * the supplied instrument file will be added. Error is thrown if
             * a directory is supplied and Index is not equal to -1.
             * @throws Exception if the operation failed.
             */
            void AddInstruments(String DbDir, String FilePath, int Index = -1);

            /**
             * Adds all supported instruments in the specified directory
             * to the specified instruments database directory. The
             * instruments in the subdirectories will not be processed
             * @param DbDir The absolute path name of a directory in the
             * instruments database in which only the new instruments
             * (that are not already in the database) will be added.
             * @param FsDir The absolute path name of a directory in the file
             * system.
             * @throws Exception if the operation failed.
             */
            void AddInstrumentsNonrecursive(String DbDir, String FsDir);

            /**
             * Adds all supported instruments in the specified file system
             * direcotry to the specified instruments database directory,
             * including the instruments in the subdirectories of the
             * supplied directory.
             * @param DbDir The absolute path name of a directory in the
             * instruments database in which only the new instruments
             * (that are not already in the database) will be added.
             * @param FsDir The absolute path name of an existing
             * directory in the file system.
             * @param Flat If true, the respective subdirectory structure will
             * not be recreated in the instruments database and all instruments
             * will be added directly in the specified database directory.
             * @throws Exception if the operation failed.
             */
            void AddInstrumentsRecursive(String DbDir, String FsDir, bool Flat = false);

            /**
             * Gets the number of instruments in the specified directory.
             * @param Dir The absolute path name of the directory.
             * @throws Exception - if database error occurs, or
             * the specified path name is invalid.
             * @returns The number of instruments in the specified directory
             * or -1 if the directory doesn't exist.
             */
            int GetInstrumentCount(String Dir);

            /**
             * Gets the list of instruments in the specified directory.
             * @param Dir The absolute path name of the directory.
             * @throws Exception - if database error occurs, or
             * the specified path name is invalid.
             */
            StringListPtr GetInstruments(String Dir);

            /**
             * Removes the specified instrument from the database.
             * @param Instr The absolute path name of the instrument to remove.
             * @throws Exception - If the specified instrument does not exist,
             * or database error occurs.
             */
            void RemoveInstrument(String Instr);

            /**
             * Gets information about the specified instrument.
             * @param Instr The absolute path name of the instrument.
             * @throws Exception - if database error occurs, or if
             * the specified instrument is not found.
             */
            DbInstrument GetInstrumentInfo(String Instr);

            /**
             * Renames the specified instrument.
             * @param Instr The absolute path name of the instrument to rename.
             * @param Name The new name for the instrument.
             * @throws Exception - In case the given instrument does not exists,
             * or the specified name is not a valid name, or if an instrument
             * with name equal to the new name already exists, or
             * if database error occurs.
             */
            void RenameInstrument(String Instr, String Name);

            /**
             * Moves the specified instrument into the specified directory.
             * @param Instr The absolute path name of the instrument to move.
             * @param Dst The directory where the instrument will be moved to.
             * @throws Exception - In case the given directory or instrument
             * does not exist, or if an instrument with name equal to the name
             * of the specified instrument already exists in the specified
             * destination directory, or if database error occurs.
             */
            void MoveInstrument(String Instr, String Dst);

            /**
             * Changes the description of the specified instrument.
             * @throws Exception - if database error occurs, or if
             * the specified instrument is not found.
             */
            void SetInstrumentDescription(String Instr, String Desc);
            
            /**
             * Closes the database connection if opened and deletes
             * the InstrumentsDb instance.
             */
            static void Destroy();

            
        private:
            sqlite3* db;
            String DbFile;
            static InstrumentsDb* pInstrumentsDb;
            Mutex DbInstrumentsMutex;
            ListenerList<InstrumentsDb::Listener*> llInstrumentsDbListeners;
            
            InstrumentsDb();
            ~InstrumentsDb();
            
            /**
             * Gets the instruments database. If the database is not
             * opened, a connection to the database is established first.
             * @returns The instruments database.
             * @throws Exception if fail to open the database.
             */
            sqlite3* GetDb();

            /**
             * Gets the number of directories in the directory
             * with ID DirId.
             * @returns The number of directories in the specified directory
             * or -1 if the directory doesn't exist.
             */
            int GetDirectoryCount(int DirId);

            /**
             * Gets a list containing the IDs of all directories in
             * the specified instrument directory.
             * @returns The IDs of all directories in the specified directory.
             * @throws Exception - if database error occurs.
             */
            IntListPtr GetDirectoryIDs(int DirId);

            /**
             * Gets the directory ID.
             * @param Dir The absolute path name of the directory.
             * @returns The directory ID or -1 if the directory is not found.
             * @throws Exception - if database error occurs.
             */
            int GetDirectoryId(String Dir);

            /**
             * Gets the directory ID.
             * @param ParentDirId The ID of the parent directory.
             * @param DirName The directory name.
             * @throws Exception - if database error occurs.
             * @returns The ID of the specified directory
             * or -1 if the directory doesn't exist.
             */
            int GetDirectoryId(int ParentDirId, String DirName);

            /**
             * Removes the specified directory from the database.
             * @param DirId The ID of the directory to remove.
             * @throws Exception - If the specified directory is not empty.
             */
            void RemoveDirectory(int DirId);

            /**
             * Removes all directories in the specified directory.
             * Do NOT call this method before ensuring that all
             * directories in the specified directory are empty.
             * @param DirId The ID of the directory.
             * @throws Exception - if at least one of the directories in the
             * specified directory is not empty or if database error occurs.
             * @see IsDirectoryEmpty
             */
            void RemoveAllDirectories(int DirId);

            /**
             * Determines whether the specified directory is empty.
             * If the directory doesn't exist the return value is false.
             * @throws Exception - if database error occurs.
             */
            bool IsDirectoryEmpty(int DirId);

            /**
             * Removes the content of the specified directory from the database.
             * @param DirId The ID of the directory.
             * @param Level Used to prevent stack overflow, which may occur
             * due to large or infinite recursive loop.
             * @throws Exception - If database error occurs.
             */
            void RemoveDirectoryContent(int DirId, int Level = 0);

            /**
             * Gets the ID of the specified database instrument.
             * @param Instr The absolute path name of the instrument.
             * @returns The instrument ID or -1 if the instrument is not found.
             * @throws Exception - if database error occurs.
             */
            int GetInstrumentId(String Instr);

            /**
             * Gets the ID of the specified database instrument.
             * @param DirId The ID of the directory containing the instrument.
             * @param InstrName The name of the instrument.
             * @returns The instrument ID or -1 if the instrument is not found.
             * @throws Exception - if database error occurs.
             */
            int GetInstrumentId(int DirId, String InstrName);

            /**
             * Removes the specified instrument from the database.
             * @param InstrId The ID of the instrument to remove.
             * @throws Exception - If the specified instrument does not exist.
             */
            void RemoveInstrument(int InstrId);

            /**
             * Removes all instruments in the specified directory.
             * @param DirId The ID of the directory.
             * @throws Exception - if database error occurs.
             */
            void RemoveAllInstruments(int DirId);

            /**
             * Gets the number of instruments in the directory
             * with ID DirId.
             * @returns The number of instruments in the specified directory
             * or -1 if the directory doesn't exist.
             */
            int GetInstrumentCount(int DirId);

            /**
             * Gets a list containing the IDs of all instruments in
             * the specified instrument directory.
             * @returns The IDs of all instruments in the specified directory.
             * @throws Exception - if database error occurs.
             */
            IntListPtr GetInstrumentIDs(int DirId);

            /**
             * Adds the instruments in the specified file
             * to the specified instruments database directory.
             * @param DbDir The absolute path name of a directory in the
             * instruments database in which only the new instruments
             * (that are not already in the database) will be added.
             * @param File The absolute path name of a file in the file system.
             * @param Index The index of the instrument (in the given
             * instrument file) to add. If -1 is specified, all instruments in
             * the supplied instrument file will be added.
             * @throws Exception if the operation failed.
             */
            void AddInstrumentsFromFile(String DbDir, String File, int Index = -1);

            /**
             * Adds the specified GIG instrument(s) to the specified location
             * in the instruments database.
             * @param DbDir The instruments database directory
             * in which the instrument will be added.
             * @param File The absolute path name of the instrument file.
             * @param Index The index of the instrument (in the given
             * instrument file) to add. If -1 is specified, all instruments in
             * the supplied instrument file will be added.
             * @throws Exception if the operation failed.
             */
            void AddGigInstruments(String DbDir, String File, int Index = -1);

            /**
             * Adds the specified GIG instrument.
             * @throws Exception if the operation failed.
             */
            void AddGigInstrument(sqlite3_stmt* pStmt, String DbDir, int DirId, String File, ::gig::Instrument* pInstrument, int Index);

            /**
             * Used to execute SQL commands which return empty result set.
             */
            void ExecSql(String Sql);

            /**
             * Used to execute SQL commands which return empty result set.
             */
            void ExecSql(String Sql, String Param);

            /**
             * Used to execute SQL commands which returns integer.
             */
            int ExecSqlInt(String Sql);

            /**
             * Used to execute SQL commands which returns integer.
             */
            int ExecSqlInt(String Sql, String Param);

            /**
             * Used to execute SQL commands which returns integer.
             */
            String ExecSqlString(String Sql);

            /**
             * Used to execute SQL commands which returns integer list.
             */
            IntListPtr ExecSqlIntList(String Sql);

            /**
             * Used to execute SQL commands which returns string list.
             */
            StringListPtr ExecSqlStringList(String Sql);
            
            /**
             * Binds the specified text parameter.
             */
            void BindTextParam(sqlite3_stmt* pStmt, int Index, String Text);
            
            /**
             * Binds the specified integer parameter.
             */
            void BindIntParam(sqlite3_stmt* pStmt, int Index, int Param);

            /**
             * Checks whether an instrument with the specified name already
             * exists in the specified directory and if so a new unique name
             * is returnded. The new name is generated by adding the suffix
             * [<nr>] to the end of the name , where <nr> is a number between
             * 2 and 1000.
             * throws Exception if cannot find an unique name. This is done
             * because it is highly unlikely that this can happen, so it is
             * supposed that this is due to a bug or an infinite loop.
             */
            String GetUniqueInstrumentName(int DirId, String Name);

            void FireDirectoryCountChanged(String Dir);
            void FireDirectoryInfoChanged(String Dir);
            void FireDirectoryNameChanged(String Dir, String NewName);
            void FireInstrumentCountChanged(String Dir);
            void FireInstrumentInfoChanged(String Instr);
            void FireInstrumentNameChanged(String Instr, String NewName);

            /**
             * Strips the non-directory suffix from the file name. If the string
             * ends with `/' only the last character is removed. If the string
             * doesn't starts with `/' charater, an empty string is returned.
             */
            static String GetDirectoryPath(String File);

            /**
             * Returns the file name extracted from the specified absolute path
             * name. If the string doesn't starts with `/' or ends with `/',
             * an empty string is returned.
             */
            static String GetFileName(String Path);

            /**
             * Strips the last directory from the specified path name. If the 
             * string doesn't starts with `/'  an empty string is returned.
             */
            static String GetParentDirectory(String Dir);

            /**
             * Checks whether the specified path is valid.
             * @throws Exception - if the specified path is invalid.
             */
            static void CheckPathName(String Path);

            /**
             * Checks whether the specified file name is valid.
             * @throws Exception - if the specified file name is invalid.
             */
            static void CheckFileName(String File);
    };
    
    /**
     * This class is used for recursive
     */
    class DirectoryScanner {
        public:
            /**
             * Recursively scans all subdirectories of the specified
             * directory and adds the supported instruments to the database.
             * @throws Exception - if the specified directories are invalid.
             */
            static void Scan(String DbDir, String FsDir, bool Flat);

        private:
            static String DbDir;
            static String FsDir;
            static bool Flat;
            static int FtwCallback(const char* fpath, const struct stat* sb, int typeflag);
    };

} // namespace LinuxSampler

#endif // __LS_INSTRUMENTSDB_H__

#endif // HAVE_SQLITE3
