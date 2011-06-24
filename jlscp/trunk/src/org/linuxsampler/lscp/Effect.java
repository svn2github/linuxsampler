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

import static org.linuxsampler.lscp.Parser.*;

/**
 *
 * @author Grigor Iliev
 */
public class Effect implements Parseable {
	private int effectId = -1;
	private String system = null;
	private String module = null;
	private String name = null;
	private String description = "";

	/** Creates a new instance of <code>Effect</code> */
	public
	Effect() { }

	/**
	 * Creates a new instance of <code>Effect</code> and parses the information
	 * about a specific effect described by <code>resultSet</code>.
	 * @param resultSet An array with information categories about an effect entity.
	 * @throws LscpException If the parse fail.
	 */
	public
	Effect(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}

	/**
	 * Gets the numerical ID of this effect.
	 * @return The numerical ID of this effect
	 * or -1 if the effect ID is not set.
	 */
	public int
	getEffectId() { return effectId; }

	/**
	 * Sets the numerical ID of this effect.
	 * @param id The new effect ID.
	 */
	public void
	setEffectId(int id) { effectId = id; }

	/**
	 * Gets the name of the effect plugin system the effect is based on (e.g. "LADSPA").
	 */
	public String
	getSystem() { return system; }

	/**
	 * Gets the module of the effect plugin system that contains this effect.
	 * The module is usually the dynamic-linked library (DLL) filename of
	 * the effect plugin, including full path.
	 * @return The module of the effect plugin system that contains this effect.
	 */
	public String
	getModule() { return module; }

	/**
	 * Gets the unique name of the effect within its module.
	 * @return The unique name of the effect within its module.
	 */
	public String
	getName() { return name; }

	/**
	 * Gets human readable name of the effect,
	 * intended to be displayed in user interfaces.
	 * @return The human readable name of the effect,
	 * intended to be displayed in user interfaces.
	 */
	public String
	getDescription() { return description; }

	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("SYSTEM: ")) {
			system = s.substring("SYSTEM: ".length());
		} else if(s.startsWith("MODULE: ")) {
			module = toNonEscapedString(s.substring("MODULE: ".length()));
		} else if(s.startsWith("NAME: ")) {
			name = toNonEscapedString(s.substring("NAME: ".length()));
		} else if(s.startsWith("DESCRIPTION: ")) {
			description = toNonEscapedString(s.substring("DESCRIPTION: ".length()));
		} else return false;

		return true;
	}
}
