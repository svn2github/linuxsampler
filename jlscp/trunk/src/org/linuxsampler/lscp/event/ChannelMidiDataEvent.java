/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005-2008 Grigor Iliev <grigor@grigoriliev.com>
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

package org.linuxsampler.lscp.event;

/**
 * A semantic event which indicates that MIDI data has arrived on a specific sampler channel.
 * @author Grigor Iliev
 */
public class ChannelMidiDataEvent extends MidiDataEvent {
	private int channelId = -1;
	
	/** Creates a new instance of <code>ChannelMidiDataEvent</code> */
	public
	ChannelMidiDataEvent(Object source, Type type, int note, int velocity) {
		super(source, type, note, velocity);
	}
	
	/**
	 * Returns the ID of the sampler channel, to which MIDI data has arrived.
	 */
	public int
	getChannelId() { return channelId; }
	
	/**
	 * Sets the ID of the sampler channel, to which MIDI data has arrived.
	 */
	public void
	setChannelId(int id) { channelId = id; }
	
}
