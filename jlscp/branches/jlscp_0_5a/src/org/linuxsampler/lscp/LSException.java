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
 * Thrown to indicate that LinuxSampler has returned an error message.
 * @author  Grigor Iliev
 */
public class LSException extends Exception {
	private int code;
	
	/** 
	 * Creates a new instance of LSException with the specified error code and detail message.
	 * @param code Specifies the error code.
	 * @param msg Specifies the detail message.
	 */
	public
	LSException(int code, String msg) {
		super(msg);
		this.code = code;
	}
	
	/**
	 * Gets the numeric unique identifier of the error.
	 * @return The numeric unique identifier of the error.
	 */
	public int
	getCode() { return code; }
}
