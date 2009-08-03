/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005-2007 Grigor Iliev <grigor@grigoriliev.com>
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

package org.linuxsampler.lscp.event;

/**
 *
 * @author Grigor Iliev
 */
public class InstrumentsDbEvent extends java.util.EventObject {
	private String pathName;
	private String newName;
	private int jobId;
	
	
	/**
	 * Constructs an <code>InstrumentsDbEvent</code> object.
	 * @param source The object that originated the event.
	 * @param pathName Depending on the event this is
	 * the absolute path name of either a directory, or an instrument.
	 */
	public
	InstrumentsDbEvent(Object source, String pathName) {
		this(source, pathName, null);
	}
	
	/**
	 * Constructs an <code>InstrumentsDbEvent</code> object.
	 * @param source The object that originated the event.
	 * @param pathName Depending on the event this is
	 * the absolute (escaped) path name of either a directory, or an instrument.
	 * @param newName When an instrument or directory is renamed,
	 * specifies the new (non-escaped) name for the respective instrument or directory.
	 */
	public
	InstrumentsDbEvent(Object source, String pathName, String newName) {
		super(source);
		this.pathName = pathName;
		this.newName = newName;
	}
	
	/**
	 * Constructs an <code>InstrumentsDbEvent</code> object.
	 * @param source The object that originated the event.
	 * @param jobId The job ID.
	 */
	public
	InstrumentsDbEvent(Object source, int jobId) {
		super(source);
		this.jobId = jobId;
	}
	
	/**
	 * Gets the (escaped) path name of the changed instrument or directory.
	 */
	public String
	getPathName() { return pathName; }
	
	/**
	 * When an instrument or directory is renamed, this method
	 * returns the new (non-escaped) name for the respective instrument or directory.
	 */
	public String
	getNewName() { return newName; }
	
	/**
	 * Returns the ID of the job, which status has changed.
	 */
	public int
	getJobId() { return jobId; }
}
