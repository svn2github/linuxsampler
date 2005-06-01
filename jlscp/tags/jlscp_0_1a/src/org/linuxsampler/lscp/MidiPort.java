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
	private String name = null;
	private final Vector<Parameter> prmList = new Vector<Parameter>();
	
	/**
	 * Gets the name of this MIDI port.
	 * @return The name of this MIDI port.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this MIDI port.
	 * @param name A <code>String</code> object containing the new name for this MIDI port.
	 */
	public void
	setName(String name) { this.name = name; }
	
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
	 * Returns the name of this MIDI port.
	 * @return The name of this MIDI port.
	 */
	public String
	toString() { return getName(); }
}
