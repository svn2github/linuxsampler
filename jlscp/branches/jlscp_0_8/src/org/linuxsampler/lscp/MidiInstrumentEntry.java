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
 * Specifies a position of a MIDI instrument in a MIDI instrument map.
 * @author Grigor Iliev
 */
public class MidiInstrumentEntry implements Comparable<MidiInstrumentEntry> {
	private int midiBank;
	private int midiProgram;
	
	/**
	 * Creates a new instance of <code>MidiInstrumentEntry</code>.
	 * @param midiBank The MIDI bank number.
	 * @param midiProgram The MIDI program number.
	 * @throws IndexOutOfBoundsException If <code>midiBank</code>
	 * is out of range <code>(midiBank < 0 || midiBank > 16129)</code>,
	 * or <code>midiProgram</code> is out of range
	 * <code>(midiProgram < 0 || midiProgram > 127)</code>.
	 */
	public
	MidiInstrumentEntry(int midiBank, int midiProgram) {
		if(midiBank < 0 || midiBank > 16129) 
			throw new IndexOutOfBoundsException("midiBank is out of range");
		
		if(midiProgram < 0 || midiProgram > 127) 
			throw new IndexOutOfBoundsException("midiProgram is out of range");
		
		this.midiBank = midiBank;
		this.midiProgram = midiProgram;
	}
	
	/**
	 * Gets the MIDI bank number.
	 */
	public int
	getMidiBank() { return midiBank; }
	
	/**
	 * Gets the MIDI program number.
	 */
	public int
	getMidiProgram() { return midiProgram; }
	
	public boolean
	equals(Object obj) {
		if(obj == null || !(obj instanceof MidiInstrumentEntry)) return false;
		MidiInstrumentEntry e = (MidiInstrumentEntry)obj;
		
		if(getMidiBank() == e.getMidiBank() &&
			getMidiProgram() == e.getMidiProgram()) return true;
		
		return false;
	}
	
	public int
	compareTo(MidiInstrumentEntry e) {
		if(getMidiBank() < e.getMidiBank()) return -1;
		if(getMidiBank() > e.getMidiBank()) return 1;
		
		if(getMidiProgram() < e.getMidiProgram()) return -1;
		if(getMidiProgram() > e.getMidiProgram()) return 1;
		
		return 0;
	}
}
