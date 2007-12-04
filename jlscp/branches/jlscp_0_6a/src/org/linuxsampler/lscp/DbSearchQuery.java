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
import java.text.SimpleDateFormat;

import java.util.Date;
import java.util.Vector;

/**
 * This class represents a query containg the search criterias
 * for the instruments to obtain.
 * @author Grigor Iliev
 */
public class DbSearchQuery {
	private static DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	
	public String name = null;
	public Vector<String> formatFamilies = new Vector<String>();
	public long minSize = -1;
	public long maxSize = -1;
	public Date createdBefore = null;
	public Date createdAfter = null;
	public Date modifiedBefore = null;
	public Date modifiedAfter = null;
	public String description = null;
	public String product = null;
	public String artists = null;
	public String keywords = null;
	public InstrumentType instrumentType = InstrumentType.BOTH;
	
	public enum InstrumentType {
		CHROMATIC,
		DRUM,
		BOTH
	}
	
	
	/** Creates a new instance of <code>DbSearchQuery</code> */
	public
	DbSearchQuery() {
		
	}
	
	public String
	getCreatedBefore() {
		if(createdBefore == null) return null;
		return dateFormat.format(createdBefore);
	}
	
	public String
	getCreatedAfter() {
		if(createdAfter == null) return null;
		return dateFormat.format(createdAfter);
	}
	
	public String
	getModifiedBefore() {
		if(modifiedBefore == null) return null;
		return dateFormat.format(modifiedBefore);
	}
	
	public String
	getModifiedAfter() {
		if(modifiedAfter == null) return null;
		return dateFormat.format(modifiedAfter);
	}
}
