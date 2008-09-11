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
 * A semantic event which indicates that MIDI data has arrived.
 * @author Grigor Iliev
 */
public class MidiDataEvent extends java.util.EventObject {
	public static enum Type {
		NOTE_ON  ("NOTE_ON"),
		NOTE_OFF ("NOTE_OFF");
		
		private final String name;
		
		Type(String name) {
			this.name = name;
		}
		
		public String
		toString() { return name; }
	}
	
	private Type type;
	private int note;
	private int velocity;
	
	/** Creates a new instance of <code>MidiDataEvent</code> */
	public
	MidiDataEvent(Object source, Type type, int note, int velocity) {
		super(source);
		
		this.type = type;
		this.note = note;
		this.velocity = velocity;
	}
	
	public Type
	getType() { return type; }
	
	public int
	getNote() { return note; }
	
	public int
	getVelocity() { return velocity; }
}
