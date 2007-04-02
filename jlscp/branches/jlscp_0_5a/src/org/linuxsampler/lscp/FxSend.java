/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005-2007 Grigor Iliev <grigor@grigoriliev.com>
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
 * Provides information about the current settings of a specific effect send.
 * @author Grigor Iliev
 */
public class FxSend implements Parseable {
	private int fxSendId = -1;
	private String name = null;
	private int midiController = -1;
	private float level = 0;
	private Integer[] aor = null;
	
	
	/** Creates a new instance of <code>FxSend</code> */
	public
	FxSend() { }
	
	/**
	 * Creates a new instance of <code>FxSend</code> and parses the information
	 * about a specific effect send described by <code>resultSet</code>.
	 * @param resultSet An array with information categories about an effect send entity.
	 * @throws LscpException If the parse fail.
	 */
	public
	FxSend(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets the numerical ID of this effect send.
	 * @return The numerical ID of this effect
	 * send or -1 if the effect send number is not set.
	 */
	public int
	getFxSendId() { return fxSendId; }
	
	/**
	 * Sets the numerical ID of this effect send.
	 * @param id The new effect send number.
	 */
	public void
	setFxSendId(int id) { fxSendId = id; }
	
	/**
	 * Gets the name of this effect send.
	 * @return The name of this effect send.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this effect send.
	 * @param name The new name of this effect send.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Gets the MIDI controller, which is able to modify the send level.
	 * @return The MIDI controller, which is able to modify the
	 * send level, or -1 if the effect send number is not set.
	 */
	public int
	getMidiController() { return midiController; }
	
	/**
	 * Gets the current send level.
	 * @return The current send level.
	 */
	public float
	getLevel() { return level; }
	
	/**
	 * Gets a list which reflects to which audio channel of the selected
	 * audio output device each effect send output channel is routed to.
	 * The number of the array's position represents the effect send output channel
	 * and the value at the specified position represents
	 * to which channel of the selected audio output device the
	 * effect send output channel is routed to.
	 * @return A list which reflects to which audio channel of the selected audio
	 * output device each effect send output channel is routed to.
	 */
	public Integer[]
	getAudioOutputRouting() { return aor; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("NAME: ")) {
			name = s.substring("NAME: ".length());
		} else if(s.startsWith("MIDI_CONTROLLER: ")) {
			s = s.substring("MIDI_CONTROLLER: ".length());
			midiController = Parser.parseInt(s);
		} else if(s.startsWith("LEVEL: ")) {
			s = s.substring("LEVEL: ".length());
			level = Parser.parseFloat(s);
		} else if(s.startsWith("AUDIO_OUTPUT_ROUTING: ")) {
			s = s.substring("AUDIO_OUTPUT_ROUTING: ".length());
			aor = Parser.parseIntList(s);
		} else return false;
	
		return true;
	}
	
	/**
	 * Returns the name of this effect send.
	 * @return The name of this effect send.
	 */
	public String
	toString() { return getName(); }
	
	/**
	 * Determines whether the specified object is of type
	 * <code>FxSend</code> and has equal ID.
	 * @param obj The reference object with which to compare.
	 * @return <code>true</code> if the specified object is of type
	 * <code>FxSend</code> and has equal ID.
	 */
	public boolean
	equals(Object obj) {
		if(obj == null) return false;
		if(!(obj instanceof FxSend)) return false;
		FxSend fxs = (FxSend)obj;
		if(getFxSendId() != fxs.getFxSendId()) return false;
		
		return true;
	}
}
