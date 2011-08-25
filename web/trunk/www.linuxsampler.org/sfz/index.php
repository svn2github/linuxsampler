<?php
include '../tmpl/header.php';
?>

<h2>SFZ support in LinuxSampler</h2>
<p>
  <table>
    <tr>
      <td>
        <img src="/gfx/logos/sfz.png" />
      </td>
      <td>
  SFZ is an open file format for samplers, currently evolving to a standard
  among many commercial samplers. The articulation files are ordinary human
  readable text files, which can be viewed and edited with any ordinary text
  editor. This page documents the current status of LinuxSampler regarding
  support of the SFZ format. Since development of the SFZ format engine in
  LinuxSampler is quickly evolving, this page may not be always up to date,
  so please also check the <a href="/">latest Subversion commits on our frontsite</a>.
      </td>
    </tr>
  </table>
</p>


<h2>SFZ v1 opcodes</h2>
<p>The SFZ version 1 opcodes are defined in the <a href="http://www.cakewalk.com/DevXchange/article.aspx?aid=108">SFZ File Format Specification</a>.</p>

<table class="decocomp">
<thead>
  <tr>
    <td class="decocomp_header">Opcode</td>
    <td class="decocomp_header">Supported</td>
    <td class="decocomp_header">Comment</td>
  </tr>
</thead>
<tbody>

<tr><td class="decocomp_header" colspan="3"><b>Instrument Structure</b></td></tr>
<tr><td class="decocomp">&lt;region><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">&lt;group><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Sample Definition</b></td></tr>
<tr><td class="decocomp">sample</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Input Controls</b></td></tr>
<tr><td class="decocomp">lochan</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hichan</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">key</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lovel</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hivel</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lobend</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hibend</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lochanaft</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hichanaft</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lopolyaft</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hipolyaft</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lorand</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hirand</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lobpm</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hibpm</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">seq_length</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">seq_position</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_last</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_down</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_up</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_previous</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sw_vel</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">trigger</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">group</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">off_by</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Alias: offby</td></tr>
<tr><td class="decocomp">off_mode</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Alias: offmode</td></tr>
<tr><td class="decocomp">on_loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">on_hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Performance Parameters</b></td></tr>
<tr><td class="decocomp_header" colspan="3">Sample Player</td></tr>
<tr><td class="decocomp">delay</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">delay_random</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">delay_ccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: delay_onccN</td></tr>
<tr><td class="decocomp">offset<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">offset_random</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">offset_ccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: offset_onccN</td></tr>
<tr><td class="decocomp">end</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">count</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">loop_mode</td><td style="background: #ffb; text-align: center">Partial</td><td class="decocomp">Alias: loopmode<br>Supported values: no_loop, one_shot, loop_continuous<br>Unsupported value: loop_sustain</td></tr>
<tr><td class="decocomp">loop_start</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Alias: loopstart</td></tr>
<tr><td class="decocomp">loop_end</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Alias: loopend</td></tr>
<tr><td class="decocomp">sync_beats</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sync_offset</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch</td></tr>
<tr><td class="decocomp">transpose</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">tune</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitch_keycenter</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitch_keytrack</td><td style="background: #ffb; text-align: center">Partial</td><td class="decocomp">Zero is correct (no change in pitch) but all other values are interpreted as 100.</td></tr>
<tr><td class="decocomp">pitch_veltrack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitch_random</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">bend_up</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Alias: bendup</td></tr>
<tr><td class="decocomp">bend_down</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Alias: benddown</td></tr>
<tr><td class="decocomp">bend_step</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch EG</td></tr>
<tr><td class="decocomp">pitcheg_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_start</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_attack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_hold</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Could be fine-tuned: sfzplayer uses a linear curve, LS uses an exponential.</td></tr>
<tr><td class="decocomp">pitcheg_sustain</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_release</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Could be fine-tuned: sfzplayer uses a linear curve, LS uses an exponential.</td></tr>
<tr><td class="decocomp">pitcheg_depth<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2delay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2attack<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2hold<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2decay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2sustain<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2release<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_vel2depth<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch LFO</td></tr>
<tr><td class="decocomp">pitchlfo_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_fade</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_freq</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_depth</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_depthccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_depthchanaft<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_depthpolyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_freqccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_freqchanaft<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_freqpolyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter</td></tr>
<tr><td class="decocomp">fil_type</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Alias: filtype<br>Supported v1 values (all): lpf_1p, hpf_1p, lpf_2p, hpf_2p, bfp_2p, brf_2p.<br>Supported v2 values: lpf_4p, hpr_4p, lpf_6p, hpf_6p.<br>Unsupported v2 values: bpf_1p, brf_1p, apf_1p, pkf_2p, lpf_2p_sv, hpf_2p_sv, bpf_2p_sv, brf_2p_sv, comb, pink.</td></tr>
<tr><td class="decocomp">cutoff</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff_ccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: cutoff_onccN</td></tr>
<tr><td class="decocomp">cutoff_chanaft</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff_polyaft</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil_keytrack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil_keycenter</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil_veltrack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil_random</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter EG</td></tr>
<tr><td class="decocomp">fileg_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_start</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_attack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_hold</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_sustain</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_release</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_depth<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2delay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2attack<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2hold<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2decay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2sustain<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2release<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_vel2depth<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter LFO</td></tr>
<tr><td class="decocomp">fillfo_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_fade</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_freq</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_depth</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_depthccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_depthchanaft<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_depthpolyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_freqccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_freqchanaft<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_freqpolyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Amplifier</td></tr>
<tr><td class="decocomp">volume</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pan</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Works, but can be fine-tuned. sfzplayer uses L=cos((100 + pan) / 200 * pi / 2) * sqrt(2), Dimension LE uses L=sqrt((100 - x) / 100), but LS uses a line segment approximation measured from GigaStudio, which lies somewhere between to other two.</td></tr>
<tr><td class="decocomp">width</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">position</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amp_keytrack</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amp_keycenter</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amp_veltrack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amp_velcurve_N</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amp_random</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">rt_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">output<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">gain_ccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: gain_onccN</td></tr>
<tr><td class="decocomp">xfin_lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfin_hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfout_lokey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfout_hikey</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xf_keycurve</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfin_lovel</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfin_hivel</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfout_lovel</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfout_hivel</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xf_velcurve</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfin_loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfin_hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfout_loccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xfout_hiccN</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">xf_cccurve</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Amplifier EG</td></tr>
<tr><td class="decocomp">ampeg_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_start</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_attack</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_hold</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_decay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_sustain</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_release</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_vel2delay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_vel2attack<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_vel2hold<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_vel2decay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_vel2sustain<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_vel2release<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">ampeg_delayccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_delay_onccN</td></tr>
<tr><td class="decocomp">ampeg_startccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_start_onccN</td></tr>
<tr><td class="decocomp">ampeg_attackccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_attack_onccN</td></tr>
<tr><td class="decocomp">ampeg_holdccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_hold_onccN</td></tr>
<tr><td class="decocomp">ampeg_decayccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_decay_onccN</td></tr>
<tr><td class="decocomp">ampeg_sustainccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_sustain_onccN</td></tr>
<tr><td class="decocomp">ampeg_releaseccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">v2-alias: ampeg_release_onccN</td></tr>

<tr><td class="decocomp_header" colspan="3">Amplifier LFO</td></tr>
<tr><td class="decocomp">amplfo_delay</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_fade</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_freq</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_depth</td><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_depthccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_depthchanaft<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_depthpolyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_freqccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_freqchanaft<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_freqpolyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Equalizer</td></tr>
<tr><td class="decocomp">eq1_freq</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq2_freq</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq3_freq</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq1_freqccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq1_freq_onccN</td></tr>
<tr><td class="decocomp">eq2_freqccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq2_freq_onccN</td></tr>
<tr><td class="decocomp">eq3_freqccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq3_freq_onccN</td></tr>
<tr><td class="decocomp">eq1_vel2freq</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq2_vel2freq</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq3_vel2freq</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq1_bw</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq2_bw</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq3_bw</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq1_bwccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq1_bw_onccN</td></tr>
<tr><td class="decocomp">eq2_bwccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq2_bw_onccN</td></tr>
<tr><td class="decocomp">eq3_bwccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq3_bq_onccN</td></tr>
<tr><td class="decocomp">eq1_gain</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq2_gain</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq3_gain</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq1_gainccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq1_gain_onccN</td></tr>
<tr><td class="decocomp">eq2_gainccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq2_gain_onccN</td></tr>
<tr><td class="decocomp">eq3_gainccN</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">v2-alias: eq3_gain_onccN</td></tr>
<tr><td class="decocomp">eq1_vel2gain</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq2_vel2gain</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">eq3_vel2gain</td><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Effects</td></tr>
<tr><td class="decocomp">effect1<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">effect2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

</tbody>
</table>
<br>

<h2>SFZ v2 opcodes</h2>
<p>
  The SFZ version 2 opcodes are listed in the book <a href="http://noisesculpture.com/cakewalk-synthesizers"><i>Cakewalk Synthesizers: From Presets to Power User</i></a> by Simon Cann.
  The list below is not quite complete, the book also has opcodes for a noise generator and SFZ v2 effects.
</p>

<table class="decocomp">
<thead>
  <tr>
    <td class="decocomp_header">Opcode</td>
    <td class="decocomp_header">Supported</td>
    <td class="decocomp_header">Comment</td>
  </tr>
</thead>
<tbody>

<tr><td class="decocomp_header" colspan="3"><b>Instrument Structure</b></td></tr>
<tr><td class="decocomp">&lt;global><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">&lt;control><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">&lt;curve><td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">&lt;effects><td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Sample Definition</b></td></tr>
<tr><td class="decocomp">md5<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">waveguide<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>&lt;control> Header Directives</b></td></tr>
<tr><td class="decocomp">default_path<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">octave_offset<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">note_offset<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">set_ccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">#define<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Loading</b></td></tr>
<tr><td class="decocomp">load_mode<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">load_start<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">load_end<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sample_quality<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">image<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Wavetable Oscillator</b></td></tr>
<tr><td class="decocomp">oscillator<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_phase<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_quality<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_table_size<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_multi<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_mode<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_detune<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_detune_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_detune_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">oscillator_detune_stepccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">oscillator_detune_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">oscillator_mod_depth<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_mod_depth_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">oscillator_mod_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Input Controls</b></td></tr>
<tr><td class="decocomp">loprog<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hiprog<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lotimer<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">hitimer<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">polyphony<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">reverse_loccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">reverse_hiccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">start_loccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">start_hiccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">stop_loccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">stop_hiccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sustain_sw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">sustenuto_sw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">rt_dead<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3"><b>Performance Parameters</b></td></tr>
<tr><td class="decocomp_header" colspan="3">Sample Player</td></tr>
<tr><td class="decocomp">delay_beats<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">stop_beats<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">delay_samples<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">delay_samples_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">loop_crossfade<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Amplifier</td></tr>
<tr><td class="decocomp">volume_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">volume_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">volume_stepccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">volume_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">pan_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">pan_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">pan_stepccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">pan_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">width_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">width_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">width_stepccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">width_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch</td></tr>
<tr><td class="decocomp">pitch_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitch_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitch_stepccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitch_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">Not listed in the book, but recognized by Dimension LE.</td></tr>
<tr><td class="decocomp">bend_stepup<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">bend_stepdown<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter</td></tr>
<tr><td class="decocomp">fil2_type<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff2_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff2_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff_stepccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff2_stepccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff2_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance2_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance_smoothccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance2_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance_stepccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance2_stepccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance_curveccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">resonance2_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil2_keytrack<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil2_keycenter<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil2_veltrack<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">EG</td></tr>
<tr><td class="decocomp">egN_timeX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_timeX_onccY<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_levelX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_levelX_onccY<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_shapeX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_curveX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_sustain<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_loop<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_loop_count<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_volume<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_amplitude<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_pan<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_width<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_pan_curve<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_pan_curveccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_volume_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_amplitude_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_pan_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_width_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_freq_lfoX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_depth_lfoX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_depthadd_lfoX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_pitch<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_pitch_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_cutoff<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_cutoff2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_resonance<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_resonance2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_cutoff_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_cutoff2_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_resonance_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_resonance2_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq1freq<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq2freq<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq3freq<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq1bw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq2bw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq3bw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq1gain<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq2gain<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq3gain<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq1freq_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq2freq_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq3freq_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq1bw_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq2bw_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq3bw_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq1gain_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq2gain_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_eq3gain_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_decim<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_bitred<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_rectify<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_ringmod<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_noiselevel<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_noisestep<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_noisetone<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_driveshape<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_decim_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_bitred_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_rectify_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_ringmod_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_noiselevel_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_noisestep_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_noisetone_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_driveshape_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">LFO</td></tr>
<tr><td class="decocomp">lfoN_freq<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_freq_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_freq_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_freq_stepccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_delay<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_delay_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_fade<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_fade_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_phase<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_phase_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_count<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_wave<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_steps<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_stepX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_smooth<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_smooth_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_volume<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_amplitude<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pan<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_width<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_volume_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_amplitude_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pan_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_width_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_volume_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_amplitude_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pan_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_width_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_volume_stepccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_amplitude_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pan_stepccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_width_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_freq_lfoX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_depth_lfoX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_depthadd_lfoX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pitch<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pitch_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pitch_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_pitch_stepccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance2<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff2_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance_onccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance2_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff2_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance_smoothccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance2_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff_stepccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_cutoff2_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance_stepccX<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_resonance2_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1freq<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2freq<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3freq<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1bw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2bw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3bw<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1gain<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2gain<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3gain<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1freq_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2freq_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3freq_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1bw_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2bw_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3bw_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1gain_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2gain_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3gain_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1freq_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2freq_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3freq_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1bw_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2bw_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3bw_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1gain_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2gain_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3gain_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3freq_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1bw_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2bw_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3bw_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq1gain_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq2gain_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_eq3gain_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_decim<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_bitred<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noiselevel<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisestep<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisetone<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_drive<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_decim_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_bitred_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noiselevel_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisestep_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisetone_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_drive_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_decim_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_bitred_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noiselevel_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisestep_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisetone_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_drive_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_decim_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_bitred_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noiselevel_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisestep_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_noisetone_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_drive_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Curves</td></tr>
<tr><td class="decocomp">vN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
</tbody>
</table>
<br>

<h2>ARIA custom opcodes</h2>
<p>The ARIA Engine from Plogue / Garritan implements some <a href="http://www.plogue.com/phpBB3/viewtopic.php?f=14&amp;t=4389">custom sfz opcodes</a>. Only some of them are listed here.</p>

<table class="decocomp">
<thead>
  <tr>
    <td class="decocomp_header">Opcode</td>
    <td class="decocomp_header">Supported</td>
    <td class="decocomp_header">Comment</td>
  </tr>
</thead>
<tbody>

<tr><td class="decocomp">amplitude<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplitude_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplitude_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplitude_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pan_law<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
</tbody>
</table>
<br>

<h2>LinuxSampler opcodes</h2>
<p>The following LinuxSampler custom opcodes are planned to be implemented as extensions to the SFZ format.</p>

<table class="decocomp">
<thead>
  <tr>
    <td class="decocomp_header">Opcode</td>
    <td class="decocomp_header">Supported</td>
    <td class="decocomp_header">Comment</td>
  </tr>
</thead>
<tbody>

<tr><td class="decocomp_header" colspan="3">Amplifier</td></tr>
<tr><td class="decocomp">position_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">position_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">position_curveccN <td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">gain_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">gain_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch</td></tr>
<tr><td class="decocomp">transpose_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">transpose_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">transpose_curveccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">tune_onccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">tune_smoothccN<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">tune_curveccN <td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter</td></tr>
<tr><td class="decocomp">cutoff2_chanaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">cutoff2_polyaft<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fil2_random<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">EG</td></tr>
<tr><td class="decocomp">egN_position<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">egN_position_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">LFO</td></tr>
<tr><td class="decocomp">lfoN_depth<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_depth_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_position<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_position_onccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_position_smoothccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">lfoN_position_stepccX<td style="background: #ff9090; text-align: center">No</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Amplifier LFO</td></tr>
<tr><td class="decocomp">amplfo_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">amplfo_fade_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter EG</td></tr>
<tr><td class="decocomp">fileg_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_start_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_attack_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_hold_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_decay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_sustain_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_release_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fileg_depth_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Filter LFO</td></tr>
<tr><td class="decocomp">fillfo_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">fillfo_fade_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch EG</td></tr>
<tr><td class="decocomp">pitcheg_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_start_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_attack_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_hold_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_decay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_sustain_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_release_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitcheg_depth_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>

<tr><td class="decocomp_header" colspan="3">Pitch LFO</td></tr>
<tr><td class="decocomp">pitchlfo_delay_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
<tr><td class="decocomp">pitchlfo_fade_onccN<td style="background: #90ff90; text-align: center">Yes</td><td class="decocomp">&nbsp;</td></tr>
</tbody>
</table>
<br>

<?php
include '../tmpl/footer.php';
?>
