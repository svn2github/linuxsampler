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
 * Represents a MIDI instrument map used for mapping instruments
 * to corresponding MIDI bank select and MIDI program change messages.
 * @author Grigor Iliev
 */
public class MidiInstrumentMapInfo {
	private int mapId;
	private String name;
	private boolean defaultMap;
	
	
	/**
	 * Creates a new instance of <code>MidiInstrumentMapInfo</code>
	 * with the specified name and map ID.
	 * @param mapId Specifies the ID of the map.
	 * @param name Specifies the name of the map.
	 */
	public
	MidiInstrumentMapInfo(int mapId, String name) {
		this(mapId, name, false);
	}
	
	/**
	 * Creates a new instance of <code>MidiInstrumentMapInfo</code>.
	 * @param mapId Specifies the ID of the map.
	 * @param name Specifies the name of the map.
	 * @param defaultMap Specifies whether this is the default map.
	 */
	public
	MidiInstrumentMapInfo(int mapId, String name, boolean defaultMap) {
		this.mapId = mapId;
		this.name = name;
		this.defaultMap = defaultMap;
	}
	
	/* Gets the ID of this MIDI instrument map. */
	public int
	getMapId() { return mapId; }
	
	/**
	 * Gets the name of this MIDI instrument map.
	 * @return The name of this MIDI instrument map.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this MIDI instrument map.
	 * @param name The new name of this MIDI instrument map.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Determines whether this map is the default map.
	 * @return <code>true</code> if this is the default
	 * map, <code>false</code> otherwise.
	 */
	public boolean
	isDefault() { return defaultMap; }
	
	/**
	 * Returns the name of this map.
	 * @return The name of this map.
	 */
	public String
	toString() { return getName(); }
}
