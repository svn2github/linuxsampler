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
 * This class represents a factory for creating <code>Parameter</code> instances.
 * @author Grigor Iliev
 */
public class ParameterFactory {
	private
	ParameterFactory() {
		
	}
	
	/**
	 * Creates a <code>Parameter&lt;Boolean&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;Boolean&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<Boolean>
	createParameter(String name, Boolean value) {
		return new BoolParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;Boolean[]&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;Boolean[]&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<Boolean[]>
	createParameter(String name, Boolean[] value) {
		return new BoolListParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;Float&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;Float&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<Float>
	createParameter(String name, Float value) {
		return new FloatParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;Float[]&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;Float[]&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<Float[]>
	createParameter(String name, Float[] value) {
		return new FloatListParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;Integer&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;Integer&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<Integer>
	createParameter(String name, Integer value) {
		return new IntParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;Integer[]&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;Integer[]&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<Integer[]>
	createParameter(String name, Integer[] value) {
		return new IntListParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;String&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;String&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<String>
	createParameter(String name, String value) {
		return new StringParameter(name, value);
	}
	
	/**
	 * Creates a <code>Parameter&lt;String[]&gt;</code>
	 * instance with the specified name and value.
	 * @param name The parameter name.
	 * @param value The parameter value.
	 * @return The newly created <code>Parameter&lt;String[]&gt;</code>
	 * instance with the specified name and value.
	 */
	public static Parameter<String[]>
	createParameter(String name, String[] value) {
		return new StringListParameter(name, value);
	}
}
