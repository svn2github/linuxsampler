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

import java.util.Vector;


/**
 * This class is used to provide detailed information about a MIDI port.
 * @author  Grigor Iliev
 */
public class MidiPort {
	private Parameter<String> name;
	private final Vector<Parameter> prmList = new Vector<Parameter>();
	
	/**
	 * Gets the name of this MIDI port.
	 * @return The name of this MIDI port.
	 */
	public String
	getName() { return name == null ? null : name.getValue(); }
	
	/**
	 * Gets the <code>NAME</code> parameter.
	 * @return A <code>Parameter<String></code> instance.
	 */
	public Parameter<String>
	getNameParameter() { return name; }
	
	/**
	 * Sets the <code>NAME</code> parameter.
	 * @param name A <code>Parameter<String></code> instance.
	 */
	public void
	setNameParameter(Parameter<String> name) { this.name = name; }
	
	/**
	 * Adds additional parameter to this MIDI port.
	 * @param prm The additional parameter to be added.
	 */
	public void
	addParameter(Parameter prm) { prmList.add(prm); }
	
	/**
	 * Gets <code>Parameter</code> array with the additional parameters of this MIDI port.
	 * @return <code>Parameter</code> array with the additional parameters of this MIDI port.
	 */
	public Parameter[]
	getAdditionalParameters() { return prmList.toArray(new Parameter[prmList.size()]); }
	
	/**
	 * Determines whether this MIDI port has additional parameters.
	 * @return <code>true</code> if this MIDI port has additional parameters,
	 *  <code>false</code> otherwise. 
	 */
	public boolean
	hasAdditionalParameters() { return !prmList.isEmpty(); }
	
	/**
	 * Gets a <code>Parameter</code> array providing all parameters
	 * of this MIDI port (including <code>NAME</code> parameter).
	 * @return A <code>Parameter</code> array providing all parameters
	 * of this MIDI port.
	 */
	public Parameter[]
	getAllParameters() {
		Parameter[] params = new Parameter[prmList.size() + 1];
		params[0] = getNameParameter();
		for(int i = 0; i < prmList.size(); i++) params[i + 1] = prmList.get(i);
		return params;
	}
	
	/**
	 * Returns the name of this MIDI port.
	 * @return The name of this MIDI port.
	 */
	public String
	toString() { return getName(); }
}
