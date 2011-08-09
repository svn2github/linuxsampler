/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2008 Anders Dahnielson <anders@dahnielson.com>          *
 *   Copyright (C) 2009 - 2011 Anders Dahnielson and Grigor Iliev          *
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

#ifndef LIBSFZ_SFZ_H
#define LIBSFZ_SFZ_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "../common/SampleFile.h"
#include "../common/SampleManager.h"
#include "../../common/ArrayList.h"

#define TRIGGER_ATTACK  ((unsigned char) (1 << 0)) // 0x01
#define TRIGGER_RELEASE ((unsigned char) (1 << 1)) // 0x02
#define TRIGGER_FIRST   ((unsigned char) (1 << 2)) // 0x04
#define TRIGGER_LEGATO  ((unsigned char) (1 << 3)) // 0x08

namespace sfz
{
    // Forward declarations
    class Articulation;
    class Region;
    class Group;
    class Instrument;
    class File;
    class LookupTable;
    class SampleManager;

    class Sample : public LinuxSampler::SampleFileBase<Region> {
        private:
            int  End;
            long TotalFrames;
            
        public:
            Sample(String File, bool DontClose = false, uint offset = 0, int end = -2 /* -2 means unspecified */)
                  : LinuxSampler::SampleFileBase<Region>(File, DontClose)
            {
                Offset = offset;
                End = end;
                
                long tfc = LinuxSampler::SampleFileBase<Region>::GetTotalFrameCount();
                if (Offset >= tfc) {
                    std::cerr << "Offset for file '" << this->GetFile() << "' too long (" << Offset << ")" << std::endl;
                    Offset = 0;
                }
                
                if (End == -2 || End > tfc) TotalFrames = tfc;
                else if (End == -1 || End < Offset) TotalFrames = 0;
                else TotalFrames = End;
            }
            virtual ~Sample() { }
            
            virtual long GetTotalFrameCount() { return TotalFrames; }
            
            friend class SampleManager;
    };

    // Enumerations
    enum sw_vel_t    { VEL_CURRENT, VEL_PREVIOUS };
    enum off_mode_t  { OFF_FAST, OFF_NORMAL };
    enum loop_mode_t { NO_LOOP, ONE_SHOT, LOOP_CONTINUOUS, LOOP_SUSTAIN, LOOP_UNSET };
    enum curve_t     { GAIN, POWER };
    enum filter_t    { LPF_1P, HPF_1P, BPF_1P, BRF_1P, APF_1P,
                       LPF_2P, HPF_2P, BPF_2P, BRF_2P, PKF_2P,
                       LPF_4P, HPF_4P,
                       LPF_6P, HPF_6P };

    typedef unsigned char trigger_t;
    typedef unsigned char uint8_t;

    class SampleManager : public LinuxSampler::SampleManager<Sample, Region> {
    public:
        Sample* FindSample(std::string samplePath, uint offset, int end);

    protected:
        virtual void OnSampleInUse(Sample* pSample) {
            pSample->Open();
        }

        virtual void OnSampleInNotUse(Sample* pSample) {
            pSample->Close();
        }
    };
    
    class CC {
        public:
            uint8_t   Controller;  ///< MIDI controller number.
            short int Curve;
            float     Influence;   ///< Controller Value.
            float     Smooth;      ///< The speed of parameter change in milliseconds
            
            CC(uint8_t Controller = 0, float Influence = 0.0f, short int Curve = -1, float Smooth = 0) {
                this->Controller = Controller;
                this->Influence  = Influence;
                this->Curve      = Curve;
                this->Smooth     = Smooth;
            }
                    
            CC(const CC& cc) { Copy(cc); }
            void operator=(const CC& cc) { Copy(cc); }
                    
            void Copy(const CC& cc) {
                Controller = cc.Controller;
                Influence  = cc.Influence;
                Curve      = cc.Curve;
                Smooth     = cc.Smooth;
            }
    };

    /////////////////////////////////////////////////////////////
    // class Exception

    class Exception :
        public std::runtime_error
    {
        public:
        Exception(const std::string& msg) :
            runtime_error(msg)
        {
        }

        std::string Message()
        {
            return what();
        }

        void PrintMessage()
        {
            std::cerr << what() << std::endl << std::flush;
        }
    };

    /////////////////////////////////////////////////////////////
    // class optional

    //  Handy class nicked from LinuxSampler...
    //  Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck
    //  Copyright (C) 2005, 2006 Christian Schoenebeck

    class optional_base
    {
        public:
        class nothing_t { public: nothing_t() {} };
        static const nothing_t nothing;
    };

    template<class T>
    class optional :
        public optional_base
    {
        public:
        optional()
        {
            initialized = false;
        }

        optional(T data)
        {
            this->data  = data;
            initialized = true;
        }

        optional(nothing_t)
        {
            initialized = false;
        }

        template <class T_inner>
        optional(T_inner data)
        {
            this->data  = T(data);
            initialized = true;
        }

        const T& get() const throw (Exception)
        {
            if (!initialized) throw Exception("optional variable not initialized");
            return data;
        }

        T& get() throw (Exception)
        {
            if (!initialized) throw Exception("optional variable not initialized");
            return data;
        }

        void unset()
        {
            initialized = false;
        }

        optional& operator =(const optional& arg) throw (Exception)
        {
            if (!arg.initialized) {
                            initialized = false;
                        } else {
                            this->data  = arg.data;
                            initialized = true;
                        }
            return *this;
        }

        optional& operator =(const T& arg)
        {
            this->data  = arg;
            initialized = true;
            return *this;
        }

        const T& operator *() const throw (Exception) { return get(); }
        T&       operator *()       throw (Exception) { return get(); }

        const T* operator ->() const throw (Exception)
        {
            if (!initialized) throw Exception("optional variable not initialized");
            return &data;
        }

        T* operator ->() throw (Exception)
        {
            if (!initialized) throw Exception("optional variable not initialized");
            return &data;
        }

        operator bool()   const { return initialized; }
        bool operator !() const { return !initialized; }

        protected:
        T    data;
        bool initialized;
    };

    /////////////////////////////////////////////////////////////
    // class Articulation

    // Articulation containing all performance parameters for synthesis
    class Articulation
    {
    public:
        Articulation();
        virtual ~Articulation();
    };

    class EGNode
    {
    public:
        float time;
        float level;
        float shape;
        float curve;
        LinuxSampler::ArrayList<CC> time_oncc;
        LinuxSampler::ArrayList<CC> level_oncc;
        
        EGNode();
        EGNode(const EGNode& egNode) { Copy(egNode); }
        void operator=(const EGNode& egNode) { Copy(egNode); }
        void Copy(const EGNode& egNode);
    };

    class EG
    {
    public:
        LinuxSampler::ArrayList<EGNode> node;
        int sustain;
        int loop;
        int loop_count;
        float amplitude;
        float cutoff;
        EG();
        EG(const EG& eg) { Copy(eg); }
        void operator=(const EG& eg) { Copy(eg); }
        void Copy(const EG& eg);
    };

    class LFO
    {
    public:
        float delay; // 0 to 100 seconds
        float freq; // 0 to 20 Hz
        float fade; // 0 to 100 seconds
        float phase; // 0 to 360 degrees
        uint  wave; // 0 to 4294967296
        float volume; // -144 to 6 dB
        int   pitch; // -9600 to 9600 cents
        int   cutoff; // -9600 to 9600 cents
        float resonance; // 0 to 40 dB
        float pan; // -100 to 100 %
        
        LinuxSampler::ArrayList<CC> delay_oncc; // 0 to 100 seconds
        LinuxSampler::ArrayList<CC> freq_oncc; // 0 to 20 Hz
        LinuxSampler::ArrayList<CC> freq_smoothcc; // 0 to ? milliseconds
        LinuxSampler::ArrayList<CC> fade_oncc; // 0 to 100 seconds
        LinuxSampler::ArrayList<CC> phase_oncc; // 0 to 360 degrees
        LinuxSampler::ArrayList<CC> volume_oncc; // -144 to 6 dB
        LinuxSampler::ArrayList<CC> volume_smoothcc; // 0 to ? milliseconds
        LinuxSampler::ArrayList<CC> pitch_oncc;
        LinuxSampler::ArrayList<CC> pitch_smoothcc; // 0 to ? milliseconds
        LinuxSampler::ArrayList<CC> pan_oncc; // -100 to 100 %
        LinuxSampler::ArrayList<CC> pan_smoothcc; // 0 to ? milliseconds
        LinuxSampler::ArrayList<CC> cutoff_oncc; // -9600 to 9600 cents
        LinuxSampler::ArrayList<CC> cutoff_smoothcc; // 0 to ? milliseconds
        LinuxSampler::ArrayList<CC> resonance_oncc; // 0 to 40 dB
        LinuxSampler::ArrayList<CC> resonance_smoothcc; // 0 to ? milliseconds
        
        LFO();
        LFO(const LFO& lfo) { Copy(lfo); }
        void operator=(const LFO& lfo) { Copy(lfo); }
        void Copy(const LFO& lfo);
    };

    // Fixed size array with copy-on-write semantics
    template<class T>
    class Array
    {
    private:
        struct Rep {
            int refcount;
            T a[128];

            Rep() : refcount(1) { }
            static void release(Rep* rep) {
                if (!--rep->refcount) delete rep;
            }
        } *ptr;
    public:
        Array() : ptr(0) { }
        ~Array() { Rep::release(ptr); }

        Array& operator=(const Array& array) {
            if (this != &array) {
                ptr = array.ptr;
                if (ptr) ptr->refcount++;
            }
            return *this;
        }

        const T& operator[](int i) const { return ptr->a[i]; }

        void set(int i, const T& v) {
            if (!ptr) {
                ptr = new Rep;
            } else if (ptr->refcount > 1 && ptr->a[i] != v) {
                Rep* newptr = new Rep(*ptr);
                newptr->refcount = 1;
                Rep::release(ptr);
                ptr = newptr;
            }
            ptr->a[i] = v;
        }
    };

    /////////////////////////////////////////////////////////////
    // class Definition

    // Base definition used by groups and regions
    class Definition
    {
    public:
        Definition();
        virtual ~Definition();

        // sample definition
        std::string sample;

        // input controls
        int   lochan;    int   hichan;
        int   lokey;     int   hikey;
        int   lovel;     int   hivel;
        Array<int> locc; Array<int> hicc;
        int   lobend;    int   hibend;
        float lobpm;     float hibpm;
        int   lochanaft; int   hichanaft;
        int   lopolyaft; int   hipolyaft;
        int   loprog;    int   hiprog;
        float lorand;    float hirand;
        float lotimer;   float hitimer;

        int seq_length;
        int seq_position;

        Array<int> start_locc; Array<int> start_hicc;
        Array<int> stop_locc;  Array<int> stop_hicc;

        int sw_lokey;    int sw_hikey;
        int sw_last;
        int sw_down;
        int sw_up;
        int sw_previous;
        sw_vel_t sw_vel;

        trigger_t trigger;

        uint group;
        uint off_by;
        off_mode_t off_mode;

        Array<int> on_locc; Array<int> on_hicc;

        // sample player
        optional<int> count;
        optional<float> delay; optional<float> delay_random; Array<optional<float> > delay_oncc;
        optional<int> delay_beats; optional<int> stop_beats;
        optional<int> delay_samples; Array<optional<int> > delay_samples_oncc;
        optional<int> end;
        optional<float> loop_crossfade;
        optional<uint> offset; optional<int> offset_random; Array<optional<int> > offset_oncc;
        loop_mode_t loop_mode;
        optional<int> loop_start; optional<int> loop_end;
        optional<int> sync_beats;
        optional<int> sync_offset;

        // amplifier
        float volume;
        float pan;
        float width;
        float position;
        float amp_keytrack; int amp_keycenter; float amp_veltrack; Array<float> amp_velcurve; float amp_random;
        float rt_decay;
        Array<float> gain_oncc;
        int xfin_lokey; int xfin_hikey;
        int xfout_lokey; int xfout_hikey;
        curve_t xf_keycurve;
        int xfin_lovel; int xfin_hivel;
        int xfout_lovel; int xfout_hivel;
        curve_t xf_velcurve;
        Array<int> xfin_locc; Array<int> xfin_hicc;
        Array<int> xfout_locc; Array<int> xfout_hicc;
        curve_t xf_cccurve;

        // pitch
        int transpose;
        int tune;
        int pitch_keycenter; int pitch_keytrack; int pitch_veltrack; int pitch_random;
        int bend_up; int bend_down; int bend_step;

        // filter
        filter_t fil_type; filter_t fil2_type;
        optional<float> cutoff; optional<float> cutoff2;
        Array<int> cutoff_oncc; Array<int> cutoff2_oncc;
        int cutoff_cc; // TODO: this is just a temporary fix to avoid
                       // looping through the cutoff_oncc array
        Array<int> cutoff_smoothcc; Array<int> cutoff2_smoothcc;
        Array<int> cutoff_stepcc; Array<int> cutoff2_stepcc;
        Array<int> cutoff_curvecc; Array<int> cutoff2_curvecc;
        int cutoff_chanaft; int cutoff2_chanaft;
        int cutoff_polyaft; int cutoff2_polyaft;
        float resonance; float resonance2;
        Array<int> resonance_oncc; Array<int> resonance2_oncc;
        Array<int> resonance_smoothcc; Array<int> resonance2_smoothcc;
        Array<int> resonance_stepcc; Array<int> resonance2_stepcc;
        Array<int> resonance_curvecc; Array<int> resonance2_curvecc;
        int fil_keytrack; int fil2_keytrack;
        int fil_keycenter; int fil2_keycenter;
        int fil_veltrack; int fil2_veltrack;
        int fil_random; int fil2_random;

        // per voice equalizer
        float eq1_freq; float eq2_freq; float eq3_freq;
        Array<float> eq1_freq_oncc; Array<float> eq2_freq_oncc; Array<float> eq3_freq_oncc;
        float eq1_vel2freq; float eq2_vel2freq; float eq3_vel2freq;
        float eq1_bw; float eq2_bw; float eq3_bw;
        Array<float> eq1_bw_oncc; Array<float> eq2_bw_oncc; Array<float> eq3_bw_oncc;
        float eq1_gain; float eq2_gain; float eq3_gain;
        Array<float> eq1_gain_oncc; Array<float> eq2_gain_oncc; Array<float> eq3_gain_oncc;
        float eq1_vel2gain; float eq2_vel2gain; float eq3_vel2gain;

        //Deprecated (from version 1)
        float ampeg_delay, ampeg_start, ampeg_attack, ampeg_hold, ampeg_decay, ampeg_sustain, ampeg_release;
        float ampeg_vel2delay, ampeg_vel2attack, ampeg_vel2hold, ampeg_vel2decay, ampeg_vel2sustain, ampeg_vel2release;
        LinuxSampler::ArrayList<CC> ampeg_delaycc, ampeg_startcc, ampeg_attackcc, ampeg_holdcc;
        LinuxSampler::ArrayList<CC> ampeg_decaycc, ampeg_sustaincc, ampeg_releasecc;
        float fileg_delay, fileg_start, fileg_attack, fileg_hold, fileg_decay, fileg_sustain, fileg_release;
        float fileg_vel2delay, fileg_vel2attack, fileg_vel2hold, fileg_vel2decay, fileg_vel2sustain, fileg_vel2release;
        float pitcheg_delay, pitcheg_start, pitcheg_attack, pitcheg_hold, pitcheg_decay, pitcheg_sustain, pitcheg_release;
        float pitcheg_vel2delay, pitcheg_vel2attack, pitcheg_vel2hold, pitcheg_vel2decay, pitcheg_vel2sustain, pitcheg_vel2release;
        int   fileg_depth, pitcheg_depth;
        float amplfo_delay, amplfo_fade, amplfo_freq, amplfo_depth;
        float fillfo_delay, fillfo_fade, fillfo_freq, fillfo_depth;
        float pitchlfo_delay, pitchlfo_fade, pitchlfo_freq;
        int pitchlfo_depth;
        Array<int> pitchlfo_depthcc;
        
        LinuxSampler::ArrayList<CC> pitchlfo_freqcc; // 0 to 20 Hz
        LinuxSampler::ArrayList<CC> fillfo_depthcc;  // -1200 to 1200 cents
        LinuxSampler::ArrayList<CC> fillfo_freqcc;   // 0 to 20 Hz
        LinuxSampler::ArrayList<CC> amplfo_depthcc;  // -10 to 10 dB
        LinuxSampler::ArrayList<CC> amplfo_freqcc;   // 0 to 20 Hz

        // envelope generators
        LinuxSampler::ArrayList<EG> eg;

        // low frequency oscillators
        LinuxSampler::ArrayList<LFO> lfos;
        
        LinuxSampler::ArrayList<CC> volume_oncc;
        LinuxSampler::ArrayList<CC> volume_curvecc; // used only as temporary buffer during the parsing - values are then moved to volume_oncc
        LinuxSampler::ArrayList<CC> volume_smoothcc; // used only as temporary buffer during the parsing - values are then moved to volume_oncc
    };

    class Query {
    public:
        uint8_t chan;        // MIDI channel
        uint8_t key;         // MIDI note
        uint8_t vel;         // MIDI velocity
        int bend;            // MIDI pitch bend
        uint8_t bpm;         // host BPM
        uint8_t chanaft;     // MIDI channel pressure
        uint8_t polyaft;     // MIDI polyphonic aftertouch
        uint8_t prog;        // MIDI program change
        float rand;          // generated random number
        trigger_t trig;      // how it was triggered
        uint8_t* cc;         // all 128 CC values
        float timer;         // time since previous region in the group was triggered
        bool* sw;            // state of region key switches, 128 possible values
        uint8_t last_sw_key; // last key pressed in the key switch range
        uint8_t prev_sw_key; // previous note value

        void search(const Instrument* pInstrument);
        void search(const Instrument* pInstrument, int triggercc);
        Region* next();
    private:
        LinuxSampler::ArrayList<Region*>* pRegionList;
        int regionIndex;
    };

    /////////////////////////////////////////////////////////////
    // class Region

    /// Defines Region information of an Instrument
    class Region :
        public Definition
    {
    public:
        Region();
        virtual ~Region();

        Sample* pSample;
        Sample* GetSample(bool create = true);
        void DestroySampleIfNotUsed();

        Region*      GetParent() { return this; }; // needed by EngineBase
        Instrument*  GetInstrument() { return pInstrument; }
        void         SetInstrument(Instrument* pInstrument) { this->pInstrument = pInstrument; }

        bool HasLoop();
        uint GetLoopStart();
        uint GetLoopEnd();
        uint GetLoopCount();

        /// Return true if region is triggered by key. Region is
        /// assumed to come from a search in the lookup table.
        bool OnKey(const Query& q);

        /// Return an articulation for the current state
        Articulation* GetArticulation(int bend, uint8_t bpm, uint8_t chanaft, uint8_t polyaft, uint8_t* cc);

        // unique region id
        int id;

    private:
        Instrument* pInstrument;
        int seq_counter;
    };
    
    class Curve {
        public:
            float v[128];
            Curve() { for (int i = 0; i < 128; i++) v[i] = 0; }
            Curve(const Curve& curve) { Copy(curve); }
            void operator=(const Curve& curve) { Copy(curve); }
            void Copy(const Curve& curve) { for (int i = 0; i < 128; i++) v[i] = curve.v[i]; }
    };

    /////////////////////////////////////////////////////////////
    // class Instrument

    /// Provides all necessary information for the synthesis of an Instrument
    class Instrument : public SampleManager
    {
    public:
        Instrument(std::string name = "Unknown", SampleManager* pSampleManager = NULL);
        virtual ~Instrument();

        std::string GetName() { return name; }
        SampleManager* GetSampleManager() { return pSampleManager; }

        bool DestroyRegion(Region* pRegion);
        bool HasKeyBinding(uint8_t key);
        bool HasKeySwitchBinding(uint8_t key);

        /// List of Regions belonging to this Instrument
        std::vector<Region*> regions;
        ::LinuxSampler::ArrayList<Curve> curves;

        friend class File;
        friend class Query;

    private:
        std::string name;
        std::vector<bool> KeyBindings;
        std::vector<bool> KeySwitchBindings;
        SampleManager* pSampleManager;
        LookupTable* pLookupTable;
        LookupTable* pLookupTableCC[128];
    };

    /////////////////////////////////////////////////////////////
    // class Group

    /// A Group act just as a template containing Region default values
    class Group :
        public Definition
    {
    public:
        Group();
        virtual ~Group();

        /// Reset Group to default values
        void Reset();

        /// Create a new Region
        Region* RegionFactory();

        // id counter
        int id;

    };

    /////////////////////////////////////////////////////////////
    // class File

    /// Parses SFZ files and provides abstract access to the data
    class File
    {
    public:
        /// Load an existing SFZ file
        File(std::string file, SampleManager* pSampleManager = NULL);
        virtual ~File();

        /// Returns a pointer to the instrument object
        Instrument* GetInstrument();

    private:
        void  push_header(std::string token);
        void  push_opcode(std::string token);
        int parseKey(const std::string& value);
        EG& eg(int x);
        EGNode& egnode(int x, int y);
        LFO& lfo(int x);
        void copyCurves(LinuxSampler::ArrayList<CC>& curves, LinuxSampler::ArrayList<CC>& dest);
        void copySmoothValues(LinuxSampler::ArrayList<CC>& smooths, LinuxSampler::ArrayList<CC>& dest);

        std::string currentDir;
        /// Pointer to the Instrument belonging to this file
        Instrument* _instrument;

        // state variables
        enum section_t { UNKNOWN, GROUP, REGION, CONTROL, CURVE };
        section_t _current_section;
        Region* _current_region;
        Group* _current_group;
        Curve* _current_curve;
        Definition* pCurDef;

        // control header directives
        std::string default_path;
        int octave_offset;
        int note_offset;
    };

} // !namespace sfz

#endif // !LIBSFZ_SFZ_H
