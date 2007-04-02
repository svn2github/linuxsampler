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
 * Defines the generic properties that every device should have.
 *
 * @author  Grigor Iliev
 */
public interface Device {
	/**
	 * Gets the numerical ID of this device.
	 * @return The numerical ID of this device or -1 if the device number is not set.
	 */
	public int getDeviceId();
	
	/**
	 * Gets the driver name used by this device.
	 * @return The driver name used by this device.
	 */
	public String getDriverName();
	
	/**
	 * Determines whether this device is active.
	 * @return <code>false</code> if the device is inactive and <code>true</code> otherwise.
	 */
	public boolean isActive();
	
	/**
	 * Gets the <code>ACTIVE</code> parameter.
	 * @return A <code>Parameter<Boolean></code> instance
	 * representing the active state of the device.
	 */
	public Parameter<Boolean> getActiveParameter();
	
	/**
	 * Gets <code>Parameter</code> array with the additional parameters of this device.
	 * @return <code>Parameter</code> array with the additional parameters of this device.
	 */
	public Parameter[]
	getAdditionalParameters();
	
	/**
	 * Determines whether this device has additional parameters.
	 * @return <code>true</code> if this device has additional parameters,
	 *  <code>false</code> otherwise. 
	 */
	public boolean
	hasAdditionalParameters();
}
