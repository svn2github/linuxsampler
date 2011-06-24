/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2011 Grigor Iliev <grigor@grigoriliev.com>
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
 *
 * @author Grigor Iliev
 */
public class EffectInstance extends Effect {
	private int instanceId = -1;
	private int parameterCount = -1;

	private final Vector<EffectParameter> prmList = new Vector<EffectParameter>();

	/** Creates a new instance of <code>EffectInstance</code> */
	public
	EffectInstance() { }

	/**
	 * Creates a new instance of <code>EffectInstance</code> and parses the information
	 * about a specific effect instance described by <code>resultSet</code>.
	 * @param resultSet An array with information categories about an effect entity.
	 * @throws LscpException If the parse fail.
	 */
	public
	EffectInstance(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}

	/**
	 * Gets the numerical ID of this effect instance.
	 * @return The numerical ID of this effect instance
	 * or -1 if the effect instance ID is not set.
	 */
	public int
	getInstanceId() { return instanceId; }

	/**
	 * Sets the numerical ID of this effect instance.
	 * @param id The new effect instance ID.
	 */
	public void
	setInstanceId(int id) { instanceId = id; }

	/**
	 * Gets the number of parameters (input controls) the effect instance provides,
	 * to allow controlling the effect parameters in realtime.
	 * @return The number of parameters the effect instance provides.
	 */
	public int
	getParameterCount() { return parameterCount; }

	/**
	 * Adds effect parameter.
	 * @param prm The effect parameter to be added.
	 */
	public void
	addParameter(EffectParameter prm) { prmList.add(prm); }

	/**
	 * Gets all parameters available for this effect.
	 * @return <code>FloatParameter</code> array with all parameters available for this effect.
	 */
	public EffectParameter[]
	getParameters() { return prmList.toArray(new EffectParameter[prmList.size()]); }

	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(super.parse(s)) return true;

		if(s.startsWith("INPUT_CONTROLS: ")) {
			s = s.substring("INPUT_CONTROLS: ".length());
			parameterCount = Parser.parseInt(s);
		} else return false;

		return true;
	}
}
