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
 * This class implements the <code>Parameter&lt;Boolean&gt;</code> interface.
 * @author  Grigor Iliev
 */
public class BoolParameter extends AbstractParameter<Boolean> {
	/** Creates a new instance of <code>BoolParameter</code> */
	public
	BoolParameter() {
		setType(ParameterType.BOOL);
		setMultiplicity(false);
	}
	
	/**
	 * Creates a <code>BoolParameter</code> instance with the specified name.
	 * @param name The parameter name.
	 */
	public
	BoolParameter(String name) {
		this(name, null);
	}
	
	/**
	 * Creates a <code>BoolParameter</code> instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 */
	public
	BoolParameter(String name, Boolean value) {
		this();
		setName(name);
		setValue(value);
	}
	
	/**
	 * Creates a new instance of <code>BoolParameter</code>
	 * and parses the specified lines.
	 * @param lnS A <code>String</code> array with lines to be parsed.
	 * @throws LscpException If the parse fail.
	 */
	public
	BoolParameter(String[] lnS) throws LscpException {
		this();
		parseLines(lnS);
	}
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(super.parse(s)) return true;
		else if(s.startsWith("DEFAULT: ")) {
			s = s.substring("DEFAULT: ".length(), s.length());
			setDefault(Boolean.parseBoolean(s));
			return true;
		} else if(s.startsWith("POSSIBILITIES: ")) {
			s = s.substring("POSSIBILITIES: ".length(), s.length());
			setPossibilities(Parser.parseBoolList(s));
			return true;
		}
		
		return false;
	}
	
	/**
	 * Parses the specified character string and sets the value of this parameter
	 * with the parsed result.
	 * @param s A character string containing the value to be parsed.
	 */
	public void
	parseValue(String s) { setValue(Boolean.parseBoolean(s)); }
	
	/**
	 * Gets a character string representation of the parameter's value.
	 * @return A character string representation of the parameter's value.
	 */
	public String
	getStringValue() { return String.valueOf(getValue()); }
}
