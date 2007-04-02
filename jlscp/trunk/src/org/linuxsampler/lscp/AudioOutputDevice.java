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

/**
 * Provides information about the current settings of a specific audio output device.
 * @author  Grigor Iliev
 */
public class AudioOutputDevice extends AbstractDevice {
	private Parameter<Integer> channels = null;
	private Parameter<Integer> samplerate = null;
	
	private AudioOutputChannel[] audioChannels = new AudioOutputChannel[0];
	
	
	/** Creates a new instance of AudioOutputDevice */
	public
	AudioOutputDevice() {
		
	}
	
	/**
	 * Gets the amount of audio output channels this device currently offers.
	 * @return The amount of audio output channels this device currently offers.
	 */
	public int
	getChannelCount() { return channels == null ? 0 : channels.getValue(); }
	
	/**
	 * Gets the <code>CHANNELS</code> parameter.
	 * @return A <code>Parameter<Integer></code> instance.
	 */
	public Parameter<Integer>
	getChannelsParameter() { return channels; }
	
	/**
	 * Sets the <code>CHANNELS</code> parameter.
	 * @param channels The new <code>CHANNELS</code> parameter.
	 */
	public void
	setChannelsParameter(Parameter<Integer> channels) { this.channels = channels; }
	
	/**
	 * Gets the sample rate this device uses.
	 * @return The sample rate this device uses.
	 */
	public int
	getSampleRate() { return samplerate == null ? 0 : samplerate.getValue(); }
	
	/**
	 * Gets the <code>SAMPLERATE</code> parameter.
	 * @return A <code>Parameter<Integer></code> instance.
	 */
	public Parameter<Integer>
	getSampleRateParameter() { return samplerate; }
	
	/**
	 * Sets the <code>SAMPLERATE</code> parameter.
	 * @param samplerate The new <code>SAMPLERATE</code> parameter.
	 */
	public void
	setSampleRateParameter(Parameter<Integer> samplerate) { this.samplerate = samplerate; }
	
	/**
	 * Gets the current non-<code>null</code>
	 * list of audio channels this device offers.
	 * @return An <code>AudioOutputChannel</code> array
	 * providing all audio channels this device offers.
	 */
	public AudioOutputChannel[]
	getAudioChannels() { return audioChannels; }
	
	/**
	 * Sets the current list of audio output channels.
	 * @param channels The new list of audio output channels.
	 * @throws IllegalArgumentException If <code>channels</code> is <code>null</code>.
	 */
	public void
	setAudioChannels(AudioOutputChannel[] channels) {
		if(channels == null)
			throw new IllegalArgumentException("channels must be non null");
		audioChannels = channels;
	}
	
	/**
	 * Gets the audio output channel at the specified index.
	 * @param index The index of the audio output channel to be retrieved.
	 */
	public AudioOutputChannel
	getAudioChannel(int index) { return audioChannels[index]; }
	
	/**
	 * Gets the current number of audio output channels this device offers.
	 * @return The current number of audio output channels this device offers.
	 */
	public int
	getAudioChannelCount() { return audioChannels.length; }
	
	/**
	 * Gets a <code>Parameter</code> array providing all parameters
	 * of this audio output device (including <code>ACTIVE</code>,
	 * <code>CHANNELS</code> and <code>SAMPLERATE</code> parameters).
	 * @return A <code>Parameter</code> array providing all parameters
	 * of this MIDI port.
	 */
	public Parameter[]
	getAllParameters() {
		Parameter[] ap = getAdditionalParameters();
		Parameter[] params = new Parameter[ap.length + 3];
		params[0] = getActiveParameter();
		params[1] = channels;
		params[2] = samplerate;
		
		for(int i = 0; i < ap.length; i++) params[i + 3] = ap[i];
		
		return params;
	}
}
