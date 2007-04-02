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
 * Provides general information about LinuxSampler instance.
 * @author Grigor Iliev
 */
public final class ServerInfo implements Parseable {
	private String desc = null;
	private String ver = null;
	private String protoVer = null;
	
	/**
	 * Creates a new instance of <code>ServerInfo</code> and parses the information
	 * described by <code>resultSet</code>.
	 * @param resultSet An array with information categories about a sampler.
	 */
	public
	ServerInfo(String[] resultSet) {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets description about the sampler.
	 * @return Description about the sampler.
	 */
	public String
	getDescription() { return desc; }
	
	/**
	 * Gets the version of the sampler.
	 * @return The version of the sampler.
	 */
	public String
	getVersion() { return ver; }
	
	/**
	 * Gets the version of the LSCP protocol.
	 * @return The version of the LSCP protocol.
	 */
	public String
	getProtocolVersion() { return protoVer; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 */
	public boolean
	parse(String s) {
		if(s.startsWith("DESCRIPTION: ")) {
			desc = s.substring("DESCRIPTION: ".length());
		} else if(s.startsWith("VERSION: ")) {
			ver = s.substring("VERSION: ".length());
		} else if(s.startsWith("PROTOCOL_VERSION: ")) {
			protoVer = s.substring("PROTOCOL_VERSION: ".length());
		} else return false;
		
		return true;
	}
}
