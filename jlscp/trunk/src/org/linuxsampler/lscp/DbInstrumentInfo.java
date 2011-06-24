/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005-2010 Grigor Iliev <grigor@grigoriliev.com>
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
import java.text.NumberFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;

import java.util.Date;

import static org.linuxsampler.lscp.Parser.*;


/**
 * Provides information about a database instrument.
 * @author Grigor Iliev
 */
public class DbInstrumentInfo extends AbstractInstrument implements Parseable {
	private String directoryPath = null;
	private final Date dateCreated = new EnhancedDate();
	private final Date dateModified = new EnhancedDate();
	private long size = 0;
	private boolean drum = false;
	private String product = "";
	private String artists = "";
	private String keywords = "";
	private boolean showAbsolutePath = false;
	
	private static DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	private static DateFormat dateFormat2 = DateFormat.getInstance();
	private static NumberFormat numberFormat = NumberFormat.getInstance();
	
	static {
		numberFormat.setMinimumFractionDigits(0);
		numberFormat.setMaximumFractionDigits(1);
	}

	/** Creates a new instance of <code>DbInstrumentInfo</code>. */
	public
	DbInstrumentInfo() { }
	
	/**
	 * Creates a new instance of <code>DbInstrumentInfo</code>.
	 * @param resultSet An array with information categories about a DB instrument.
	 */
	public
	DbInstrumentInfo(String[] resultSet) throws LscpException {
		for(String s : resultSet)
			if(!parse(s)) Client.getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
	}
	
	/**
	 * Returns the absolute path name of the directory containing this instrument.
	 **/
	public String
	getDirectoryPath() { return directoryPath; }
	
	/**
	 * Sets the absolute path name of the directory containing this instrument.
	 **/
	public void
	setDirectoryPath(String dir) { directoryPath = dir; }
	
	/**
	 * Returns the absolute path name of this instrument or
	 * <code>null</code> if the directory path for this instrument is not set.
	 **/
	public String
	getInstrumentPath() {
		if(getDirectoryPath() == null) return null;
		if(getDirectoryPath().length() == 1) {
			if(!getDirectoryPath().equals("/")) return null;
			return getDirectoryPath() + toEscapedFileName(getName());
		}
		
		return getDirectoryPath() + "/" + toEscapedFileName(getName());
	}
	
	/**
	 * Returns the date when the instrument is created.
	 **/
	public Date
	getDateCreated() { return dateCreated; }
	
	/**
	 * Returns the date when the instrument is last modified.
	 **/
	public Date
	getDateModified() { return dateModified; }
	
	/**
	 * Returns the size of the instrument in bytes.
	 **/
	public long
	getSize() { return size; }
	
	/**
	 * Gets a user friendly representation of the instruments size.
	 */
	public String
	getFormatedSize() {
		String s;
		long i = getSize();
		if(i > 1024*1024*1024) {
			double d = i;
			d /= (1024*1024*1024);
			s = numberFormat.format(d) + " GB";
		} else if(i > 1024*1024) {
			double d = i;
			d /= (1024*1024);
			s = numberFormat.format(d) + " MB";
		} else if(i > 1024) {
			double d = i;
			d /= (1024);
			s = numberFormat.format(d) + " KB";
		} else {
			s = numberFormat.format(i) + " bytes";
		}
		
		return s;
	}
	
	/**
	 * Determines whether the instrument is a drumkit or a chromatic instrument.
	 **/
	public boolean
	isDrum() { return drum; }
	
	/**
	 * Returns the product title of the instrument.
	 **/
	public String
	getProduct() { return product; }
	
	/**
	 * Lists the artist names.
	 **/
	public String
	getArtists() { return artists; }
	
	/**
	 * Provides a list of keywords that refer to the instrument.
	 * Keywords are separated with semicolon and blank.
	 **/
	public String
	getKeywords() { return keywords; }
	
	public String
	getEngine() {
		// TODO: engine lookup?
		return getFormatFamily();
	}
	
	/**
	 * Parses a line of text.
	 * @param s The string to be parsed.
	 * @return <code>true</code> if the line has been processed, <code>false</code> otherwise.
	 * @throws LscpException If some error occurs.
	 */
	public boolean
	parse(String s) throws LscpException {
		if (super.parse(s)) return true;
		
		if(s.startsWith("CREATED: ")) {
			s = s.substring("CREATED: ".length());
			try { dateCreated.setTime(dateFormat.parse(s).getTime()); }
			catch(ParseException e) { throw new LscpException(e.getMessage()); }
		} else if(s.startsWith("MODIFIED: ")) {
			s = s.substring("MODIFIED: ".length());
			try { dateModified.setTime(dateFormat.parse(s).getTime()); }
			catch(ParseException e) { throw new LscpException(e.getMessage()); }
		} else if(s.startsWith("SIZE: ")) {
			try { size = Long.parseLong(s.substring("SIZE: ".length())); }
			catch(NumberFormatException x) { 
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
			}
		} else if(s.startsWith("IS_DRUM: ")) {
			drum = Boolean.parseBoolean(s.substring("IS_DRUM: ".length()));
		} else if(s.startsWith("PRODUCT: ")) {
			product = s.substring("PRODUCT: ".length());
			product = toNonEscapedString(product);
		} else if(s.startsWith("ARTISTS: ")) {
			artists = s.substring("ARTISTS: ".length());
			artists = toNonEscapedString(artists);
		} else if(s.startsWith("KEYWORDS: ")) {
			keywords = s.substring("KEYWORDS: ".length());
			keywords = toNonEscapedString(keywords);
		} else return false;
		
		return true;
	}
	
	/**
	 * Determines whether the <code>toString()</code>
	 * method should return the instrument name or
	 * the absolute path name of the instrument.
	 * The default value is <code>false</code>.
	 */
	public boolean
	getShowAbsolutePath() { return showAbsolutePath; }
	
	/**
	 * Sets whether the <code>toString()</code> method
	 * should return the absolute path name of the instrument.
	 * @param b If <code>true</code> the <code>toString()</code>
	 * method will return the absolute path name of the
	 * instrument instead of the instrument name.
	 */
	public void
	setShowAbsolutePath(boolean b) { showAbsolutePath = b; }
	
	/**
	 * Returns the name or the absolute path name of
	 * the instrument as specified by {@link #getShowAbsolutePath}.
	 * @see #setShowAbsolutePath
	 */
	public String
	toString() {
		if(getShowAbsolutePath()) return getInstrumentPath();
		return getName();
	}
	
	private class EnhancedDate extends Date {
		public String
		toString() { return dateFormat2.format(this); }
	}
}
