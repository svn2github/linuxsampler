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

/**
 * Provides information about the fill state of a disk stream buffer.
 * @author  Grigor Iliev
 */
public class BufferFill {
	private int streamID;
	private int value;
	
	/** Creates a new instance of <code>BufferFill</code>. */
	public
	BufferFill() { this(0, 0); }
	
	/** 
	 * Creates a new instance of <code>BufferFill</code> with
	 * the specified stream ID and fill amount.
	 * @param streamID The stream ID of the disk stream buffer.
	 * @param value The fill amount of the disk stream buffer.
	 */
	public
	BufferFill(int streamID, int value) {
		setStreamID(streamID);
		setValue(value);
	}
	
	/**
	 * Gets the stream ID of the disk stream buffer.
	 * @return The stream ID of the disk stream buffer.
	 */
	public int
	getStreamID() { return streamID; }
	
	/**
	 * Sets the stream ID of the disk stream buffer.
	 * @param id The stream ID of the disk stream buffer.
	 */
	public void
	setStreamID(int id) { streamID = id; }
	
	/**
	 * Gets the fill amount of the buffer.
	 * @return The fill amount of the buffer.
	 */
	public int
	getValue() { return value; }
	
	/**
	 * Sets the fill amount of the buffer.
	 * @param val The fill amount of the buffer.
	 */
	public void
	setValue(int val) { value = val; }
}
