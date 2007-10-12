// This little test application demonstrates how to create and modify DLS
// files with libgig 3.0.0.
//
// Date: 2006-04-29
//
// Compile with: 'g++ -lgig -o dlswritedemo dlswritedemo.cpp'

#include <DLS.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    // four stupid little sample "waves"
    // (each having three sample points length, 16 bit depth, mono)
    int16_t sampleData1[] = { 1, 2, 3 };
    int16_t sampleData2[] = { 4, 5, 6 };
    int16_t sampleData3[] = { 7, 8, 9 };
    int16_t sampleData4[] = { 10,11,12 };
    try {
        // create an empty DLS file
        DLS::File file;
        // we give it an internal name, not mandatory though
        file.pInfo->Name = "Foo DLS File";

        // create four samples
        DLS::Sample* pSample1 = file.AddSample();
        DLS::Sample* pSample2 = file.AddSample();
        DLS::Sample* pSample3 = file.AddSample();
        DLS::Sample* pSample4 = file.AddSample();
        // give those samples a name (not mandatory)
        pSample1->pInfo->Name = "Foo Sample 1";
        pSample2->pInfo->Name = "Foo Sample 2";
        pSample3->pInfo->Name = "Foo Sample 3";
        pSample4->pInfo->Name = "Foo Sample 4";
        // set meta informations for those samples
        pSample1->Channels = 1; // mono
        pSample1->BitDepth = 16; // 16 bits
        pSample1->FrameSize = 16/*bitdepth*/ / 8/*1 byte are 8 bits*/ * 1/*mono*/;
        pSample1->SamplesPerSecond = 44100;
        pSample2->Channels = 1; // mono
        pSample2->BitDepth = 16; // 16 bits
        pSample2->FrameSize = 16 / 8 * 1;
        pSample2->SamplesPerSecond = 44100;
        pSample3->Channels = 1; // mono
        pSample3->BitDepth = 16; // 16 bits
        pSample3->FrameSize = 16 / 8 * 1;
        pSample3->SamplesPerSecond = 44100;
        pSample4->Channels = 1; // mono
        pSample4->BitDepth = 16; // 16 bits
        pSample4->FrameSize = 16 / 8 * 1;
        pSample4->SamplesPerSecond = 44100;
        // resize those samples to a length of three sample points
        // (again: _sample_points_ NOT bytes!)
        pSample1->Resize(3);
        pSample2->Resize(3);
        pSample3->Resize(3);
        pSample4->Resize(3);
        // retrieve a buffer in RAM to place the sample's wave forms there
        void* pData = pSample1->LoadSampleData();
        memccpy(pData, sampleData1, 3, 2);
        pData = pSample2->LoadSampleData();
        memccpy(pData, sampleData2, 3, 2);
        pData = pSample3->LoadSampleData();
        memccpy(pData, sampleData3, 3, 2);
        pData = pSample4->LoadSampleData();
        memccpy(pData, sampleData4, 3, 2);

        // create four instruments
        DLS::Instrument* pInstrument1 = file.AddInstrument();
        DLS::Instrument* pInstrument2 = file.AddInstrument();
        DLS::Instrument* pInstrument3 = file.AddInstrument();
        DLS::Instrument* pInstrument4 = file.AddInstrument();
        // give them a name (not mandatory)
        pInstrument1->pInfo->Name = "Foo Instrument 1";
        pInstrument2->pInfo->Name = "Foo Instrument 2";
        pInstrument3->pInfo->Name = "Foo Instrument 3";
        pInstrument4->pInfo->Name = "Foo Instrument 4";
        // create a region for all instruments and apply a sample to the
        // regions
        pInstrument1->AddRegion()->SetSample(pSample1);
        pInstrument2->AddRegion()->SetSample(pSample2);
        pInstrument3->AddRegion()->SetSample(pSample3);
        pInstrument4->AddRegion()->SetSample(pSample4);

        // save file as of now
        file.Save("foo.dls");
    } catch (RIFF::Exception e) {
        e.PrintMessage();
        return -1;
    }
    return 0;
}
