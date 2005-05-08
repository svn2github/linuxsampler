/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003-2005 by Christian Schoenebeck                      *
 *                              <cuse@users.sourceforge.net>               *
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
#if 1
#include "RIFF.h"

namespace RIFF {

// *************** Chunk **************
// *

    Chunk::Chunk() {
        #if DEBUG
        std::cout << "Chunk::Chunk()" << std::endl;
        #endif // DEBUG
        ulPos      = 0;
        pParent    = NULL;
        pChunkData = NULL;
    }

    #if POSIX
    Chunk::Chunk(int hFile, unsigned long StartPos, bool EndianNative, List* Parent) {
    #else
    Chunk::Chunk(FILE* hFile, unsigned long StartPos, bool EndianNative, List* Parent) {
    #endif // POSIX
        #if DEBUG
        std::cout << "Chunk::Chunk(FILE,ulong,bool,List*),StartPos=" << StartPos << std::endl;
        #endif // DEBUG
        Chunk::hFile  = hFile;
        ulStartPos    = StartPos + CHUNK_HEADER_SIZE;
        bEndianNative = EndianNative;
        pParent       = Parent;
        ulPos         = 0;
        pChunkData    = NULL;
        ReadHeader(StartPos);
    }

    Chunk::~Chunk() {
        if (pChunkData) delete[] pChunkData;
    }

    void Chunk::ReadHeader(unsigned long fPos) {
        #if DEBUG
        std::cout << "Chunk::Readheader(" << fPos << ") ";
        #endif // DEBUG
        #if POSIX
        if (lseek(hFile, fPos, SEEK_SET) != -1) {
            read(hFile, &ChunkID, 4);
            read(hFile, &ChunkSize, 4);
        #else
        if (!fseek(hFile, fPos, SEEK_SET)) {
            fread(&ChunkID, 4, 1, hFile);
            fread(&ChunkSize, 4, 1, hFile);
        #endif // POSIX
            #if WORDS_BIGENDIAN
            if (ChunkID == CHUNK_ID_RIFF) {
                bEndianNative = false;
            }
            #else // little endian
            if (ChunkID == CHUNK_ID_RIFX) {
                bEndianNative = false;
                ChunkID = CHUNK_ID_RIFF;
            }
            #endif // WORDS_BIGENDIAN
            if (!bEndianNative) {
                //swapBytes_32(&ChunkID);
                swapBytes_32(&ChunkSize);
            }
            #if DEBUG
            std::cout << "ckID=" << convertToString(ChunkID) << " ";
            std::cout << "ckSize=" << ChunkSize << " ";
            std::cout << "bEndianNative=" << bEndianNative << std::endl;
            #endif // DEBUG
        }
    }

    /**
     *  Returns the String representation of the chunk's ID (e.g. "RIFF",
     *  "LIST").
     */
    String Chunk::GetChunkIDString() {
        return convertToString(ChunkID);
    }

    /**
     *  Sets the position within the chunk body, thus within the data portion
     *  of the chunk (in bytes).
     *
     *  @param Where  - position offset (in bytes)
     *  @param Whence - optional: defines to what <i>\a Where</i> relates to,
     *                  if omitted \a Where relates to beginning of the chunk
     *                  data
     */
    unsigned long Chunk::SetPos(unsigned long Where, stream_whence_t Whence) {
     #if DEBUG
     std::cout << "Chunk::SetPos(ulong)" << std::endl;
     #endif // DEBUG
        switch (Whence) {
            case stream_curpos:
                ulPos += Where;
                break;
            case stream_end:
                ulPos = ChunkSize - 1 - Where;
                break;
            case stream_backward:
                ulPos -= Where;
                break;
            case stream_start: default:
                ulPos = Where;
                break;
        }
        if (ulPos > ChunkSize) ulPos = ChunkSize;
        return ulPos;
    }

    /**
     *  Returns the number of bytes left to read in the chunk body.
     *  When reading data from the chunk using the Read*() Methods, the
     *  position within the chunk data (that is the chunk body) will be
     *  incremented by the number of read bytes and RemainingBytes() returns
     *  how much data is left to read from the current position to the end
     *  of the chunk data.
     *
     *  @returns  number of bytes left to read
     */
    unsigned long Chunk::RemainingBytes() {
       #if DEBUG
       std::cout << "Chunk::Remainingbytes()=" << ChunkSize - ulPos << std::endl;
       #endif // DEBUG
        return ChunkSize - ulPos;
    }

    /**
     *  Returns the current state of the chunk object.
     *  Following values are possible:
     *  - RIFF::stream_ready :
     *    chunk data can be read (this is the usual case)
     *  - RIFF::stream_closed :
     *    the data stream was closed somehow, no more reading possible
     *  - RIFF::stream_end_reached :
     *    alreaady reached the end of the chunk data, no more reading
     *    possible without SetPos()
     */
    stream_state_t Chunk::GetState() {
      #if DEBUG
      std::cout << "Chunk::GetState()" << std::endl;
      #endif // DEBUG
        #if POSIX
        if (hFile == 0)        return stream_closed;
        #else
        if (hFile == NULL)     return stream_closed;
        #endif // POSIX
        if (ulPos < ChunkSize) return stream_ready;
        else                   return stream_end_reached;
    }

    /**
     *  Reads \a WordCount number of data words with given \a WordSize and
     *  copies it into a buffer pointed by \a pData. The buffer has to be
     *  allocated and be sure to provide the correct \a WordSize, as this
     *  will be important and taken into account for eventual endian
     *  correction (swapping of bytes due to different native byte order of
     *  a system). The position within the chunk will automatically be
     *  incremented.
     *
     *  @param pData      destination buffer
     *  @param WordCount  number of data words to read
     *  @param WordSize   size of each data word to read
     *  @returns          number of successfully read data words or 0 if end
     *                    of file reached or error occured
     */
    unsigned long Chunk::Read(void* pData, unsigned long WordCount, unsigned long WordSize) {
       #if DEBUG
       std::cout << "Chunk::Read(void*,ulong,ulong)" << std::endl;
       #endif // DEBUG
        if (ulPos >= ChunkSize) return 0;
        if (ulPos + WordCount * WordSize >= ChunkSize) WordCount = (ChunkSize - ulPos) / WordSize;
        #if POSIX
        if (lseek(hFile, ulStartPos + ulPos, SEEK_SET) < 0) return 0;
        unsigned long readWords = read(hFile, pData, WordCount * WordSize);
        if (readWords < 1) return 0;
        readWords /= WordSize;
        #else // standard C functions
        if (fseek(hFile, ulStartPos + ulPos, SEEK_SET)) return 0;
        unsigned long readWords = fread(pData, WordSize, WordCount, hFile);
        #endif // POSIX
        if (!bEndianNative && WordSize != 1) {
            switch (WordSize) {
                case 2:
                    for (unsigned long iWord = 0; iWord < readWords; iWord++)
                        swapBytes_16((uint16_t*) pData + iWord);
                    break;
                case 4:
                    for (unsigned long iWord = 0; iWord < readWords; iWord++)
                        swapBytes_32((uint32_t*) pData + iWord);
                    break;
                default:
                    for (unsigned long iWord = 0; iWord < readWords; iWord++)
                        swapBytes((uint8_t*) pData + iWord * WordSize, WordSize);
                    break;
            }
        }
        SetPos(readWords * WordSize, stream_curpos);
        return readWords;
    }

    /** Just an internal wrapper for the main <i>Read()</i> method with additional Exception throwing on errors. */
    unsigned long Chunk::ReadSceptical(void* pData, unsigned long WordCount, unsigned long WordSize) {
        unsigned long readWords = Read(pData, WordCount, WordSize);
        if (readWords != WordCount) throw RIFF::Exception("End of chunk data reached.");
        return readWords;
    }

    /**
     * Reads \a WordCount number of 8 Bit signed integer words and copies it
     * into the buffer pointed by \a pData. The buffer has to be allocated.
     * The position within the chunk will automatically be incremented.
     *
     * @param pData             destination buffer
     * @param WordCount         number of 8 Bit signed integers to read
     * @returns                 number of read integers
     * @throws RIFF::Exception  if an error occured or less than
     *                          \a WordCount integers could be read!
     */
    unsigned long Chunk::ReadInt8(int8_t* pData, unsigned long WordCount) {
       #if DEBUG
       std::cout << "Chunk::ReadInt8(int8_t*,ulong)" << std::endl;
       #endif // DEBUG
        return ReadSceptical(pData, WordCount, 1);
    }

    /**
     * Reads \a WordCount number of 8 Bit unsigned integer words and copies
     * it into the buffer pointed by \a pData. The buffer has to be
     * allocated. The position within the chunk will automatically be
     * incremented.
     *
     * @param pData             destination buffer
     * @param WordCount         number of 8 Bit unsigned integers to read
     * @returns                 number of read integers
     * @throws RIFF::Exception  if an error occured or less than
     *                          \a WordCount integers could be read!
     */
    unsigned long Chunk::ReadUint8(uint8_t* pData, unsigned long WordCount) {
       #if DEBUG
       std::cout << "Chunk::ReadUint8(uint8_t*,ulong)" << std::endl;
       #endif // DEBUG
        return ReadSceptical(pData, WordCount, 1);
    }

    /**
     * Reads \a WordCount number of 16 Bit signed integer words and copies
     * it into the buffer pointed by \a pData. The buffer has to be
     * allocated. Endian correction will automatically be done if needed.
     * The position within the chunk will automatically be incremented.
     *
     * @param pData             destination buffer
     * @param WordCount         number of 16 Bit signed integers to read
     * @returns                 number of read integers
     * @throws RIFF::Exception  if an error occured or less than
     *                          \a WordCount integers could be read!
     */
    unsigned long Chunk::ReadInt16(int16_t* pData, unsigned long WordCount) {
      #if DEBUG
      std::cout << "Chunk::ReadInt16(int16_t*,ulong)" << std::endl;
      #endif // DEBUG
        return ReadSceptical(pData, WordCount, 2);
    }

    /**
     * Reads \a WordCount number of 16 Bit unsigned integer words and copies
     * it into the buffer pointed by \a pData. The buffer has to be
     * allocated. Endian correction will automatically be done if needed.
     * The position within the chunk will automatically be incremented.
     *
     * @param pData             destination buffer
     * @param WordCount         number of 8 Bit unsigned integers to read
     * @returns                 number of read integers
     * @throws RIFF::Exception  if an error occured or less than
     *                          \a WordCount integers could be read!
     */
    unsigned long Chunk::ReadUint16(uint16_t* pData, unsigned long WordCount) {
      #if DEBUG
      std::cout << "Chunk::ReadUint16(uint16_t*,ulong)" << std::endl;
      #endif // DEBUG
        return ReadSceptical(pData, WordCount, 2);
    }

    /**
     * Reads \a WordCount number of 32 Bit signed integer words and copies
     * it into the buffer pointed by \a pData. The buffer has to be
     * allocated. Endian correction will automatically be done if needed.
     * The position within the chunk will automatically be incremented.
     *
     * @param pData             destination buffer
     * @param WordCount         number of 32 Bit signed integers to read
     * @returns                 number of read integers
     * @throws RIFF::Exception  if an error occured or less than
     *                          \a WordCount integers could be read!
     */
    unsigned long Chunk::ReadInt32(int32_t* pData, unsigned long WordCount) {
       #if DEBUG
       std::cout << "Chunk::ReadInt32(int32_t*,ulong)" << std::endl;
       #endif // DEBUG
        return ReadSceptical(pData, WordCount, 4);
    }

    /**
     * Reads \a WordCount number of 32 Bit unsigned integer words and copies
     * it into the buffer pointed by \a pData. The buffer has to be
     * allocated. Endian correction will automatically be done if needed.
     * The position within the chunk will automatically be incremented.
     *
     * @param pData             destination buffer
     * @param WordCount         number of 32 Bit unsigned integers to read
     * @returns                 number of read integers
     * @throws RIFF::Exception  if an error occured or less than
     *                          \a WordCount integers could be read!
     */
    unsigned long Chunk::ReadUint32(uint32_t* pData, unsigned long WordCount) {
       #if DEBUG
       std::cout << "Chunk::ReadUint32(uint32_t*,ulong)" << std::endl;
       #endif // DEBUG
        return ReadSceptical(pData, WordCount, 4);
    }

    /**
     * Reads one 8 Bit signed integer word and increments the position within
     * the chunk.
     *
     * @returns                 read integer word
     * @throws RIFF::Exception  if an error occured
     */
    int8_t Chunk::ReadInt8() {
      #if DEBUG
      std::cout << "Chunk::ReadInt8()" << std::endl;
      #endif // DEBUG
        int8_t word;
        ReadSceptical(&word,1,1);
        return word;
    }

    /**
     * Reads one 8 Bit unsigned integer word and increments the position
     * within the chunk.
     *
     * @returns                 read integer word
     * @throws RIFF::Exception  if an error occured
     */
    uint8_t Chunk::ReadUint8() {
      #if DEBUG
      std::cout << "Chunk::ReadUint8()" << std::endl;
      #endif // DEBUG
        uint8_t word;
        ReadSceptical(&word,1,1);
        return word;
    }

    /**
     * Reads one 16 Bit signed integer word and increments the position
     * within the chunk. Endian correction will automatically be done if
     * needed.
     *
     * @returns                 read integer word
     * @throws RIFF::Exception  if an error occured
     */
    int16_t Chunk::ReadInt16() {
      #if DEBUG
      std::cout << "Chunk::ReadInt16()" << std::endl;
      #endif // DEBUG
        int16_t word;
        ReadSceptical(&word,1,2);
        return word;
    }

    /**
     * Reads one 16 Bit unsigned integer word and increments the position
     * within the chunk. Endian correction will automatically be done if
     * needed.
     *
     * @returns                 read integer word
     * @throws RIFF::Exception  if an error occured
     */
    uint16_t Chunk::ReadUint16() {
      #if DEBUG
      std::cout << "Chunk::ReadUint16()" << std::endl;
      #endif // DEBUG
        uint16_t word;
        ReadSceptical(&word,1,2);
        return word;
    }

    /**
     * Reads one 32 Bit signed integer word and increments the position
     * within the chunk. Endian correction will automatically be done if
     * needed.
     *
     * @returns                 read integer word
     * @throws RIFF::Exception  if an error occured
     */
    int32_t Chunk::ReadInt32() {
      #if DEBUG
      std::cout << "Chunk::ReadInt32()" << std::endl;
      #endif // DEBUG
        int32_t word;
        ReadSceptical(&word,1,4);
        return word;
    }

    /**
     * Reads one 32 Bit unsigned integer word and increments the position
     * within the chunk. Endian correction will automatically be done if
     * needed.
     *
     * @returns                 read integer word
     * @throws RIFF::Exception  if an error occured
     */
    uint32_t Chunk::ReadUint32() {
      #if DEBUG
      std::cout << "Chunk::ReadUint32()" << std::endl;
      #endif // DEBUG
        uint32_t word;
        ReadSceptical(&word,1,4);
        return word;
    }

    void* Chunk::LoadChunkData() {
        if (!pChunkData) {
            #if POSIX
            if (lseek(hFile, ulStartPos, SEEK_SET) == -1) return NULL;
            pChunkData = new uint8_t[GetSize()];
            if (!pChunkData) return NULL;
            unsigned long readWords = read(hFile, pChunkData, GetSize());
            #else
            if (fseek(hFile, ulStartPos, SEEK_SET)) return NULL;
            pChunkData = new uint8_t[GetSize()];
            if (!pChunkData) return NULL;
            unsigned long readWords = fread(pChunkData, 1, GetSize(), hFile);
            #endif // POSIX
            if (readWords != GetSize()) {
                delete[] pChunkData;
                return (pChunkData = NULL);
            }
        }
        return pChunkData;
    }

    void Chunk::ReleaseChunkData() {
        if (pChunkData) {
            delete[] pChunkData;
            pChunkData = NULL;
        }
    }



// *************** List ***************
// *

    List::List() : Chunk() {
      #if DEBUG
      std::cout << "List::List()" << std::endl;
      #endif // DEBUG
        pSubChunks    = NULL;
        pSubChunksMap = NULL;
    }

    #if POSIX
    List::List(int hFile, unsigned long StartPos, bool EndianNative, List* Parent)
    #else
    List::List(FILE* hFile, unsigned long StartPos, bool EndianNative, List* Parent)
    #endif // POSIX
      : Chunk(hFile, StartPos, EndianNative, Parent) {
        #if DEBUG
        std::cout << "List::List(FILE*,ulong,bool,List*)" << std::endl;
        #endif // DEBUG
        pSubChunks    = NULL;
        pSubChunksMap = NULL;
        ReadHeader(StartPos);
        ulStartPos    = StartPos + LIST_HEADER_SIZE;
    }

    List::~List() {
      #if DEBUG
      std::cout << "List::~List()" << std::endl;
      #endif // DEBUG
        if (pSubChunks) {
            ChunkList::iterator iter = pSubChunks->begin();
            ChunkList::iterator end  = pSubChunks->end();
            while (iter != end) {
                delete *iter;
                iter++;
            }
            delete pSubChunks;
        }
        if (pSubChunksMap) delete pSubChunksMap;
    }

    /**
     *  Returns subchunk with chunk ID <i>\a ChunkID</i> within this chunk
     *  list. Use this method if you expect only one subchunk of that type in
     *  the list. It there are more than one, it's undetermined which one of
     *  them will be returned! If there are no subchunks with that desired
     *  chunk ID, NULL will be returned.
     *
     *  @param ChunkID - chunk ID of the sought subchunk
     *  @returns         pointer to the subchunk or NULL if there is none of
     *                   that ID
     */
    Chunk* List::GetSubChunk(uint32_t ChunkID) {
      #if DEBUG
      std::cout << "List::GetSubChunk(uint32_t)" << std::endl;
      #endif // DEBUG
        if (!pSubChunksMap) LoadSubChunks();
        return (*pSubChunksMap)[ChunkID];
    }

    /**
     *  Returns sublist chunk with list type <i>\a ListType</i> within this
     *  chunk list. Use this method if you expect only one sublist chunk of
     *  that type in the list. It there are more than one, it's undetermined
     *  which one of them will be returned! If there are no sublists with
     *  that desired list type, NULL will be returned.
     *
     *  @param ListType - list type of the sought sublist
     *  @returns          pointer to the sublist or NULL if there is none of
     *                    that type
     */
    List* List::GetSubList(uint32_t ListType) {
        #if DEBUG
        std::cout << "List::GetSubList(uint32_t)" << std::endl;
        #endif // DEBUG
        if (!pSubChunks) LoadSubChunks();
        ChunkList::iterator iter = pSubChunks->begin();
        ChunkList::iterator end  = pSubChunks->end();
        while (iter != end) {
            if ((*iter)->GetChunkID() == CHUNK_ID_LIST) {
                List* l = (List*) *iter;
                if (l->GetListType() == ListType) return l;
            }
            iter++;
        }
        return NULL;
    }

    /**
     *  Returns the first subchunk within the list. You have to call this
     *  method before you can call GetNextSubChunk(). Recall it when you want
     *  to start from the beginning of the list again.
     *
     *  @returns  pointer to the first subchunk within the list, NULL
     *            otherwise
     */
    Chunk* List::GetFirstSubChunk() {
        #if DEBUG
        std::cout << "List::GetFirstSubChunk()" << std::endl;
        #endif // DEBUG
        if (!pSubChunks) LoadSubChunks();
        ChunksIterator = pSubChunks->begin();
        return (ChunksIterator != pSubChunks->end()) ? *ChunksIterator : NULL;
    }

    /**
     *  Returns the next subchunk within the list. You have to call
     *  GetFirstSubChunk() before you can use this method!
     *
     *  @returns  pointer to the next subchunk within the list or NULL if
     *            end of list is reached
     */
    Chunk* List::GetNextSubChunk() {
        #if DEBUG
        std::cout << "List::GetNextSubChunk()" << std::endl;
        #endif // DEBUG
        if (!pSubChunks) return NULL;
        ChunksIterator++;
        return (ChunksIterator != pSubChunks->end()) ? *ChunksIterator : NULL;
    }

    /**
     *  Returns the first sublist within the list (that is a subchunk with
     *  chunk ID "LIST"). You have to call this method before you can call
     *  GetNextSubList(). Recall it when you want to start from the beginning
     *  of the list again.
     *
     *  @returns  pointer to the first sublist within the list, NULL
     *            otherwise
     */
    List* List::GetFirstSubList() {
        #if DEBUG
        std::cout << "List::GetFirstSubList()" << std::endl;
        #endif // DEBUG
        if (!pSubChunks) LoadSubChunks();
        ListIterator            = pSubChunks->begin();
        ChunkList::iterator end = pSubChunks->end();
        while (ListIterator != end) {
            if ((*ListIterator)->GetChunkID() == CHUNK_ID_LIST) return (List*) *ListIterator;
            ListIterator++;
        }
        return NULL;
    }

    /**
     *  Returns the next sublist (that is a subchunk with chunk ID "LIST")
     *  within the list. You have to call GetFirstSubList() before you can
     *  use this method!
     *
     *  @returns  pointer to the next sublist within the list, NULL if
     *            end of list is reached
     */
    List* List::GetNextSubList() {
        #if DEBUG
        std::cout << "List::GetNextSubList()" << std::endl;
        #endif // DEBUG
        if (!pSubChunks) return NULL;
        if (ListIterator == pSubChunks->end()) return NULL;
        ListIterator++;
        ChunkList::iterator end = pSubChunks->end();
        while (ListIterator != end) {
            if ((*ListIterator)->GetChunkID() == CHUNK_ID_LIST) return (List*) *ListIterator;
            ListIterator++;
        }
        return NULL;
    }

    /**
     *  Returns number of subchunks within the list.
     */
    unsigned int List::CountSubChunks() {
        if (!pSubChunks) LoadSubChunks();
        return pSubChunks->size();
    }

    /**
     *  Returns number of subchunks within the list with chunk ID
     *  <i>\a ChunkId</i>.
     */
    unsigned int List::CountSubChunks(uint32_t ChunkID) {
        unsigned int result = 0;
        if (!pSubChunks) LoadSubChunks();
        ChunkList::iterator iter = pSubChunks->begin();
        ChunkList::iterator end  = pSubChunks->end();
        while (iter != end) {
            if ((*iter)->GetChunkID() == ChunkID) {
                result++;
            }
            iter++;
        }
        return result;
    }

    /**
     *  Returns number of sublists within the list.
     */
    unsigned int List::CountSubLists() {
        return CountSubChunks(CHUNK_ID_LIST);
    }

    /**
     *  Returns number of sublists within the list with list type
     *  <i>\a ListType</i>
     */
    unsigned int List::CountSubLists(uint32_t ListType) {
        unsigned int result = 0;
        if (!pSubChunks) LoadSubChunks();
        ChunkList::iterator iter = pSubChunks->begin();
        ChunkList::iterator end  = pSubChunks->end();
        while (iter != end) {
            if ((*iter)->GetChunkID() == CHUNK_ID_LIST) {
                List* l = (List*) *iter;
                if (l->GetListType() == ListType) result++;
            }
            iter++;
        }
        return result;
    }

    void List::ReadHeader(unsigned long fPos) {
      #if DEBUG
      std::cout << "List::Readheader(ulong) ";
      #endif // DEBUG
        Chunk::ReadHeader(fPos);
        ChunkSize -= 4;
        #if POSIX
        lseek(hFile, fPos + CHUNK_HEADER_SIZE, SEEK_SET);
        read(hFile, &ListType, 4);
        #else
        fseek(hFile, fPos + CHUNK_HEADER_SIZE, SEEK_SET);
        fread(&ListType, 4, 1, hFile);
        #endif // POSIX
      #if DEBUG
      std::cout << "listType=" << convertToString(ListType) << std::endl;
      #endif // DEBUG
        if (!bEndianNative) {
            //swapBytes_32(&ListType);
        }
    }

    void List::LoadSubChunks() {
       #if DEBUG
       std::cout << "List::LoadSubChunks()";
       #endif // DEBUG
        if (!pSubChunks) {
            pSubChunks    = new ChunkList();
            pSubChunksMap = new ChunkMap();
            unsigned long uiOriginalPos = GetPos();
            SetPos(0); // jump to beginning of list chunk body
            while (RemainingBytes() >= CHUNK_HEADER_SIZE) {
                Chunk* ck;
                uint32_t ckid;
                Read(&ckid, 4, 1);
       #if DEBUG
       std::cout << " ckid=" << convertToString(ckid) << std::endl;
       #endif // DEBUG
                if (ckid == CHUNK_ID_LIST) {
                    ck = new RIFF::List(hFile, ulStartPos + ulPos - 4, bEndianNative, this);
                    SetPos(ck->GetSize() + LIST_HEADER_SIZE - 4, RIFF::stream_curpos);
                }
                else { // simple chunk
                    ck = new RIFF::Chunk(hFile, ulStartPos + ulPos - 4, bEndianNative, this);
                    SetPos(ck->GetSize() + CHUNK_HEADER_SIZE - 4, RIFF::stream_curpos);
                }
                pSubChunks->push_back(ck);
                (*pSubChunksMap)[ckid] = ck;
                if (GetPos() % 2 != 0) SetPos(1, RIFF::stream_curpos); // jump over pad byte
            }
            SetPos(uiOriginalPos); // restore position before this call
        }
    }

    /**
     *  Returns string representation of the lists's id
     */
    String List::GetListTypeString() {
        return convertToString(ListType);
    }



// *************** File ***************
// *

    File::File(const String& path) : List() {
      #if DEBUG
      std::cout << "File::File("<<path<<")" << std::endl;
      #endif // DEBUG
        bEndianNative = true;
        #if POSIX
        hFile = open(path.c_str(), O_RDONLY | O_NONBLOCK);
        if (hFile <= 0) {
            hFile = 0;
            throw RIFF::Exception("Can't open \"" + path + "\"");
        }
        #else
        hFile = fopen(path.c_str(), "rb");
        if (!hFile) throw RIFF::Exception("Can't open \"" + path + "\"");
        #endif // POSIX
        ulStartPos = RIFF_HEADER_SIZE;
        ReadHeader(0);
        if (ChunkID != CHUNK_ID_RIFF) {
            throw RIFF::Exception("Not a RIFF file");
        }
    }

    File::~File() {
       #if DEBUG
       std::cout << "File::~File()" << std::endl;
       #endif // DEBUG
        #if POSIX
        if (hFile) close(hFile);
        #else
        if (hFile) fclose(hFile);
        #endif // POSIX
    }

    unsigned long File::GetFileSize() {
        #if POSIX
        struct stat filestat;
        fstat(hFile, &filestat);
        long size = filestat.st_size;
        #else // standard C functions
        long curpos = ftell(hFile);
        fseek(hFile, 0, SEEK_END);
        long size = ftell(hFile);
        fseek(hFile, curpos, SEEK_SET);
        #endif // POSIX
        return size;
    }



// *************** Exception ***************
// *

    void Exception::PrintMessage() {
        std::cout << "RIFF::Exception: " << Message << std::endl;
    }


// *************** functions ***************
// *

    /**
     * Returns the name of this C++ library. This is usually "libgig" of
     * course. This call is equivalent to DLS::libraryName() and
     * gig::libraryName().
     */
    String libraryName() {
        return PACKAGE;
    }

    /**
     * Returns version of this C++ library. This call is equivalent to
     * DLS::libraryVersion() and gig::libraryVersion().
     */
    String libraryVersion() {
        return VERSION;
    }

} // namespace RIFF
#endif
