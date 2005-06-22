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
 * This class provides detailed information about an audio output chanel.
 * @author  Grigor Iliev
 */
public class AudioOutputChannel {
	private String name = null;
	private boolean mixChannel = false;
	private int mcDst = 0;
	
	private final Vector<Parameter> prmList = new Vector<Parameter>();
	
	
	/** Creates a new instance of AudioOutputChannel */
	public AudioOutputChannel() {
	}
	
	/**
	 * Gets the name of this audio output channel.
	 * @return The name of this audio output channel.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this audio output channel.
	 * @param name A <code>String</code> object containing the new name
	 * for this audio output channel.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Determines whether this channel is a mix-channel.
	 * @return <code>true</code> if this is a mix-channel, <code>false</code> otherwise.
	 */
	public boolean
	isMixChannel() { return mixChannel; }
	
	/**
	 * Sets whether this channel is a mix-channel.
	 * @param mixChannel Specifies whether this channel is a mix-channel or not.
	 */
	public void
	setMixChannel(boolean mixChannel) { this.mixChannel = mixChannel; }
	
	/**
	 * Gets the number of the real audio channel this mix channel refers to.
	 * @return The number of the real audio channel this mix channel refers to.
	 */
	public int
	getMixChannelDest() { return mcDst; }
	
	/**
	 * Sets the number of the real audio channel this mix channel refers to.
	 * @param chNum The number of the real audio channel this mix channel refers to.
	 */
	public void
	setMixChannelDest(int chNum) { mcDst = chNum; }
	
	/**
	 * Adds additional parameter to this audio output channel.
	 * @param prm The additional parameter to be added.
	 */
	public void
	addParameter(Parameter prm) { prmList.add(prm); }
	
	/**
	 * Gets an <code>Parameter</code> array with the additional parameters
	 * of this audio output channel.
	 * @return An <code>Parameter</code> array with the additional parameters
	 * of this audio output channel.
	 */
	public Parameter[]
	getAdditionalParameters() {
		return prmList.toArray(new Parameter[prmList.size()]);
	}
	
	/**
	 * Determines whether this audio output channel has additional parameters.
	 * @return <code>true</code> if this audio output channel has additional parameters,
	 *  <code>false</code> otherwise. 
	 */
	public boolean
	hasAdditionalParameters() { return prmList.size() > 0; }
	
	/**
	 * Returns the name of this audio output chanel.
	 * @return The name of this audio output chanel.
	 */
	public String
	toString() { return getName(); }
}
