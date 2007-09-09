/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2007 Christian Schoenebeck                              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

#include "Path.h"

namespace LinuxSampler {

void Path::appendNode(std::string Name) {
    if (!Name.size()) return;
    elements.push_back(Name);
}

std::string Path::toPosix() {
    // POSIX paths consist of forward slash separators and requires forward
    // slashes in path and file names to be encoded as "%2f", the file names
    // "." and ".." have special meanings
    // (see http://www.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap03.html#tag_03_169
    // and http://www.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap03.html#tag_03_266 )
    std::string result;
    for (int iElement = 0; iElement < elements.size(); iElement++) {
        // encode percent characters
        std::string e = elements[iElement];
        for (
            int pos = e.find("%"); pos != std::string::npos;
            pos = e.find("%", pos+2)
        ) e.replace(pos/*offset*/, 1/*length*/, "%%"/*by*/);
        // encode forward slashes
        for (
            int pos = e.find("/"); pos != std::string::npos;
            pos = e.find("/", pos+3)
        ) e.replace(pos/*offset*/, 1/*length*/, "%2f"/*by*/);
        // append encoded node to full encoded path
        result += "/" + e;
    }
    if (!result.size()) result = "/";
    return result;
}

Path Path::operator+(const Path& p) {
    Path result = *this;
    for (int i = 0; i < p.elements.size(); i++)
        result.elements.push_back(p.elements[i]);
    return result;
}

Path Path::operator+(const Path* p) {
    return *this + *p;
}

} // namespace LinuxSampler
