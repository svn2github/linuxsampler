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

#ifndef LS_FILE_H
#define LS_FILE_H

#include <memory>
#include <string>
#include <vector>

#include "Mutex.h"

#if WIN32

/*
dirent.h
POSIX WIN32 Directory Browsing parts
Copyright (C) 2005 OpenAsthra
blogs.openasthra AT gmail.com
modifications copyright 2009 by Benno Senoner
Licence: LGPL
*/

#ifndef _DIRENT_H_
#define _DIRENT_H_

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct DIR DIR;

struct dirent{
  long		d_ino;
  long		d_off;
  unsigned short	d_reclen;
  unsigned char d_type;
  unsigned short  d_namlen; 
  char		d_name[1];
};

DIR           *opendir(const char *);
int           closedir(DIR *);
struct dirent *readdir(DIR *);
void          rewinddir(DIR *);

void seekdir (DIR *dirp, long int pos);
long int telldir (DIR *dirp);

int scandir(const char *dir, struct dirent ***namelist,
      int (*filter)(const struct dirent *),
      int (*compar)(const struct dirent **, const struct dirent **));

int ftw(const char *dirpath,
        int (*fn) (const char *fpath, const struct stat *sb,
        int typeflag),
        int nopenfd);


int dirfd(DIR *dirp);

#define S_IFMT        0170000
#define S_IFDIR       0040000
#define S_IFREG       0100000

#define __S_ISTYPE(mode, mask)  (((mode) & S_IFMT) == (mask))
#define S_ISDIR(mode)    __S_ISTYPE((mode), S_IFDIR)
#define S_ISREG(mode)    __S_ISTYPE((mode), S_IFREG)

#define DT_DIR  4
#define DT_REG  8

int	stat(const char *path, struct stat *buf);

#define FTW_F 0x01
#define FTW_D 0x02
#define FTW_DNR 0x03
#define FTW_NS 0x04
#define FTW_SL 0x05

#ifdef __cplusplus
}
#endif

#endif
/* end of POSIX WIN32 Directory Browsing implementation */ 

#else
#include <sys/stat.h>
#endif

namespace LinuxSampler {

    typedef std::auto_ptr<std::vector<std::string> > FileListPtr;

    class File {
        public:
            class DirectoryWalker {
                public:
                    virtual void DirectoryEntry(std::string Path) = 0;
                    virtual void FileEntry(std::string Path) = 0;
            };
            
            File(std::string FileName);
            
            /**
             * Tests whether the file exists.
             */
            bool Exist();

            /**
             * Provides appropriate error message if failed to retrieve
             * information about the specified file, in which case Exist() returns false.
             */
            std::string GetErrorMsg();

            /**
             * Tests whether it's a regular file.
             */
            bool IsFile();

            /**
             * Tests whether it's a directory.
             */
            bool IsDirectory();
            
            /**
             * Returns the size of the file in bytes.
             */
            unsigned long GetSize();

            /**
             * Returns the names of the regular files in the specified directory.
             * @throws Exception If failed to list the directory content.
             */
            static FileListPtr GetFiles(std::string Dir);
            
            /**
             * Walks through the directory tree that is located under the
             * directory <b>Dir</b>, and calls <b>pWalker->DirectoryEntry()</b>
             * once for each directory in the tree and <b>pWalker->FileEntry()</b>
             * once for each file in the tree. Note that this method can be 
             * recursively invoked from within the callback functions
             * <b>pWalker->DirectoryEntry()</b> and <b>pWalker->FileEntry()</b>.
             * @throws Exception If the specified path is missing or is not a directory.
             * Exception is also thrown, and the directory tree walk is stopped,
             * if <b>pWalker->DirectoryEntry()</b> or <b>pWalker->FileEntry()</b>
             * throws Exception.
             */
            static void WalkDirectoryTree(std::string Dir, DirectoryWalker* pWalker);

            static char DirSeparator;

        private:
            bool bExist;
            std::string ErrorMsg;
            static Mutex DirectoryWalkerMutex;
            static std::vector<DirectoryWalker*> DirectoryWalkers;
            static std::string DWErrorMsg;

            struct stat Status;
            static int FtwCallback(const char* fpath, const struct stat* sb, int typeflag);
    };
}

#endif
