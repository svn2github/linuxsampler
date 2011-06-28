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

/**
 *
 * @author Grigor Iliev
 */
public class EffectParameter extends FloatParameter {
	
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	@Override
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("DESCRIPTION: ")) {
			s = s.substring("DESCRIPTION: ".length(), s.length());
			setDescription(Parser.toNonEscapedString(s));
			return true;
		}
		
		if(super.parse(s)) return true;
		else if(s.startsWith("VALUE: ")) {
			s = s.substring("VALUE: ".length(), s.length());
			setValue(Parser.parseFloat(s));
			return true;
		}
		
		return false;
	}
}
