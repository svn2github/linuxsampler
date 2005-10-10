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
 * This class provides default implementation of the <code>Parameter</code> interface.
 *
 * @author  Grigor Iliev
 */
public abstract class AbstractParameter<T> implements Parameter<T>, Parseable {
	private String name = null;
	private ParameterType type = null;
	private String desc = null;
	private boolean fix = true;
	private boolean multiplicity = true;
	
	private boolean mandatory = false;
	private String[] depends = null;
	
	private T val = null;
	private T dflt = null;
	private Number rangeMin = null;
	private Number rangeMax = null;
	private T[] possibilities = null;
	
	
	public
	AbstractParameter() {
		
	}

	/**
	 * Gets the name of this parameter.
	 * @return The name of this parameter.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this parameter.
	 * @param name A <code>String</code> object containing the new name for this parameter.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Gets the description of this parameter.
	 * @return The description of this parameter.
	 */
	public String
	getDescription() { return desc; }
	
	/**
	 * Sets the description of this parameter.
	 * @param desc A <code>String</code> instance containing the description of this parameter.
	 */
	public void
	setDescription(String desc) { this.desc = desc; }
	
	/**
	 * Gets the type of this parameter.
	 * @return The type of this parameter.
	 */
	public ParameterType
	getType() { return type; }
	
	/**
	 * Sets the type of this parameter.
	 * @param type The type of this parameter.
	 */
	public void
	setType(ParameterType type) { this.type = type; }
	
	/**
	 * Gets the current value of this parameter.
	 * @return The current value of this parameter.
	 */
	public T
	getValue() { return val; }
	
	/**
	 * Sets the current value of this parameter.
	 * @param val The new value for this parameter.
	 */
	public void
	setValue(T val) { this.val = val; }
	
	/**
	 * Determines whether this parameter contains boolean value.
	 * @return <code>true</code> if this parameter contains boolean value,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isBoolean() { return type == ParameterType.BOOL; }
	
	/**
	 * Determines whether this parameter contains integer value.
	 * @return <code>true</code> if this parameter contains integer value,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isInteger() { return type == ParameterType.INT; }
	
	/**
	 * Determines whether this parameter contains float value.
	 * @return <code>true</code> if this parameter contains float value,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isFloat() { return type == ParameterType.FLOAT; }
	
	/**
	 * Determines whether this parameter contains string value.
	 * @return <code>true</code> if this parameter contains string value,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isString() { return type == ParameterType.STRING; }
	
	/**
	 * Determines whether this parameter contains list of boolean values.
	 * @return <code>true</code> if this parameter contains list of boolean values,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isBooleanList() { return type == ParameterType.BOOL_LIST; }
	
	/**
	 * Determines whether this parameter contains list of integer values.
	 * @return <code>true</code> if this parameter contains list of integer values,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isIntegerList() { return type == ParameterType.INT_LIST; }
	
	/**
	 * Determines whether this parameter contains list of float values.
	 * @return <code>true</code> if this parameter contains list of float values,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isFloatList() { return type == ParameterType.FLOAT_LIST; }
	
	/**
	 * Determines whether this parameter contains list of string values.
	 * @return <code>true</code> if this parameter contains list of string values,
	 * <code>false</code> otherwise.
	 */
	public boolean
	isStringList() { return type == ParameterType.STRING_LIST; }
	
	/**
	 * Defines if this parameter can be altered.
	 * @return <code>true</code> if the parameter is readonly and <code>false</code>
	 * if the parameter can be altered.
	 */
	public boolean
	isFixed() { return fix; }
	
	/**
	 * Defines if this parameter allows only one value or list of values.
	 * @return <code>false</code> if this parameter allows only one value and <code>true</code>
	 * if allows a list of values.
	 */
	public boolean
	isMultiplicity() { return multiplicity; }
	
	/**
	 * Sets if this parameter allows only one value or list of values.
	 * @param b <code>true</code> if this parameter allows list of values,
	 * <code>false</code> otherwise.
	 */
	public void
	setMultiplicity(boolean b) { multiplicity = b; }
	
	/**
	 * Defines if this parameter must be given when the device is to be created.
	 * @return <code>true</code> if this parameter must be given when the device 
	 * is to be created and <code>false</code> otherwise.
	 */
	public boolean
	isMandatory() { return mandatory; }
	
	/**
	 * Gets a <code>String</code> array with parameter's names this parameter depends on.
	 * @return A <code>String</code> array with parameter's names this parameter depends on
	 * or <code>null</code> if this parameter has no dependances.
	 */
	public String[]
	getDependances() { return depends; }
	
	/**
	 * Checks if this parameter depends on some other parameter(s).
	 * @return <code>true</code> if this parameter depends on some other parameter(s)
	 * and <code>false</code> otherwise.
	 */
	public boolean
	hasDependances() { return depends != null; }
	
	/**
	 * Parses a line of text.
	 * @param s A string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("DESCRIPTION: ")) {
			desc = s.substring("DESCRIPTION: ".length(), s.length());
			return true;
		} else if(s.startsWith("FIX: ")) {
			fix = Boolean.parseBoolean(s.substring("FIX: ".length(), s.length()));
			return true;
		} else if(s.startsWith("MANDATORY: ")) {
			mandatory = Boolean.parseBoolean (
				s.substring("MANDATORY: ".length(), s.length())
			);
			return true;
		} else if(s.startsWith("DEPENDS: ")) {
			s = s.substring("DEPENDS: ".length(), s.length());
			depends = Parser.parseList(s);
			return true;
		}else if(s.startsWith("TYPE: ")) {
			
			return true;
		}else if(s.startsWith("MULTIPLICITY: ")) {
			
			return true;
		}
		
		return false;
	}
	
	/**
	 * Parses the specified lines.
	 * @param lnS The lines to be parsed.
	 * @throws LscpException If some error occurs.
	 */
	protected void
	parseLines(String[] lnS) throws LscpException {
		for(String s : lnS) if(!parse(s)) {
			Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
		}
	}
	
	/**
	 * Gets the default value for this parameter.
	 * @return The default value for this parameter.
	 */
	public T
	getDefault() { return dflt; }
	
	/**
	 * Sets the default value for this parameter.
	 * @param dflt Specifies the default value for this parameter.
	 */
	public T
	setDefault(T dflt) { return this.dflt = dflt; }
	
	/**
	 * Gets the lower limit of the allowed value range for this parameter.
	 * @return The lower limit of the allowed value range for this
	 * parameter or <code>null</code> if the parameter doesn't have lower limit.
	 */
	public Number
	getRangeMin() { return rangeMin; }
	
	/**
	 * Sets the lower limit of the allowed value range for this parameter.
	 * @param min Specifies the lower limit of the allowed value range for this parameter.
	 */
	public void
	setRangeMin(Number min) { rangeMin = min; }
	
	/**
	 * Gets the upper limit of the allowed value range for this parameter.
	 * @return The upper limit of the allowed value range for this
	 * parameter or <code>null</code> if the parameter doesn't have upper limit.
	 */
	public Number
	getRangeMax() { return rangeMax; }
	
	/**
	 * Sets the upper limit of the allowed value range for this parameter.
	 * @param max Specifies the upper limit of the allowed value range for this parameter.
	 */
	public void
	setRangeMax(Number max) { rangeMax = max; }
	
	/**
	 * Gets a list of possible values for this parameter.
	 * @return A list of possible values for this parameter.
	 */
	public T[]
	getPossibilities() { return possibilities; }
		
	/**
	 * Sets the list of possible values for this parameter.
	 * @param pos The new list of possible values for this parameter.
	 */
	public void
	setPossibilities(T[] pos) { possibilities = pos; }
		
	/**
	 * Determines whether this parameter has a lower limit.
	 * @return <code>true</code> if this parameter has a lower limit,
	 * <code>false</code> otherwise.
	 */
	public boolean
	hasRangeMin() { return rangeMin != null; }
	
	/**
	 * Determines whether this parameter has an upper limit.
	 * @return <code>true</code> if this parameter has an upper limit,
	 * <code>false</code> otherwise.
	 */
	public boolean
	hasRangeMax() { return rangeMax != null; }
	
	/**
	 * Determines whether this parameter has a list of possible values.
	 * @return <code>true</code> if this parameter has a list of possible values,
	 * <code>false</code> otherwise.
	 */
	public boolean
	hasPossibilities() { return possibilities != null; }
	
	/**
	 * Returns the name of this parameter.
	 * @return The name of this parameter.
	 */
	public String
	toString() { return getName(); }
}
