/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003 by Christian Schoenebeck                           *
 *                         <cuse@users.sourceforge.net>                    *
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
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/
 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "RIFF.h"

using namespace std;

void PrintUsage();
void PrintChunkList(RIFF::List* list, bool PrintSize);

int main(int argc, char *argv[])
{
    int  FileArgIndex = 1;
    bool bPrintSize   = false;

    if (argc <= 1) {
        PrintUsage();
        return EXIT_FAILURE;
    }
    if (argc >= 3) {
        if (argv[1][0] == '-') {
            switch (argv[1][1]) {
                case 's':
                    bPrintSize = true;
                    break;
                default:
                    PrintUsage();
                    return EXIT_FAILURE;
            }
            FileArgIndex++;
        }
    }
    FILE* hFile = fopen(argv[FileArgIndex], "r");
    if (!hFile) {
        cout << "Invalid file argument!" << endl;
        return EXIT_FAILURE;
    }
    fclose(hFile);
    try {
        RIFF::File* riff = new RIFF::File(argv[FileArgIndex]);
        cout << "RIFF(" << riff->GetListTypeString() << ")->";
        if (bPrintSize) cout << " (" << riff->GetSize() << " Bytes)";
        cout << endl;
        PrintChunkList(riff, bPrintSize);
        delete riff;
    }
    catch (RIFF::Exception e) {
        e.PrintMessage();
        return EXIT_FAILURE;
    }
    catch (...) {
        cout << "Unknown exception while trying to parse file." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void PrintChunkList(RIFF::List* list, bool PrintSize) {
    RIFF::Chunk* ck = list->GetFirstSubChunk();
    while (ck != NULL) {
        RIFF::Chunk* ckParent = ck;
        while (ckParent->GetParent() != NULL) {
            cout << "            "; // e.g. 'LIST(INFO)->'
            ckParent = ckParent->GetParent();
        }
        cout << ck->GetChunkIDString();
        switch (ck->GetChunkID()) {
            case CHUNK_ID_LIST: case CHUNK_ID_RIFF:
              {
                RIFF::List* l = (RIFF::List*) ck;
                cout << "(" << l->GetListTypeString() << ")->";
                if (PrintSize) cout << " (" << l->GetSize() << " Bytes)";
                cout << endl;
                PrintChunkList(l, PrintSize);
                break;
              }
            default:
                cout << ";";
                if (PrintSize) cout << " (" << ck->GetSize() << " Bytes)";
                cout << endl;
        }
        ck = list->GetNextSubChunk();
    }
}

void PrintUsage() {
    cout << "rifftree - parses an arbitrary RIFF file and prints out the RIFF tree structure." << endl;
    cout << endl;
    cout << "Usage: rifftree [-s] FILE" << endl;
    cout << endl;
    cout << "	-s  Print the size of each chunk." << endl;
    cout << endl;
}
