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

import static org.linuxsampler.lscp.Parser.*;

/**
 * Provides information about a specific sampler engine.
 * @author  Grigor Iliev
 */
public class SamplerEngine implements Parseable {
	private String name = null;
	private String desc = null;
	private String ver = null;
	
	
	/** Creates a new instance of <code>SamplerEngine</code> */
	public SamplerEngine() {
	}
	
	/**
	 * Creates a new instance of <code>SamplerEngine</code> and parses the information
	 * about a sampler engine described by <code>resultSet</code>.
	 * @param resultSet An array of information categories about a sampler engine.
	 */
	public
	SamplerEngine(String[] resultSet) {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets the name of this sampler engine.
	 * @return The name of this sampler engine.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this sampler engine.
	 * @param name A <code>String</code> instance containing the new name for
	 * this sampler engine.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Gets a description about this sampler engine.
	 * @return A description about this sampler engine.
	 */
	public String
	getDescription() { return desc; }
	
	/**
	 * Gets the version of this sampler engine.
	 * @return The version of this sampler engine.
	 */
	public String
	getVersion() { return ver; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 */
	public boolean
	parse(String s) {
		if(s.startsWith("DESCRIPTION: ")) {
			desc = s.substring("DESCRIPTION: ".length(), s.length());
			desc = toNonEscapedString(desc);
		} else if(s.startsWith("VERSION: ")) {
			ver = s.substring("VERSION: ".length(), s.length());
		} else return false;
		
		return true;
	}
	
	/**
	 * Compares this <code>SamplerEngine</code> instance to the specified object.
	 * The result is <code>true</code> if <code>obj</code> is reference to
	 * <code>this</code>, or if <code>obj</code> is a <code>SamplerEngine</code> instance
	 * and has non-<code>null</code> name equal to the name of this engine. 
	 *
	 * @return <code>true</code> if <code>obj</code> is reference to
	 * <code>this</code>, or if <code>obj</code> is a <code>SamplerEngine</code> instance
	 * and has non-<code>null</code> name equal to the name of this engine;
	 * <code>false</code> otherwise.
	 * @see #getName
	 */
	public boolean
	equals(Object obj) {
		if(this == obj) return true;
		
		if(getName() == null || obj == null) return false;
		
		if(obj instanceof SamplerEngine)
			return getName().equals(((SamplerEngine)obj).getName());
		
		return false;
	}
	
	public String
	toString() { return getName() + " engine"; }
}
