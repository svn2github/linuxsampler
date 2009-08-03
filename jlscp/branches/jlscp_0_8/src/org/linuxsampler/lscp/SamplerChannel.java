/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005-2006 Grigor Iliev <grigor@grigoriliev.com>
 *
 *   This file is part of jlscp.
 *
 *   jlscp is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2
 *   as published by the Free Software Foundation.
 *
 *   jlscp is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with jlscp; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA  02111-1307  USA
 */

package org.linuxsampler.lscp;

import static org.linuxsampler.lscp.Parser.*;

/**
 * Provides information about the current settings of a specific sampler channel.
 * @author  Grigor Iliev
 */
public class SamplerChannel implements Parseable {
	/** Indicates that the channel is muted because of the presence of a solo channel. */
	private final static int MUTED_BY_SOLO = -1;
		
	private int chnId = -1;
	
	private SamplerEngine engine = null;
	private int aoDevice = -1;
	private int aoChannels = 0;
	private Integer[] aor = null;
	private String instrFile = null;
	private int instrIdx = 0;
	private String instrName = null;
	private int instrStat = 0;
	private int miDev = -1;
	private int miPort = 0;
	private int miChn = -1;
	private float vol = 0;
	private int mute = 0;
	private boolean solo = false;
	private int midiInstrumentMapId = -1;
	
	/** Creates a new instance of SamplerChannel */
	public
	SamplerChannel() {
	}
	
	/**
	 * Creates a new instance of <code>SamplerChannel</code> and parses the information
	 * about a specific sampler channel described by <code>resultSet</code>.
	 * @param resultSet An array with information categories about a sampler channel.
	 * @throws LscpException If the parse fail.
	 */
	public
	SamplerChannel(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets the sampler channel number.
	 * @return The sampler channel number or -1 if the sampler channel number is not set.
	 */
	public int
	getChannelId() { return chnId; }
	
	/**
	 * Sets the sampler channel number.
	 * @param id The new sampler channel number.
	 */
	public void
	setChannelId(int id) { chnId = id; }
	
	/**
	 * Gets the engine that is deployed on the sampler channel.
	 * @return The engine that is deployed on the sampler channel
	 * or <code>null</code> if there is no engine deployed yet for this sampler channel.
	 */
	public SamplerEngine
	getEngine() { return engine; }
	
	/**
	 * Associates the specified sampler engine to this sampler channel.
	 * @param engine A <code>SamplerEngine</code> instance containing the information
	 * about the engine to be assigned to this channel.
	 */
	public void
	setEngine(SamplerEngine engine) { this.engine = engine; }
	
	/**
	 * Gets the numerical ID of the audio output device which is currently connected 
	 * to this sampler channel to output the audio signal.
	 *
	 * @return The numerical ID of the audio output device or -1 if there is no
	 * device connected to this sampler channel.
	 */
	public int
	getAudioOutputDevice() { return aoDevice; }
	
	/**
	 * Gets the number of output channels the sampler channel offers.
	 * @return The number of output channels the sampler channel offers.
	 */
	public int
	getAudioOutputChannels() { return aoChannels; }
	
	/**
	 * Gets a list which reflects to which audio channel of the selected audio output device
	 * each sampler output channel is routed to. The number of the array's position represents
	 * the sampler output channel and the value at the specified position represents
	 * to which channel of the selected audio output device the
	 * sampler output channel is routed to.
	 * @return A list which reflects to which audio channel of the selected audio output device
	 * each sampler output channel is routed to.
	 */
	public Integer[]
	getAudioOutputRouting() { return aor; }
	
	/**
	 * Gets the file name of the loaded instrument.
	 * @return The file name of the loaded instrument.
	 * or <code>null</code> if there is no instrument yet loaded for this sampler channel.
	 */
	public String
	getInstrumentFile() { return instrFile; }
	
	/**
	 * Gets the instrument index number of the loaded instrument.
	 * @return The instrument index number of the loaded instrument.
	 */
	public int
	getInstrumentIndex() { return instrIdx; }
	
	/**
	 * Gets the name of the loaded instrument.
	 * @return The name of the loaded instrument or
	 * <code>null</code> if there is no instrument loaded.
	 */
	public String
	getInstrumentName() { return instrName; }
	
	/**
	 * Gets the instrument status - an integer values from 0 to 100 indicating loading
	 * progress percentage for the instrument. Negative value indicates a loading exception.
	 * Value of 100 indicates that the instrument is fully loaded.
	 * @return The instrument status.
	 */
	public int
	getInstrumentStatus() { return instrStat; }
	
	/**
	 * Gets the numerical ID of the MIDI input device which is currently connected
	 * to this sampler channel to deliver MIDI input commands.
	 * @return The numerical ID of the MIDI input device which is currently connected
	 * to this sampler channel to deliver MIDI input commands or -1 if there is no device
	 * connected to this sampler channel.
	 */
	public int
	getMidiInputDevice() { return miDev; }
	
	/**
	 * Gets the port number of the MIDI input device.
	 * @return The port number of the MIDI input device.
	 */
	public int
	getMidiInputPort() { return miPort; }
	
	/**
	 * Gets the MIDI input channel number this sampler channel should listen to
	 * or -1 to listen on all MIDI channels.
	 * @return The MIDI input channel number this sampler channel should listen to
	 * or -1 to listen on all MIDI channels.
	 */
	public int
	getMidiInputChannel() { return miChn; }
	
	/**
	 * Gets the channel volume factor. Value less then 1.0 means attenuation,
	 * value greater then 1.0 means amplification.
	 * @return The channel volume factor.
	 */
	public float
	getVolume() { return vol; }
	
	/**
	 * Determines whether this channel is muted.
	 * @return <code>true</code> if the channel is muted, <code>false</code> otherwise.
	 */
	public boolean
	isMuted() { return mute != 0; }
	
	/**
	 * Determines whether this channel is muted because of the presence of a solo channel.
	 * All channels, muted because of the presence of a solo channel, will be 
	 * automatically unmuted when there are no solo channels left.
	 * @return <code>true</code> if the channel is muted because of the presence of a solo 
	 * channel, <code>false</code> otherwise.
	 */
	public boolean
	isMutedBySolo() { return mute == MUTED_BY_SOLO; }
	
	/**
	 * Determines whether this channel is a solo channel.
	 * @return <code>true</code> if the channel is a solo channel, <code>false</code> otherwise.
	 */
	public boolean
	isSoloChannel() { return solo; }
	
	/**
	 * Gets the numerical id of the MIDI instrument
	 * map, to which this sampler channel is assigned to.
	 * @return The numerical id of the MIDI instrument map, to
	 * which this sampler channel is assigned to, or <code>-1</code>
	 * if no MIDI instrument map is assigned to this sampler
	 * channel and <code>-2</code> if the channel is assigned
	 * to the default MIDI instrument map.
	 * @see #isUsingDefaultMidiInstrumentMap
	 */
	public int
	getMidiInstrumentMapId() { return midiInstrumentMapId; }
	
	/**
	 * Determines whether the sampler channel is
	 * assigned to the default MIDI instrument map.
	 * @return <code>true</code> if the sampler channel is assigned
	 * to the default MIDI instrument map, <code>false</code> otherwise.
	 */
	public boolean
	isUsingDefaultMidiInstrumentMap() { return getMidiInstrumentMapId() == -2; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("ENGINE_NAME: ")) {
			s = s.substring("ENGINE_NAME: ".length());
			if(s.equals("NONE")) engine = null;
			else {
				engine = new SamplerEngine();
				engine.setName(s);
			}
		} else if(s.startsWith("AUDIO_OUTPUT_DEVICE: ")) {
			s = s.substring("AUDIO_OUTPUT_DEVICE: ".length());
			if(s.equals("NONE")) aoDevice = -1;
			else aoDevice = Parser.parseInt(s);
		} else if(s.startsWith("AUDIO_OUTPUT_CHANNELS: ")) {
			s = s.substring("AUDIO_OUTPUT_CHANNELS: ".length());
			if(s.equals("NONE")) aoChannels = -1;
			else aoChannels = Parser.parseInt(s);
		} else if(s.startsWith("AUDIO_OUTPUT_ROUTING: ")) {
			s = s.substring("AUDIO_OUTPUT_ROUTING: ".length());
			aor = Parser.parseIntList(s);
		} else if(s.startsWith("INSTRUMENT_FILE: ")) {
			s = s.substring("INSTRUMENT_FILE: ".length());
			if(s.equals("NONE")) instrFile = null;
			else instrFile = s;
		} else if(s.startsWith("INSTRUMENT_NR: ")) {
			s = s.substring("INSTRUMENT_NR: ".length());
			if(s.equals("NONE")) instrIdx = -1;
			else instrIdx = Parser.parseInt(s);
		} else if(s.startsWith("INSTRUMENT_NAME: ")) {
			s = s.substring("INSTRUMENT_NAME: ".length());
			if(s.equals("NONE")) instrName = null;
			else instrName = toNonEscapedString(s);
		} else if(s.startsWith("INSTRUMENT_STATUS: ")) {
			s = s.substring("INSTRUMENT_STATUS: ".length());
			instrStat = Parser.parseInt(s);
		} else if(s.startsWith("MIDI_INPUT_DEVICE: ")) {
			s = s.substring("MIDI_INPUT_DEVICE: ".length());
			if(s.equals("NONE")) miDev = -1;
			else miDev = Parser.parseInt(s);
		} else if(s.startsWith("MIDI_INPUT_PORT: ")) {
			s = s.substring("MIDI_INPUT_PORT: ".length());
			if(s.equals("NONE")) miPort = -1;
			else miPort = Parser.parseInt(s);
		} else if(s.startsWith("MIDI_INPUT_CHANNEL: ")) {
			s = s.substring("MIDI_INPUT_CHANNEL: ".length());
			if(s.equals("ALL")) miChn = -1;
			else miChn = Parser.parseInt(s);
		} else if(s.startsWith("VOLUME: ")) {
			s = s.substring("VOLUME: ".length());
			try { vol = Float.parseFloat(s); }
			catch(NumberFormatException x) { throw new LscpException (
				LscpI18n.getLogMsg("CommandFailed!"), x
			);}
		} else if(s.startsWith("MUTE: ")) {
			s = s.substring("MUTE: ".length());
			if(s.equals("MUTED_BY_SOLO")) mute = MUTED_BY_SOLO;
			else mute = Boolean.parseBoolean(s) ? 1 : 0;
		} else if(s.startsWith("SOLO: ")) {
			s = s.substring("SOLO: ".length());
			solo = Boolean.parseBoolean(s);
		} else if(s.startsWith("MIDI_INSTRUMENT_MAP: ")) {
			s = s.substring("MIDI_INSTRUMENT_MAP: ".length());
			if(s.equals("NONE")) midiInstrumentMapId = -1;
			else if(s.equals("DEFAULT")) midiInstrumentMapId = -2;
			else midiInstrumentMapId = Parser.parseInt(s);
		} else return false;
	
		return true;
	}
	
	/**
	 * Returns the numerical ID of this sampler channel.
	 * @return The numerical ID of this sampler channel.
	 */
	public String
	toString() { return String.valueOf(getChannelId()); }
}
