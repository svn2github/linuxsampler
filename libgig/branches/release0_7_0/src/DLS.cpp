/***************************************************************************
 *                                                                         *
 *   libgig - C++ cross-platform Gigasampler format file loader library    *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Christian Schoenebeck                     *
 *                               <cuse@users.sourceforge.net>              *
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

#include "DLS.h"

namespace DLS {

// *************** Connection  ***************
// *

    void Connection::Init(conn_block_t* Header) {
        Source               = (conn_src_t) Header->source;
        Control              = (conn_src_t) Header->control;
        Destination          = (conn_dst_t) Header->destination;
        Scale                = Header->scale;
        SourceTransform      = (conn_trn_t) CONN_TRANSFORM_SRC(Header->transform);
        ControlTransform     = (conn_trn_t) CONN_TRANSFORM_CTL(Header->transform);
        DestinationTransform = (conn_trn_t) CONN_TRANSFORM_DST(Header->transform);
        SourceInvert         = CONN_TRANSFORM_INVERT_SRC(Header->transform);
        SourceBipolar        = CONN_TRANSFORM_BIPOLAR_SRC(Header->transform);
        ControlInvert        = CONN_TRANSFORM_INVERT_CTL(Header->transform);
        ControlBipolar       = CONN_TRANSFORM_BIPOLAR_CTL(Header->transform);
    }



// *************** Articulation  ***************
// *

    Articulation::Articulation(RIFF::List* artList) {
        if (artList->GetListType() != LIST_TYPE_ART2 &&
            artList->GetListType() != LIST_TYPE_ART1) {
              throw DLS::Exception("<art1-list> or <art2-list> chunk expected");
        }
        uint32_t headerSize = artList->ReadUint32();
        Connections         = artList->ReadUint32();
        artList->SetPos(headerSize);

        pConnections = new Connection[Connections];
        Connection::conn_block_t connblock;
        for (uint32_t i = 0; i <= Connections; i++) {
            artList->Read(&connblock.source, 1, 2);
            artList->Read(&connblock.control, 1, 2);
            artList->Read(&connblock.destination, 1, 2);
            artList->Read(&connblock.transform, 1, 2);
            artList->Read(&connblock.scale, 1, 4);
            pConnections[i].Init(&connblock);
        }
    }

    Articulation::~Articulation() {
       if (pConnections) delete[] pConnections;
    }



// *************** Articulator  ***************
// *

    Articulator::Articulator(RIFF::List* ParentList) {
        pParentList    = ParentList;
        pArticulations = NULL;
    }

    Articulation* Articulator::GetFirstArticulation() {
        if (!pArticulations) LoadArticulations();
        if (!pArticulations) return NULL;
        ArticulationsIterator = pArticulations->begin();
        return (ArticulationsIterator != pArticulations->end()) ? *ArticulationsIterator : NULL;
    }

    Articulation* Articulator::GetNextArticulation() {
        if (!pArticulations) return NULL;
        ArticulationsIterator++;
        return (ArticulationsIterator != pArticulations->end()) ? *ArticulationsIterator : NULL;
    }

    void Articulator::LoadArticulations() {
        // prefer articulation level 2
        RIFF::List* lart = pParentList->GetSubList(LIST_TYPE_LAR2);
        if (!lart)  lart = pParentList->GetSubList(LIST_TYPE_LART);
        if (lart) {
            uint32_t artCkType = (lart->GetListType() == LIST_TYPE_LAR2) ? LIST_TYPE_ART2
                                                                         : LIST_TYPE_ART1;
            RIFF::List* art = lart->GetFirstSubList();
            while (art) {
                if (art->GetListType() == artCkType) {
                    if (!pArticulations) pArticulations = new ArticulationList;
                    pArticulations->push_back(new Articulation(art));
                }
                art = lart->GetNextSubList();
            }
        }
    }

    Articulator::~Articulator() {
        if (pArticulations) {
            ArticulationList::iterator iter = pArticulations->begin();
            ArticulationList::iterator end  = pArticulations->end();
            while (iter != end) {
                delete *iter;
                iter++;
            }
            delete pArticulations;
        }
    }



// *************** Info  ***************
// *

    Info::Info(RIFF::List* list) {
        if (list) {
            RIFF::List* lstINFO = list->GetSubList(LIST_TYPE_INFO);
            if (lstINFO) {
                LoadString(CHUNK_ID_INAM, lstINFO, Name);
                LoadString(CHUNK_ID_IARL, lstINFO, ArchivalLocation);
                LoadString(CHUNK_ID_ICRD, lstINFO, CreationDate);
                LoadString(CHUNK_ID_ICMT, lstINFO, Comments);
                LoadString(CHUNK_ID_IPRD, lstINFO, Product);
                LoadString(CHUNK_ID_ICOP, lstINFO, Copyright);
                LoadString(CHUNK_ID_IART, lstINFO, Artists);
                LoadString(CHUNK_ID_IGNR, lstINFO, Genre);
                LoadString(CHUNK_ID_IKEY, lstINFO, Keywords);
                LoadString(CHUNK_ID_IENG, lstINFO, Engineer);
                LoadString(CHUNK_ID_ITCH, lstINFO, Technician);
                LoadString(CHUNK_ID_ISFT, lstINFO, Software);
                LoadString(CHUNK_ID_IMED, lstINFO, Medium);
                LoadString(CHUNK_ID_ISRC, lstINFO, Source);
                LoadString(CHUNK_ID_ISRF, lstINFO, SourceForm);
                LoadString(CHUNK_ID_ICMS, lstINFO, Commissioned);
            }
        }
    }



// *************** Resource ***************
// *

    Resource::Resource(Resource* Parent, RIFF::List* lstResource) {
        pParent = Parent;

        pInfo = new Info(lstResource);

        RIFF::Chunk* ckDLSID = lstResource->GetSubChunk(CHUNK_ID_DLID);
        if (ckDLSID) {
            pDLSID = new dlsid_t;
            ckDLSID->Read(&pDLSID->ulData1, 1, 4);
            ckDLSID->Read(&pDLSID->usData2, 1, 2);
            ckDLSID->Read(&pDLSID->usData3, 1, 2);
            ckDLSID->Read(pDLSID->abData, 8, 1);
        }
        else pDLSID = NULL;
    }

    Resource::~Resource() {
        if (pDLSID) delete pDLSID;
        if (pInfo)  delete pInfo;
    }



// *************** Sampler ***************
// *

    Sampler::Sampler(RIFF::List* ParentList) {
        RIFF::Chunk* wsmp = ParentList->GetSubChunk(CHUNK_ID_WSMP);
        if (!wsmp) throw DLS::Exception("Mandatory <wsmp> chunk not found.");
        uint32_t headersize = wsmp->ReadUint32();
        UnityNote        = wsmp->ReadUint16();
        FineTune         = wsmp->ReadInt16();
        Gain             = wsmp->ReadInt32();
        SamplerOptions   = wsmp->ReadUint32();
        NoSampleDepthTruncation = SamplerOptions & F_WSMP_NO_TRUNCATION;
        NoSampleCompression     = SamplerOptions & F_WSMP_NO_COMPRESSION;
        SampleLoops             = wsmp->ReadUint32();
        pSampleLoops            = (SampleLoops) ? new sample_loop_t[SampleLoops] : NULL;
        wsmp->SetPos(headersize);
        for (uint32_t i = 0; i < SampleLoops; i++) {
            wsmp->Read(pSampleLoops + i, 4, 4);
            if (pSampleLoops[i].Size > sizeof(sample_loop_t)) { // if loop struct was extended
                wsmp->SetPos(pSampleLoops[i].Size - sizeof(sample_loop_t), RIFF::stream_curpos);
            }
        }
    }

    Sampler::~Sampler() {
        if (pSampleLoops) delete[] pSampleLoops;
    }



// *************** Sample ***************
// *

    Sample::Sample(File* pFile, RIFF::List* waveList, unsigned long WavePoolOffset) : Resource(pFile, waveList) {
        ulWavePoolOffset = WavePoolOffset - LIST_HEADER_SIZE;
        pCkFormat = waveList->GetSubChunk(CHUNK_ID_FMT);
        pCkData   = waveList->GetSubChunk(CHUNK_ID_DATA);
        if (!pCkFormat || !pCkData) throw DLS::Exception("Mandatory chunks in wave list not found.");

        // common fields
        FormatTag              = pCkFormat->ReadUint16();
        Channels               = pCkFormat->ReadUint16();
        SamplesPerSecond       = pCkFormat->ReadUint32();
        AverageBytesPerSecond  = pCkFormat->ReadUint32();
        BlockAlign             = pCkFormat->ReadUint16();

        // PCM format specific
        if (FormatTag == WAVE_FORMAT_PCM) {
            BitDepth     = pCkFormat->ReadUint16();
            FrameSize    = (FormatTag == WAVE_FORMAT_PCM) ? (BitDepth / 8) * Channels
                                                          : 0;
            SamplesTotal = (FormatTag == WAVE_FORMAT_PCM) ? pCkData->GetSize() / FrameSize
                                                          : 0;
        }
        else {
            BitDepth     = 0;
            FrameSize    = 0;
            SamplesTotal = 0;
        }
    }

    void* Sample::LoadSampleData() {
        return pCkData->LoadChunkData();
    }

    void Sample::ReleaseSampleData() {
        pCkData->ReleaseChunkData();
    }

    /**
     * Sets the position within the sample (in sample points, not in
     * bytes). Use this method and <i>Read()</i> if you don't want to load
     * the sample into RAM, thus for disk streaming.
     *
     * @param SampleCount  number of sample points
     * @param Whence       to which relation \a SampleCount refers to
     */
    unsigned long Sample::SetPos(unsigned long SampleCount, RIFF::stream_whence_t Whence) {
        if (FormatTag != WAVE_FORMAT_PCM) return 0; // failed: wave data not PCM format
        unsigned long orderedBytes = SampleCount * FrameSize;
        unsigned long result = pCkData->SetPos(orderedBytes, Whence);
        return (result == orderedBytes) ? SampleCount
                                        : result / FrameSize;
    }

    /**
     * Reads \a SampleCount number of sample points from the current
     * position into the buffer pointed by \a pBuffer and increments the
     * position within the sample. Use this method and <i>SetPos()</i> if you
     * don't want to load the sample into RAM, thus for disk streaming.
     *
     * @param pBuffer      destination buffer
     * @param SampleCount  number of sample points to read
     */
    unsigned long Sample::Read(void* pBuffer, unsigned long SampleCount) {
        if (FormatTag != WAVE_FORMAT_PCM) return 0; // failed: wave data not PCM format
        return pCkData->Read(pBuffer, SampleCount, FrameSize); // FIXME: channel inversion due to endian correction?
    }



// *************** Region ***************
// *

    Region::Region(Instrument* pInstrument, RIFF::List* rgnList) : Resource(pInstrument, rgnList), Articulator(rgnList), Sampler(rgnList) {
        pCkRegion = rgnList;

        RIFF::Chunk* rgnh = rgnList->GetSubChunk(CHUNK_ID_RGNH);
        rgnh->Read(&KeyRange, 2, 2);
        rgnh->Read(&VelocityRange, 2, 2);
        uint16_t optionflags = rgnh->ReadUint16();
        SelfNonExclusive = optionflags & F_RGN_OPTION_SELFNONEXCLUSIVE;
        KeyGroup = rgnh->ReadUint16();
        // Layer is optional
        if (rgnh->RemainingBytes() >= sizeof(uint16_t)) {
            rgnh->Read(&Layer, 1, sizeof(uint16_t));
        }
        else Layer = 0;

        RIFF::Chunk* wlnk = rgnList->GetSubChunk(CHUNK_ID_WLNK);
        optionflags  = wlnk->ReadUint16();
        PhaseMaster  = optionflags & F_WAVELINK_PHASE_MASTER;
        MultiChannel = optionflags & F_WAVELINK_MULTICHANNEL;
        PhaseGroup         = wlnk->ReadUint16();
        Channel            = wlnk->ReadUint32();
        WavePoolTableIndex = wlnk->ReadUint32();

        pSample = NULL;
    }

    Region::~Region() {
    }

    Sample* Region::GetSample() {
        if (pSample) return pSample;
        File* file = (File*) GetParent()->GetParent();
        unsigned long soughtoffset = file->pWavePoolTable[WavePoolTableIndex];
        Sample* sample = file->GetFirstSample();
        while (sample) {
            if (sample->ulWavePoolOffset == soughtoffset) return (pSample = sample);
            sample = file->GetNextSample();
        }
        return NULL;
    }



// *************** Instrument ***************
// *

    Instrument::Instrument(File* pFile, RIFF::List* insList) : Resource(pFile, insList), Articulator(insList) {
        pCkInstrument = insList;

        RIFF::Chunk* insh = pCkInstrument->GetSubChunk(CHUNK_ID_INSH);
        if (!insh) throw DLS::Exception("Mandatory chunks in <lins> list chunk not found.");
        Regions = insh->ReadUint32();
        midi_locale_t locale;
        insh->Read(&locale, 2, 4);
        MIDIProgram    = locale.instrument;
        IsDrum         = locale.bank & DRUM_TYPE_MASK;
        MIDIBankCoarse = (uint8_t) MIDI_BANK_COARSE(locale.bank);
        MIDIBankFine   = (uint8_t) MIDI_BANK_FINE(locale.bank);
        MIDIBank       = MIDI_BANK_MERGE(MIDIBankCoarse, MIDIBankFine);

        pRegions   = NULL;
    }

    Region* Instrument::GetFirstRegion() {
        if (!pRegions) LoadRegions();
        if (!pRegions) return NULL;
        RegionsIterator = pRegions->begin();
        return (RegionsIterator != pRegions->end()) ? *RegionsIterator : NULL;
    }

    Region* Instrument::GetNextRegion() {
        if (!pRegions) return NULL;
        RegionsIterator++;
        return (RegionsIterator != pRegions->end()) ? *RegionsIterator : NULL;
    }

    void Instrument::LoadRegions() {
        RIFF::List* lrgn = pCkInstrument->GetSubList(LIST_TYPE_LRGN);
        if (!lrgn) throw DLS::Exception("Mandatory chunks in <ins > chunk not found.");
        uint32_t regionCkType = (lrgn->GetSubList(LIST_TYPE_RGN2)) ? LIST_TYPE_RGN2 : LIST_TYPE_RGN; // prefer regions level 2
        RIFF::List* rgn = lrgn->GetFirstSubList();
        while (rgn) {
            if (rgn->GetListType() == regionCkType) {
                if (!pRegions) pRegions = new RegionList;
                pRegions->push_back(new Region(this, rgn));
            }
            rgn = lrgn->GetNextSubList();
        }
    }

    Instrument::~Instrument() {
        if (pRegions) {
            RegionList::iterator iter = pRegions->begin();
            RegionList::iterator end  = pRegions->end();
            while (iter != end) {
                delete *iter;
                iter++;
            }
            delete pRegions;
        }
    }



// *************** File ***************
// *

    File::File(RIFF::File* pRIFF) : Resource(NULL, pRIFF) {
        if (!pRIFF) throw DLS::Exception("NULL pointer reference to RIFF::File object.");
        this->pRIFF = pRIFF;

        RIFF::Chunk* ckVersion = pRIFF->GetSubChunk(CHUNK_ID_VERS);
        if (ckVersion) {
            pVersion = new version_t;
            ckVersion->Read(pVersion, 4, 2);
        }
        else pVersion = NULL;

        RIFF::Chunk* colh = pRIFF->GetSubChunk(CHUNK_ID_COLH);
        if (!colh) throw DLS::Exception("Mandatory chunks in RIFF list chunk not found.");
        Instruments = colh->ReadUint32();

        RIFF::Chunk* ptbl = pRIFF->GetSubChunk(CHUNK_ID_PTBL);
        if (!ptbl) throw DLS::Exception("Mandatory <ptbl> chunk not found.");
        uint32_t headersize = ptbl->ReadUint32();
        WavePoolCount  = ptbl->ReadUint32();
        pWavePoolTable = new uint32_t[WavePoolCount];
        ptbl->SetPos(headersize);
        ptbl->Read(pWavePoolTable, WavePoolCount, sizeof(uint32_t));

        pSamples     = NULL;
        pInstruments = NULL;
        Instruments  = 0;
    }

    File::~File() {
        if (pInstruments) {
            InstrumentList::iterator iter = pInstruments->begin();
            InstrumentList::iterator end  = pInstruments->end();
            while (iter != end) {
                delete *iter;
                iter++;
            }
            delete pInstruments;
        }

        if (pSamples) {
            SampleList::iterator iter = pSamples->begin();
            SampleList::iterator end  = pSamples->end();
            while (iter != end) {
                delete *iter;
                iter++;
            }
            delete pSamples;
        }

        if (pWavePoolTable) delete[] pWavePoolTable;
        if (pVersion) delete pVersion;
    }

    Sample* File::GetFirstSample() {
        if (!pSamples) LoadSamples();
        if (!pSamples) return NULL;
        SamplesIterator = pSamples->begin();
        return (SamplesIterator != pSamples->end()) ? *SamplesIterator : NULL;
    }

    Sample* File::GetNextSample() {
        if (!pSamples) return NULL;
        SamplesIterator++;
        return (SamplesIterator != pSamples->end()) ? *SamplesIterator : NULL;
    }

    void File::LoadSamples() {
        RIFF::List* wvpl = pRIFF->GetSubList(LIST_TYPE_WVPL);
        if (wvpl) {
            unsigned long wvplFileOffset = wvpl->GetFilePos();
            RIFF::List* wave = wvpl->GetFirstSubList();
            while (wave) {
                if (wave->GetListType() == LIST_TYPE_WAVE) {
                    if (!pSamples) pSamples = new SampleList;
                    unsigned long waveFileOffset = wave->GetFilePos();
                    pSamples->push_back(new Sample(this, wave, waveFileOffset - wvplFileOffset));
                }
                wave = wvpl->GetNextSubList();
            }
        }
        else { // Seen a dwpl list chunk instead of a wvpl list chunk in some file (officially not DLS compliant)
            RIFF::List* dwpl = pRIFF->GetSubList(LIST_TYPE_DWPL);
            if (dwpl) {
                unsigned long dwplFileOffset = dwpl->GetFilePos();
                RIFF::List* wave = dwpl->GetFirstSubList();
                while (wave) {
                    if (wave->GetListType() == LIST_TYPE_WAVE) {
                        if (!pSamples) pSamples = new SampleList;
                        unsigned long waveFileOffset = wave->GetFilePos();
                        pSamples->push_back(new Sample(this, wave, waveFileOffset - dwplFileOffset));
                    }
                    wave = dwpl->GetNextSubList();
                }
            }
        }
    }

    Instrument* File::GetFirstInstrument() {
        if (!pInstruments) LoadInstruments();
        if (!pInstruments) return NULL;
        InstrumentsIterator = pInstruments->begin();
        return (InstrumentsIterator != pInstruments->end()) ? *InstrumentsIterator : NULL;
    }

    Instrument* File::GetNextInstrument() {
        if (!pInstruments) return NULL;
        InstrumentsIterator++;
        return (InstrumentsIterator != pInstruments->end()) ? *InstrumentsIterator : NULL;
    }

    void File::LoadInstruments() {
        RIFF::List* lstInstruments = pRIFF->GetSubList(LIST_TYPE_LINS);
        if (lstInstruments) {
            RIFF::List* lstInstr = lstInstruments->GetFirstSubList();
            while (lstInstr) {
                if (lstInstr->GetListType() == LIST_TYPE_INS) {
                    if (!pInstruments) pInstruments = new InstrumentList;
                    pInstruments->push_back(new Instrument(this, lstInstr));
                }
                lstInstr = lstInstruments->GetNextSubList();
            }
        }
    }



// *************** Exception ***************
// *

    Exception::Exception(String Message) : RIFF::Exception(Message) {
    }

    void Exception::PrintMessage() {
        std::cout << "DLS::Exception: " << Message << std::endl;
    }

} // namespace DLS
