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

#ifndef LS_PATH_H
#define LS_PATH_H

#include <vector>
#include <string>

namespace LinuxSampler {

/** @brief Portable Path Abstraction
 *
 * Correct path and file names are dependent to the underlying OS and FS.
 * Especially the set of forbidden characters (and their encodings / escape
 * sequences) in path and file names differ on the various systems. This
 * class is meant as a portable wrapper to circumvent these problems by
 * storing the file names in its raw, human readable (intended) form and
 * provides OS specific methods like @c toPosix() for converting the path into
 * the correct encoding, as expected by the respective system.
 *
 * This class is currently only used internally by the LSCP parser. A lot
 * generalization work would have to be done to use this class as a overall
 * replacement for all @c char* / @c std::string file name arguments in the
 * sampler or even its C++ API. Probably we'll use something like
 * @c boost::filesystem::path instead of this class in future.
 */
class Path {
public:
    /**
     * Concatenate exactly one path node or filename to the end of this Path
     * object. This can be used to build up a full qualified path, directory
     * by directory.
     *
     * @param Name - name of the path node's name or filename in it's raw,
     *               human readable/expected form
     */
    void appendNode(std::string Name);

    /**
     * Convert this Path into the correct encoding as expected by POSIX
     * compliant system calls.
     */
    std::string toPosix();

    /**
     * Convert this Path into the correct encoding as expected
     * by the instruments database implementation.
     */
    std::string toDbPath();

    /**
     * Concatenate two paths.
     */
    Path operator+(const Path& p);

    /**
     * Concatenate two paths.
     */
    Path operator+(const Path* p);

private:
    std::vector<std::string> elements; ///< stores the path names raw = unencoded, each element is one node of the path
};

} // namespace LinuxSampler

#endif // LS_PATH_H
