<?php
include '../tmpl/header.php';
?>

<h1>LinuxSampler sfz Support</h1>
<h2>sfz v1 opcodes</h2>
<p>The sfz v1 opcodes are defined in the <a href="http://www.cakewalk.com/DevXchange/article.aspx?aid=108">sfz File Format Specification</a>.</p>
<table border="1">
<tr style="background: #eee"><th>Opcode</th><th>LS<br>support</th><th>Comment</th></tr>
<tr><td style="background: #ddd" colspan="3"><b>Instrument Structure</b></td></tr>
<tr><td>&lt;region><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>&lt;group><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Sample Definition</b></td></tr>
<tr><td>sample</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Input Controls</b></td></tr>
<tr><td>lochan</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hichan</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>key</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lovel</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hivel</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lobend</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hibend</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lochanaft</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hichanaft</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lopolyaft</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>hipolyaft</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lorand</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>hirand</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lobpm</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>hibpm</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>seq_length</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>seq_position</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_last</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_down</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_up</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_previous</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>sw_vel</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>trigger</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>group</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>off_by</td><td style="background: #90ff90; text-align: center">Yes</td><td>Alias: offby</td></tr>
<tr><td>off_mode</td><td style="background: #90ff90; text-align: center">Yes</td><td>Alias: offmode</td></tr>
<tr><td>on_loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>on_hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Performance Parameters</b></td></tr>
<tr><td style="background: #ddd" colspan="3">Sample Player</td></tr>
<tr><td>delay</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>delay_random</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>delay_ccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: delay_onccN</td></tr>
<tr><td>offset<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>offset_random</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>offset_ccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: offset_onccN</td></tr>
<tr><td>end</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>count</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>loop_mode</td><td style="background: #ffb">P?</td><td>Alias: loopmode. bara delvis, dvs om loop eller inte (+ one_shot?)
    no_loop, one_shot, loop_continuous, loop_sustain</td></tr>
<tr><td>loop_start</td><td style="background: #ffb">P?</td><td>Alias: loopstart. är det rätt? - TODO use sample loop when loop_start
    not defined</td></tr>
<tr><td>loop_end</td><td style="background: #ffb">P?</td><td>Alias: loopend. är det rätt? - TODO &quot;</td></tr>
<tr><td>sync_beats</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>sync_offset</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch</td></tr>
<tr><td>transpose</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>tune</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitch_keycenter</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitch_keytrack</td><td style="background: #ffb; text-align: center">Partial</td><td>Zero is correct (no change in pitch) but all other values are interpreted as 100.</td></tr>
<tr><td>pitch_veltrack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitch_random</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>bend_up</td><td style="background: #ff9090; text-align: center">No</td><td>Alias: bendup</td></tr>
<tr><td>bend_down</td><td style="background: #ff9090; text-align: center">No</td><td>Alias: benddown</td></tr>
<tr><td>bend_step</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch EG</td></tr>
<tr><td>pitcheg_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_start</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_attack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_hold</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td>Could be fine-tuned: sfzplayer uses a linear curve, LS uses an exponential.</td></tr>
<tr><td>pitcheg_sustain</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_release</td><td style="background: #90ff90; text-align: center">Yes</td><td>Could be fine-tuned: sfzplayer uses a linear curve, LS uses an exponential.</td></tr>
<tr><td>pitcheg_depth<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2delay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2attack<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2hold<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2decay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2sustain<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2release<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_vel2depth<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch LFO</td></tr>
<tr><td>pitchlfo_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_fade</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_freq</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_depth</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_depthccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_depthchanaft<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_depthpolyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_freqccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_freqchanaft<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_freqpolyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter</td></tr>
<tr><td>fil_type</td><td style="background: #90ff90; text-align: center">Yes</td><td>Alias: filtype<p>Supported v1 values (all): lpf_1p, hpf_1p, lpf_2p, hpf_2p, bfp_2p, brf_2p.<p>Supported v2 values: lpf_4p, hpr_4p, lpf_6p, hpf_6p.<p>Unsupported v2 values: bpf_1p, brf_1p, apf_1p, pkf_2p, lpf_2p_sv, hpf_2p_sv, bpf_2p_sv, brf_2p_sv, comb, pink.</td></tr>
<tr><td>cutoff</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>cutoff_ccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: cutoff_onccN</td></tr>
<tr><td>cutoff_chanaft</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>cutoff_polyaft</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fil_keytrack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fil_keycenter</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fil_veltrack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fil_random</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter EG</td></tr>
<tr><td>fileg_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_start</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_attack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_hold</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_sustain</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_release</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_depth<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2delay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2attack<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2hold<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2decay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2sustain<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2release<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_vel2depth<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter LFO</td></tr>
<tr><td>fillfo_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_fade</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_freq</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_depth</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_depthccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_depthchanaft<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_depthpolyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>fillfo_freqccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_freqchanaft<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_freqpolyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Amplifier</td></tr>
<tr><td>volume</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pan</td><td style="background: #ffb">P?</td><td>funkar, men kan finetunas</td></tr>
<tr><td>width</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>position</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amp_keytrack</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amp_keycenter</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amp_veltrack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amp_velcurve_N</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amp_random</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>rt_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>output<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>gain_ccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: gain_onccN</td></tr>
<tr><td>xfin_lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfin_hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfout_lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfout_hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xf_keycurve</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfin_lovel</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfin_hivel</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfout_lovel</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfout_hivel</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xf_velcurve</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfin_loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfin_hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfout_loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xfout_hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>xf_cccurve</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Amplifier EG</td></tr>
<tr><td>ampeg_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_start</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_attack</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_hold</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_sustain</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_release</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_vel2delay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_vel2attack<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_vel2hold<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_vel2decay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_vel2sustain<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_vel2release<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>ampeg_delayccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_delay_onccN</td></tr>
<tr><td>ampeg_startccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_start_onccN</td></tr>
<tr><td>ampeg_attackccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_attack_onccN</td></tr>
<tr><td>ampeg_holdccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_hold_onccN</td></tr>
<tr><td>ampeg_decayccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_decay_onccN</td></tr>
<tr><td>ampeg_sustainccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_sustain_onccN</td></tr>
<tr><td>ampeg_releaseccN<td style="background: #90ff90; text-align: center">Yes</td><td>v2-alias: ampeg_release_onccN</td></tr>
<tr><td style="background: #ddd" colspan="3">Amplifier LFO</td></tr>
<tr><td>amplfo_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_fade</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_freq</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_depth</td><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_depthccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_depthchanaft<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_depthpolyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amplfo_freqccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_freqchanaft<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_freqpolyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Equalizer</td></tr>
<tr><td>eq1_freq</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq2_freq</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq3_freq</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq1_freqccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq1_freq_onccN</td></tr>
<tr><td>eq2_freqccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq2_freq_onccN</td></tr>
<tr><td>eq3_freqccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq3_freq_onccN</td></tr>
<tr><td>eq1_vel2freq</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq2_vel2freq</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq3_vel2freq</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq1_bw</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq2_bw</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq3_bw</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq1_bwccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq1_bw_onccN</td></tr>
<tr><td>eq2_bwccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq2_bw_onccN</td></tr>
<tr><td>eq3_bwccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq3_bq_onccN</td></tr>
<tr><td>eq1_gain</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq2_gain</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq3_gain</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq1_gainccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq1_gain_onccN</td></tr>
<tr><td>eq2_gainccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq2_gain_onccN</td></tr>
<tr><td>eq3_gainccN</td><td style="background: #ff9090; text-align: center">No</td><td>v2-alias: eq3_gain_onccN</td></tr>
<tr><td>eq1_vel2gain</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq2_vel2gain</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>eq3_vel2gain</td><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Effects</td></tr>
<tr><td>effect1<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>effect2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
</table>

<h2>sfz v2 opcodes</h2>
<p>The sfz v2 opcodes are listed in the book <a href="http://noisesculpture.com/cakewalk-synthesizers"><i>Cakewalk Synthesizers: From Presets to Power User</i></a> by Simon Cann.</p>
<p>The list below is not quite complete, the book also has opcodes for a noise generator and sfz v2 effects.</p>

<table border="1">
<tr style="background: #eee"><th>Opcode</th><th>LS<br>support</th><th>Comment</th></tr>
<tr><td style="background: #ddd" colspan="3"><b>Instrument Structure</b></td></tr>
<tr><td>&lt;global><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>&lt;control><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>&lt;curve><td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>&lt;effects><td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Sample Definition</b></td></tr>
<!-- <tr><td>sample<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr> -->
<tr><td>md5<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>waveguide<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>&lt;control> Header Directives</b></td></tr>
<tr><td>default_path<td style="background: #ffb; text-align: center">P?</td><td>"funkar kanske, om det inte ska vara en /"</td></tr>
<tr><td>octave_offset<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>note_offset<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>set_ccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>#define<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Loading</b></td></tr>
<tr><td>load_mode<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>load_start<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>load_end<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>sample_quality<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>image<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Wavetable Oscillator</b></td></tr>
<tr><td>oscillator<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_phase<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_quality<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_table_size<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_multi<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_mode<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_detune<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_detune_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_mod_depth<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_mod_depth_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>oscillator_mod_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Input Controls</b></td></tr>
<tr><td>loprog<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>hiprog<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lotimer<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>hitimer<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>polyphony<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>reverse_loccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>reverse_hiccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>start_loccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>start_hiccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>stop_loccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>stop_hiccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>sustain_sw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>sustenuto_sw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>rt_dead<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3"><b>Performance Parameters</b></td></tr>
<tr><td style="background: #ddd" colspan="3">Sample Player</td></tr>
<tr><td>delay_beats<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>stop_beats<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>delay_samples<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>delay_samples_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>loop_crossfade<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Amplifier</td></tr>
<tr><td>volume_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>volume_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>volume_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>pan_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>pan_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>pan_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>width_onccN<td style="background: #ff9090; text-align: center">No</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>width_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>width_curveccN<td style="background: #ff9090; text-align: center">No</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch</td></tr>
<tr><td>pitch_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>pitch_curveccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>pitch_stepccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>pitch_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>Not listed in the book, but supported in Dimension LE.</td></tr>
<tr><td>bend_stepup<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>bend_stepdown<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter</td></tr>
<tr><td>fil2_type<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff2_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>cutoff2_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff_stepccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff2_stepccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>cutoff2_curveccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>resonance2_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>resonance2_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance_stepccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance2_stepccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>resonance_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>resonance2_curveccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>fil2_keytrack<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>fil2_keycenter<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>fil2_veltrack<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">EG</td></tr>
<tr><td>egN_timeX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_timeX_onccY<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_levelX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_levelX_onccY<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_shapeX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_curveX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_sustain<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_loop<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_loop_count<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_volume<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_amplitude<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_pan<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_width<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_pan_curve<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_pan_curveccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_volume_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_amplitude_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_pan_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_width_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_freq_lfoX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_depth_lfoX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_depthadd_lfoX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_pitch<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_pitch_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_cutoff<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_cutoff2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_resonance<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_resonance2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_cutoff_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_cutoff2_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_resonance_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>egN_resonance2_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq1freq<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq2freq<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq3freq<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq1bw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq2bw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq3bw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq1gain<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq2gain<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq3gain<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq1freq_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq2freq_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq3freq_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq1bw_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq2bw_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq3bw_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq1gain_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq2gain_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_eq3gain_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_decim<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_bitred<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_rectify<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_ringmod<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_noiselevel<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_noisestep<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_noisetone<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_driveshape<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_decim_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_bitred_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_rectify_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_ringmod_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_noiselevel_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_noisestep_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_noisetone_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_driveshape_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">LFO</td></tr>
<tr><td>lfoN_freq<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_freq_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_freq_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_delay<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_delay_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_fade<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_fade_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_phase<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_phase_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_count<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_wave<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_steps<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_stepX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_smooth<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_smooth_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_volume<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_amplitude<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pan<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_width<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_volume_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_amplitude_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pan_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_width_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_volume_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_amplitude_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pan_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_width_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_volume_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_amplitude_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pan_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_width_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_freq_lfoX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_depth_lfoX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_depthadd_lfoX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pitch<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pitch_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pitch_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_pitch_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance2<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff2_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance_onccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance2_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff2_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance2_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_cutoff2_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_resonance2_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1freq<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2freq<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3freq<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1bw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2bw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3bw<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1gain<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2gain<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3gain<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1freq_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2freq_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3freq_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1bw_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2bw_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3bw_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1gain_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2gain_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3gain_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1freq_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2freq_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3freq_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1bw_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2bw_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3bw_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1gain_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2gain_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3gain_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1bw_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2bw_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3bw_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq1gain_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq2gain_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_eq3gain_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_decim<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_bitred<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noiselevel<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisestep<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisetone<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_drive<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_decim_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_bitred_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noiselevel_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisestep_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisetone_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_drive_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_decim_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_bitred_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noiselevel_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisestep_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisetone_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_drive_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_decim_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_bitred_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noiselevel_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisestep_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_noisetone_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_drive_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Curves</td></tr>
<tr><td>vN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
</table>
<h2>ARIA custom opcodes</h2>
<p>The ARIA Engine from Plouge / Garritan implements some <a href="http://www.plogue.com/phpBB3/viewtopic.php?f=14&t=4386">custom sfz opcodes</a>. Only some of them are listed here.</p>

<table border="1">
<tr style="background: #eee"><th>Opcode</th><th>LS<br>support</th><th>Comment</th></tr>
<tr><td>amplitude<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amplitude_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amplitude_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>amplitude_curveccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>pan_law<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
</table>
<h2>LinuxSampler extensions</h2>
<table border="1">
<tr style="background: #eee"><th>Opcode</th><th>LS<br>support</th><th>Comment</th></tr>
<tr><td style="background: #ddd" colspan="3">Amplifier</td></tr>
<tr><td>position_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>position_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>position_curveccN <td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>gain_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>gain_curveccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch</td></tr>
<tr><td>transpose_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>transpose_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>transpose_curveccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>tune_onccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>tune_smoothccN<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>tune_curveccN <td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter</td></tr>
<tr><td>cutoff2_chanaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>cutoff2_polyaft<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>fil2_random<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">EG</td></tr>
<tr><td>egN_position<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>egN_position_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">LFO</td></tr>
<tr><td>lfoN_depth<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_depth_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_position<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_position_onccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_position_smoothccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td>lfoN_position_stepccX<td style="background: #ff9090; text-align: center">No</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Amplifier LFO</td></tr>
<tr><td>amplfo_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>amplfo_fade_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter EG</td></tr>
<tr><td>fileg_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_start_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_attack_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_hold_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_decay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_sustain_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_release_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fileg_depth_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Filter LFO</td></tr>
<tr><td>fillfo_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>fillfo_fade_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch EG</td></tr>
<tr><td>pitcheg_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_start_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_attack_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_hold_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_decay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_sustain_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_release_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitcheg_depth_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td style="background: #ddd" colspan="3">Pitch LFO</td></tr>
<tr><td>pitchlfo_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
<tr><td>pitchlfo_fade_onccN<td style="background: #90ff90; text-align: center">Yes</td><td>&nbsp;</td></tr>
</table>

<?php
include '../tmpl/footer.php';
?>
