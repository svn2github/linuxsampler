/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003 by Christian Schoenebeck                           *
 *                         <cuse@users.sourceforge.net>                    *
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

#ifndef __RIFF_H__
#define __RIFF_H__

#define POSIX 1
#define DEBUG 0

#include <string>
#include <list>
#include <map>
#include <iostream>

#if POSIX
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
#endif // POSIX

#include <stdint.h>

//typedef unsigned char  uint8_t;
//typedef unsigned short uint16_t;
//typedef unsigned int   uint32_t;

#include <stdio.h>

#if WORDS_BIGENDIAN
# define CHUNK_ID_RIFF	0x52494646
# define CHUNK_ID_RIFX	0x52494658
# define CHUNK_ID_LIST	0x4C495354
#else  // little endian
# define CHUNK_ID_RIFF	0x46464952
# define CHUNK_ID_RIFX	0x58464952
# define CHUNK_ID_LIST	0x5453494C
#endif // WORDS_BIGENDIAN

#define CHUNK_HEADER_SIZE	8
#define LIST_HEADER_SIZE	12
#define RIFF_HEADER_SIZE	12


/** RIFF specific classes and definitions */
namespace RIFF {

    /* just symbol prototyping */
    class Chunk;
    class List;

    typedef std::string String;

    /** Current state of the file stream. */
    typedef enum {
        stream_ready       = 0,
        stream_end_reached = 1,
        stream_closed      = 2
    } stream_state_t;

    /** File stream position dependent to these relations. */
    typedef enum {
        stream_start    = 0,
        stream_curpos   = 1,
        stream_backward = 2,
        stream_end      = 3
    } stream_whence_t;

    /** Provides convenient methods to access data of RIFF chunks in general. */
    class Chunk {
        public:
            #if POSIX
            Chunk(int hFile, unsigned long StartPos, bool EndianNative, List* Parent);
            #else
            Chunk(FILE* hFile, unsigned long StartPos, bool EndianNative, List* Parent);
            #endif // POSIX
            String         GetChunkIDString();
            uint32_t       GetChunkID() { return ChunkID; };
            List*          GetParent()  { return pParent; };
            unsigned long  GetSize()    { return ChunkSize; }; ///< Chunk size in bytes (without header, thus the chunk data body)
            unsigned long  GetPos()     { return ulPos; };     ///< Position within the chunk data body
            unsigned long  GetFilePos() { return ulStartPos + ulPos; }; ///< Current, actual offset in file.
            unsigned long  SetPos(unsigned long Where, stream_whence_t Whence = stream_start);
            unsigned long  RemainingBytes();
            stream_state_t GetState();
            unsigned long  Read(void* pData, unsigned long WordCount, unsigned long WordSize);
            unsigned long  ReadInt8(int8_t* pData,     unsigned long WordCount = 1);
            unsigned long  ReadUint8(uint8_t* pData,   unsigned long WordCount = 1);
            unsigned long  ReadInt16(int16_t* pData,   unsigned long WordCount = 1);
            unsigned long  ReadUint16(uint16_t* pData, unsigned long WordCount = 1);
            unsigned long  ReadInt32(int32_t* pData,   unsigned long WordCount = 1);
            unsigned long  ReadUint32(uint32_t* pData, unsigned long WordCount = 1);
            int8_t         ReadInt8();
            uint8_t        ReadUint8();
            int16_t        ReadInt16();
            uint16_t       ReadUint16();
            int32_t        ReadInt32();
            uint32_t       ReadUint32();
            void*          LoadChunkData();     ///< Load the whole chunk body in memory (on success returns a pointer to the data in RAM, else NULL).
            void           ReleaseChunkData();  ///< Free loaded chunk body data from memory (RAM).
           ~Chunk();
        protected:
            uint32_t      ChunkID;
            uint32_t      ChunkSize;		/* in bytes */
            List*         pParent;
            #if POSIX
            int           hFile;
            #else
            FILE*         hFile;
            #endif // POSIX
            unsigned long ulStartPos;		/* actual position in file where chunk (without header) starts */
            unsigned long ulPos; 		/* # of bytes from ulStartPos */
            bool          bEndianNative;
            uint8_t*      pChunkData;

            Chunk();
            void          ReadHeader(unsigned long fPos);
            unsigned long ReadSceptical(void* pData, unsigned long WordCount, unsigned long WordSize);
            inline void   swapBytes_16(void* Word) {
                uint8_t byteCache = *((uint8_t*) Word);
                *((uint8_t*) Word)     = *((uint8_t*) Word + 1);
                *((uint8_t*) Word + 1) = byteCache;
            }
            inline void   swapBytes_32(void* Word) {
                uint8_t byteCache = *((uint8_t*) Word);
                *((uint8_t*) Word)     = *((uint8_t*) Word + 3);
                *((uint8_t*) Word + 3) = byteCache;
                byteCache = *((uint8_t*) Word + 1);
                *((uint8_t*) Word + 1) = *((uint8_t*) Word + 2);
                *((uint8_t*) Word + 2) = byteCache;
            }
            inline void   swapBytes(void* Word, unsigned long WordSize) {
                uint8_t byteCache;
                unsigned long lo = 0, hi = WordSize - 1;
                for (; lo < hi; hi--, lo++) {
                    byteCache = *((uint8_t*) Word + lo);
                    *((uint8_t*) Word + lo) = *((uint8_t*) Word + hi);
                    *((uint8_t*) Word + hi) = byteCache;
                }
            }
            inline String convertToString(uint32_t word) {
                String result;
                for (int i = 0; i < 4; i++) {
                    uint8_t byte = *((uint8_t*)(&word) + i);
                    char c = byte;
                    result += c;
                }
                return result;
            }
    };

    /** Provides convenient methods to access data of RIFF list chunks and their subchunks. */
    class List : public Chunk {
        public:
            #if POSIX
            List(int hFile, unsigned long StartPos, bool EndianNative, List* Parent);
            #else
            List(FILE* hFile, unsigned long StartPos, bool EndianNative, List* Parent);
            #endif // POSIX
            String       GetListTypeString();
            uint32_t     GetListType() { return ListType; }
            Chunk*       GetSubChunk(uint32_t ChunkID); /* use this if you expect only one subchunk of that type in the list */
            List*        GetSubList(uint32_t ListType); /* use this if you expect only one sublist chunk of that type in the list */
            Chunk*       GetFirstSubChunk();
            Chunk*       GetNextSubChunk();
            List*        GetFirstSubList();
            List*        GetNextSubList();
            unsigned int CountSubChunks();
            unsigned int CountSubChunks(uint32_t ChunkID);
            unsigned int CountSubLists();
            unsigned int CountSubLists(uint32_t ListType);
           ~List();
        protected:
            typedef std::map<uint32_t, RIFF::Chunk*>  ChunkMap;
            typedef std::list<Chunk*>                 ChunkList;

            uint32_t   ListType;
            ChunkList* pSubChunks;
            ChunkMap*  pSubChunksMap;
            ChunkList::iterator ChunksIterator;
            ChunkList::iterator ListIterator;

            List();
            void ReadHeader(unsigned long fPos);
            void LoadSubChunks();
    };

    /** Parses arbitrary RIFF files and provides together with it's base classes convenient methods to walk through the RIFF tree. */
    class File : public List {
        public:
            File(const String& path);
           ~File();
        private:
            unsigned long GetFileSize();
    };

    /** Will be thrown whenever an error occurs while parsing a RIFF file. */
    class Exception {
        public:
            String Message;

            Exception(String Message) { Exception::Message = Message; };
            void PrintMessage();
            virtual ~Exception() {};
    };

} // namespace RIFF
#endif // __RIFF_H__
