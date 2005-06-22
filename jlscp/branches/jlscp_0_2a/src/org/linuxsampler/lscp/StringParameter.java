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
 * This class implements the <code>Parameter&lt;String&gt;</code> interface.
 * @author  Grigor Iliev
 */
public class StringParameter extends AbstractParameter<String> {
	/** Creates a new instance of <code>StringParameter</code> */
	public
	StringParameter() {
		setType(ParameterType.STRING);
		setMultiplicity(false);
	}
	
	/**
	 * Creates a <code>StringParameter</code> instance with the specified name.
	 * @param name The parameter name.
	 */
	public
	StringParameter(String name) {
		this(name, null);
	}
	
	/**
	 * Creates a <code>StringParameter</code> instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 */
	public
	StringParameter(String name, String value) {
		this();
		setName(name);
		setValue(value);
	}
	
	/**
	 * Creates a new instance of <code>StringParameter</code>
	 * and parses the specified lines.
	 * @param lnS A <code>String</code> array with lines to be parsed.
	 * @throws LscpException If the parse fail.
	 */
	protected
	StringParameter(String[] lnS) throws LscpException {
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
			setDefault(s.substring("DEFAULT: ".length(), s.length()));
			return true;
		} else if(s.startsWith("POSSIBILITIES: ")) {
			s = s.substring("POSSIBILITIES: ".length(), s.length());
			setPossibilities(Parser.parseStringList(s));
			return true;
		}
		
		return false;
	}
	
	/**
	 * Sets the current value of this parameter with the specified character string.
	 * @param s The new value for this parameter.
	 * @throws LscpException If the parsing failed.
	 */
	public void
	parseValue(String s) throws LscpException {
		if(s == null || s.length() == 0) setValue(s);
		else if(s.charAt(0) != '\'' || s.charAt(s.length() - 1) != '\'')
			throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
		setValue(s.substring(1, s.length() - 1));
	}
	
	/**
	 * Gets the current value of this parameter.
	 * @return The current value of this parameter.
	 */
	public String
	getStringValue() { return '\'' + getValue() + '\''; }
}
