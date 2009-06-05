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

/*
dirent.c
POSIX WIN32 Directory Browsing parts
Copyright (C) 2005 OpenAsthra
blogs.openasthra AT gmail.com
modifications copyright 2009 by Benno Senoner
Licence: LGPL
*/

#include "dirent.h"
#include <errno.h>
#include <io.h> 
#include <stdlib.h>
#include <string.h>

struct DIR
{
  long handle; 
  long int pos;
  struct _finddata_t  info;
  struct dirent d_ent; 
};

//aux functions
static int StripRegEx(char *name);
static int PreOrderTraversal(DIR *dirp, int (*fn) (const char *fpath, const struct stat *sb, int typeflag));
static int CallFn(int (*fn) (const char *fpath, const struct stat *sb, int typeflag), char *dirpath, DIR *dirp);


//posix directory browsing API implementation

DIR *opendir(const char *name)
{
  DIR *dir = NULL;
  const char *all;
  long len;
  
  if((NULL == name) || ('\0' == *name))
  {
    errno = EINVAL;
    return dir;
  }
  
  len = strlen(name);
  all = strchr("/\\", name[len - 1]) ? "*" : "/*";
    
  len += strlen(all) + 1;

  dir = (DIR *) malloc((len*sizeof(char)) + sizeof(*dir));
  if(NULL == dir)
  {
    errno = ENOMEM;
    return NULL;
  }
    
  dir->d_ent.d_namlen = len;
  dir->pos = 0;
  strcpy(dir->d_ent.d_name, name);
  strcat(dir->d_ent.d_name, all);
  dir->handle = (long) _findfirst(dir->d_ent.d_name, &dir->info);
  if(dir->handle == -1)
  {
    free(dir);
    dir = NULL;
  }

  return dir;
}

int closedir(DIR *dir)
{
  int result = -1;

  if(dir)
  {
    if(dir->handle != -1)
    {
      result = _findclose(dir->handle);
    }
    free(dir);
  }

  if(result == -1)
  {
    errno = EBADF;
  }

  return result;
}

struct dirent *readdir(DIR *dir)
{
  struct dirent *result = 0;

  if(dir && dir->handle != -1)
  {
    if(_findnext(dir->handle, &dir->info) != -1)
    {
      result = &dir->d_ent;
      strcpy(result->d_name, dir->info.name);
	  result->d_type = DT_REG;
	  if(dir->info.attrib & _A_SUBDIR) result->d_type = DT_DIR;
      dir->pos ++;
    }
  }
  else
  {
    errno = EBADF;
  }

  return result;
}

void rewinddir(DIR *dir)
{
    if(dir && dir->handle != -1)
    {
        _findclose(dir->handle);
        dir->handle = (long) _findfirst(dir->d_ent.d_name, &dir->info);
        dir->pos = 0;
    }
    else
    {
        errno = EBADF;
    }
}

int	stat(const char *path, struct stat *buf)
{
	struct _finddata_t  info;
	long handle;
	mode_t mode = 0;

	if(!buf | !path)
		return -1;

	handle = _findfirst(path, &info);
	if(handle == -1) 
	    return -1;
	_findclose(handle);
	
	
	buf->st_size = info.size;
	buf->st_atime = info.time_access;
	buf->st_ctime = info.time_create;

		
	/* | dir/regular | systemfile | readonly | write |*/
	
    mode = S_IFREG;
	if(info.attrib & _A_SUBDIR) mode = S_IFDIR;
	buf->st_mode = mode;

	return 0;
}

int dirfd(DIR *dirp)
{
  if (NULL == dirp)
  {
    return -1;
  }

  return dirp->handle;
}

void seekdir (DIR *dirp, long int pos)
{
  long int i;

  if (NULL == dirp)
  {
    return;
  }

  if (pos < 0)
  {
    pos = dirp->pos + pos;
    _findclose(dirp->handle);
    dirp->handle = (long) _findfirst(dirp->d_ent.d_name, &dirp->info);
  }

  for (i=0; i<pos; i++)
  {
    if(_findnext(dirp->handle, &dirp->info) != -1)
    {
      dirp->pos ++;
    }
    else
    {
      break;
    }
  }

}


long int telldir (DIR *dirp)
{
  if (NULL == dirp)
  {
    return -1;
  }

  return dirp->pos;

}


int scandir(const char *dir, struct dirent ***namelist,
      int (*filter)(const struct dirent *),
      int (*compar)(const struct dirent **, const struct dirent **))
{
  struct dirent *result = 0;
   struct dirent **namlist;
  int namelistlen = 0;
  int num_enrties= 0;

  DIR *dirp = opendir(dir);

  if (NULL == dirp)
  {
    return -1;
  }

  if(dirp && dirp->handle != -1)
  {
    while(_findnext(dirp->handle, &dirp->info) != -1)
    {
      num_enrties++;
    }
  }

  rewinddir(dirp);

  namlist = (struct dirent **) malloc(num_enrties * sizeof(struct dirent *));

  if (NULL == namlist)
  {
    closedir(dirp);
    return namelistlen;
  }

  if(dirp && dirp->handle != -1)
  {
    while(_findnext(dirp->handle, &dirp->info) != -1)
    {
      result = (struct dirent *) malloc(sizeof(struct dirent) + strlen(dirp->info.name) + 1);
      strcpy(result->d_name, dirp->info.name);
	  result->d_type = DT_REG;
	  if(dirp->info.attrib & _A_SUBDIR) result->d_type = DT_DIR;
      if (filter)
      {
        if (filter(result))
        {
          namlist[namelistlen] = result;
          namelistlen++;
        }
      }
      else
      {
        namlist[namelistlen] = result;
        namelistlen++;
      }
    }
  }

  //qdirsort(namlist, namelistlen, compar); //todo

  *namelist = namlist;

  closedir(dirp);

  return namelistlen;
}

int ftw(const char *dirpath,
        int (*fn) (const char *fpath, const struct stat *sb,
        int typeflag),
        int nopenfd)
{
  struct dirent *result = 0;
  struct dirent **namlist;
  int namelistlen = 0;
  int num_enrties= 0;
  struct stat sb;
  int typeflag = 0;

  DIR *dirp = opendir(dirpath);

  if (NULL == dirp)
  {
    return -1;
  }


  if (CallFn(fn, (char *)dirpath, dirp))
  {
    closedir(dirp);
    return 0;
  }
 
  if(dirp && (dirp->handle != -1))
  {
    while(_findnext(dirp->handle, &dirp->info) != -1)
    {
      if ((dirp->info.attrib & _A_SUBDIR) && 
          (strcmp(dirp->info.name, ".")) && (strcmp(dirp->info.name, "..")))
      {
        if (PreOrderTraversal(dirp, fn)>0)
        {
          break;
        }
      }
      else
      {
        if (CallFn(fn, dirp->info.name, dirp))
        {
          break;
        }
      }
    }
  }

  closedir(dirp);
  return 0;

}

//aux functions
int StripRegEx(char *name)
{
  char *t = strstr(name, "/*");
  if (t)
  {
    *t='\0';
  }
  else
  {
    t = strstr(name, "\\*");
    if (t)
    {
      *t='\0';
    }
  }

  return 0;
}

int CallFn(int (*fn) (const char *fpath, const struct stat *sb,
        int typeflag), char *dirpath, DIR *dirp)
{
  struct stat sb;
  int typeflag = 0;

  if (fn)
  {
    stat(dirpath, &sb);
    if (dirp->info.attrib & _A_SUBDIR)
    {
      typeflag = FTW_D;
    }
    else
    {
      typeflag = FTW_F;
    }
    return fn(dirpath, &sb, typeflag);
  }
  return 0;
}


int PreOrderTraversal(DIR *dirp, int (*fn) (const char *fpath, const struct stat *sb, int typeflag))
{
  DIR *dirp2;
  struct stat sb;
  int typeflag = 0;
  char *tmpdirnam;
    
  StripRegEx(dirp->d_ent.d_name);

  tmpdirnam = (char *)malloc(strlen(dirp->d_ent.d_name)+strlen(dirp->info.name)+2);
  if (!tmpdirnam)
  {
    return -1;
  }

  strcpy(tmpdirnam, dirp->d_ent.d_name);
  strcat(tmpdirnam, "/");
  strcat(tmpdirnam, dirp->info.name);

  dirp2 = opendir(tmpdirnam);

  if (NULL == dirp2)
  {
    free(tmpdirnam);
    return -1;
  }

  if (CallFn(fn, tmpdirnam, dirp2))
  {
    free(tmpdirnam);
    closedir(dirp2);
    return 1;
  }

  while(_findnext(dirp2->handle, &dirp2->info) != -1)
    {
      if (strcmp(dirp2->info.name, ".."))
      {
        if ((dirp2->info.attrib & _A_SUBDIR) && strcmp(dirp2->info.name, ".") && strcmp(dirp2->info.name, ".."))
        {
          if (PreOrderTraversal(dirp2, fn))
          {
            free(tmpdirnam);
            closedir(dirp2);
            return 1;
          }
        }
        else
        {
          if (CallFn(fn, dirp2->info.name, dirp2))
          {
            free(tmpdirnam);
            closedir(dirp2);
            return 1;
          }
        }
      } /*if (strcmp(dirp2->info.name, ".."))*/
    }

   free(tmpdirnam);
   closedir(dirp2);
   return 0;
  
}

/* end of POSIX WIN32 Directory Browsing dirent.c implementation */


#else
#include <dirent.h>
#include <ftw.h>
#endif

namespace LinuxSampler {

    char File::DirSeparator = '/';

    Mutex File::DirectoryWalkerMutex;
    std::vector<File::DirectoryWalker*> File::DirectoryWalkers;
    std::string File::DWErrorMsg;

    File::File(std::string Path) {
            bExist = !stat(Path.c_str(), &Status);
            if(!bExist) ErrorMsg = strerror(errno);
    }
    
    bool File::Exist() {
        return bExist;
    }
    
    std::string File::GetErrorMsg() {
        return ErrorMsg;
    }
    
    bool File::IsFile() {
        if(!Exist()) return false;
        
            return S_ISREG(Status.st_mode);
    }
    
    bool File::IsDirectory() {
        if(!Exist()) return false;
        
            return S_ISDIR(Status.st_mode);
    }
    
    unsigned long File::GetSize() {
        if(!Exist()) return 0;
        
            return Status.st_size;      
    }
    
    FileListPtr File::GetFiles(std::string Dir) {
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
    }
    
    void File::WalkDirectoryTree(std::string Dir, DirectoryWalker* pWalker) {
        dmsg(2,("File: WalkDirectoryTree(Dir=%s)\n", Dir.c_str()));
        File f = File(Dir);
        if(!f.Exist()) throw Exception("Fail to stat `" + Dir + "`: " + f.GetErrorMsg());
        if(!f.IsDirectory()) throw Exception("The specified path is not a directory: " + Dir);
        
        DirectoryWalkerMutex.Lock();
        DirectoryWalkers.push_back(pWalker);
        DWErrorMsg = "Failed to process directory tree: " + Dir;
        
            if (ftw(Dir.c_str(), FtwCallback, 10)) {
                DirectoryWalkers.pop_back();
                if (DirectoryWalkers.size() == 0) DirectoryWalkerMutex.Unlock();
                throw Exception(DWErrorMsg);
            }
        DirectoryWalkers.pop_back();
        if (DirectoryWalkers.size() == 0) DirectoryWalkerMutex.Unlock();
    }


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
}
