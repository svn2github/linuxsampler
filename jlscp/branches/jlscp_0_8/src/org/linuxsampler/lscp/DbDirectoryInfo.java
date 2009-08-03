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

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import static org.linuxsampler.lscp.Parser.*;


/**
 * Provides information about a database instrument directory.
 * @author Grigor Iliev
 */
public class DbDirectoryInfo {
	private String name = "";
	private String description = "";
	private final Date dateCreated = new EnhancedDate();
	private final Date dateModified = new EnhancedDate();
	private String parentDirectoryPath = null;
	private boolean showAbsolutePath = false;
	
	private static DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	private static DateFormat dateFormat2 = DateFormat.getInstance();
	
	/**
	 * Creates a new instance of <code>DbDirectoryInfo</code>.
	 * @param resultSet An array with information categories about a DB directory.
	 */
	public
	DbDirectoryInfo(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Gets the name of this directory.
	 * @return The name of this directory.
	 */
	public String
	getName() { return name; }
	
	/**
	 * Sets the name of this directory.
	 * @param name The name of this directory.
	 */
	public void
	setName(String name) { this.name = name; }
	
	/**
	 * Gets a brief description about this directory.
	 * @return A brief description about this directory.
	 */
	public String
	getDescription() { return description; }
	
	/**
	 * Returns the date when the directory is created.
	 **/
	public Date
	getDateCreated() { return dateCreated; }
	
	/**
	 * Returns the date when the directory is last modified.
	 **/
	public Date
	getDateModified() { return dateModified; }
	
	/**
	 * Returns the absolute path name of the directory or
	 * <code>null</code> if the parent directory path is not set.
	 **/
	public String
	getDirectoryPath() {
		if(getParentDirectoryPath() == null && getName().equals("/")) return "/";
		if(getParentDirectoryPath() == null) return null;
		if(getParentDirectoryPath().length() == 1) {
			if(!getParentDirectoryPath().equals("/")) return null;
			return getParentDirectoryPath() + toEscapedFileName(getName());
		}
		
		return getParentDirectoryPath() + "/" + toEscapedFileName(getName());
	}
	
	/**
	 * Returns the absolute path name of the directory containing this directory.
	 **/
	public String
	getParentDirectoryPath() { return parentDirectoryPath; }
	
	/**
	 * Sets the absolute path name of the directory containing this directory.
	 **/
	public void
	setParentDirectoryPath(String dir) { parentDirectoryPath = dir; }
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if(s.startsWith("DESCRIPTION: ")) {
			description = s.substring("DESCRIPTION: ".length());
			description = toNonEscapedString(description);
		} else if(s.startsWith("CREATED: ")) {
			s = s.substring("CREATED: ".length());
			try { dateCreated.setTime(dateFormat.parse(s).getTime()); }
			catch(ParseException e) { throw new LscpException(e.getMessage()); }
		} else if(s.startsWith("MODIFIED: ")) {
			s = s.substring("MODIFIED: ".length());
			try { dateModified.setTime(dateFormat.parse(s).getTime()); }
			catch(ParseException e) { throw new LscpException(e.getMessage()); }
		} else return false;
		
		return true;
	}
	
	/**
	 * Determines whether the <code>toString()</code>
	 * method should return the directory name or
	 * the absolute path name of the directory.
	 * The default value is <code>false</code>.
	 */
	public boolean
	getShowAbsolutePath() { return showAbsolutePath; }
	
	/**
	 * Sets whether the <code>toString()</code> method
	 * should return the absolute path name of the directory.
	 * @param b If <code>true</code> the <code>toString()</code>
	 * method will return the absolute path name of the directory
	 * instead of the directory name.
	 */
	public void
	setShowAbsolutePath(boolean b) { showAbsolutePath = b; }
	
	/**
	 * Returns the name or the absolute path name of
	 * the directory as specified by {@link #getShowAbsolutePath}.
	 * @see #setShowAbsolutePath
	 */
	public String
	toString() {
		if(getShowAbsolutePath()) return getDirectoryPath();
		return getName();
	}
	
	private class EnhancedDate extends Date {
		public String
		toString() { return dateFormat2.format(this); }
	}
}
