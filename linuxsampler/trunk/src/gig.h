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

#ifndef __GIG_H__
#define __GIG_H__

#include "DLS.h"

#include <math.h>
#include <string.h>

/// Initial size of the sample buffer which is used for decompression of
/// compressed sample wave streams - this value should always be bigger than
/// the biggest sample piece expected to be read by the sampler engine,
/// otherwise the buffer size will be raised at runtime and thus the buffer
/// reallocated which is time consuming and unefficient.
#define INITIAL_SAMPLE_BUFFER_SIZE		512000 // 512 kB

#if WORDS_BIGENDIAN
# define LIST_TYPE_3PRG	0x33707267
# define LIST_TYPE_3EWL	0x3365776C
# define CHUNK_ID_SMPL	0x736D706C
# define CHUNK_ID_3GIX	0x33676978
# define CHUNK_ID_3EWA	0x33657761
# define CHUNK_ID_3LNK	0x336C6E6B
# define CHUNK_ID_3EWG	0x33657767
# define CHUNK_ID_EWAV	0x65776176
#else  // little endian
# define LIST_TYPE_3PRG	0x67727033
# define LIST_TYPE_3EWL	0x6C776533
# define CHUNK_ID_SMPL	0x6C706D73
# define CHUNK_ID_3GIX	0x78696733
# define CHUNK_ID_3EWA	0x61776533
# define CHUNK_ID_3LNK	0x6B6E6C33
# define CHUNK_ID_3EWG	0x67776533
# define CHUNK_ID_EWAV	0x76617765
#endif // WORDS_BIGENDIAN

/** (so far) every exponential paramater in the gig format has a basis of 1.000000008813822 */
#define GIG_EXP_DECODE(x)					(pow(1.000000008813822, x))
#define GIG_PITCH_TRACK_EXTRACT(x)				(!(x & 0x01))
#define GIG_VCF_RESONANCE_CTRL_EXTRACT(x)			((x >> 4) & 0x03)
#define GIG_EG_CTR_ATTACK_INFLUENCE_EXTRACT(x)			((x >> 1) & 0x03)
#define GIG_EG_CTR_DECAY_INFLUENCE_EXTRACT(x)			((x >> 3) & 0x03)
#define GIG_EG_CTR_RELEASE_INFLUENCE_EXTRACT(x)			((x >> 5) & 0x03)
//TODO: the transformation functions are not very accurate compared to the original ones
#define GIG_VELOCITY_TRANSFORM_NONLINEAR(x,dynamic,scale)	((1.0-1.0/pow(x,1.0/(129.0-x))) * (1.0+scale/20.0) + (5.0-dynamic)*pow(x/300.0* (1.0+2.0*scale/128.0),2))
#define GIG_VELOCITY_TRANSFORM_LINEAR(x,dynamic,scale)		((1.0+scale*3.0/128.0)/110.0*x+(5.0-dynamic)/5.0+(5.0-dynamic)*scale)
#define GIG_VELOCITY_TRANSFORM_SPECIAL(x,dynamic,scale)		((1.0+9.0*scale/129.0)*(1.0-1.0/pow(x,1.0/(129.0-x))+pow(3.0*x/pow(129,2),2)+pow((5.0-dynamic)*x/500.0,2)))

/** Gigasampler specific classes and definitions */
namespace gig {

    typedef std::string String;

    /** Lower and upper limit of a range. */
    struct range_t {
        uint8_t low;  ///< Low value of range.
        uint8_t high; ///< High value of range.
    };

    /** Pointer address and size of a buffer. */
    struct buffer_t {
        void*         pStart;            ///< Points to the beginning of the buffer.
        unsigned long Size;              ///< Size of the actual data in the buffer in bytes.
        unsigned long NullExtensionSize; ///< The buffer might be bigger than the actual data, if that's the case that unused space at the end of the buffer is filled with NULLs and NullExtensionSize reflects that unused buffer space in bytes. Those NULL extensions are mandatory for differential algorithms that have to take the following data words into account, thus have to access past the buffer's boundary. If you don't know what I'm talking about, just forget this variable. :)
    };

    /** Standard types of sample loops. */
    typedef enum {
        loop_type_normal        = 0x00000000,  ///< Loop forward (normal)
        loop_type_bidirectional = 0x00000001,  ///< Alternating loop (forward/backward, also known as Ping Pong)
        loop_type_backward      = 0x00000002   ///< Loop backward (reverse)
    } loop_type_t;

    /** Society of Motion Pictures and Television E time format. */
    typedef enum {
        smpte_format_no_offset          = 0x00000000,  ///< no SMPTE offset
        smpte_format_24_frames          = 0x00000018,  ///< 24 frames per second
        smpte_format_25_frames          = 0x00000019,  ///< 25 frames per second
        smpte_format_30_frames_dropping = 0x0000001D,  ///< 30 frames per second with frame dropping (30 drop)
        smpte_format_30_frames          = 0x0000001E   ///< 30 frames per second
    } smpte_format_t;

    /** Defines the shape of a function graph. */
    typedef enum {
        curve_type_nonlinear = 0,
        curve_type_linear    = 1,
        curve_type_special   = 2,
        curve_type_unknown   = 0xffffffff
    } curve_type_t;

    /** Dimensions allow to bypass one of the following controllers. */
    typedef enum {
        dim_bypass_ctrl_none,
        dim_bypass_ctrl_94,   ///< Effect 4 Depth (MIDI Controller 94)
        dim_bypass_ctrl_95    ///< Effect 5 Depth (MIDI Controller 95)
    } dim_bypass_ctrl_t;

    /** Defines how LFO3 is controlled by. */
    typedef enum {
        lfo3_ctrl_internal            = 0x00, ///< Only internally controlled.
        lfo3_ctrl_modwheel            = 0x01, ///< Only controlled by external modulation wheel.
        lfo3_ctrl_aftertouch          = 0x02, ///< Only controlled by aftertouch controller.
        lfo3_ctrl_internal_modwheel   = 0x03, ///< Controlled internally and by external modulation wheel.
        lfo3_ctrl_internal_aftertouch = 0x04  ///< Controlled internally and by aftertouch controller.
    } lfo3_ctrl_t;

    /** Defines how LFO2 is controlled by. */
    typedef enum {
        lfo2_ctrl_internal            = 0x00, ///< Only internally controlled.
        lfo2_ctrl_modwheel            = 0x01, ///< Only controlled by external modulation wheel.
        lfo2_ctrl_foot                = 0x02, ///< Only controlled by external foot controller.
        lfo2_ctrl_internal_modwheel   = 0x03, ///< Controlled internally and by external modulation wheel.
        lfo2_ctrl_internal_foot       = 0x04  ///< Controlled internally and by external foot controller.
    } lfo2_ctrl_t;

    /** Defines how LFO1 is controlled by. */
    typedef enum {
        lfo1_ctrl_internal            = 0x00, ///< Only internally controlled.
        lfo1_ctrl_modwheel            = 0x01, ///< Only controlled by external modulation wheel.
        lfo1_ctrl_breath              = 0x02, ///< Only controlled by external breath controller.
        lfo1_ctrl_internal_modwheel   = 0x03, ///< Controlled internally and by external modulation wheel.
        lfo1_ctrl_internal_breath     = 0x04  ///< Controlled internally and by external breath controller.
    } lfo1_ctrl_t;

    /** Defines how the filter cutoff frequency is controlled by. */
    typedef enum {
        vcf_cutoff_ctrl_none         = 0x00,
        vcf_cutoff_ctrl_modwheel     = 0x81,  ///< Modulation Wheel (MIDI Controller 1)
        vcf_cutoff_ctrl_effect1      = 0x8c,  ///< Effect Controller 1 (Coarse, MIDI Controller 12)
        vcf_cutoff_ctrl_effect2      = 0x8d,  ///< Effect Controller 2 (Coarse, MIDI Controller 13)
        vcf_cutoff_ctrl_breath       = 0x82,  ///< Breath Controller (Coarse, MIDI Controller 2)
        vcf_cutoff_ctrl_foot         = 0x84,  ///< Foot Pedal (Coarse, MIDI Controller 4)
        vcf_cutoff_ctrl_sustainpedal = 0xc0,  ///< Sustain Pedal (MIDI Controller 64)
        vcf_cutoff_ctrl_softpedal    = 0xc3,  ///< Soft Pedal (MIDI Controller 67)
        vcf_cutoff_ctrl_genpurpose7  = 0xd2,  ///< General Purpose Controller 7 (Button, MIDI Controller 82)
        vcf_cutoff_ctrl_genpurpose8  = 0xd3,  ///< General Purpose Controller 8 (Button, MIDI Controller 83)
        vcf_cutoff_ctrl_aftertouch   = 0x80   ///< Key Pressure
    } vcf_cutoff_ctrl_t;

    /** Defines how the filter resonance is controlled by. */
    typedef enum {
        vcf_res_ctrl_none        = 0xffffffff,
        vcf_res_ctrl_genpurpose3 = 0,           ///< General Purpose Controller 3 (Slider, MIDI Controller 18)
        vcf_res_ctrl_genpurpose4 = 1,           ///< General Purpose Controller 4 (Slider, MIDI Controller 19)
        vcf_res_ctrl_genpurpose5 = 2,           ///< General Purpose Controller 5 (Button, MIDI Controller 80)
        vcf_res_ctrl_genpurpose6 = 3            ///< General Purpose Controller 6 (Button, MIDI Controller 81)
    } vcf_res_ctrl_t;
    
    /**
     * Defines a controller that has a certain contrained influence on a
     * particular synthesis parameter (used to define attenuation controller,
     * EG1 controller and EG2 controller).
     *
     * You should use the respective <i>typedef</i> (means either
     * attenuation_ctrl_t, eg1_ctrl_t or eg2_ctrl_t) in your code!
     */
    struct leverage_ctrl_t {
        typedef enum {
            type_none              = 0x00, ///< No controller defined
            type_channelaftertouch = 0x2f, ///< Channel Key Pressure
            type_velocity          = 0xff, ///< Key Velocity
            type_controlchange     = 0xfe  ///< Ordinary MIDI control change controller, see field 'controller_number'
        } type_t;
        
        type_t type;              ///< Controller type
        uint   controller_number; ///< MIDI controller number if this controller is a control change controller, 0 otherwise
    };
    
    /**
     * Defines controller influencing attenuation.
     *
     * @see leverage_ctrl_t
     */
    typedef leverage_ctrl_t attenuation_ctrl_t;
    
    /**
     * Defines controller influencing envelope generator 1.
     *
     * @see leverage_ctrl_t
     */
    typedef leverage_ctrl_t eg1_ctrl_t;
    
    /**
     * Defines controller influencing envelope generator 2.
     *
     * @see leverage_ctrl_t
     */
    typedef leverage_ctrl_t eg2_ctrl_t;

    /**
     * Defines the type of dimension, that is how the dimension zones (and
     * thus how the dimension regions are selected by. The number of
     * dimension zones is always a power of two. All dimensions can have up
     * to 32 zones (except the layer dimension with only up to 8 zones and
     * the samplechannel dimension which currently allows only 2 zones).
     */
    typedef enum {
        dimension_none              = 0x00, ///< Dimension not in use.
        dimension_samplechannel     = 0x80, ///< If used sample has more than one channel (thus is not mono).
        dimension_layer             = 0x81, ///< For layering of up to 8 instruments (and eventually crossfading of 2 or 4 layers).
        dimension_velocity          = 0x82, ///< Key Velocity (this is the only dimension where the ranges can exactly be defined).
        dimension_channelaftertouch = 0x83, ///< Channel Key Pressure
        dimension_releasetrigger    = 0x84, ///< Special dimension for triggering samples on releasing a key.
        dimension_keyboard          = 0x85, ///< Key Position
        dimension_modwheel          = 0x01, ///< Modulation Wheel (MIDI Controller 1)
        dimension_breath            = 0x02, ///< Breath Controller (Coarse, MIDI Controller 2)
        dimension_foot              = 0x04, ///< Foot Pedal (Coarse, MIDI Controller 4)
        dimension_portamentotime    = 0x05, ///< Portamento Time (Coarse, MIDI Controller 5)
        dimension_effect1           = 0x0c, ///< Effect Controller 1 (Coarse, MIDI Controller 12)
        dimension_effect2           = 0x0d, ///< Effect Controller 2 (Coarse, MIDI Controller 13)
        dimension_genpurpose1       = 0x10, ///< General Purpose Controller 1 (Slider, MIDI Controller 16)
        dimension_genpurpose2       = 0x11, ///< General Purpose Controller 2 (Slider, MIDI Controller 17)
        dimension_genpurpose3       = 0x12, ///< General Purpose Controller 3 (Slider, MIDI Controller 18)
        dimension_genpurpose4       = 0x13, ///< General Purpose Controller 4 (Slider, MIDI Controller 19)
        dimension_sustainpedal      = 0x40, ///< Sustain Pedal (MIDI Controller 64)
        dimension_portamento        = 0x41, ///< Portamento (MIDI Controller 65)
        dimension_sostenutopedal    = 0x42, ///< Sostenuto Pedal (MIDI Controller 66)
        dimension_softpedal         = 0x43, ///< Soft Pedal (MIDI Controller 67)
        dimension_genpurpose5       = 0x30, ///< General Purpose Controller 5 (Button, MIDI Controller 80)
        dimension_genpurpose6       = 0x31, ///< General Purpose Controller 6 (Button, MIDI Controller 81)
        dimension_genpurpose7       = 0x32, ///< General Purpose Controller 7 (Button, MIDI Controller 82)
        dimension_genpurpose8       = 0x33, ///< General Purpose Controller 8 (Button, MIDI Controller 83)
        dimension_effect1depth      = 0x5b, ///< Effect 1 Depth (MIDI Controller 91)
        dimension_effect2depth      = 0x5c, ///< Effect 2 Depth (MIDI Controller 92)
        dimension_effect3depth      = 0x5d, ///< Effect 3 Depth (MIDI Controller 93)
        dimension_effect4depth      = 0x5e, ///< Effect 4 Depth (MIDI Controller 94)
        dimension_effect5depth      = 0x5f  ///< Effect 5 Depth (MIDI Controller 95)
    } dimension_t;

    /**
     * Intended for internal usage: will be used to convert a dimension value
     * into the corresponding dimension bit number.
     */
    typedef enum {
        split_type_normal,         ///< dimension value between 0-127, no custom range of zones
        split_type_customvelocity, ///< a velocity dimension split with custom range definition for each zone (if a velocity dimension split has no custom defined zone ranges then it's also just of type split_type_normal)
        split_type_bit             ///< dimension values are already the sought bit number
    } split_type_t;

    /** General dimension definition. */
    struct dimension_def_t {
        dimension_t  dimension;  ///< Specifies which source (usually a MIDI controller) is associated with the dimension.
        uint8_t      bits;       ///< Number of "bits" (1 bit = 2 splits/zones, 2 bit = 4 splits/zones, 3 bit = 8 splits/zones,...).
        uint8_t      zones;      ///< Number of zones the dimension has.
        split_type_t split_type; ///< Intended for internal usage: will be used to convert a dimension value into the corresponding dimension bit number.
        range_t*     ranges;     ///< Intended for internal usage: Points to the beginning of a range_t array which reflects the value ranges of each dimension zone (only if custom defined ranges are defined, is NULL otherwise).
        unsigned int zone_size;  ///< Intended for internal usage: reflects the size of each zone (128/zones) for normal split types only, 0 otherwise.
    };

    /** Defines which frequencies are filtered by the VCF. */
    typedef enum {
        vcf_type_lowpass      = 0x00,
        vcf_type_lowpassturbo = 0xff, ///< More poles than normal lowpass
        vcf_type_bandpass     = 0x01,
        vcf_type_highpass     = 0x02,
        vcf_type_bandreject   = 0x03
    } vcf_type_t;

    /** Defines the envelope of a crossfade. */
    struct crossfade_t {
        #if WORDS_BIGENDIAN
        uint8_t in_start;   ///< Start position of fade in.
        uint8_t in_end;     ///< End position of fade in.
        uint8_t out_start;  ///< Start position of fade out.
        uint8_t out_end;    ///< End postition of fade out.
        #else // little endian
        uint8_t out_end;    ///< End postition of fade out.
        uint8_t out_start;  ///< Start position of fade out.
        uint8_t in_end;     ///< End position of fade in.
        uint8_t in_start;   ///< Start position of fade in.
        #endif // WORDS_BIGENDIAN
    };

    /** Reflects the current playback state for a sample. */
    struct playback_state_t {
        unsigned long position;          ///< Current position within the sample.
        bool          reverse;           ///< If playback direction is currently backwards (in case there is a pingpong or reverse loop defined).
        unsigned long loop_cycles_left;  ///< How many times the loop has still to be passed, this value will be decremented with each loop cycle.
    };

    // just symbol prototyping
    class File;
    class Instrument;
    class Sample;

    /** Encapsulates articulation information of a dimension region.
     *
     *  Every Gigasampler Instrument has at least one dimension region
     *  (exactly then when it has no dimension defined).
     *
     *  Gigasampler provides three Envelope Generators and Low Frequency
     *  Oscillators:
     *
     *  - EG1 and LFO1, both controlling sample amplitude
     *  - EG2 and LFO2, both controlling filter cutoff frequency
     *  - EG3 and LFO3, both controlling sample pitch
     */
    class DimensionRegion : protected DLS::Sampler {
        public:
            uint8_t            VelocityUpperLimit;            ///< Defines the upper velocity value limit of a velocity split (only if an user defined limit was set, thus a value not equal to 128/NumberOfSplits, else this value is 0).
            Sample*            pSample;                       ///< Points to the Sample which is assigned to the dimension region.
            // Sample Amplitude EG/LFO
            uint16_t           EG1PreAttack;                  ///< Preattack value of the sample amplitude EG (0 - 1000 permille).
            double             EG1Attack;                     ///< Attack time of the sample amplitude EG (0.000 - 60.000s).
            double             EG1Decay1;                     ///< Decay time of the sample amplitude EG (0.000 - 60.000s).
            double             EG1Decay2;                     ///< Only if <i>EG1InfiniteSustain == false</i>: 2nd decay stage time of the sample amplitude EG (0.000 - 60.000s).
            bool               EG1InfiniteSustain;            ///< If <i>true</i>, instead of going into Decay2 phase, Decay1 level will be hold until note will be released.
            uint16_t           EG1Sustain;                    ///< Sustain value of the sample amplitude EG (0 - 1000 permille).
            double             EG1Release;                    ///< Release time of the sample amplitude EG (0.000 - 60.000s).
            bool               EG1Hold;                       ///< If <i>true</i>, Decay1 stage should be postponed until the sample reached the sample loop start.
            eg1_ctrl_t         EG1Controller;                 ///< MIDI Controller which has influence on sample amplitude EG parameters (attack, decay, release).
            bool               EG1ControllerInvert;           ///< Invert values coming from defined EG1 controller.
            uint8_t            EG1ControllerAttackInfluence;  ///< Amount EG1 Controller has influence on the EG1 Attack time (0 - 3, where 0 means off).
            uint8_t            EG1ControllerDecayInfluence;   ///< Amount EG1 Controller has influence on the EG1 Decay time (0 - 3, where 0 means off).
            uint8_t            EG1ControllerReleaseInfluence; ///< Amount EG1 Controller has influence on the EG1 Release time (0 - 3, where 0 means off).
            double             LFO1Frequency;                 ///< Frequency of the sample amplitude LFO (0.10 - 10.00 Hz).
            uint16_t           LFO1InternalDepth;             ///< Firm pitch of the sample amplitude LFO (0 - 1200 cents).
            uint16_t           LFO1ControlDepth;              ///< Controller depth influencing sample amplitude LFO pitch (0 - 1200 cents).
            lfo1_ctrl_t        LFO1Controller;                ///< MIDI Controller which controls sample amplitude LFO.
            bool               LFO1FlipPhase;                 ///< Inverts phase of the sample amplitude LFO wave.
            bool               LFO1Sync;                      ///< If set to <i>true</i> only one LFO should be used for all voices.
            // Filter Cutoff Frequency EG/LFO
            uint16_t           EG2PreAttack;                  ///< Preattack value of the filter cutoff EG (0 - 1000 permille).
            double             EG2Attack;                     ///< Attack time of the filter cutoff EG (0.000 - 60.000s).
            double             EG2Decay1;                     ///< Decay time of the filter cutoff EG (0.000 - 60.000s).
            double             EG2Decay2;                     ///< Only if <i>EG2InfiniteSustain == false</i>: 2nd stage decay time of the filter cutoff EG (0.000 - 60.000s).
            bool               EG2InfiniteSustain;            ///< If <i>true</i>, instead of going into Decay2 phase, Decay1 level will be hold until note will be released.
            uint16_t           EG2Sustain;                    ///< Sustain value of the filter cutoff EG (0 - 1000 permille).
            double             EG2Release;                    ///< Release time of the filter cutoff EG (0.000 - 60.000s).
            eg2_ctrl_t         EG2Controller;                 ///< MIDI Controller which has influence on filter cutoff EG parameters (attack, decay, release).
            bool               EG2ControllerInvert;           ///< Invert values coming from defined EG2 controller.
            uint8_t            EG2ControllerAttackInfluence;  ///< Amount EG2 Controller has influence on the EG2 Attack time (0 - 3, where 0 means off).
            uint8_t            EG2ControllerDecayInfluence;   ///< Amount EG2 Controller has influence on the EG2 Decay time (0 - 3, where 0 means off).
            uint8_t            EG2ControllerReleaseInfluence; ///< Amount EG2 Controller has influence on the EG2 Release time (0 - 3, where 0 means off).
            double             LFO2Frequency;                 ///< Frequency of the filter cutoff LFO (0.10 - 10.00 Hz).
            uint16_t           LFO2InternalDepth;             ///< Firm pitch of the filter cutoff LFO (0 - 1200 cents).
            uint16_t           LFO2ControlDepth;              ///< Controller depth influencing filter cutoff LFO pitch (0 - 1200).
            lfo2_ctrl_t        LFO2Controller;                ///< MIDI Controlle which controls the filter cutoff LFO.
            bool               LFO2FlipPhase;                 ///< Inverts phase of the filter cutoff LFO wave.
            bool               LFO2Sync;                      ///< If set to <i>true</i> only one LFO should be used for all voices.
            // Sample Pitch EG/LFO
            double             EG3Attack;                     ///< Attack time of the sample pitch EG (0.000 - 10.000s).
            int16_t            EG3Depth;                      ///< Depth of the sample pitch EG (-1200 - +1200).
            double             LFO3Frequency;                 ///< Frequency of the sample pitch LFO (0.10 - 10.00 Hz).
            int16_t            LFO3InternalDepth;             ///< Firm depth of the sample pitch LFO (-1200 - +1200 cents).
            int16_t            LFO3ControlDepth;              ///< Controller depth of the sample pitch LFO (-1200 - +1200 cents).
            lfo3_ctrl_t        LFO3Controller;                ///< MIDI Controller which controls the sample pitch LFO.
            bool               LFO3Sync;                      ///< If set to <i>true</i> only one LFO should be used for all voices.
            // Filter
            bool               VCFEnabled;                    ///< If filter should be used.
            vcf_type_t         VCFType;                       ///< Defines the general filter characteristic (lowpass, highpass, bandpass, etc.).
            vcf_cutoff_ctrl_t  VCFCutoffController;           ///< Specifies which external controller has influence on the filter cutoff frequency.
            uint8_t            VCFCutoff;                     ///< Max. cutoff frequency.
            curve_type_t       VCFVelocityCurve;              ///< Defines a transformation curve for the incoming velocity values, affecting the VCF.
            uint8_t            VCFVelocityScale;              ///< (0-127) Amount velocity controls VCF cutoff frequency (only if no other VCF cutoff controller is defined).
            uint8_t            VCFVelocityDynamicRange;       ///< 0x04 = lowest, 0x00 = highest
            uint8_t            VCFResonance;                  ///< Firm internal filter resonance weight.
            bool               VCFResonanceDynamic;           ///< If <i>true</i>: Increases the resonance Q according to changes of controllers that actually control the VCF cutoff frequency (EG2, ext. VCF MIDI controller).
            vcf_res_ctrl_t     VCFResonanceController;        ///< Specifies which external controller has influence on the filter resonance Q.
            bool               VCFKeyboardTracking;           ///< If <i>true</i>: VCF cutoff frequence will be dependend to the note key position relative to the defined breakpoint value.
            uint8_t            VCFKeyboardTrackingBreakpoint; ///< See VCFKeyboardTracking (0 - 127).
            // Key Velocity Transformations
            curve_type_t       VelocityResponseCurve;         ///< Defines a transformation curve to the incoming velocity values affecting amplitude.
            uint8_t            VelocityResponseDepth;         ///< Dynamic range of velocity affecting amplitude (0 - 4).
            uint8_t            VelocityResponseCurveScaling;  ///< 0 - 127
            curve_type_t       ReleaseVelocityResponseCurve;  ///< Defines a transformation curve to the incoming release veloctiy values affecting envelope times.
            uint8_t            ReleaseVelocityResponseDepth;  ///< Dynamic range of release velocity affecting envelope time (0 - 4).
            uint8_t            ReleaseTriggerDecay;           ///< 0 - 8
            // Mix / Layer
            crossfade_t        Crossfade;
            bool               PitchTrack;                    ///< If <i>true</i>: sample will be pitched according to the key position (this will be disabled for drums for example).
            dim_bypass_ctrl_t  DimensionBypass;               ///< If defined, the MIDI controller can switch on/off the dimension in realtime.
            int8_t             Pan;                           ///< Panorama / Balance (-64..0..63 <-> left..middle..right)
            bool               SelfMask;                      ///< If <i>true</i>: high velocity notes will stop low velocity notes at the same note, with that you can save voices that wouldn't be audible anyway.
            attenuation_ctrl_t AttenuationController;         ///< MIDI Controller which has influence on the volume level of the sample (or entire sample group).
            bool               InvertAttenuationController;   ///< Inverts the values coming from the defined Attenuation Controller.
            uint8_t            AttenuationControllerThreshold;///< 0-127
            uint8_t            ChannelOffset;                 ///< Audio output where the audio signal of the dimension region should be routed to (0 - 9).
            bool               SustainDefeat;                 ///< If <i>true</i>: Sustain pedal will not hold a note.
            bool               MSDecode;                      ///< Gigastudio flag: defines if Mid Side Recordings should be decoded.
            uint16_t           SampleStartOffset;             ///< Number of samples the sample start should be moved (0 - 2000).
            // derived attributes from DLS::Sampler
            DLS::Sampler::UnityNote;
            DLS::Sampler::FineTune;
            DLS::Sampler::Gain;
            DLS::Sampler::SampleLoops;
            DLS::Sampler::pSampleLoops;

            // Methods
            double GetVelocityAttenuation(uint8_t MIDIKeyVelocity);
        protected:
            DimensionRegion(RIFF::List* _3ewl);
           ~DimensionRegion();
            friend class Region;
        private:
            typedef enum { ///< Used to decode attenuation, EG1 and EG2 controller
                _lev_ctrl_none              = 0x00,
                _lev_ctrl_modwheel          = 0x03, ///< Modulation Wheel (MIDI Controller 1)
                _lev_ctrl_breath            = 0x05, ///< Breath Controller (Coarse, MIDI Controller 2)
                _lev_ctrl_foot              = 0x07, ///< Foot Pedal (Coarse, MIDI Controller 4)
                _lev_ctrl_effect1           = 0x0d, ///< Effect Controller 1 (Coarse, MIDI Controller 12)
                _lev_ctrl_effect2           = 0x0f, ///< Effect Controller 2 (Coarse, MIDI Controller 13)
                _lev_ctrl_genpurpose1       = 0x11, ///< General Purpose Controller 1 (Slider, MIDI Controller 16)
                _lev_ctrl_genpurpose2       = 0x13, ///< General Purpose Controller 2 (Slider, MIDI Controller 17)
                _lev_ctrl_genpurpose3       = 0x15, ///< General Purpose Controller 3 (Slider, MIDI Controller 18)
                _lev_ctrl_genpurpose4       = 0x17, ///< General Purpose Controller 4 (Slider, MIDI Controller 19)
                _lev_ctrl_portamentotime    = 0x0b, ///< Portamento Time (Coarse, MIDI Controller 5)
                _lev_ctrl_sustainpedal      = 0x01, ///< Sustain Pedal (MIDI Controller 64)
                _lev_ctrl_portamento        = 0x19, ///< Portamento (MIDI Controller 65)
                _lev_ctrl_sostenutopedal    = 0x1b, ///< Sostenuto Pedal (MIDI Controller 66)
                _lev_ctrl_softpedal         = 0x09, ///< Soft Pedal (MIDI Controller 67)
                _lev_ctrl_genpurpose5       = 0x1d, ///< General Purpose Controller 5 (Button, MIDI Controller 80)
                _lev_ctrl_genpurpose6       = 0x1f, ///< General Purpose Controller 6 (Button, MIDI Controller 81)
                _lev_ctrl_genpurpose7       = 0x21, ///< General Purpose Controller 7 (Button, MIDI Controller 82)
                _lev_ctrl_genpurpose8       = 0x23, ///< General Purpose Controller 8 (Button, MIDI Controller 83)
                _lev_ctrl_effect1depth      = 0x25, ///< Effect 1 Depth (MIDI Controller 91)
                _lev_ctrl_effect2depth      = 0x27, ///< Effect 2 Depth (MIDI Controller 92)
                _lev_ctrl_effect3depth      = 0x29, ///< Effect 3 Depth (MIDI Controller 93)
                _lev_ctrl_effect4depth      = 0x2b, ///< Effect 4 Depth (MIDI Controller 94)
                _lev_ctrl_effect5depth      = 0x2d, ///< Effect 5 Depth (MIDI Controller 95)
                _lev_ctrl_channelaftertouch = 0x2f, ///< Channel Key Pressure
                _lev_ctrl_velocity          = 0xff  ///< Key Velocity
            } _lev_ctrl_t;        
            typedef std::map<uint32_t, double*> VelocityTableMap;

            static uint              Instances;                  ///< Number of DimensionRegion instances.
            static VelocityTableMap* pVelocityTables;            ///< Contains the tables corresponding to the various velocity parameters (VelocityResponseCurve and VelocityResponseDepth).
            double*                  pVelocityAttenuationTable;  ///< Points to the velocity table corresponding to the velocity parameters of this DimensionRegion.
            
            leverage_ctrl_t DecodeLeverageController(_lev_ctrl_t EncodedController);
    };

    /** Encapsulates sample waves used for playback. */
    class Sample : public DLS::Sample {
        public:
            uint16_t       SampleGroup;
            uint32_t       Manufacturer;      ///< Specifies the MIDI Manufacturer's Association (MMA) Manufacturer code for the sampler intended to receive this file's waveform. If no particular manufacturer is to be specified, a value of 0 should be used.
            uint32_t       Product;           ///< Specifies the MIDI model ID defined by the manufacturer corresponding to the Manufacturer field. If no particular manufacturer's product is to be specified, a value of 0 should be used.
            uint32_t       SamplePeriod;      ///< Specifies the duration of time that passes during the playback of one sample in nanoseconds (normally equal to 1 / Samplers Per Second, where Samples Per Second is the value found in the format chunk).
            uint32_t       MIDIUnityNote;     ///< Specifies the musical note at which the sample will be played at it's original sample rate.
            uint32_t       FineTune;          ///< Specifies the fraction of a semitone up from the specified MIDI unity note field. A value of 0x80000000 means 1/2 semitone (50 cents) and a value of 0x00000000 means no fine tuning between semitones.
            smpte_format_t SMPTEFormat;       ///< Specifies the Society of Motion Pictures and Television E time format used in the following <i>SMPTEOffset</i> field. If a value of 0 is set, <i>SMPTEOffset</i> should also be set to 0.
            uint32_t       SMPTEOffset;       ///< The SMPTE Offset value specifies the time offset to be used for the synchronization / calibration to the first sample in the waveform. This value uses a format of 0xhhmmssff where hh is a signed value that specifies the number of hours (-23 to 23), mm is an unsigned value that specifies the number of minutes (0 to 59), ss is an unsigned value that specifies the number of seconds (0 to 59) and ff is an unsigned value that specifies the number of frames (0 to -1).
            uint32_t       Loops;             ///< Number of defined sample loops (so far only seen single loops in gig files - please report me if you encounter more!).
            uint32_t       LoopID;            ///< Specifies the unique ID that corresponds to one of the defined cue points in the cue point list (only if Loops > 0), as the Gigasampler format only allows one loop definition at the moment, this attribute isn't really useful for anything.
            loop_type_t    LoopType;          ///< The type field defines how the waveform samples will be looped (only if Loops > 0).
            uint32_t       LoopStart;         ///< The start value specifies the offset (in sample points) in the waveform data of the first sample to be played in the loop (only if Loops > 0).
            uint32_t       LoopEnd;           ///< The end value specifies the offset (in sample points) in the waveform data which represents the end of the loop (only if Loops > 0).
            uint32_t       LoopSize;          ///< Length of the looping area (in sample points) which is equivalent to <i>LoopEnd - LoopStart</i>.
            uint32_t       LoopFraction;      ///< The fractional value specifies a fraction of a sample at which to loop (only if Loops > 0). This allows a loop to be fine tuned at a resolution greater than one sample. A value of 0 means no fraction, a value of 0x80000000 means 1/2 of a sample length. 0xFFFFFFFF is the smallest fraction of a sample that can be represented.
            uint32_t       LoopPlayCount;     ///< Number of times the loop should be played (only if Loops > 0, a value of 0 = infinite).
            bool           Compressed;        ///< If the sample wave is compressed (probably just interesting for instrument and sample editors, as this library already handles the decompression in it's sample access methods anyway).

            // own methods
            buffer_t      LoadSampleData();
            buffer_t      LoadSampleData(unsigned long SampleCount);
            buffer_t      LoadSampleDataWithNullSamplesExtension(uint NullSamplesCount);
            buffer_t      LoadSampleDataWithNullSamplesExtension(unsigned long SampleCount, uint NullSamplesCount);
            buffer_t      GetCache();
            // overridden methods
            void          ReleaseSampleData();
            unsigned long SetPos(unsigned long SampleCount, RIFF::stream_whence_t Whence = RIFF::stream_start);
            unsigned long GetPos();
            unsigned long Read(void* pBuffer, unsigned long SampleCount);
            unsigned long ReadAndLoop(void* pBuffer, unsigned long SampleCount, playback_state_t* pPlaybackState);
        protected:
            static unsigned int  Instances;               ///< Number of instances of class Sample.
            static unsigned long DecompressionBufferSize; ///< Current size of the decompression buffer.
            static void*         pDecompressionBuffer;    ///< Small buffer used for decompression only.
            unsigned long        FrameOffset;             ///< Current offset (sample points) in current sample frame (for decompression only).
            unsigned long*       FrameTable;              ///< For positioning within compressed samples only: stores the offset values for each frame.
            unsigned long        SamplePos;               ///< For compressed samples only: stores the current position (in sample points).
            buffer_t             RAMCache;                ///< Buffers samples (already uncompressed) in RAM.

            Sample(File* pFile, RIFF::List* waveList, unsigned long WavePoolOffset);
           ~Sample();
            /**
             * Swaps the order of the data words in the given memory area
             * with a granularity given by \a WordSize.
             *
             * @param pData    - pointer to the memory area to be swapped
             * @param AreaSize - size of the memory area to be swapped (in bytes)
             * @param WordSize - size of the data words (in bytes)
             */
            inline void SwapMemoryArea(void* pData, unsigned long AreaSize, uint WordSize) {
                switch (WordSize) { // TODO: unefficient
                    case 1: {
                        uint8_t* pDst = (uint8_t*) pData;
                        uint8_t  cache;
                        unsigned long lo = 0, hi = AreaSize - 1;
                        for (; lo < hi; hi--, lo++) {
                            cache    = pDst[lo];
                            pDst[lo] = pDst[hi];
                            pDst[hi] = cache;
                        }
                        break;
                    }
                    case 2: {
                        uint16_t* pDst = (uint16_t*) pData;
                        uint16_t  cache;
                        unsigned long lo = 0, hi = (AreaSize >> 1) - 1;
                        for (; lo < hi; hi--, lo++) {
                            cache    = pDst[lo];
                            pDst[lo] = pDst[hi];
                            pDst[hi] = cache;
                        }
                        break;
                    }
                    case 4: {
                        uint32_t* pDst = (uint32_t*) pData;
                        uint32_t  cache;
                        unsigned long lo = 0, hi = (AreaSize >> 2) - 1;
                        for (; lo < hi; hi--, lo++) {
                            cache    = pDst[lo];
                            pDst[lo] = pDst[hi];
                            pDst[hi] = cache;
                        }
                        break;
                    }
                    default: {
                        uint8_t* pCache = new uint8_t[WordSize]; // TODO: unefficient
                        unsigned long lo = 0, hi = AreaSize - WordSize;
                        for (; lo < hi; hi -= WordSize, lo += WordSize) {
                            memcpy(pCache, (uint8_t*) pData + lo, WordSize);
                            memcpy((uint8_t*) pData + lo, (uint8_t*) pData + hi, WordSize);
                            memcpy((uint8_t*) pData + hi, pCache, WordSize);
                        }
                        delete[] pCache;
                        break;
                    }
                }
            }
            inline long Min(long A, long B) {
                return (A > B) ? B : A;
            }
            inline long Abs(long val) { return (val > 0) ? val : -val; }
        private:
            void ScanCompressedSample();
            friend class File;
            friend class Region;
    };

    // TODO: <3dnl> list not used yet - not important though (just contains optional descriptions for the dimensions)
    /** Defines <i>Region</i> information of an <i>Instrument</i>. */
    class Region : public DLS::Region {
        public:
            unsigned int            Dimensions;               ///< Number of defined dimensions.
            dimension_def_t         pDimensionDefinitions[5]; ///< Defines the five possible dimensions (the dimension's controller and number of bits/splits).
            uint32_t                DimensionRegions;         ///< Total number of DimensionRegions this Region contains.
            DimensionRegion*        pDimensionRegions[32];    ///< Pointer array to the 32 possible dimension regions (reflects NULL for dimension regions not in use). Avoid to access the array directly and better use GetDimensionRegionByValue() instead, but of course in some cases it makes sense to use the array (e.g. iterating through all DimensionRegions).

            DimensionRegion* GetDimensionRegionByValue(uint Dim4Val, uint Dim3Val, uint Dim2Val, uint Dim1Val, uint Dim0Val);
            DimensionRegion* GetDimensionRegionByBit(uint8_t Dim4Bit, uint8_t Dim3Bit, uint8_t Dim2Bit, uint8_t Dim1Bit, uint8_t Dim0Bit);
            Sample*          GetSample();
        protected:
            uint8_t VelocityTable[128]; ///< For velocity dimensions with custom defined zone ranges only: used for fast converting from velocity MIDI value to dimension bit number.

            Region(Instrument* pInstrument, RIFF::List* rgnList);
            void LoadDimensionRegions(RIFF::List* rgn);
            Sample* GetSampleFromWavePool(unsigned int WavePoolTableIndex);
           ~Region();
            friend class Instrument;
    };

    /** Provides all neccessary information for the synthesis of an <i>Instrument</i>. */
    class Instrument : protected DLS::Instrument {
        public:
            // derived attributes from DLS::Resource
            DLS::Resource::pInfo;
            DLS::Resource::pDLSID;
            // derived attributes from DLS::Instrument
            DLS::Instrument::IsDrum;
            DLS::Instrument::MIDIBank;
            DLS::Instrument::MIDIBankCoarse;
            DLS::Instrument::MIDIBankFine;
            DLS::Instrument::MIDIProgram;
            DLS::Instrument::Regions;
            // own attributes
            int32_t   Attenuation;       ///< in dB
            uint16_t  EffectSend;
            int16_t   FineTune;          ///< in cents
            uint16_t  PitchbendRange;    ///< Number of semitones pitchbend controller can pitch (default is 2).
            bool      PianoReleaseMode;
            range_t   DimensionKeyRange; ///< 0-127 (where 0 means C1 and 127 means G9)


            // derived methods from DLS::Resource
            DLS::Resource::GetParent;
            // overridden methods
            Region*   GetFirstRegion();
            Region*   GetNextRegion();
            // own methods
            Region*   GetRegion(unsigned int Key);
        protected:
            Region**  pRegions;            ///< Pointer array to the regions
            Region*   RegionKeyTable[128]; ///< fast lookup for the corresponding Region of a MIDI key
            int       RegionIndex;

            Instrument(File* pFile, RIFF::List* insList);
           ~Instrument();
            friend class File;
    };

    // TODO: <3gnm> chunk not added yet (just contains the names of the sample groups)
    /** Parses Gigasampler files and provides abstract access to the data. */
    class File : protected DLS::File {
        public:
            // derived attributes from DLS::Resource
            DLS::Resource::pInfo;
            DLS::Resource::pDLSID;
            // derived attributes from DLS::File
            DLS::File::pVersion;
            DLS::File::Instruments;

            // derived methods from DLS::Resource
            DLS::Resource::GetParent;
            // overridden  methods
            File(RIFF::File* pRIFF);
            Sample*     GetFirstSample();     ///< Returns a pointer to the first <i>Sample</i> object of the file, <i>NULL</i> otherwise.
            Sample*     GetNextSample();      ///< Returns a pointer to the next <i>Sample</i> object of the file, <i>NULL</i> otherwise.
            Instrument* GetFirstInstrument(); ///< Returns a pointer to the first <i>Instrument</i> object of the file, <i>NULL</i> otherwise.
            Instrument* GetNextInstrument();  ///< Returns a pointer to the next <i>Instrument</i> object of the file, <i>NULL</i> otherwise.
            Instrument* GetInstrument(uint index);
           ~File() {};
        protected:
            typedef std::list<Sample*>     SampleList;
            typedef std::list<Instrument*> InstrumentList;

            SampleList*              pSamples;
            SampleList::iterator     SamplesIterator;
            InstrumentList*          pInstruments;
            InstrumentList::iterator InstrumentsIterator;

            void LoadSamples();
            void LoadInstruments();
            friend class Region;
    };

    /** Will be thrown whenever a gig specific error occurs while trying to access a Gigasampler File. */
    class Exception : public DLS::Exception {
        public:
            Exception(String Message);
            void PrintMessage();
    };

} // namespace gig

#endif // __GIG_H__
