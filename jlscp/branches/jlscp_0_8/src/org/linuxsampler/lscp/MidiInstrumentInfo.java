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

import static org.linuxsampler.lscp.Parser.*;

/**
 * Provides information about a MIDI instrument.
 * @author Grigor Iliev
 */
public class MidiInstrumentInfo extends AbstractInstrument implements Parseable {
	private int mapId = -1;
	private MidiInstrumentEntry entry;
	
	private String engine;
	private String instrName = "Untitled";
	private double volume = 1.0;
	private LoadMode loadMode = LoadMode.DEFAULT;
	
	public static enum LoadMode {
		/** It will be up to the InstrumentManager to decide which mode to use. */
		DEFAULT ("Default"),
		
		/**
		 * The instrument will be loaded when when demanded by
		 * at least one sampler channel. It will immediately be freed
		 * from memory when not needed by any sampler channel anymore.
		 */
		ON_DEMAND ("On Demand"),
		
		/**
		 * Same as <code>ON_DEMAND</code> with the difference that the instrument
		 * will be kept in memory even when not needed by any sampler channel.
		 */
		ON_DEMAND_HOLD ("On Demand and Hold"),
		
		/**
		 * The instrument will be immediately loaded into memory
		 * and the instrument will be kept all the time.
		 */
		PERSISTENT ("Persistent");
		
		private final String name;
		
		LoadMode(String name) { this.name = name; }
		
		public String
		toString() { return name; }
	}
	
	
	/** Creates a new instance of <code>MidiInstrumentInfo</code> */
	public MidiInstrumentInfo() {
		
	}
	
	/**
	 * Creates a new instance of <code>MidiInstrumentInfo</code>.
	 * @param mapId The ID of the map containing this instrument.
	 * @param entry The instrument position in the map.
	 */
	public MidiInstrumentInfo(int mapId, MidiInstrumentEntry entry) {
		this.mapId = mapId;
		this.entry = entry;
	}
	
	/**
	 * Creates a new instance of <code>MidiInstrumentInfo</code> and parses the
	 * provided information about this instrument.
	 * @param mapId The ID of the map containing this instrument.
	 * @param entry Provides the position of the MIDI instrument in the MIDI instrument map.
	 * @param resultSet An array with information categories about a MIDI instrument.
	 * @throws LscpException If the parse fails.
	 */
	public
	MidiInstrumentInfo(int mapId, MidiInstrumentEntry entry, String[] resultSet)
									throws LscpException {
		this.mapId = mapId;
		this.entry = entry;
		
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets the position of the MIDI instrument in a MIDI instrument map.
	 * @return The position of the MIDI instrument in a MIDI instrument map.
	 */
	public MidiInstrumentEntry
	getEntry() { return entry; }
	
	/**
	 * Gets the ID of the map containing this instrument.
	 * @return The ID of the map containing this instrument.
	 */
	public int
	getMapId() { return mapId; }
	
	/**
	 * Gets the index of the MIDI bank, containing this instrument.
	 * @return The index of the MIDI bank, containing this instrument.
	 */
	public int
	getMidiBank() { return entry.getMidiBank(); }
	
	/**
	 * Gets the MIDI program number of this instrument.
	 * @return The MIDI program number of this instrument.
	 */
	public int
	getMidiProgram() { return entry.getMidiProgram(); }
	
	/**
	 * Gets the name of the sampler engine to be used to load the instrument.
	 * @return The name of the sampler engine to be used to load the instrument.
	 */
	public String
	getEngine() { return engine; }
	
	/**
	 * Sets the name of the sampler engine to be used to load the instrument.
	 * @param engine The name of the sampler engine to be used to load the instrument.
	 */
	public void
	setEngine(String engine) { this.engine = engine; }
	
	/**
	 * Gets the name of the loaded instrument as reflected by its file.
	 * @return The name of the loaded instrument as reflected by its file.
	 */
	public String
	getInstrumentName() { return instrName; }
	
	/**
	 * Sets the name of this instrument as reflected by its file.
	 * @param name The  name of the instrument as reflected by its file.
	 *
	public void
	setInstrumentName(String name) { this.instrName = name; }*/
	
	/**
	 * Returns the volume, specified for this instrument, where a
	 * value < 1.0 means attenuation and a value > 1.0 means amplification.
	 */
	public double
	getVolume() { return volume; }
	
	/**
	 * Sets the volume level for this instrument,  where a
	 * value < 1.0 means attenuation and a value > 1.0 means amplification.
	 */
	public void
	setVolume(double volume) { this.volume = volume; }
	
	/**
	 * Gets the load mode of this MIDI instrument.
	 * @return The load mode of this MIDI instrument.
	 */
	public LoadMode
	getLoadMode() { return loadMode; }
	
	/**
	 * Sets the load mode of this MIDI instrument.
	 * @param loadMode Specifies the load mode for this MIDI instrument.
	 */
	public void
	setLoadMode(LoadMode loadMode) { this.loadMode = loadMode; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("NAME: ")) {
			setName(toNonEscapedString(s.substring("NAME: ".length())));
		} else if(s.startsWith("ENGINE_NAME: ")) {
			setEngine(s.substring("ENGINE_NAME: ".length()));
		} else if(s.startsWith("INSTRUMENT_NAME: ")) {
			instrName = toNonEscapedString(s.substring("INSTRUMENT_NAME: ".length()));
		} else if(s.startsWith("LOAD_MODE: ")) {
			s = s.substring("LOAD_MODE: ".length());
			if(s.length() == 0) setLoadMode(LoadMode.DEFAULT);
			else setLoadMode(LoadMode.valueOf(s));
		} else if(s.startsWith("VOLUME: ")) {
			s = s.substring("VOLUME: ".length());
			setVolume(Parser.parseFloat(s));
		} else return super.parse(s);
		
		return true;
	}
	
	/**
	 * Determines whether the specified object is of type
	 * <code>MidiInstrumentInfo</code> and has equal map ID, MIDI bank and MIDI program.
	 * @param obj The reference object with which to compare.
	 * @return <code>true</code> if the specified object is of type
	 * <code>MidiInstrumentInfo</code> and has equal map ID, MIDI bank and MIDI program.
	 */
	public boolean
	equals(Object obj) {
		if(obj == null) return false;
		if(!(obj instanceof MidiInstrumentInfo)) return false;
		MidiInstrumentInfo i = (MidiInstrumentInfo)obj;
		if(getMapId() != i.getMapId()) return false;
		if(getMidiBank() != i.getMidiBank()) return false;
		if(getMidiProgram() != i.getMidiProgram()) return false;
		
		return true;
	}
}
