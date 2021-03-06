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
 * This class provides default implementation of the <code>Device</code> interface.
 * @author  Grigor Iliev
 */
public abstract class AbstractDevice implements Device {
	private String driver = null;
	private boolean active = false;
	
	private final Vector<Parameter> prmList = new Vector<Parameter>();
	
	
	public
	AbstractDevice() {
	}
	
	/**
	 * Gets the driver name used by this device.
	 * @return The driver name used by this device.
	 */
	public String
	getDriverName() {  return driver; }
	
	/**
	 * Sets the driver name of this device.
	 * @param driver The new name for this device.
	 */
	public void
	setDriverName(String driver) {  this.driver = driver; }
	
	/**
	 * Determines whether this device is active.
	 * @return <code>false</code> if the device is inactive and <code>true</code> otherwise.
	 */
	public boolean
	isActive() { return active; }
	
	/**
	 * Sets whether this audio output device is active or not.
	 * @param active <code>false</code> if the device is inactive and doesn't output any sound,
	 * <code>true</code> otherwise.
	 */
	public void
	setActive(boolean active) { this.active = active; }
	
	/**
	 * Adds additional parameter to this device.
	 * @param prm The additional parameter to be added.
	 */
	public void
	addParameter(Parameter prm) { prmList.add(prm); }
	
	/**
	 * Gets <code>Parameter</code> array with the additional parameters of this device.
	 * @return <code>Parameter</code> array with the additional parameters of this device.
	 */
	public Parameter[]
	getAdditionalParameters() { return prmList.toArray(new Parameter[prmList.size()]); }
	
	/**
	 * Determines whether this device has additional parameters.
	 * @return <code>true</code> if this device has additional parameters,
	 *  <code>false</code> otherwise. 
	 */
	public boolean
	hasAdditionalParameters() { return !prmList.isEmpty(); }
}
