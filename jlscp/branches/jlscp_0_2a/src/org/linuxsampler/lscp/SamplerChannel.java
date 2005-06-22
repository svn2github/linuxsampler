/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005 Grigor Kirilov Iliev
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

/**
 * Provides information about current settings of a specific sampler channel.
 * @author  Grigor Iliev
 */
public class SamplerChannel implements Parseable {
	private int chnID = -1;
	
	private String engine = null;
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
	getChannelID() { return chnID; }
	
	/**
	 * Sets the sampler channel number.
	 * @param id The new sampler channel number.
	 */
	public void
	setChannelID(int id) { chnID = id; }
	
	/**
	 * Gets the name of the engine that is deployed on the sampler channel.
	 * @return The name of the engine that is deployed on the sampler channel
	 * or <code>null</code> if there is no engine deployed yet for this sampler channel.
	 */
	public String
	getEngineName() { return engine; }
	
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
	 * each sampler output channel is routed to.
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
	 * Gets the instrument name of the loaded instrument.
	 * @return The instrument name of the loaded instrument.
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
			else engine = s;
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
			instrName = s.substring("INSTRUMENT_NAME: ".length());
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
		} else return false;
	
		return true;
	}
}
