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

package org.linuxsampler.lscp;

/**
 * Provides information about a running scan job.
 * @author Grigor Iliev
 */
public class ScanJobInfo implements Parseable {
	public int filesTotal;
	public int filesScanned;
	public String scanning;
	public int status;
	
	/**
	 * Creates a new instance of <code>ScanJobInfo</code>.
	 * @param resultSet An array with information categories about a scan job.
	 */
	public
	ScanJobInfo(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Determines whether the job is finished.
	 * Note that a negative value of <code>status</code> indicates error.
	 */
	public boolean
	isFinished() {
		if(status < 0) return true;
		if(filesScanned == filesTotal && status == 100) return true;
		return false;
	}
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("FILES_TOTAL: ")) {
			s= s.substring("FILES_TOTAL: ".length());
			try { filesTotal = Integer.parseInt(s); }
			catch(NumberFormatException x) { 
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
			}
		} else if(s.startsWith("FILES_SCANNED: ")) {
			s = s.substring("FILES_SCANNED: ".length());
			try { filesScanned = Integer.parseInt(s); }
			catch(NumberFormatException x) { 
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
			}
		} else if(s.startsWith("SCANNING: ")) {
			scanning = s.substring("SCANNING: ".length());
		} else if(s.startsWith("STATUS: ")) {
			s = s.substring("STATUS: ".length());
			try { status = Integer.parseInt(s); }
			catch(NumberFormatException x) { 
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
			}
		} else return false;
		
		return true;
	}
}
