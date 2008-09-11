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
 *
 * @author Grigor Iliev
 */
public abstract class AbstractInstrument implements Instrument, Parseable {
	private String name = "Untitled";
	private String description = "";
	private String path = null;
	private int instrumentIndex = 0;
	private String formatFamily = "";
	private String formatVersion = "";
	private Integer[] keyMapping = { };
	private Integer[] keyswitchMapping = { };
	
	/**
	 * Creates a new instance of <code>AbstractInstrument</code>.
	 */
	public
	AbstractInstrument() { }
	
	/**
	 * Creates a new instance of <code>AbstractInstrument</code>.
	 * @param resultSet An array with information categories about an instrument.
	 */
	public
	AbstractInstrument(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets the name of this instrument.
	 * @return The name of this instrument.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this instrument.
	 * @param name The name of this instrument.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Gets a brief description about this instrument.
	 * @return A brief description about this instrument.
	 */
	public String
	getDescription() { return description; }
	
	/**
	 * Returns the absolute path name of the instrument file.
	 * @return The absolute path name of the instrument file.
	 */
	public String
	getFilePath() { return path; }
	
	/**
	 * Sets the absolute path name of the instrument file.
	 * @param path Specifies the absolute path name of the instrument file.
	 */
	public void
	setFilePath(String path) { this.path = path; }
	
	/**
	 * Returns the index of the instrument in the instrument file.
	 * @return The index of the instrument in the instrument file.
	 */
	public int
	getInstrumentIndex() { return instrumentIndex; }
	
	/**
	 * Sets the index of the instrument in the instrument file.
	 * @param idx The index of the instrument in the instrument file.
	 */
	public void
	setInstrumentIndex(int idx) { instrumentIndex = idx; }
	
	/**
	 * Returns the format family of the instrument.
	 **/
	public String
	getFormatFamily() { return formatFamily; }
	
	/**
	 * Returns the format version of the instrument.
	 **/
	public String
	getFormatVersion() { return formatVersion; }
	
	public Integer[]
	getKeyMapping() { return keyMapping; }
	
	public Integer[]
	getKeyswitchMapping() { return keyswitchMapping; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("NAME: ")) {
			setName(s.substring("NAME: ".length()));
		} else if(s.startsWith("DESCRIPTION: ")) {
			description = s.substring("DESCRIPTION: ".length());
			description = toNonEscapedString(description);
		} else if(s.startsWith("INSTRUMENT_FILE: ")) {
			setFilePath(s.substring("INSTRUMENT_FILE: ".length()));
		} else if(s.startsWith("INSTRUMENT_NR: ")) {
			s = s.substring("INSTRUMENT_NR: ".length());
			setInstrumentIndex(Parser.parseInt(s));
		} else if(s.startsWith("FORMAT_FAMILY: ")) {
			formatFamily = s.substring("FORMAT_FAMILY: ".length());
		} else if(s.startsWith("FORMAT_VERSION: ")) {
			formatVersion = s.substring("FORMAT_VERSION: ".length());
		} else if(s.startsWith("KEY_BINDINGS: ")) {
			s = s.substring("KEY_BINDINGS: ".length());
			keyMapping = Parser.parseIntList(s);
		} else if(s.startsWith("KEYSWITCH_BINDINGS: ")) {
			s = s.substring("KEYSWITCH_BINDINGS: ".length());
			keyswitchMapping = Parser.parseIntList(s);
		} else return false;
		
		return true;
	}
}
