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

import java.io.InputStream;
import java.io.IOException;


/**
 *
 * @author  Grigor Iliev
 */
class LscpInputStream {
	private InputStream in;
	private StringBuffer buf = new StringBuffer();
	
	/**
	 * Creates a new instance of LscpInputStream.
	 *
	 */
	public
	LscpInputStream(InputStream in) {
		this.in = in;
	}
	
	/**
	 * Reads a line. 
	 * This method is thread safe.
	 * 
	 * @return A string containing the next line readed from the stream or <code>null</code> 
	 * if the end of the stream has been reached.
	 *
	 * @throws LscpException If the end of line or file is reached unexpectedly.
	 * @throws IOException If an I/O error occurs.
	 */
	public synchronized String
	readLine() throws IOException, LscpException {
		int i;
		buf.setLength(0);
		
		while((i = in.read()) != -1) {
			if(i == '\r') {
				checkLF();
				break;
			}
			buf.append((char)i);
		}
		
		if(i == -1) {
			if(buf.length() > 0)
				throw new LscpException(LscpI18n.getLogMsg("LscpInputStream.EOL!"));
			return null;
		}
		return buf.toString();
	}
	
	/**
	 * Returns the number of bytes that can be read from this input stream without blocking.
	 *
	 * @return The number of bytes that can be read from this input stream without blocking.
	 * @throws IOException If an I/O error occurs.
	 */
	public synchronized int
	available() throws IOException { return in.available(); }
	
	private void
	skipLine() throws IOException, LscpException {
		int i;
		while((i = in.read()) != -1) {
			if(i == '\r') {
				checkLF();
				break;
			}
		}
	}
	
	private void
	checkLF() throws IOException, LscpException {
		int i = in.read();
		if(i == -1) throw new LscpException(LscpI18n.getLogMsg("LscpInputStream.EOF!"));
		if(i != '\n') throw new LscpException(LscpI18n.getLogMsg("LscpInputStream.EOL!"));
	}
}
