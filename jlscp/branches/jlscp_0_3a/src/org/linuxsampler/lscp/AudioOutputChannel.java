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
	private Parameter<String> name;
	private Parameter<Boolean> mixChannel;
	private Parameter<Integer> mcDst;
	
	private final Vector<Parameter> prmList = new Vector<Parameter>();
	
	
	/** Creates a new instance of AudioOutputChannel */
	public
	AudioOutputChannel() {
	}
	
	/**
	 * Gets the name of this audio output channel.
	 * @return The name of this audio output channel.
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
	 * Determines whether this channel is a mix-channel.
	 * @return <code>true</code> if this is a mix-channel, <code>false</code> otherwise.
	 */
	public boolean
	isMixChannel() { return mixChannel == null ? false : mixChannel.getValue(); }
	
	/**
	 * Gets the <code>IS_MIX_CHANNEL</code> parameter.
	 * @return A <code>Parameter<Integer></code> instance.
	 */
	public Parameter<Boolean>
	getMixChannelParameter() { return mixChannel; }
	
	/**
	 * Sets whether this channel is a mix-channel.
	 * @param mixChannel Specifies whether this channel is a mix-channel or not.
	 */
	public void
	setMixChannelParameter(Parameter<Boolean> mixChannel) {
		this.mixChannel = mixChannel;
	}
	
	/**
	 * Gets the number of the real audio channel this mix channel refers to.
	 * @return The number of the real audio channel this mix channel refers to.
	 */
	public int
	getMixChannelDest() { return mcDst == null ? -1 : mcDst.getValue(); }
	
	/**
	 * Gets the <code>MIX_CHANNEL_DESTINATION</code> parameter.
	 * @return The <code>MIX_CHANNEL_DESTINATION</code> parameter.
	 */
	public Parameter<Integer>
	getMixChannelDestParameter() { return mcDst; }
	
	/**
	 * Sets the <code>MIX_CHANNEL_DESTINATION</code> parameter.
	 * @param mcDst The new <code>MIX_CHANNEL_DESTINATION</code> parameter.
	 */
	public void
	setMixChannelDestParameter(Parameter<Integer> mcDst) { this.mcDst = mcDst; }
	
	/**
	 * Adds additional parameter to this audio output channel.
	 * @param prm The additional parameter to be added.
	 */
	public void
	addParameter(Parameter prm) { prmList.add(prm); }
	
	/**
	 * Gets a <code>Parameter</code> array with the additional parameters
	 * of this audio output channel.
	 * @return A <code>Parameter</code> array with the additional parameters
	 * of this audio output channel.
	 */
	public Parameter[]
	getAdditionalParameters() {
		return prmList.toArray(new Parameter[prmList.size()]);
	}
	
	/**
	 * Gets a <code>Parameter</code> array providing all parameters
	 * of this audio output channel (including <code>NAME</code>,
	 * <code>IS_MIX_CHANNEL</code>, <code>MIX_CHANNEL_DESTINATION</code> parameters).
	 * @return A <code>Parameter</code> array providing all parameters
	 * of this audio output channel.
	 */
	public Parameter[]
	getAllParameters() {
		Parameter[] params;
		
		if(getMixChannelDestParameter() != null) {
			params = new Parameter[prmList.size() + 3];
			params[2] = getMixChannelDestParameter();
			for(int i = 0; i < prmList.size(); i++) params[i + 3] = prmList.get(i);
		} else {
			params = new Parameter[prmList.size() + 2];
			for(int i = 0; i < prmList.size(); i++) params[i + 2] = prmList.get(i);
		}
		
		params[0] = getNameParameter();
		params[1] = getMixChannelParameter();
		
		return params;
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
