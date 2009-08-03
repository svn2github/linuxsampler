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

package org.linuxsampler.lscp.event;

/**
 * A semantic event which indicates changes to an item.
 * @author Grigor Iliev
 */
public class ItemInfoEvent extends java.util.EventObject {
	private int itemID;
	
	/**
	 * Constructs a <code>ItemInfoEvent</code> object.
	 * @param source The object that originated the event.
	 * @param itemID The numerical ID of the item whose settings have changed.
	 */
	public
	ItemInfoEvent(Object source, int itemID) {
		super(source);
		this.itemID = itemID;
	}
	
	/**
	 * Gets the numerical ID of the item whose settings have changed.
	 * @return The numerical ID of the item whose settings have changed.
	 */
	public int
	getItemID() { return itemID; }
}
