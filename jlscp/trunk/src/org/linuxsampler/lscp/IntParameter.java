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
 * This class implements the <code>Parameter&lt;Integer&gt;</code> interface.
 * @author  Grigor Iliev
 */
public class IntParameter extends AbstractParameter<Integer> {
	/** Creates a new instance of <code>IntParameter</code> */
	public
	IntParameter() {
		setType(ParameterType.INT);
		setMultiplicity(false);
	}
	
	/**
	 * Creates an <code>IntParameter</code> instance with the specified name.
	 * @param name The parameter name.
	 */
	public
	IntParameter(String name) {
		this(name, null);
	}
	
	/**
	 * Creates an <code>IntParameter</code> instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 */
	public
	IntParameter(String name, Integer value) {
		this();
		setName(name);
		setValue(value);
	}
	
	/**
	 * Creates a new instance of <code>IntParameter</code>
	 * and parses the specified lines.
	 * @param lnS A <code>String</code> array with lines to be parsed.
	 * @throws LscpException If the parse fail.
	 */
	protected
	IntParameter(String[] lnS) throws LscpException {
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
		else if(s.startsWith("RANGE_MIN: ")) {
			s = s.substring("RANGE_MIN: ".length(), s.length());
			try {
				setRangeMin(Integer.parseInt(s));
				return true;
			} catch(NumberFormatException x) { throw new LscpException (
				LscpI18n.getLogMsg("notInt!", "RANGE_MIN"), x
			);}
		} else if(s.startsWith("RANGE_MAX: ")) {
			s = s.substring("RANGE_MAX: ".length(), s.length());
			try {
				setRangeMax(Integer.parseInt(s));
				return true;
			} catch(NumberFormatException x) { throw new LscpException (
				LscpI18n.getLogMsg("notInt!", "RANGE_MAX"), x
			);}
		} else if(s.startsWith("DEFAULT: ")) {
			s = s.substring("DEFAULT: ".length(), s.length());
			try {
				setDefault(Integer.parseInt(s));
				return true;
			} catch(NumberFormatException x) { throw new LscpException (
				LscpI18n.getLogMsg("notInt!", "DEFAULT"), x
			);}	
		} else if(s.startsWith("POSSIBILITIES: ")) {
			s = s.substring("POSSIBILITIES: ".length(), s.length());
			setPossibilities(Parser.parseIntList(s));
			return true;
		}
		
		return false;
	}
	
	/**
	 * Parses the specified character string and sets the value of this parameter
	 * with the parsed result.
	 * @param s A character string containing the value to be parsed.
	 * @throws LscpException If the parsing failed.
	 */
	public void
	parseValue(String s) throws LscpException { setValue(Parser.parseInt(s)); }
	
	/**
	 * Gets a character string representation of the parameter's value.
	 * @return A character string representation of the parameter's value.
	 */
	public String
	getStringValue() { return String.valueOf(getValue()); }
	
	
}
