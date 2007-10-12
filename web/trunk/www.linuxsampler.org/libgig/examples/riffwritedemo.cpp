// This little test application demonstrates how to create and modify
// arbitrary RIFF files with libgig 3.0.0.
//
// Date: 2006-04-29
//
// Compile with: 'g++ -lgig -o riffwritedemo riffwritedemo.cpp'

#include <RIFF.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_TYPE_FOOX	0x584F4F46
#define LIST_TYPE_GOOX  0x584F4F47
#define CHUNK_ID_AAAA	0x41414141
#define CHUNK_ID_BBBB	0x42424242
#define CHUNK_ID_CCCC	0x43434343

int main() {
    try {
        // Create a RIFF file with one list chunk <FOOX> having three
        // subchunks (<AAA>, <BBBB> and <CCCC>) and save it as
        // "footext.riff". Data for the three chunks will be directly
        // written to disk.
        {
            // create empty RIFF file with RIFF file type <GOOX>
            RIFF::File file(LIST_TYPE_GOOX);
            // add a sublist chunk with type <FOOX>
            RIFF::List* pList = file.AddSubList(LIST_TYPE_FOOX);
            // add three subchunks to the sublist chunk, each having a data
            // body size of one byte
            RIFF::Chunk* pChunkA = pList->AddSubChunk(CHUNK_ID_AAAA, 1);
            RIFF::Chunk* pChunkB = pList->AddSubChunk(CHUNK_ID_BBBB, 1);
            RIFF::Chunk* pChunkC = pList->AddSubChunk(CHUNK_ID_CCCC, 1);
            // write that new RIFF file
            file.Save("footext.riff");

            // write an arbitrary byte to the chunks
            // (by directly writing to disk)
            uint8_t c = '1';
            pChunkA->WriteUint8(&c); c = '2';
            pChunkB->WriteUint8(&c); c = '3';
            pChunkC->WriteUint8(&c);

            // resize (enlarge) chunk A and B to five bytes each
            pChunkA->Resize(5);
            pChunkB->Resize(5);
            // actually apply the resize operations to the file
            file.Save();

            // now that the file and thus the chunks are physically resized,
            // we can write more data to them
            c = 'V';
            pChunkA->WriteUint8(&c);
            c = 'E';
            pChunkA->WriteUint8(&c);
            c = 'R';
            pChunkA->WriteUint8(&c);
            c = 'A';
            pChunkA->WriteUint8(&c);
            c = '6';
            pChunkA->WriteUint8(&c);

            c = 'A';
            pChunkB->WriteUint8(&c);
            c = 'R';
            pChunkB->WriteUint8(&c);
            c = 'E';
            pChunkB->WriteUint8(&c);
            c = 'V';
            pChunkB->WriteUint8(&c);
            c = '7';
            pChunkB->WriteUint8(&c);

            // resize (shrink) chunk A to one byte
            pChunkA->Resize(1);
            file.Save();

            // write an arbitrary new byte to chunk A
            c = 'Q';
            pChunkA->WriteUint8(&c);
        }

        // Create yet another RIFF file with one list chunk <FOOX> having
        // three subchunks (<AAA>, <BBBB> and <CCCC>) and save it as
        // "footextRAM.riff". Data for the three chunks will this time be
        // 'written' to RAM and afterwards actually be written to disk by
        // the File::Save() call.
        {
            // create empty RIFF file with RIFF file type <GOOX>
            RIFF::File file(LIST_TYPE_GOOX);
            // add a sublist chunk with type <FOOX>
            RIFF::List* pList = file.AddSubList(LIST_TYPE_FOOX);
            // add three subchunks to the sublist chunk, each having a data
            // body size of one byte
            RIFF::Chunk* pChunkA = pList->AddSubChunk(CHUNK_ID_AAAA, 1);
            RIFF::Chunk* pChunkB = pList->AddSubChunk(CHUNK_ID_BBBB, 1);
            RIFF::Chunk* pChunkC = pList->AddSubChunk(CHUNK_ID_CCCC, 1);
            // write that new RIFF file
            file.Save("footextRAM.riff");
            // get the buffer to copy the chunks' data to
            char* pAData = (char*) pChunkA->LoadChunkData();
            char* pBData = (char*) pChunkB->LoadChunkData();
            char* pCData = (char*) pChunkC->LoadChunkData();
            // copy the chunks' data to the retrieved buffer
            pAData[0] = '1';
            pBData[0] = '2';
            pCData[0] = '3';

            // we already schedule to enlarge chunk A and B to a size of
            // five bytes
            pChunkA->Resize(5);
            pChunkB->Resize(5);
            // write the buffered chunk data to disk and apply the resize
            // operations in one rush
            file.Save();

            char vera6[] = "vera6";
            char arev7[] = "arev7";
            // we have to re-retrieve the buffers, as we resized the chunks
            pAData = (char*) pChunkA->LoadChunkData();
            pBData = (char*) pChunkB->LoadChunkData();
            pCData = (char*) pChunkC->LoadChunkData();
            // write arbitrary five bytes as data to the chunk's buffers
            memcpy(pAData, vera6, 5);
            memcpy(pBData, arev7, 5);
            // actually write that data to disk
            file.Save();

            // shrink chunk A to a data body size of one byte
            pChunkA->Resize(1);
            // perform shrink operation
            file.Save();

            // finally write another arbitrary byte to the shrinked chunk
            pAData = (char*) pChunkA->LoadChunkData();
            pAData[0] = 'Q';
            file.Save();
        }

        // In this example we create a RIFF file as in the previous example,
        // but this time we delete chunks afterwards.
        {
            // create empty RIFF file with RIFF file type <GOOX>
            RIFF::File file(LIST_TYPE_GOOX);
            // add a sublist chunk with type <FOOX>
            RIFF::List* pList = file.AddSubList(LIST_TYPE_FOOX);
            // add three subchunks to the sublist chunk, each having a data
            // body size of one byte
            RIFF::Chunk* pChunkA = pList->AddSubChunk(CHUNK_ID_AAAA, 1);
            RIFF::Chunk* pChunkB = pList->AddSubChunk(CHUNK_ID_BBBB, 1);
            RIFF::Chunk* pChunkC = pList->AddSubChunk(CHUNK_ID_CCCC, 1);
            // write that new RIFF file
            file.Save("footext_delete.riff");

            // write some arbitrary data to the chunks
            uint8_t c = '1';
            pChunkA->WriteUint8(&c); c = '2';
            pChunkB->WriteUint8(&c); c = '3';
            pChunkC->WriteUint8(&c);

            // schedule to enlarge chunk A and B to five bytes
            pChunkA->Resize(5);
            pChunkB->Resize(5);
            // perform scheduled enlarge operations
            file.Save();

            // write some more data to the enlarged chunks
            c = 'V';
            pChunkA->WriteUint8(&c);
            c = 'E';
            pChunkA->WriteUint8(&c);
            c = 'R';
            pChunkA->WriteUint8(&c);
            c = 'A';
            pChunkA->WriteUint8(&c);
            c = '6';
            pChunkA->WriteUint8(&c);

            c = 'A';
            pChunkB->WriteUint8(&c);
            c = 'R';
            pChunkB->WriteUint8(&c);
            c = 'E';
            pChunkB->WriteUint8(&c);
            c = 'V';
            pChunkB->WriteUint8(&c);
            c = '7';
            pChunkB->WriteUint8(&c);

            // schedule to delete chunk A
            pList->DeleteSubChunk(pChunkA);
            // apply 'delete' operation to file
            file.Save();
        }
    } catch (RIFF::Exception e) {
        e.PrintMessage();
        return -1;
    }
    return 0;
}
