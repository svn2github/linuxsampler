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
 * Provides information about the current settings of a specific MIDI input device.
 * @author  Grigor Iliev
 */
public class MidiInputDevice extends AbstractDevice {
	private MidiPort[] midiPorts = new MidiPort[0];
	
	/** Creates a new instance of MidiInputDevice */
	public
	MidiInputDevice() { }
	
	/**
	 * Gets the current non-<code>null</code> list of MIDI ports this device offers.
	 * @return A <code>MidiPort</code> array providing all MIDI ports this device offers.
	 */
	public MidiPort[]
	getMidiPorts() { return midiPorts; }
	
	/**
	 * Sets the current list of MIDI ports.
	 * @param ports The new list of MIDI ports.
	 * @throws IllegalArgumentException If <code>ports</code> is <code>null</code>.
	 */
	public void
	setMidiPorts(MidiPort[] ports) {
		if(ports == null) throw new IllegalArgumentException("ports must be non null");
		midiPorts = ports;
	}
	
	/**
	 * Gets the MIDI port at the specified index.
	 * @param index The index of the MIDI port to be retrieved.
	 */
	public MidiPort
	getMidiPort(int index) { return midiPorts[index]; }
	
	/**
	 * Gets the current number of MIDI ports this device offers.
	 * @return The current number of MIDI ports this device offers.
	 */
	public int
	getMidiPortCount() { return midiPorts.length; }
}
