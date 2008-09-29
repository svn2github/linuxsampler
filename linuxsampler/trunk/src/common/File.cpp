/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2008 Grigor Iliev, Benno Senoner                        *
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

#include "File.h"

#include <cstring>
#include <errno.h>
#include <sstream>

#include "Exception.h"
#include "global_private.h"

#if WIN32

#else
#include <dirent.h>
#include <ftw.h>
#endif

namespace LinuxSampler {

#if WIN32
    char File::DirSeparator = '\\';
#else
    char File::DirSeparator = '/';
#endif

    Mutex File::DirectoryWalkerMutex = Mutex();
    std::vector<File::DirectoryWalker*> File::DirectoryWalkers;
    std::string File::DWErrorMsg;

    File::File(std::string Path) {
        #if WIN32
        
        #else
            bExist = !stat(Path.c_str(), &Status);
            if(!bExist) ErrorMsg = strerror(errno);
        #endif
    }
    
    bool File::Exist() {
        return bExist;
    }
    
    std::string File::GetErrorMsg() {
        return ErrorMsg;
    }
    
    bool File::IsFile() {
        if(!Exist()) return false;
        
        #if WIN32
        
        #else
            return S_ISREG(Status.st_mode);
        #endif
    }
    
    bool File::IsDirectory() {
        if(!Exist()) return false;
        
        #if WIN32
        
        #else
            return S_ISDIR(Status.st_mode);
        #endif
    }
    
    unsigned long File::GetSize() {
        if(!Exist()) return 0;
        
        #if WIN32
        
        #else
            return Status.st_size;
        #endif       
    }
    
    FileListPtr File::GetFiles(std::string Dir) {
        #if WIN32
        
        #else
            DIR* pDir = opendir(Dir.c_str());
            if (pDir == NULL) {
                std::stringstream ss;
                ss << "Failed to list the directory content of `";
                ss << Dir << "`: " << strerror(errno);
                throw Exception(ss.str());
            }
            
            FileListPtr fileList(new std::vector<std::string>);
            
            struct dirent* pEnt = readdir(pDir);
            while (pEnt != NULL) {
                if (pEnt->d_type != DT_REG) {
                    pEnt = readdir(pDir);
                    continue;
                }

                fileList->push_back(std::string(pEnt->d_name));
                pEnt = readdir(pDir);
            }
            
            if (closedir(pDir)) {
                std::stringstream ss;
                ss << "Failed to close directory `" << Dir << "`: ";
                ss << strerror(errno);
                throw Exception(ss.str());
            }
            
            return fileList;
        #endif
    }
    
    void File::WalkDirectoryTree(std::string Dir, DirectoryWalker* pWalker) {
        dmsg(2,("File: WalkDirectoryTree(Dir=%s)\n", Dir.c_str()));
        File f = File(Dir);
        if(!f.Exist()) throw Exception("Fail to stat `" + Dir + "`: " + f.GetErrorMsg());
        if(!f.IsDirectory()) throw Exception("The specified path is not a directory: " + Dir);
        
        DirectoryWalkerMutex.Lock();
        DirectoryWalkers.push_back(pWalker);
        DWErrorMsg = "Failed to process directory tree: " + Dir;
        
        #if WIN32
        
        #else
            if (ftw(Dir.c_str(), FtwCallback, 10)) {
                DirectoryWalkers.pop_back();
                if (DirectoryWalkers.size() == 0) DirectoryWalkerMutex.Unlock();
                throw Exception(DWErrorMsg);
            }
        #endif
        DirectoryWalkers.pop_back();
        if (DirectoryWalkers.size() == 0) DirectoryWalkerMutex.Unlock();
    }

#if WIN32

#else
    int File::FtwCallback(const char* fpath, const struct stat* sb, int typeflag) {
        dmsg(2,("File: FtwCallback(fpath=%s)\n", fpath));
        try {
            if (typeflag == FTW_D) DirectoryWalkers.back()->DirectoryEntry(std::string(fpath));
            else if (typeflag == FTW_F) DirectoryWalkers.back()->FileEntry(std::string(fpath));
        } catch(Exception e) {
            e.PrintMessage();
            DWErrorMsg = e.Message();
            return -1;
        }
        
        return 0;
    };
#endif
	std::string File::basename(std::string path) {
		size_t begin = 0;
		size_t end = path.length();
		
		for(size_t i=0; i<path.length(); ++i){
			if(path[i] == File::DirSeparator) begin = i+1;
		}
		return path.substr(begin, end).c_str();
	}
	
	std::string File::basename(std::string path, std::string sep) {
		std::string tmp = File::basename(path);
		if(sep.empty())
			sep = ".";
		size_t begin = 0;
		size_t end = tmp.length();
		size_t lastdot = tmp.find_last_of(sep)-1;
		if(lastdot > 0)
			end = lastdot;
		return tmp.substr(begin, end).c_str();
	}
}
