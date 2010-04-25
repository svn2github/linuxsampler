/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2008 Anders Dahnielson <anders@dahnielson.com>          *
 *   Copyright (C) 2009 - 2010 Anders Dahnielson and Grigor Iliev          *
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

#include "sfz.h"

#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <cstring>

#include "../../common/File.h"
#include "../../common/Path.h"
#include "../../common/global_private.h"

namespace sfz
{

    Sample* SampleManager::FindSample(std::string samplePath) {
        std::map<Sample*, std::set<Region*> >::iterator it = sampleMap.begin();
        for (; it != sampleMap.end(); it++) {
            if (it->first->GetFile() == samplePath) return it->first;
        }

        return NULL;
    }

    /////////////////////////////////////////////////////////////
    // class optional

    const optional_base::nothing_t optional_base::nothing;

    /////////////////////////////////////////////////////////////
    // class Articulation

    Articulation::Articulation()
    {
    }

    Articulation::~Articulation()
    {
    }

    /////////////////////////////////////////////////////////////
    // class Definition

    Definition::Definition() :
        locc(128), hicc(128), start_locc(128), start_hicc(128), stop_locc(128),
        stop_hicc(128), on_locc(128), on_hicc(128), delay_oncc(128), delay_samples_oncc(128),
        offset_oncc(128), amp_velcurve(128), gain_oncc(128), xfin_locc(128), xfin_hicc(128),
        xfout_locc(128), xfout_hicc(128), cutoff_oncc(128), cutoff2_oncc(128), cutoff_smoothcc(128),
        cutoff2_smoothcc(128), cutoff_stepcc(128), cutoff2_stepcc(128), cutoff_curvecc(128),
        cutoff2_curvecc(128), resonance_oncc(128), resonance2_oncc(128), resonance_smoothcc(128),
        resonance2_smoothcc(128), resonance_stepcc(128), resonance2_stepcc(128),
        resonance_curvecc(128), resonance2_curvecc(128), eq1_freq_oncc(128), eq2_freq_oncc(128),
        eq3_freq_oncc(128), eq1_bw_oncc(128), eq2_bw_oncc(128), eq3_bw_oncc(128),
        eq1_gain_oncc(128), eq2_gain_oncc(128), eq3_gain_oncc(128)

    {
    }

    Definition::~Definition()
    {
    }

    /////////////////////////////////////////////////////////////
    // class Region

    Region::Region()
    {
        pSample = NULL;
        seq_counter = 1;
    }

    Region::~Region()
    {
        DestroySampleIfNotUsed();
    }

    Sample* Region::GetSample(bool create)
    {
        if(pSample == NULL && create) {
            Sample* sf = GetInstrument()->GetSampleManager()->FindSample(sample);
            if (sf != NULL) pSample = sf; // Reuse already created sample
            else pSample = new Sample(sample);
            GetInstrument()->GetSampleManager()->AddSampleConsumer(pSample, this);
        }
        return pSample;
    }

    void Region::DestroySampleIfNotUsed() {
        if (pSample == NULL) return;
        GetInstrument()->GetSampleManager()->RemoveSampleConsumer(pSample, this);
        if (!GetInstrument()->GetSampleManager()->HasSampleConsumers(pSample)) {
            GetInstrument()->GetSampleManager()->RemoveSample(pSample);
            delete pSample;
            pSample = NULL;
        }
    }

    bool
    Region::OnKey(uint8_t chan, uint8_t key, uint8_t vel,
              int bend, uint8_t bpm, uint8_t chanaft, uint8_t polyaft,
              uint8_t prog, float rand, trigger_t trig, uint8_t* cc,
              float timer, bool* sw, uint8_t last_sw_key, uint8_t prev_sw_key)
    {
        // chan        (MIDI channel)
        // key         (MIDI note)
        // vel         (MIDI velocity)

        // bend        (MIDI pitch bend)
        // bpm         (host BPM)
        // chanaft     (MIDI channel pressure)
        // polyaft     (MIDI polyphonic aftertouch)
        // prog        (MIDI program change)
        // rand        (generated random number)
        // trigger     (how it was triggered)
        // cc          (all 128 CC values)

        // timer       (time since previous region in the group was triggered)
        // sw          (the state of region key switches, 128 possible values)
        // last_sw_key (the last key pressed in the key switch range)
        // prev_sw_key (the previous note value)

        bool is_triggered (
            chan    >= lochan     &&  chan    <= hichan     &&
            key     >= lokey      &&  key     <= hikey      &&
            vel     >= lovel      &&  vel     <= hivel      &&
            bend    >= lobend     &&  bend    <= hibend     &&
            bpm     >= lobpm      &&  bpm     <  hibpm      &&
            chanaft >= lochanaft  &&  chanaft <= hichanaft  &&
            polyaft >= lopolyaft  &&  polyaft <= hipolyaft  &&
            prog    >= loprog     &&  prog    <= hiprog     &&
            rand    >= lorand     &&  rand    <  hirand     &&
            timer   >= lotimer    &&  timer   <= hitimer    &&

            ( sw_last == -1 ||
              ((sw_last >= sw_lokey && sw_last <= sw_hikey) ? (last_sw_key == sw_last) : false) ) &&

            ( sw_down == -1 ||
              ((sw_down >= sw_lokey && (sw_hikey == -1 || sw_down <= sw_hikey)) ? (sw[sw_down]) : false) )  &&

            ( sw_up   == -1 ||
              ((sw_up   >= sw_lokey && (sw_hikey == -1 || sw_up   <= sw_hikey)) ? (!sw[sw_up]) : true) )  &&

            ( sw_previous == -1 ||
              prev_sw_key == sw_previous )  &&

            ((trigger & trig) != 0)
        );

        if (!is_triggered)
            return false;

        for (int i = 0; i < 128; ++i)
        {
            if (locc[i] != -1 && hicc[i] != -1 && !(cc[i] >= locc[i] && cc[i] <= hicc[i]))
                return false;
        }

        // seq_position has to be checked last, so we know that we
        // increment the right counter
        is_triggered = (seq_counter == seq_position);
        seq_counter = (seq_counter % seq_length) + 1;

        return is_triggered;
    }

    bool
    Region::OnControl(uint8_t chan, uint8_t cont, uint8_t val,
        int bend, uint8_t bpm, uint8_t chanaft, uint8_t polyaft,
        uint8_t prog, float rand, trigger_t trig, uint8_t* cc,
        float timer, bool* sw, uint8_t last_sw_key, uint8_t prev_sw_key)
    {
        // chan      (MIDI channel)
        // cont      (MIDI controller)
        // val       (MIDI controller value)

        // bend      (MIDI pitch bend)
        // bpm       (host BPM)
        // chanaft   (MIDI channel pressure)
        // polyaft   (MIDI polyphonic aftertouch)
        // prog      (MIDI program change)
        // rand      (generated random number)
        // trigger   (how it was triggered)
        // cc        (all CC values)

        // timer       (time since previous region in the group was triggered)
        // sw          (the state of region key switches, 128 possible values)
        // last_sw_key (the last key pressed in the key switch range)
        // prev_sw_key (the previous note value)

        bool is_triggered = (
            chan    >= lochan           &&  chan    <= hichan             &&
            ((val   >= on_locc[cont]    &&  val     <= on_hicc[cont])     ||
             (val   >= start_locc[cont] &&  val     <= start_hicc[cont])) &&
            bend    >= lobend           &&  bend    <= hibend             &&
            bpm     >= lobpm            &&  bpm     <  hibpm              &&
            chanaft >= lochanaft        &&  chanaft <= hichanaft          &&
            polyaft >= lopolyaft        &&  polyaft <= hipolyaft          &&
            prog    >= loprog           &&  prog    <= hiprog             &&
            rand    >= lorand           &&  rand    <  hirand             &&
            timer   >= lotimer          &&  timer   <= hitimer            &&

            ( sw_last == -1 ||
              ((sw_last >= sw_lokey && sw_last <= sw_hikey) ? (last_sw_key == sw_last) : false) ) &&

            ( sw_down == -1 ||
              ((sw_down >= sw_lokey && (sw_hikey == -1 || sw_down <= sw_hikey)) ? (sw[sw_down]) : false) )  &&

            ( sw_up   == -1 ||
              ((sw_up   >= sw_lokey && (sw_hikey == -1 || sw_up   <= sw_hikey)) ? (!sw[sw_up]) : true) )  &&

            ( sw_previous == -1 ||
              prev_sw_key == sw_previous )  &&

            ((trigger & trig) != 0)
        );

        if (!is_triggered)
            return false;

        for (int i = 0; i < 128; ++i)
        {
            if (locc[i] != -1 && hicc[i] != -1 && !(cc[i] >= locc[i] && cc[i] <= hicc[i]))
                return false;
        }

        return true;
    }

    Articulation*
    Region::GetArticulation(int bend, uint8_t bpm, uint8_t chanaft, uint8_t polyaft, uint8_t* cc)
    {
        return new Articulation(); //todo: implement GetArticulation()
    }

    bool Region::HasLoop() {
        bool b = loop_mode == ::sfz::LOOP_CONTINUOUS || loop_mode == ::sfz::LOOP_SUSTAIN; // TODO: ONE_SHOT mode
        return b && GetLoopStart() && GetLoopEnd() && GetLoopEnd() > GetLoopStart();
    }

    uint Region::GetLoopStart() {
        return (!loop_start) ? 0 : *loop_start; // TODO: use sample loop when loop_start not defined
    }

    uint Region::GetLoopEnd() {
        return (!loop_end) ? 0 : *loop_end; // TODO: use sample loop when loop_end not defined
    }

    uint Region::GetLoopCount() {
        return (!count) ? 0 : *count;
    }

    /////////////////////////////////////////////////////////////
    // class Instrument

    Instrument::Instrument(std::string name, SampleManager* pSampleManager) : KeyBindings(128, false), KeySwitchBindings(128, false)
    {
        this->name = name;
        this->pSampleManager = pSampleManager ? pSampleManager : this;
    }

    Instrument::~Instrument()
    {
        for(int i = 0; i < regions.size(); i++) {
            delete (regions[i]);
        }
        regions.clear();
    }

    std::vector<Region*> Instrument::GetRegionsOnKey (
        uint8_t chan, uint8_t key, uint8_t vel,
        int bend, uint8_t bpm, uint8_t chanaft, uint8_t polyaft,
        uint8_t prog, float rand, trigger_t trig, uint8_t* cc,
        float timer, bool* sw, uint8_t last_sw_key, uint8_t prev_sw_key
    ) {
        std::vector<Region*> v;
        for (int i = 0; i < regions.size(); i++) {
            if (regions[i]->OnKey (
                chan, key, vel, bend, bpm, chanaft, polyaft, prog,
                rand, trig, cc, timer, sw, last_sw_key, prev_sw_key)
                    ) { v.push_back(regions[i]); }
        }

        return v;
    }

    bool Instrument::DestroyRegion(Region* pRegion) {
        for (std::vector<Region*>::iterator it = regions.begin(); it != regions.end(); it++) {
            if(*it == pRegion) {
                regions.erase(it);
                delete pRegion;
                return true;
            }
        }

        return false;
    }

    bool Instrument::HasKeyBinding(uint8_t key) {
        if (key > 127) return false;
        return KeyBindings[key];
    }

    bool Instrument::HasKeySwitchBinding(uint8_t key) {
        if (key > 127) return false;
        return KeySwitchBindings[key];
    }

    /////////////////////////////////////////////////////////////
    // class Group

    Group::Group() :
        id(0)
    {
        Reset();
    }

    Group::~Group()
    {
    }

    void
    Group::Reset()
    {
        // This is where all the default values are set.

        // sample definition default
        sample = "";

        // input control
        lochan = 1; hichan = 16;
        lokey = 0; hikey = 127;
        lovel = 0; hivel = 127;
        lobend = -8192; hibend = 8192;
        lobpm = 0; hibpm = 500;
        lochanaft = 0; hichanaft = 127;
        lopolyaft = 0; hipolyaft = 127;
        loprog = 0; hiprog = 127;
        lorand = 0.0; hirand = 1.0;
        lotimer = 0.0; hitimer = 0.0;

        seq_length = 1;
        seq_position = 1;

        sw_lokey = -1; sw_hikey = -1;
        sw_last = -1;
        sw_down = -1;
        sw_up = -1;
        sw_previous = -1;
        sw_vel = VEL_CURRENT;

        trigger = TRIGGER_ATTACK;

        group = 0;
        off_by.unset();
        off_mode = OFF_FAST;

        // sample player
        count.unset();
        delay.unset(); delay_random.unset();
        delay_beats.unset(); stop_beats.unset();
        delay_samples.unset();
        end.unset();
        loop_crossfade.unset();
        offset.unset(); offset_random.unset();
        loop_mode = NO_LOOP;
        loop_start.unset(); loop_end.unset();
        sync_beats.unset(); sync_offset.unset();

        // amplifier
        volume = 0;
        pan = 0;
        width = 100;
        position = 0;
        amp_keytrack = 0;
        amp_keycenter = 60;
        amp_veltrack = 100;
        amp_random = 0;
        rt_decay = 0;
        xfin_lokey = 0; xfin_hikey = 0;
        xfout_lokey = 127; xfout_hikey = 127;
        xf_keycurve = POWER;
        xfin_lovel = 0;    xfin_hivel = 0;
        xfout_lovel = 127; xfout_hivel = 127;
        xf_velcurve = POWER;
        xf_cccurve = POWER;

        // pitch
        transpose = 0;
        tune = 0;
        pitch_keycenter = 60;
        pitch_keytrack = 100;
        pitch_veltrack = 0;
        pitch_random = 0;
        bend_up = 200;
        bend_down = -200;
        bend_step = 1;

        // filter
        fil_type = LPF_2P;
        cutoff.unset();
        cutoff_chanaft = 0;
        cutoff_polyaft = 0;
        resonance = 0;
        fil_keytrack = 0;
        fil_keycenter = 60;
        fil_veltrack = 0;
        fil_random = 0;

        fil2_type = LPF_2P;
        cutoff2.unset();
        cutoff2_chanaft = 0;
        cutoff2_polyaft = 0;
        resonance2 = 0;
        fil2_keytrack = 0;
        fil2_keycenter = 60;
        fil2_veltrack = 0;
        fil2_random = 0;

        // per voice equalizer
        eq1_freq = 50;
        eq2_freq = 500;
        eq3_freq = 5000;
        eq1_vel2freq = 0;
        eq2_vel2freq = 0;
        eq3_vel2freq = 0;
        eq1_bw = 1;
        eq2_bw = 1;
        eq3_bw = 1;
        eq1_gain = 0;
        eq2_gain = 0;
        eq3_gain = 0;
        eq1_vel2gain = 0;
        eq2_vel2gain = 0;
        eq3_vel2gain = 0;

        // CCs
        for (int i = 0; i < 128; ++i)
        {
            // input control
            locc[i] = 0;
            hicc[i] = 127;
            start_locc[i] = -1;
            start_hicc[i] = -1;
            stop_locc[i] = -1;
            stop_hicc[i] = -1;
            on_locc[i] = -1;
            on_hicc[i] = -1;

            // sample player
            delay_oncc[i].unset();
            delay_samples_oncc[i].unset();
            offset_oncc[i].unset();

            // amplifier
            amp_velcurve[i] = -1;
            gain_oncc[i] = 0;
            xfin_locc[i] = 0;
            xfin_hicc[i] = 0;
            xfout_locc[i] = 127;
            xfout_hicc[i] = 127;

            // filter
            cutoff_oncc[i] = 0;
            cutoff_smoothcc[i] = 0;
            cutoff_stepcc[i] = 0;
            cutoff_curvecc[i] = 0;
            resonance_oncc[i] = 0;
            resonance_smoothcc[i] = 0;
            resonance_stepcc[i] = 0;
            resonance_curvecc[i] = 0;

            cutoff2_oncc[i] = 0;
            cutoff2_smoothcc[i] = 0;
            cutoff2_stepcc[i] = 0;
            cutoff2_curvecc[i] = 0;
            resonance2_oncc[i] = 0;
            resonance2_smoothcc[i] = 0;
            resonance2_stepcc[i] = 0;
            resonance2_curvecc[i] = 0;

            // per voice equalizer
            eq1_freq_oncc[i] = 0;
            eq2_freq_oncc[i] = 0;
            eq3_freq_oncc[i] = 0;
            eq1_bw_oncc[i] = 0;
            eq2_bw_oncc[i] = 0;
            eq3_bw_oncc[i] = 0;
            eq1_gain_oncc[i] = 0;
            eq2_gain_oncc[i] = 0;
            eq3_gain_oncc[i] = 0;
        }

        eg.clear();

        // deprecated
        ampeg_delay    = 0;
        ampeg_start    = 0; //in percentage
        ampeg_attack   = 0;
        ampeg_hold     = 0;
        ampeg_decay    = 0;
        ampeg_sustain  = 100; // in percentage
        ampeg_release  = 0;

        fileg_delay    = 0;
        fileg_start    = 0; //in percentage
        fileg_attack   = 0;
        fileg_hold     = 0;
        fileg_decay    = 0;
        fileg_sustain  = 100; // in percentage
        fileg_release  = 0;

        pitcheg_delay    = 0;
        pitcheg_start    = 0; //in percentage
        pitcheg_attack   = 0;
        pitcheg_hold     = 0;
        pitcheg_decay    = 0;
        pitcheg_sustain  = 100; // in percentage
        pitcheg_release  = 0;

        amplfo_delay     = 0;
        amplfo_fade      = 0;
        amplfo_freq      = 0;
        amplfo_depth     = 0;

        fillfo_delay     = 0;
        fillfo_fade      = 0;
        fillfo_freq      = 0;
        fillfo_depth     = 0;

        pitchlfo_delay   = 0;
        pitchlfo_fade    = 0;
        pitchlfo_freq    = 0;
        pitchlfo_depth   = 0;
    }

    Region*
    Group::RegionFactory()
    {
        // This is where the current group setting are copied to the new region.

        Region* region = new Region();

        region->id = id++;

        // sample definition
        region->sample = sample;

        // input control
        region->lochan = lochan;
        region->hichan = hichan;
        region->lokey = lokey;
        region->hikey = hikey;
        region->lovel = lovel;
        region->hivel = hivel;
        region->locc = locc;
        region->hicc = hicc;
        region->lobend = lobend;
        region->hibend = hibend;
        region->lobpm = lobpm;
        region->hibpm = hibpm;
        region->lochanaft = lochanaft;
        region->hichanaft = hichanaft;
        region->lopolyaft = lopolyaft;
        region->hipolyaft = hipolyaft;
        region->loprog = loprog;
        region->hiprog = hiprog;
        region->lorand = lorand;
        region->hirand = hirand;
        region->lotimer = lotimer;
        region->hitimer = hitimer;
        region->seq_length = seq_length;
        region->seq_position = seq_position;
        region->start_locc = start_locc;
        region->start_hicc = start_hicc;
        region->stop_locc = stop_locc;
        region->stop_hicc = stop_hicc;
        region->sw_lokey = sw_lokey;
        region->sw_hikey = sw_hikey;
        region->sw_last = sw_last;
        region->sw_down = sw_down;
        region->sw_up = sw_up;
        region->sw_previous = sw_previous;
        region->sw_vel = sw_vel;
        region->trigger = trigger;
        region->group = group;
        region->off_by = off_by;
        region->off_mode = off_mode;
        region->on_locc = on_locc;
        region->on_hicc = on_hicc;

        // sample player
        region->count = count;
        region->delay = delay;
        region->delay_random = delay_random;
        region->delay_oncc = delay_oncc;
        region->delay_beats = delay_beats;
        region->stop_beats = stop_beats;
        region->delay_samples = delay_samples;
        region->delay_samples_oncc = delay_samples_oncc;
        region->end = end;
        region->loop_crossfade = loop_crossfade;
        region->offset = offset;
        region->offset_random = offset_random;
        region->offset_oncc = offset_oncc;
        region->loop_mode = loop_mode;
        region->loop_start = loop_start;
        region->loop_end = loop_end;
        region->sync_beats = sync_beats;
        region->sync_offset = sync_offset;

        // amplifier
        region->volume = volume;
        region->pan = pan;
        region->width = width;
        region->position = position;
        region->amp_keytrack = amp_keytrack;
        region->amp_keycenter = amp_keycenter;
        region->amp_veltrack = amp_veltrack;
        region->amp_velcurve = amp_velcurve;
        region->amp_random = amp_random;
        region->rt_decay = rt_decay;
        region->gain_oncc = gain_oncc;
        region->xfin_lokey = xfin_lokey;
        region->xfin_hikey = xfin_hikey;
        region->xfout_lokey = xfout_lokey;
        region->xfout_hikey = xfout_hikey;
        region->xf_keycurve = xf_keycurve;
        region->xfin_lovel = xfin_lovel;
        region->xfin_hivel = xfin_lovel;
        region->xfout_lovel = xfout_lovel;
        region->xfout_hivel = xfout_hivel;
        region->xf_velcurve = xf_velcurve;
        region->xfin_locc = xfin_locc;
        region->xfin_hicc = xfin_hicc;
        region->xfout_locc = xfout_locc;
        region->xfout_hicc = xfout_hicc;
        region->xf_cccurve = xf_cccurve;

        // pitch
        region->transpose = transpose;
        region->tune = tune;
        region->pitch_keycenter = pitch_keycenter;
        region->pitch_keytrack = pitch_keytrack;
        region->pitch_veltrack = pitch_veltrack;
        region->pitch_random = pitch_random;
        region->bend_up = bend_up;
        region->bend_down = bend_down;
        region->bend_step = bend_step;

        // filter
        region->fil_type = fil_type;
        region->cutoff = cutoff;
        region->cutoff_oncc = cutoff_oncc;
        region->cutoff_smoothcc = cutoff_smoothcc;
        region->cutoff_stepcc = cutoff_stepcc;
        region->cutoff_curvecc = cutoff_curvecc;
        region->cutoff_chanaft = cutoff_chanaft;
        region->cutoff_polyaft = cutoff_polyaft;
        region->resonance = resonance;
        region->resonance_oncc = resonance_oncc;
        region->resonance_smoothcc = resonance_smoothcc;
        region->resonance_stepcc = resonance_stepcc;
        region->resonance_curvecc = resonance_curvecc;
        region->fil_keytrack = fil_keytrack;
        region->fil_keycenter = fil_keycenter;
        region->fil_veltrack = fil_veltrack;
        region->fil_random = fil_random;

        region->fil2_type = fil2_type;
        region->cutoff2 = cutoff2;
        region->cutoff2_oncc = cutoff2_oncc;
        region->cutoff2_smoothcc = cutoff2_smoothcc;
        region->cutoff2_stepcc = cutoff2_stepcc;
        region->cutoff2_curvecc = cutoff2_curvecc;
        region->cutoff2_chanaft = cutoff2_chanaft;
        region->cutoff2_polyaft = cutoff2_polyaft;
        region->resonance2 = resonance2;
        region->resonance2_oncc = resonance2_oncc;
        region->resonance2_smoothcc = resonance2_smoothcc;
        region->resonance2_stepcc = resonance2_stepcc;
        region->resonance2_curvecc = resonance2_curvecc;
        region->fil2_keytrack = fil2_keytrack;
        region->fil2_keycenter = fil2_keycenter;
        region->fil2_veltrack = fil2_veltrack;
        region->fil2_random = fil2_random;

        // per voice equalizer
        region->eq1_freq = eq1_freq;
        region->eq2_freq = eq2_freq;
        region->eq3_freq = eq3_freq;
        region->eq1_freq_oncc = eq1_freq_oncc;
        region->eq2_freq_oncc = eq2_freq_oncc;
        region->eq3_freq_oncc = eq3_freq_oncc;
        region->eq1_vel2freq = eq1_vel2freq;
        region->eq2_vel2freq = eq2_vel2freq;
        region->eq3_vel2freq = eq3_vel2freq;
        region->eq1_bw = eq1_bw;
        region->eq2_bw = eq2_bw;
        region->eq3_bw = eq3_bw;
        region->eq1_bw_oncc = eq1_bw_oncc;
        region->eq2_bw_oncc = eq2_bw_oncc;
        region->eq3_bw_oncc = eq3_bw_oncc;
        region->eq1_gain = eq1_gain;
        region->eq2_gain = eq2_gain;
        region->eq3_gain = eq3_gain;
        region->eq1_gain_oncc = eq1_gain_oncc;
        region->eq2_gain_oncc = eq2_gain_oncc;
        region->eq3_gain_oncc = eq3_gain_oncc;
        region->eq1_vel2gain = eq1_vel2gain;
        region->eq2_vel2gain = eq2_vel2gain;
        region->eq3_vel2gain = eq3_vel2gain;

        // envelope generator
        region->eg = eg;

        // deprecated
        region->ampeg_delay    = ampeg_delay;
        region->ampeg_start    = ampeg_start;
        region->ampeg_attack   = ampeg_attack;
        region->ampeg_hold     = ampeg_hold;
        region->ampeg_decay    = ampeg_decay;
        region->ampeg_sustain  = ampeg_sustain;
        region->ampeg_release  = ampeg_release;

        region->fileg_delay    = fileg_delay;
        region->fileg_start    = fileg_start;
        region->fileg_attack   = fileg_attack;
        region->fileg_hold     = fileg_hold;
        region->fileg_decay    = fileg_decay;
        region->fileg_sustain  = fileg_sustain;
        region->fileg_release  = fileg_release;

        region->pitcheg_delay    = pitcheg_delay;
        region->pitcheg_start    = pitcheg_start;
        region->pitcheg_attack   = pitcheg_attack;
        region->pitcheg_hold     = pitcheg_hold;
        region->pitcheg_decay    = pitcheg_decay;
        region->pitcheg_sustain  = pitcheg_sustain;
        region->pitcheg_release  = pitcheg_release;

        region->amplfo_delay     = amplfo_delay;
        region->amplfo_fade      = amplfo_fade;
        region->amplfo_freq      = amplfo_freq;
        region->amplfo_depth     = amplfo_depth;

        region->fillfo_delay     = fillfo_delay;
        region->fillfo_fade      = fillfo_fade;
        region->fillfo_freq      = fillfo_freq;
        region->fillfo_depth     = fillfo_depth;

        region->pitchlfo_delay   = pitchlfo_delay;
        region->pitchlfo_fade    = pitchlfo_fade;
        region->pitchlfo_freq    = pitchlfo_freq;
        region->pitchlfo_depth   = pitchlfo_depth;

        return region;
    }

    /////////////////////////////////////////////////////////////
    // class File

    File::File(std::string file, SampleManager* pSampleManager) :
        _current_section(GROUP),
        default_path(""),
        octave_offset(0),
        note_offset(0)
    {
        _instrument = new Instrument(LinuxSampler::Path::getBaseName(file), pSampleManager);
        _current_group = new Group();
        pCurDef = _current_group;
        enum token_type_t { HEADER, OPCODE };
        token_type_t token_type;
        std::string token_string;

        std::ifstream fs(file.c_str());
        currentDir = LinuxSampler::Path::stripLastName(file);
        std::string token;
        std::string line;

        while (std::getline(fs, line))
        {
            // COMMENT
            std::string::size_type slash_index = line.find("//");
            if (slash_index != std::string::npos)
                line.resize(slash_index);

            // DEFINITION
            std::stringstream linestream(line);
            while (linestream >> token)
            {
                if (token[0] == '<' and token[token.size()-1] == '>')
                {
                    // HEAD
                    if (!token_string.empty())
                    {
                        switch (token_type)
                        {
                        case HEADER:
                            push_header(token_string);
                            break;
                        case OPCODE:
                            push_opcode(token_string);
                            break;
                        }
                        token_string.erase();
                    }
                    token_string.append(token);
                    token_type = HEADER;
                }
                else if (token.find('=') != std::string::npos)
                {
                    // HEAD
                    if (!token_string.empty())
                    {
                        switch (token_type)
                        {
                        case HEADER:
                            push_header(token_string);
                            break;
                        case OPCODE:
                            push_opcode(token_string);
                            break;
                        }
                        token_string.erase();
                    }
                    token_string.append(token);
                    token_type = OPCODE;
                }
                else
                {
                    // TAIL
                    token_string.append(" ");
                    token_string.append(token);
                }
            }

            // EOL
            if (!token_string.empty())
            {
                switch (token_type)
                {
                case HEADER:
                    push_header(token_string);
                    break;
                case OPCODE:
                    push_opcode(token_string);
                    break;
                }
                token_string.erase();
            }
        }

        for (int i = 0; i < _instrument->regions.size(); i++) {
            ::sfz::Region* pRegion = _instrument->regions[i];
            int low = pRegion->lokey;
            int high = pRegion->hikey;
            if (low < 0 || low > 127 || high < 0 || high > 127 || low > high) {
                std::cerr << "Invalid key range: " << low << " - " << high << std::endl;
            } else {
                for (int j = low; j <= high; j++) _instrument->KeyBindings[j] = true;
            }

            // get keyswitches
            low = pRegion->sw_lokey;
            if (low < 0) low = 0;
            high = pRegion->sw_hikey;
            if (high == -1) {
                // Key switches not defined, so nothing to do
            } else if (low >= 0 && low <= 127 && high >= 0 && high <= 127 && high >= low) {
                for (int j = low; j <= high; j++) _instrument->KeySwitchBindings[j] = true;
            } else {
                std::cerr << "Invalid key switch range: " << low << " - " << high << std::endl;
            }

            // create velocity response curve
            int prev = 0;
            float prevvalue = 0;
            for (int v = 0 ; v < 128 ; v++) {
                if (pRegion->amp_velcurve[v] >= 0) {
                    float step = (pRegion->amp_velcurve[v] - prevvalue) / (v - prev);
                    for ( ; prev < v ; prev++) {
                        pRegion->amp_velcurve[prev] = prevvalue;
                        prevvalue += step;
                    }
                }
            }
            if (prev) {
                float step = (1 - prevvalue) / (127 - prev);
                for ( ; prev < 128 ; prev++) {
                    pRegion->amp_velcurve[prev] = prevvalue;
                    prevvalue += step;
                }
            } else {
                // default curve
                for (int v = 0 ; v < 128 ; v++) {
                    pRegion->amp_velcurve[v] = v * v / (127.0 * 127.0);
                }
            }
            // apply amp_veltrack
            float offset = -pRegion->amp_veltrack;
            if (offset <= 0) offset += 100;
            for (int v = 0 ; v < 128 ; v++) {
                pRegion->amp_velcurve[v] =
                    (offset + pRegion->amp_veltrack * pRegion->amp_velcurve[v]) / 100;
            }
        }
    }

    File::~File()
    {
        delete _current_group;
        delete _instrument;
    }

    Instrument*
    File::GetInstrument()
    {
        return _instrument;
    }

    void
    File::push_header(std::string token)
    {
        if (token == "<group>")
        {
            _current_section = GROUP;
            _current_group->Reset();
            pCurDef = _current_group;
        }
        else if (token == "<region>")
        {
            _current_section = REGION;
            _current_region = _current_group->RegionFactory();
            pCurDef = _current_region;
            _instrument->regions.push_back(_current_region);
            _current_region->SetInstrument(_instrument);
        }
        else if (token == "<control>")
        {
            _current_section = CONTROL;
            default_path = "";
            octave_offset = 0;
            note_offset = 0;
        }
        else
        {
            _current_section = UNKNOWN;
            std::cerr << "The header '" << token << "' is unsupported by libsfz!" << std::endl;
        }
    }

    void
    File::push_opcode(std::string token)
    {
        if (_current_section == UNKNOWN)
            return;

        std::string::size_type delimiter_index = token.find('=');
        std::string key = token.substr(0, delimiter_index);
        std::string value = token.substr(delimiter_index + 1);
        int x, y;

        // sample definition
        if ("sample" == key)
        {
            std::string path = default_path + value;
            #ifndef WIN32
            for (int i = 0; i < path.length(); i++) if( path[i] == '\\') path[i] = '/';
            #endif
            path = currentDir + LinuxSampler::File::DirSeparator + path; // TODO: check for absolute path

            if(pCurDef) pCurDef->sample = path;
            return;
        }

        // control header directives
        else if ("default_path" == key)
        {
            switch (_current_section)
            {
            case CONTROL:
                default_path = value;
            }
            return;
        }
        else if ("octave_offset" == key)
        {
            switch (_current_section)
            {
            case CONTROL:
                octave_offset = ToInt(value);
            }
            return;
        }
        else if ("note_offset" == key)
        {
            switch (_current_section)
            {
            case CONTROL:
                note_offset = ToInt(value);
            }
            return;
        }

        // input controls
        else if ("lochan" == key) pCurDef->lochan = ToInt(value);
        else if ("hichan" == key) pCurDef->hichan = ToInt(value);
        else if ("lokey"  == key) pCurDef->lokey  = parseKey(value);
        else if ("hikey"  == key) pCurDef->hikey  = parseKey(value);
        else if ("key" == key)
        {
            pCurDef->lokey = pCurDef->hikey = pCurDef->pitch_keycenter = parseKey(value);
        }
        else if ("lovel"  == key) pCurDef->lovel = ToInt(value);
        else if ("hivel"  == key) pCurDef->hivel = ToInt(value);
        else if ("lobend" == key) pCurDef->lobend = ToInt(value);
        else if ("hibend" == key) pCurDef->hibend = ToInt(value);
        else if ("lobpm"  == key) pCurDef->lobpm = ToInt(value);
        else if ("hibpm"  == key) pCurDef->hibpm = ToInt(value);
        else if ("lochanaft" == key) pCurDef->lochanaft = ToInt(value);
        else if ("hichanaft" == key) pCurDef->hichanaft = ToInt(value);
        else if ("lopolyaft" == key) pCurDef->lopolyaft = ToInt(value);
        else if ("hipolyaft" == key) pCurDef->hipolyaft = ToInt(value);
        else if ("loprog"  == key) pCurDef->loprog = ToInt(value);
        else if ("hiprog"  == key) pCurDef->hiprog = ToInt(value);
        else if ("lorand"  == key) pCurDef->lorand = ToFloat(value);
        else if ("hirand"  == key) pCurDef->hirand = ToFloat(value);
        else if ("lotimer" == key) pCurDef->lotimer = ToFloat(value);
        else if ("hitimer" == key) pCurDef->hitimer = ToFloat(value);
        else if ("seq_length"   == key) pCurDef->seq_length = ToInt(value);
        else if ("seq_position" == key) pCurDef->seq_position = ToInt(value);
        else if ("sw_lokey" == key) pCurDef->sw_lokey = parseKey(value);
        else if ("sw_hikey" == key) pCurDef->sw_hikey = parseKey(value);
        else if ("sw_last"  == key) pCurDef->sw_last = parseKey(value);
        else if ("sw_down"  == key) pCurDef->sw_down = parseKey(value);
        else if ("sw_up"    == key) pCurDef->sw_up = parseKey(value);
        else if ("sw_previous" == key) pCurDef->sw_previous = parseKey(value);
        else if ("sw_vel" == key)
        {
            if (value == "current") pCurDef->sw_vel = VEL_CURRENT;
            else if (value == "previous") pCurDef->sw_vel = VEL_PREVIOUS;
        }
        else if ("trigger" == key)
        {
            if (value == "attack") pCurDef->trigger = TRIGGER_ATTACK;
            else if (value == "release") pCurDef->trigger = TRIGGER_RELEASE;
            else if (value == "first")   pCurDef->trigger = TRIGGER_FIRST;
            else if (value == "legato")  pCurDef->trigger = TRIGGER_LEGATO;
        }
        else if ("group"  == key) pCurDef->group = ToInt(value);
        else if ("off_by" == key || "offby" == key) pCurDef->off_by = ToInt(value);
        else if ("off_mode" == key || "offmode" == key)
        {
            if (value == "fast")  _current_group->off_mode = OFF_FAST;
            else if (value == "normal") _current_group->off_mode = OFF_NORMAL;
        }

        // sample player
        else if ("count" == key) { pCurDef->count = ToInt(value); pCurDef->loop_mode = ONE_SHOT; }
        else if ("delay" == key) pCurDef->delay = ToFloat(value);
        else if ("delay_random"   == key) pCurDef->delay_random = ToFloat(value);
        else if ("delay_beats"    == key) pCurDef->delay_beats = ToInt(value);
        else if ("stop_beats"     == key) pCurDef->stop_beats = ToInt(value);
        else if ("delay_samples"  == key) pCurDef->delay_samples = ToInt(value);
        else if ("end"            == key) pCurDef->end = ToInt(value);
        else if ("loop_crossfade" == key) pCurDef->loop_crossfade = ToFloat(value);
        else if ("offset_random"  == key) pCurDef->offset_random = ToInt(value);
        else if ("loop_mode" == key || "loopmode" == key)
        {
            if (value == "no_loop") pCurDef->loop_mode = NO_LOOP;
            else if (value == "one_shot") pCurDef->loop_mode = ONE_SHOT;
            else if (value == "loop_continuous") pCurDef->loop_mode = LOOP_CONTINUOUS;
            else if (value == "loop_sustain") pCurDef->loop_mode = LOOP_SUSTAIN;
        }
        else if ("loop_start" == key) pCurDef->loop_start = ToInt(value);
        else if ("loopstart" == key) pCurDef->loop_start = ToInt(value); // nonstandard
        else if ("loop_end" == key) pCurDef->loop_end = ToInt(value);
        else if ("loopend" == key) pCurDef->loop_end = ToInt(value); // nonstandard
        else if ("sync_beats" == key) pCurDef->sync_beats = ToInt(value);
        else if ("sync_offset" == key) pCurDef->sync_offset = ToInt(value);

        // amplifier
        else if ("volume"   == key) pCurDef->volume = ToFloat(value);
        else if ("pan"      == key) pCurDef->pan = ToFloat(value);
        else if ("width"    == key) pCurDef->width = ToFloat(value);
        else if ("position" == key) pCurDef->position = ToFloat(value);
        else if ("amp_keytrack"  == key) pCurDef->amp_keytrack = ToFloat(value);
        else if ("amp_keycenter" == key) pCurDef->amp_keycenter = parseKey(value);
        else if ("amp_veltrack"  == key) pCurDef->amp_veltrack = ToFloat(value);
        else if ("amp_random"  == key) pCurDef->amp_random = ToFloat(value);
        else if ("rt_decay"    == key) pCurDef->rt_decay = ToFloat(value);
        else if ("xfin_lokey"  == key) pCurDef->xfin_lokey = parseKey(value);
        else if ("xfin_hikey"  == key) pCurDef->xfin_hikey = parseKey(value);
        else if ("xfout_lokey" == key) pCurDef->xfout_lokey = parseKey(value);
        else if ("xfout_hikey" == key) pCurDef->xfout_hikey = parseKey(value);
        else if ("xf_keycurve" == key)
        {
            if (value == "gain") pCurDef->xf_keycurve = GAIN;
            else if (value == "power") pCurDef->xf_keycurve = POWER;
        }
        else if ("xfin_lovel"  == key) pCurDef->xfin_lovel = ToInt(value);
        else if ("xfin_hivel"  == key) pCurDef->xfin_hivel = ToInt(value);
        else if ("xfout_lovel" == key) pCurDef->xfout_lovel = ToInt(value);
        else if ("xfout_hivel" == key) pCurDef->xfout_hivel = ToInt(value);
        else if ("xf_velcurve" == key)
        {
            if (value == "gain") pCurDef->xf_velcurve = GAIN;
            else if (value == "power") pCurDef->xf_velcurve = POWER;
        }
        else if ("xf_cccurve" == key)
        {
            if (value == "gain") pCurDef->xf_cccurve = GAIN;
            else if (value == "power") pCurDef->xf_cccurve = POWER;
        }

        // pitch
        else if ("transpose" == key) pCurDef->transpose = ToInt(value);
        else if ("tune" == key) pCurDef->tune = ToInt(value);
        else if ("pitch_keycenter" == key) pCurDef->pitch_keycenter = parseKey(value);
        else if ("pitch_keytrack" == key) pCurDef->pitch_keytrack = ToInt(value);
        else if ("pitch_veltrack" == key) pCurDef->pitch_veltrack = ToInt(value);
        else if ("pitch_random" == key) pCurDef->pitch_random = ToInt(value);
        else if ("bend_up" == key || "bendup" == key) pCurDef->bend_up = ToInt(value);
        else if ("bend_down" == key || "benddown" == key) pCurDef->bend_down = ToInt(value);
        else if ("bend_step" == key) pCurDef->bend_step = ToInt(value);

        // filter
        else if ("fil_type" == key || "filtype" == key)
        {
            if (value == "lpf_1p") pCurDef->fil_type = LPF_1P;
            else if (value == "hpf_1p") pCurDef->fil_type = HPF_1P;
            else if (value == "bpf_1p") pCurDef->fil_type = BPF_1P;
            else if (value == "brf_1p") pCurDef->fil_type = BRF_1P;
            else if (value == "apf_1p") pCurDef->fil_type = APF_1P;
            else if (value == "lpf_2p") pCurDef->fil_type = LPF_2P;
            else if (value == "hpf_2p") pCurDef->fil_type = HPF_2P;
            else if (value == "bpf_2p") pCurDef->fil_type = BPF_2P;
            else if (value == "brf_2p") pCurDef->fil_type = BRF_2P;
            else if (value == "pkf_2p") pCurDef->fil_type = PKF_2P;
            else if (value == "lpf_4p") pCurDef->fil_type = LPF_4P;
            else if (value == "hpf_4p") pCurDef->fil_type = HPF_4P;
            else if (value == "lpf_6p") pCurDef->fil_type = LPF_6P;
            else if (value == "hpf_6p") pCurDef->fil_type = HPF_6P;
        }
        else if ("fil2_type" == key)
        {
            if (value == "lpf_1p") pCurDef->fil2_type = LPF_1P;
            else if (value == "hpf_1p") pCurDef->fil2_type = HPF_1P;
            else if (value == "bpf_1p") pCurDef->fil2_type = BPF_1P;
            else if (value == "brf_1p") pCurDef->fil2_type = BRF_1P;
            else if (value == "apf_1p") pCurDef->fil2_type = APF_1P;
            else if (value == "lpf_2p") pCurDef->fil2_type = LPF_2P;
            else if (value == "hpf_2p") pCurDef->fil2_type = HPF_2P;
            else if (value == "bpf_2p") pCurDef->fil2_type = BPF_2P;
            else if (value == "brf_2p") pCurDef->fil2_type = BRF_2P;
            else if (value == "pkf_2p") pCurDef->fil2_type = PKF_2P;
            else if (value == "lpf_4p") pCurDef->fil2_type = LPF_4P;
            else if (value == "hpf_4p") pCurDef->fil2_type = HPF_4P;
            else if (value == "lpf_6p") pCurDef->fil2_type = LPF_6P;
            else if (value == "hpf_6p") pCurDef->fil2_type = HPF_6P;
        }
        else if ("cutoff"  == key) pCurDef->cutoff = ToFloat(value);
        else if ("cutoff2" == key) pCurDef->cutoff2 = ToFloat(value);
        else if ("cutoff_chanaft"  == key) pCurDef->cutoff_chanaft = ToInt(value);
        else if ("cutoff2_chanaft" == key) pCurDef->cutoff2_chanaft = ToInt(value);
        else if ("cutoff_polyaft"  == key) pCurDef->cutoff_polyaft = ToInt(value);
        else if ("cutoff2_polyaft" == key) pCurDef->cutoff2_polyaft = ToInt(value);
        else if ("resonance"  == key) pCurDef->resonance = ToFloat(value);
        else if ("resonance2" == key) pCurDef->resonance2 = ToFloat(value);
        else if ("fil_keytrack"   == key) pCurDef->fil_keytrack = ToInt(value);
        else if ("fil2_keytrack"  == key) pCurDef->fil2_keytrack = ToInt(value);
        else if ("fil_keycenter"  == key) pCurDef->fil_keycenter = parseKey(value);
        else if ("fil2_keycenter" == key) pCurDef->fil2_keycenter = parseKey(value);
        else if ("fil_veltrack"   == key) pCurDef->fil_veltrack = ToInt(value);
        else if ("fil2_veltrack"  == key) pCurDef->fil2_veltrack = ToInt(value);
        else if ("fil_random"     == key) pCurDef->fil_random = ToInt(value);
        else if ("fil2_random"    == key) pCurDef->fil2_random = ToInt(value);

        // per voice equalizer
        else if ("eq1_freq" == key) pCurDef->eq1_freq = ToFloat(value);
        else if ("eq2_freq" == key) pCurDef->eq2_freq = ToFloat(value);
        else if ("eq3_freq" == key) pCurDef->eq3_freq = ToFloat(value);
        else if ("eq1_vel2freq" == key) pCurDef->eq1_vel2freq = ToFloat(value);
        else if ("eq2_vel2freq" == key) pCurDef->eq2_vel2freq = ToFloat(value);
        else if ("eq3_vel2freq" == key) pCurDef->eq3_vel2freq = ToFloat(value);
        else if ("eq1_bw" == key) pCurDef->eq1_bw = ToFloat(value);
        else if ("eq2_bw" == key) pCurDef->eq2_bw = ToFloat(value);
        else if ("eq3_bw" == key) pCurDef->eq3_bw = ToFloat(value);
        else if ("eq1_gain" == key) pCurDef->eq1_gain = ToFloat(value);
        else if ("eq2_gain" == key) pCurDef->eq2_gain = ToFloat(value);
        else if ("eq3_gain" == key) pCurDef->eq3_gain = ToFloat(value);
        else if ("eq1_vel2gain" == key) pCurDef->eq1_vel2gain = ToFloat(value);
        else if ("eq2_vel2gain" == key) pCurDef->eq2_vel2gain = ToFloat(value);
        else if ("eq3_vel2gain" == key) pCurDef->eq3_vel2gain = ToFloat(value);

        else if (sscanf(key.c_str(), "amp_velcurve_%d", &x)) {
            pCurDef->amp_velcurve[x] = ToFloat(value);
        }

        // CCs
        else if (key.find("cc") != std::string::npos)
        {
            std::string::size_type delimiter_index = key.find("cc");
            std::string key_cc = key.substr(0, delimiter_index);
            int num_cc = ToInt(key.substr(delimiter_index + 2));

            // input controls
            if ("lo" == key_cc) pCurDef->locc[num_cc] = ToInt(value);
            else if ("hi" == key_cc) pCurDef->hicc[num_cc] = ToInt(value);
            else if ("start_lo" == key_cc) pCurDef->start_locc[num_cc] = ToInt(value);
            else if ("start_hi" == key_cc) pCurDef->start_hicc[num_cc] = ToInt(value);
            else if ("stop_lo" == key_cc) pCurDef->stop_locc[num_cc] = ToInt(value);
            else if ("stop_hi" == key_cc) pCurDef->stop_hicc[num_cc] = ToInt(value);
            else if ("on_lo" == key_cc) pCurDef->on_locc[num_cc] = ToInt(value);
            else if ("on_hi" == key_cc) pCurDef->on_hicc[num_cc] = ToInt(value);

            // sample player
            else if ("delay_on" == key_cc) pCurDef->delay_oncc[num_cc] = ToFloat(value);
            else if ("delay_samples_on" == key_cc) pCurDef->delay_samples_oncc[num_cc] = ToInt(value);
            else if ("offset_on" == key_cc) pCurDef->offset_oncc[num_cc] = ToInt(value);

            // amplifier
            else if ("gain_on"  == key_cc || "gain_" == key_cc) pCurDef->gain_oncc[num_cc]  = ToFloat(value);
            else if ("xfin_lo"  == key_cc) pCurDef->xfin_locc[num_cc]  = ToInt(value);
            else if ("xfin_hi"  == key_cc) pCurDef->xfin_hicc[num_cc]  = ToInt(value);
            else if ("xfout_lo" == key_cc) pCurDef->xfout_locc[num_cc] = ToInt(value);
            else if ("xfout_hi" == key_cc) pCurDef->xfout_hicc[num_cc] = ToInt(value);

            // filter
            else if ("cutoff_on"  == key_cc || "cutoff_" == key_cc) pCurDef->cutoff_oncc[num_cc]  = ToInt(value);
            else if ("cutoff2_on" == key_cc) pCurDef->cutoff2_oncc[num_cc] = ToInt(value);
            else if ("cutoff_smooth"  == key_cc) pCurDef->cutoff_smoothcc[num_cc]  = ToInt(value);
            else if ("cutoff2_smooth" == key_cc) pCurDef->cutoff2_smoothcc[num_cc] = ToInt(value);
            else if ("cutoff_step"  == key_cc) pCurDef->cutoff_stepcc[num_cc]  = ToInt(value);
            else if ("cutoff2_step" == key_cc) pCurDef->cutoff2_stepcc[num_cc] = ToInt(value);
            else if ("cutoff_curve" == key_cc) pCurDef->cutoff_curvecc[num_cc] = ToInt(value);
            else if ("cutoff2_curve" == key_cc) pCurDef->cutoff2_curvecc[num_cc] = ToInt(value);
            else if ("resonance_on" == key_cc) pCurDef->resonance_oncc[num_cc] = ToInt(value);
            else if ("resonance2_on" == key_cc) pCurDef->resonance2_oncc[num_cc] = ToInt(value);
            else if ("resonance_smooth" == key_cc) pCurDef->resonance_smoothcc[num_cc] = ToInt(value);
            else if ("resonance2_smooth" == key_cc) pCurDef->resonance2_smoothcc[num_cc] = ToInt(value);
            else if ("resonance_step" == key_cc) pCurDef->resonance_stepcc[num_cc] = ToInt(value);
            else if ("resonance2_step" == key_cc) pCurDef->resonance2_stepcc[num_cc] = ToInt(value);
            else if ("resonance_curve" == key_cc) pCurDef->resonance_curvecc[num_cc] = ToInt(value);
            else if ("resonance2_curve" == key_cc) pCurDef->resonance2_curvecc[num_cc] = ToInt(value);

            // per voice equalizer
            else if ("eq1_freq_on" == key_cc || "eq1_freq" == key_cc) pCurDef->eq1_freq_oncc[num_cc] = ToInt(value);
            else if ("eq2_freq_on" == key_cc || "eq2_freq" == key_cc) pCurDef->eq2_freq_oncc[num_cc] = ToInt(value);
            else if ("eq3_freq_on" == key_cc || "eq3_freq" == key_cc) pCurDef->eq3_freq_oncc[num_cc] = ToInt(value);
            else if ("eq1_bw_on" == key_cc || "eq1_bw" == key_cc) pCurDef->eq1_bw_oncc[num_cc] = ToInt(value);
            else if ("eq2_bw_on" == key_cc || "eq2_bw" == key_cc) pCurDef->eq2_bw_oncc[num_cc] = ToInt(value);
            else if ("eq3_bw_on" == key_cc || "eq3_bw" == key_cc) pCurDef->eq3_bw_oncc[num_cc] = ToInt(value);
            else if ("eq1_gain_on" == key_cc || "eq1_gain" == key_cc) pCurDef->eq1_gain_oncc[num_cc] = ToInt(value);
            else if ("eq2_gain_on" == key_cc || "eq2_gain" == key_cc) pCurDef->eq2_gain_oncc[num_cc] = ToInt(value);
            else if ("eq3_gain_on" == key_cc || "eq3_gain" == key_cc) pCurDef->eq3_gain_oncc[num_cc] = ToInt(value);
            else std::cerr << "The opcode '" << key << "' is unsupported by libsfz!" << std::endl;
        }
        // v2 envelope generators
        else if (sscanf(key.c_str(), "eg%d%n", &x, &y)) {
            const char* s = key.c_str() + y;
            if (sscanf(s, "_time%d", &y)) egnode(x, y).time = ToFloat(value);
            else if (sscanf(s, "_level%d", &y)) egnode(x, y).level = ToFloat(value);
            else if (sscanf(s, "_shape%d", &y)) egnode(x, y).shape = ToFloat(value);
            else if (sscanf(s, "_curve%d", &y)) egnode(x, y).curve = ToFloat(value);
            else if (strcmp(s, "_sustain") == 0) eg(x).sustain = ToInt(value);
            else if (strcmp(s, "_loop") == 0) eg(x).loop = ToInt(value);
            else if (strcmp(s, "_loop_count") == 0) eg(x).loop_count = ToInt(value);
            else if (strcmp(s, "_amplitude") == 0) eg(x).amplitude = ToFloat(value);
            else if (strcmp(s, "_cutoff") == 0) eg(x).cutoff = ToFloat(value);
            else std::cerr << "The opcode '" << key << "' is unsupported by libsfz!" << std::endl;
        }

        // v1 envelope generators
        else if ("ampeg_delay"   == key) pCurDef->ampeg_delay = ToFloat(value);
        else if ("ampeg_start"   == key) pCurDef->ampeg_start = ToFloat(value);
        else if ("ampeg_attack"   == key) pCurDef->ampeg_attack = ToFloat(value);
        else if ("ampeg_hold"   == key) pCurDef->ampeg_hold = ToFloat(value);
        else if ("ampeg_decay"   == key) pCurDef->ampeg_decay = ToFloat(value);
        else if ("ampeg_sustain"   == key) pCurDef->ampeg_sustain = ToFloat(value);
        else if ("ampeg_release"   == key) pCurDef->ampeg_release = ToFloat(value);
        else if ("fileg_delay"   == key) pCurDef->fileg_delay = ToFloat(value);
        else if ("fileg_start"   == key) pCurDef->fileg_start = ToFloat(value);
        else if ("fileg_attack"   == key) pCurDef->fileg_attack = ToFloat(value);
        else if ("fileg_hold"   == key) pCurDef->fileg_hold = ToFloat(value);
        else if ("fileg_decay"   == key) pCurDef->fileg_decay = ToFloat(value);
        else if ("fileg_sustain"   == key) pCurDef->fileg_sustain = ToFloat(value);
        else if ("fileg_release"   == key) pCurDef->fileg_release = ToFloat(value);
        else if ("pitcheg_delay"   == key) pCurDef->pitcheg_delay = ToFloat(value);
        else if ("pitcheg_start"   == key) pCurDef->pitcheg_start = ToFloat(value);
        else if ("pitcheg_attack"   == key) pCurDef->pitcheg_attack = ToFloat(value);
        else if ("pitcheg_hold"   == key) pCurDef->pitcheg_hold = ToFloat(value);
        else if ("pitcheg_decay"   == key) pCurDef->pitcheg_decay = ToFloat(value);
        else if ("pitcheg_sustain"   == key) pCurDef->pitcheg_sustain = ToFloat(value);
        else if ("pitcheg_release"   == key) pCurDef->pitcheg_release = ToFloat(value);

        // v1 LFO
        else if ("amplfo_delay" == key) pCurDef->amplfo_delay = ToFloat(value);
        else if ("amplfo_fade" == key) pCurDef->amplfo_fade = ToFloat(value);
        else if ("amplfo_freq" == key) pCurDef->amplfo_freq = ToFloat(value);
        else if ("amplfo_depth" == key) pCurDef->amplfo_depth = ToFloat(value);
        else if ("fillfo_delay" == key) pCurDef->fillfo_delay = ToFloat(value);
        else if ("fillfo_fade" == key) pCurDef->fillfo_fade = ToFloat(value);
        else if ("fillfo_freq" == key) pCurDef->fillfo_freq = ToFloat(value);
        else if ("fillfo_depth" == key) pCurDef->fillfo_depth = ToFloat(value);
        else if ("pitchlfo_delay" == key) pCurDef->pitchlfo_delay = ToFloat(value);
        else if ("pitchlfo_fade" == key) pCurDef->pitchlfo_fade = ToFloat(value);
        else if ("pitchlfo_freq" == key) pCurDef->pitchlfo_freq = ToFloat(value);
        else if ("pitchlfo_depth" == key) pCurDef->pitchlfo_depth = ToInt(value);

        else {
            std::cerr << "The opcode '" << key << "' is unsupported by libsfz!" << std::endl;
        }
    }

    int File::parseKey(const std::string& s) {
        int i;
        std::istringstream iss(s);
        if (isdigit(iss.peek())) {
            iss >> i;
        } else {
            switch (tolower(iss.get())) {
            case 'c': i = 0; break;
            case 'd': i = 2; break;
            case 'e': i = 4; break;
            case 'f': i = 5; break;
            case 'g': i = 7; break;
            case 'a': i = 9; break;
            case 'b': i = 11; break;
            default:
                std::cerr << "Not a note: " << s << std::endl;
                return 0;
            }
            if (iss.peek() == '#') {
                i++;
                iss.get();
            } else if (tolower(iss.peek()) == 'b') {
                i--;
                iss.get();
            }
            int octave;
            if (!(iss >> octave)) {
                std::cerr << "Not a note: " << s << std::endl;
                return 0;
            }
            i += (octave + 1) * 12;
        }
        return i + note_offset + 12 * octave_offset;
    }

    EGNode::EGNode() : time(0), level(0), shape(0), curve(0) {
    }

    EG::EG() :
        sustain(0), loop(0), loop_count(0),
        amplitude(0), cutoff(0) {
    }

    EG& File::eg(int x) {
        while (pCurDef->eg.size() <= x) {
            pCurDef->eg.add(EG());
        }
        return pCurDef->eg[x];
    }

    EGNode& File::egnode(int x, int y) {
        EG& e = eg(x);
        while (e.node.size() <= y) {
            e.node.add(EGNode());
        }
        return e.node[y];
    }

} // !namespace sfz
