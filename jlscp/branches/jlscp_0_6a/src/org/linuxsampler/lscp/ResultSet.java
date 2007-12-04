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

import java.util.Vector;


/**
 * Represents the Result set as defined in LSCP protocol specification.
 * @author  Grigor Iliev
 */
class ResultSet {
	private int idx = 0;
	
	private int code = 0;
	private String message = null;
	
	private String res = null;
	private final Vector<String> mlRes = new Vector<String>();
	
	private boolean warning = false;
	
	/** Creates a new instance of ResultSet */
	public ResultSet() {
	}
	
	/**
	 * Determines whether this result set has warning message.
	 * @return <code>true</code> if this result set has warning message,
	 * <code>false</code> otherwise.
	 */
	public boolean
	hasWarning() { return warning; }
	
	/**
	 * Sets whether this result set has warning message.
	 * @param b Determines whether this result set has warning message.
	 */
	public void
	setWarning(boolean b) { warning = b; }
	
	/**
	 * Gets the index of indexed warnings and empty result sets.
	 * @return The index of indexed warnings and empty result sets.
	 */
	public int
	getIndex() { return idx; }
	
	/**
	 * Sets the index of indexed warnings and empty result sets.
	 * @param idx The specifed index.
	 */
	public void
	setIndex(int idx) { this.idx = idx; }
	
	/**
	 * Gets the code of warning or error result set.
	 * @return The unique numeric identifier of the warning or error.
	 */
	public int
	getCode() { return code; }
	
	/**
	 * Sets the code of warning or error result set.
	 * @param code The unique numeric identifier of the warning or error.
	 */
	public void
	setCode(int code) { this.code = code; }
	
	/**
	 * Gets the warning or error message.
	 * @return The warning or error message.
	 */
	public String
	getMessage() { return message; }
	
	/**
	 * Sets the warning or error message.
	 * @param message The warning or error message.
	 */
	public void
	setMessage(String message) { this.message = message; }
	
	/**
	 * Gets a single line result set.
	 * @return A single line result set.
	 */
	public String
	getResult() { return res; }
	
	/**
	 * Sets a single line result set.
	 * @param res The single line result set.
	 */
	public void
	setResult(String res) { this.res = res; }
	
	/**
	 * Adds line to the multi-line result set.
	 * @param ln The line to be added.
	 */
	public void
	addLine(String ln) { mlRes.add(ln); }
	
	/**
	 * Gets a multi-line result set.
	 * @return A multi-line result set.
	 */
	public String[]
	getMultiLineResult() { return mlRes.toArray(new String[mlRes.size()]); }
}
