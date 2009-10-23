/***************************************************************************
 *                                                                         *
 *   libsf2 - C++ cross-platform SF2 format file access library            *
 *                                                                         *
 *   Copyright (C) 2009 by Grigor Iliev  <grigor@grigoriliev.com>          *
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

#ifndef __SF2_SF_H__
#define __SF2_SF_H__

#include "RIFF.h"

#include <vector>


#if WORDS_BIGENDIAN
#define ENDIAN_SWAP(x) \
        ( (x>>24) | ((x<<8) & 0x00FF0000) | ((x>>8) & 0x0000FF00) | (x<<24) )
#else
#define ENDIAN_SWAP(x) (x)
#endif

#define RIFF_ID(x) ENDIAN_SWAP( (*((uint32_t*) x)) )


#define RIFF_TYPE_SF2	RIFF_ID("sfbk")

// Level 0
#define LIST_TYPE_INFO	RIFF_ID("INFO")
#define LIST_TYPE_SDTA	RIFF_ID("sdta")
#define LIST_TYPE_PDTA	RIFF_ID("pdta")

// Level 1
//<INFO-list>
#define CHUNK_ID_IFIL	RIFF_ID("ifil")
#define CHUNK_ID_ISNG	RIFF_ID("isng")
#define CHUNK_ID_INAM	RIFF_ID("INAM")
#define CHUNK_ID_IROM	RIFF_ID("irom")
#define CHUNK_ID_IVER	RIFF_ID("iver")
#define CHUNK_ID_ICRD	RIFF_ID("ICRD")
#define CHUNK_ID_IENG	RIFF_ID("IENG")
#define CHUNK_ID_IPRD	RIFF_ID("IPRD")
#define CHUNK_ID_ICOP	RIFF_ID("ICOP")
#define CHUNK_ID_ICMT	RIFF_ID("ICMT")
#define CHUNK_ID_ISFT	RIFF_ID("ISFT")

//<sdta-list>
#define CHUNK_ID_SMPL	RIFF_ID("smpl")
#define CHUNK_ID_SM24	RIFF_ID("sm24")

//<pdta-list>
#define CHUNK_ID_PHDR	RIFF_ID("phdr")
#define CHUNK_ID_PBAG	RIFF_ID("pbag")
#define CHUNK_ID_PMOD	RIFF_ID("pmod")
#define CHUNK_ID_PGEN	RIFF_ID("pgen")
#define CHUNK_ID_INST	RIFF_ID("inst")
#define CHUNK_ID_IBAG	RIFF_ID("ibag")
#define CHUNK_ID_IMOD	RIFF_ID("imod")
#define CHUNK_ID_IGEN	RIFF_ID("igen")
#define CHUNK_ID_SHDR	RIFF_ID("shdr")

#define NONE 0x1ffffff

namespace sf2 {
    typedef struct _PresetBag {
        uint16_t GenNdx;
        uint16_t ModNdx;
    } PresetBag;

    typedef uint16_t SFModulator;
    typedef uint16_t SFGenerator;
    typedef uint16_t SFTransform;

    typedef struct _ModList {
        SFModulator  ModSrcOper;
        SFGenerator  ModDestOper;
        uint16_t     ModAmount;
        SFModulator  ModAmtSrcOper;
        SFTransform  ModTransOper;
    } ModList;

    typedef struct _RangesType {
        uint8_t byLo;
        uint8_t byHi;
    } RangesType;

    typedef union _GenAmountType {
        RangesType  ranges;
        short       shAmount;
        uint16_t    wAmount;
    } GenAmountType;

    typedef struct _GenList {
        SFGenerator    GenOper;
        GenAmountType  GenAmount;
    } GenList;

    typedef struct _InstBag {
        uint16_t InstGenNdx;
        uint16_t InstModNdx;
    } InstBag;

    typedef enum {
        START_ADDRS_OFFSET = 0,
        END_ADDRS_OFFSET,
        STARTLOOP_ADDRS_OFFSET,
        ENDLOOP_ADDRS_OFFSET ,
        START_ADDRS_COARSE_OFFSET,
        MOD_LFO_TO_PITCH,
        VIB_LFO_TO_PITCH,
        MOD_ENV_TO_PITCH,
        INITIAL_FILTER_FC,
        INITIAL_FILTER_Q,
        MOD_LFO_TO_FILTER_FC, // 10
        MOD_ENV_TO_FILTER_FC,
        END_ADDRS_COARSE_OFFSET,
        MOD_LFO_TO_VOLUME,
        UNUSED1,
        CHORUS_EFFECTS_SEND,
        REVERB_EFFECTS_SEND,
        PAN,
        UNUSED2,
        UNUSED3,
        UNUSED4, //20
        DELAY_MOD_LFO,
        FREQ_MOD_LFO,
        DELAY_VIB_LFO,
        FREQ_VIB_LFO,
        DELAY_MOD_ENV,
        ATTACK_MOD_ENV,
        HOLD_MOD_ENV,
        DECAY_MOD_ENV,
        SUSTAIN_MOD_ENV,
        RELEASEMODENV, // 30
        KEYNUM_TO_MOD_ENV_HOLD,
        KEYNUM_TO_MOD_ENV_DECAY,
        DELAY_VOL_ENV,
        ATTACK_VOL_ENV,
        HOLD_VOL_ENV,
        DECAY_VOL_ENV,
        SUSTAIN_VOL_ENV,
        RELEASE_VOL_ENV,
        KEYNUM_TO_VOL_ENV_HOLD,
        KEYNUM_TO_VOL_ENV_DECAY, //40
        INSTRUMENT,
        RESERVED1,
        KEY_RANGE,
        VEL_RANGE,
        STARTLOOP_ADDRS_COARSE_OFFSET,
        KEYNUM,
        VELOCITY,
        INITIAL_ATTENUATION,
        RESERVED2,
        ENDLOOP_ADDRS_COARSE_OFFSET, // 50
        COARSE_TUNE,
        FINE_TUNE,
        SAMPLE_ID,
        SAMPLE_MODES,
        RESERVED3,
        SCALE_TUNING,
        EXCLUSIVE_CLASS,
        OVERRIDING_ROOT_KEY,
        UNUSED5,
        END_OPER
    } SFGeneratorType;

    class Modulator {
        public:

            /**
             * General Controller palette of controllers.
             * Controller sources.
             */
            enum {
                NO_CONTROLLER = 0,
                NOTE_ON_VELOCITY = 2,
                NOTE_ON_KEY_NUMBER = 3,
                POLY_PRESSURE = 10,
                CHANNEL_PRESSURE = 13,
                PITCH_WHEEL = 14,
                PITCH_WHEEL_SENSITIVITY = 16,
                LINK = 127
            };

            /**
             * Controller type
             */
            enum {
                LINEAR = 0,
                CONCAVE,
                CONVEX,
                SWITCH
            };

            int  Type;
            bool MidiPalete;
            bool Direction;
            bool Polarity;
            int  Index;

            Modulator(SFModulator mod);
    };

    class ModulatorItem {
        public:
            Modulator    ModSrcOper;
	    SFGenerator  ModDestOper;
	    uint16_t     ModAmount;
	    Modulator    ModAmtSrcOper;
	    SFTransform  ModTransOper;

            ModulatorItem(ModList& mod);
    };


    typedef std::string String;

    class Exception : public RIFF::Exception {
        public: Exception(String Message) : RIFF::Exception(Message) { }
    };

    class Version {
        public:
            int Major;
            int Minor;

            Version(RIFF::Chunk* ck);
    };

    class Info {
        public:
            Version*  pVer;          ///< <ifil-ck>   ; Refers to the version of the Sound Font RIFF file
            String    SoundEngine;   ///< <isng-ck>   ; Refers to the target Sound Engine
            String    BankName;      ///< <INAM-ck>   ; Refers to the Sound Font Bank Name
            String    RomName;       ///< [<irom-ck>] ; Refers to the Sound ROM Name
            Version*  pRomVer;       ///< [<iver-ck>] ; Refers to the Sound ROM Version
            String    CreationDate;  ///< [<ICRD-ck>] ; Refers to the Date of Creation of the Bank
            String    Engineers;     ///< [<IENG-ck>] ; Sound Designers and Engineers for the Bank
            String    Product;       ///< [<IPRD-ck>] ; Product for which the Bank was intended
            String    Copyright;     ///< [<ICOP-ck>] ; Contains any Copyright message
            String    Comments;      ///< [<ICMT-ck>] ; Contains any Comments on the Bank
            String    Software;      ///< [<ISFT-ck>] ; The SoundFont tools used to create and alter the bank

            Info(RIFF::List* list);
            ~Info();
        private:
            static void LoadString(uint32_t ChunkID, RIFF::List* lstINFO, String& s);
    };

    class Sample {
        public:

            typedef enum {
                MONO_SAMPLE       = 1,
                RIGHT_SAMPLE      = 2,
                LEFT_SAMPLE       = 4,
                LINKED_SAMPLE     = 8,
                ROM_MONO_SAMPLE   = 0x8001,
                ROM_RIGHT_SAMPLE  = 0x8002,
                ROM_LEFT_SAMPLE   = 0x8004,
                ROM_LINKED_SAMPLE = 0x8008
            } Link;

            /** Reflects the current playback state for a sample. */
            class PlaybackState {
                public:
                    unsigned long position;          ///< Current position within the sample.
                    bool          reverse;           ///< If playback direction is currently backwards (in case there is a pingpong or reverse loop defined).
                    unsigned long loop_cycles_left;  ///< How many times the loop has still to be passed, this value will be decremented with each loop cycle.
            };

            /** Pointer address and size of a buffer. */
            struct buffer_t {
                void*         pStart;            ///< Points to the beginning of the buffer.
                unsigned long Size;              ///< Size of the actual data in the buffer in bytes.
                unsigned long NullExtensionSize; ///< The buffer might be bigger than the actual data, if that's the case that unused space at the end of the buffer is filled with NULLs and NullExtensionSize reflects that unused buffer space in bytes. Those NULL extensions are mandatory for differential algorithms that have to take the following data words into account, thus have to access past the buffer's boundary. If you don't know what I'm talking about, just forget this variable. :)
                buffer_t() {
                    pStart            = NULL;
                    Size              = 0;
                    NullExtensionSize = 0;
                }
            };

            String Name;

            Sample(RIFF::Chunk* ck, RIFF::Chunk* pCkSmpl, RIFF::Chunk* pCkSm24);

            String  GetName() { return Name; }
            int     GetChannelCount();
            long    GetTotalFrameCount();
            int     GetFrameSize();

            buffer_t  LoadSampleData();
            buffer_t  LoadSampleData(unsigned long SampleCount);
            buffer_t  LoadSampleDataWithNullSamplesExtension(uint NullSamplesCount);
            buffer_t  LoadSampleDataWithNullSamplesExtension(unsigned long SampleCount, uint NullSamplesCount);
            buffer_t  GetCache();
            void      ReleaseSampleData();
            unsigned long SetPos(unsigned long SampleCount);
            unsigned long GetPos();
            unsigned long Read(void* pBuffer, unsigned long SampleCount);

            unsigned long ReadAndLoop (
                void*           pBuffer,
                unsigned long   FrameCount,
                PlaybackState*  pPlaybackState
            );

        //protected:
            buffer_t      RAMCache;   ///< Buffers samples (already uncompressed) in RAM.
            RIFF::Chunk*  pCkSmpl;
            RIFF::Chunk*  pCkSm24;

        //private:
            int ChannelCount; // 2 for left and right samples

            uint32_t Start;     // in sample data points (frames)
            uint32_t End;       // in sample data points (frames)
            uint32_t StartLoop; // in sample data points (frames)
            uint32_t EndLoop;   // in sample data points (frames)
            uint32_t SampleRate;
            uint8_t  OriginalPitch;
            uint8_t  PitchCorrection;
            uint16_t SampleLink; /* If sfSampleType indicates a left or right sample, the
                                  * sample header index of the associated right or left stereo
                                  * sample respectively; zero otherwise. */
            uint16_t SampleType;
    };

    class File;
    class Instrument;

    /**
     * Instrument zone
     */
    class Region {
        public:
            int loKey, hiKey;
            int minVel, maxVel;
            int pan; // -64 - +63
            int fineTune; // -99 - +99
            int startAddrsOffset, startAddrsCoarseOffset, endAddrsOffset;
            int startloopAddrsOffset, endloopAddrsOffset;

            double EG1PreAttack;
            double EG1Attack;
            double EG1Hold;
            double EG1Decay;
            double EG1Sustain;
            double EG1Release;

            Sample* pSample;
            Instrument* pInstrument; // used when the region belongs to preset

            Region();
            Sample* GetSample() { return pSample; }
            Region* GetParent() { return this; }

            std::vector<ModulatorItem> modulators;

            friend class Instrument;
            friend class Preset;

        private:
            void SetGenerator(sf2::File* pFile, GenList& Gen);
            void SetModulator(sf2::File* pFile, ModList& Mod);
    };

    class InstrumentBase {
        public:
            String   Name;
            Region*  pGlobalRegion;

            InstrumentBase(sf2::File* pFile);
            virtual ~InstrumentBase();

            sf2::File* GetFile() { return pFile; }
            String     GetName() { return Name; }
            
            int      GetRegionCount();
            Region*  GetRegion(int idx);

            std::vector<Region*> GetRegionsOnKey(int key, uint8_t vel);

        protected:
            std::vector<Region*> regions;
            sf2::File* pFile;
    };

    class Instrument : public InstrumentBase {
        public:
            Instrument(sf2::File* pFile, RIFF::Chunk* ck);
            ~Instrument();
        //private:
            uint16_t InstBagNdx;
            
            /**
             * Load all regions (zones, bags) in the range idx1 - idx2
             */
            void LoadRegions(int idx1, int idx2);
    };

    class Preset : public InstrumentBase {
        public:
            uint16_t  PresetNum;
            uint16_t  Bank;
            uint32_t  Library;
            uint32_t  Genre;
            uint32_t  Morphology;

            Preset(sf2::File* pFile, RIFF::Chunk* ck);
            ~Preset();

        //private:
            sf2::File*  pFile;
            uint16_t    PresetBagNdx;

            /**
             * Load all regions (zones, bags) in the range idx1 - idx2
             */
            void LoadRegions(int idx1, int idx2);
    };

    class File {
        public:
            Info* pInfo;

            File(RIFF::File* pRIFF);
            ~File();

            int          GetPresetCount();
            Preset*      GetPreset(int idx);
            int          GetInstrumentCount();
            Instrument*  GetInstrument(int idx);
            int          GetSampleCount();
            Sample*      GetSample(int idx);
            void         DeleteSample(Sample* pSample);
            bool         HasSamples();

            friend class Region;
            friend class Instrument;
            friend class Preset;

        protected:
            RIFF::File*             pRIFF;
            std::vector<PresetBag>  PresetBags;
            std::vector<ModList>    PresetModLists;
            std::vector<GenList>    PresetGenLists;
            std::vector<InstBag>    InstBags;
            std::vector<ModList>    InstModLists;
            std::vector<GenList>    InstGenLists;

        private:
            std::vector<Preset*> Presets;
            std::vector<Instrument*> Instruments;
            std::vector<Sample*> Samples;
    };

    String libraryName();
    String libraryVersion();

} // namespace sf2
#endif // __SF2_SF_H__
