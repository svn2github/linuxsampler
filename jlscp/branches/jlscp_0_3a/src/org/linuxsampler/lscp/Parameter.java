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
 * Defines the generic properties that every parameter should have.
 * @author  Grigor Iliev
 */
public interface Parameter<T> {
	/**
	 * Gets the name of this parameter.
	 * @return The name of this parameter.
	 */
	public String getName();
	
	/**
	 * Sets the name of this parameter.
	 * @param name A <code>String</code> instance containing the new name for this parameter.
	 */
	public void setName(String name);
	
	/**
	 * Parses the specified character string and sets the value of this parameter
	 * with the parsed result.
	 * @param s A character string containing the value to be parsed.
	 * @throws LscpException If the parsing failed.
	 */
	public void parseValue(String s) throws LscpException;
	
	/**
	 * Gets a character string representation of the parameter's value.
	 * @return A character string representation of the parameter's value.
	 */
	public String getStringValue();
	
	/**
	 * Gets the description of this parameter.
	 * @return The description of this parameter.
	 */
	public String getDescription();
	
	/**
	 * Gets the type of this parameter.
	 * @return The type of this parameter.
	 */
	public ParameterType getType();
	
	/**
	 * Gets the current value of this parameter.
	 * @return The current value of this parameter.
	 */
	public T getValue();
	
	/**
	 * Sets the current value of this parameter.
	 * @param val The new value for this parameter.
	 */
	public void setValue(T val);
	
	/**
	 * Gets the default value for this parameter.
	 * @return The default value for this parameter.
	 */
	public T getDefault();
		
	/**
	 * Defines if this parameter can be altered.
	 * @return <code>true</code> if the parameter is readonly and <code>false</code>
	 * if the parameter can be altered.
	 */
	public boolean isFixed();
	
	/**
	 * Defines if this parameter allows only one value or list of values.
	 * @return <code>false</code> if this parameter allows only one value and <code>true</code>
	 * if allows a list of values.
	 */
	public boolean isMultiplicity();
	
	/**
	 * Defines if this parameter must be given when the device is to be created.
	 * @return <code>true</code> if this parameter must be given when the device 
	 * is to be created and <code>false</code> otherwise.
	 */
	public boolean isMandatory();
	
	/**
	 * Checks if this parameter depends on some other parameter(s).
	 * @return <code>true</code> if this parameter depends on some other parameter(s)
	 * and <code>false</code> otherwise.
	 */
	public boolean hasDependances();
	
	/**
	 * Gets a <code>String</code> array with parameter's names this parameter depends on.
	 * @return A <code>String</code> array with parameter's names this parameter depends on
	 * or <code>null</code> if this parameter has no dependances.
	 */
	public String[] getDependances();
	
	/**
	 * Determines whether this parameter has a lower limit.
	 * @return <code>true</code> if this parameter has a lower limit,
	 * <code>false</code> otherwise.
	 */
	public boolean hasRangeMin();
	
	/**
	 * Gets the lower limit of the allowed value range for this parameter.
	 * @return The lower limit of the allowed value range for this
	 * parameter or <code>null</code> if the parameter doesn't have lower limit.
	 */
	public Number getRangeMin();
	
	/**
	 * Determines whether this parameter has an upper limit.
	 * @return <code>true</code> if this parameter has an upper limit,
	 * <code>false</code> otherwise.
	 */
	public boolean hasRangeMax();
	
	/**
	 * Gets the upper limit of the allowed value range for this parameter.
	 * @return The upper limit of the allowed value range for this
	 * parameter or <code>null</code> if the parameter doesn't have upper limit.
	 */
	public Number getRangeMax();
	
	/**
	 * Determines whether this parameter has a list of possible values.
	 * @return <code>true</code> if this parameter has a list of possible values,
	 * <code>false</code> otherwise.
	 */
	public boolean hasPossibilities();
	
	/**
	 * Gets a list of possible values for this parameter.
	 * @return A list of possible values for this parameter.
	 */
	public T[] getPossibilities();
}
