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
# include <config.h>
#endif

#include <iostream>
#include <cstdlib>

#include "gig.h"

using namespace std;

void PrintSamples(gig::File* gig);
void PrintInstruments(gig::File* gig);
void PrintRegions(gig::Instrument* instr);
void PrintUsage();
void PrintDimensionRegions(gig::Region* rgn);

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        PrintUsage();
        return EXIT_FAILURE;
    }
    FILE* hFile = fopen(argv[1], "r");
    if (!hFile) {
        cout << "Invalid file argument!" << endl;
        return EXIT_FAILURE;
    }
    fclose(hFile);
    try {
        RIFF::File* riff = new RIFF::File(argv[1]);
        gig::File*  gig  = new gig::File(riff);
        PrintSamples(gig);
        cout << endl;
        PrintInstruments(gig);
        delete gig;
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

void PrintSamples(gig::File* gig) {
    int samples = 0;
    cout << "ALL Available Samples (as there might be more than referenced by Instruments):" << endl;
    gig::Sample* pSample = gig->GetFirstSample();
    while (pSample) {
        samples++;
        string name = pSample->pInfo->Name;
        if (name == "") name = "<NO NAME>";
        else            name = '\"' + name + '\"';
        cout << "    Sample " << samples << ") " << name << ", ";
        cout << pSample->SamplesPerSecond << "Hz, " << pSample->Channels << " Channels, " << pSample->Loops << " Loops";
        if (pSample->Loops) {
            cout << " (Type: ";
            switch (pSample->LoopType) {
                case gig::loop_type_normal:         cout << "normal)";   break;
                case gig::loop_type_bidirectional:  cout << "pingpong)"; break;
                case gig::loop_type_backward:       cout << "reverse)";  break;
            }
            cout << ", LoopFraction=" << pSample->LoopFraction << ", Start=" << pSample->LoopStart << ", End=" << pSample->LoopEnd;
        }
        cout << ", Length=" << pSample->SamplesTotal << " Compressed=" << ((pSample->Compressed) ? "true" : "false") << endl;
        pSample = gig->GetNextSample();
    }
}

void PrintInstruments(gig::File* gig) {
    int instruments = 0;
    cout << "Available Instruments:" << endl;
    gig::Instrument* pInstrument = gig->GetFirstInstrument();
    while (pInstrument) {
        instruments++;
        string name = pInstrument->pInfo->Name;
        if (name == "") name = "<NO NAME>";
        else            name = '\"' + name + '\"';
        cout << "    Instrument " << instruments << ") " << name << ", ";

        cout << " MIDIBank=" << pInstrument->MIDIBank << ", MIDIProgram=" << pInstrument->MIDIProgram << endl;
        PrintRegions(pInstrument);

        pInstrument = gig->GetNextInstrument();
    }
}

void PrintRegions(gig::Instrument* instr) {
    int iRegion = 1;
    gig::Region* pRegion = instr->GetFirstRegion();
    while (pRegion) {
        cout << "        Region " << iRegion++ << ") ";
        gig::Sample* pSample = pRegion->GetSample();
        if (pSample) {
            cout << "Sample: ";
            if (pSample->pInfo->Name != "") {
                cout << "\"" << pSample->pInfo->Name << "\", ";
            }
            cout << pSample->SamplesPerSecond << "Hz, " << endl;
        }
        else {
            cout << "<NO_VALID_SAMPLE_REFERENCE> ";
        }
        cout << "            KeyRange=" << pRegion->KeyRange.low << "-" << pRegion->KeyRange.high << ", ";
        cout << "VelocityRange=" << pRegion->VelocityRange.low << "-" << pRegion->VelocityRange.high << ", Layer=" << pRegion->Layer << endl;
        cout << "            Loops=" << pRegion->SampleLoops << endl;
        PrintDimensionRegions(pRegion);

        pRegion = instr->GetNextRegion();
    }
}

void PrintDimensionRegions(gig::Region* rgn) {
    int dimensionRegions = 0;
    gig::DimensionRegion* pDimensionRegion;
    while (dimensionRegions < 32) {
        pDimensionRegion = rgn->pDimensionRegions[dimensionRegions];
        if (!pDimensionRegion) break;

        cout << "            Dimension Region " << dimensionRegions + 1 << ")" << endl;

        gig::Sample* pSample = pDimensionRegion->pSample;
        if (pSample) {
            cout << "                Sample: ";
            if (pSample->pInfo->Name != "") {
                cout << "\"" << pSample->pInfo->Name << "\", ";
            }
            cout << pSample->SamplesPerSecond << "Hz, " << endl;
        }
        else {
            cout << "                Sample: <NO_VALID_SAMPLE_REFERENCE> " << endl;
        }
        cout << "                LFO1Frequency=" << pDimensionRegion->LFO1Frequency << "Hz, LFO1InternalDepth=" << pDimensionRegion-> LFO1InternalDepth << ", LFO1ControlDepth=" << pDimensionRegion->LFO1ControlDepth << " LFO1Controller=" << pDimensionRegion->LFO1Controller << endl;
        cout << "                LFO2Frequency=" << pDimensionRegion->LFO2Frequency << "Hz, LFO2InternalDepth=" << pDimensionRegion-> LFO2InternalDepth << ", LFO2ControlDepth=" << pDimensionRegion->LFO2ControlDepth << " LFO2Controller=" << pDimensionRegion->LFO2Controller << endl;
        cout << "                LFO3Frequency=" << pDimensionRegion->LFO3Frequency << "Hz, LFO3InternalDepth=" << pDimensionRegion-> LFO3InternalDepth << ", LFO3ControlDepth=" << pDimensionRegion->LFO3ControlDepth << " LFO3Controller=" << pDimensionRegion->LFO3Controller << endl;
        cout << "                EG1PreAttack=" << pDimensionRegion->EG1PreAttack << "permille, EG1Attack=" << pDimensionRegion->EG1Attack << "s, EG1Decay1=" << pDimensionRegion->EG1Decay1 << "s,  EG1Sustain=" << pDimensionRegion->EG1Sustain << "permille, EG1Release=" << pDimensionRegion->EG1Release << "s, EG1Decay2=" << pDimensionRegion->EG1Decay2 << "s, EG1Hold=" << pDimensionRegion->EG1Hold << endl;
        cout << "                EG2PreAttack=" << pDimensionRegion->EG2PreAttack << "permille, EG2Attack=" << pDimensionRegion->EG2Attack << "s, EG2Decay1=" << pDimensionRegion->EG2Decay1 << "s,  EG2Sustain=" << pDimensionRegion->EG2Sustain << "permille, EG2Release=" << pDimensionRegion->EG2Release << "s, EG2Decay2=" << pDimensionRegion->EG2Decay2 << "s" << endl;
        cout << "                VCFEnabled=" << pDimensionRegion->VCFEnabled << ", VCFType=" << pDimensionRegion->VCFType << ", VCFCutoff=" << (int) pDimensionRegion->VCFCutoff << ",  VCFResonance=" << (int) pDimensionRegion->VCFResonance << ", VCFCutoffController=" << pDimensionRegion->VCFCutoffController << endl;

        dimensionRegions++;
    }
}

void PrintUsage() {
    cout << "gigdump - parses Gigasampler files and prints out the content." << endl;
    cout << endl;
    cout << "Usage: gigdump FILE" << endl;
}
