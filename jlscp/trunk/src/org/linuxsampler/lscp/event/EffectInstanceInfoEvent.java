/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2011 Grigor Iliev <grigor@grigoriliev.com>
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
public class EffectInstanceInfoEvent extends java.util.EventObject {
	private int instanceId = -1;
	
	/**
	 * Constructs an <code>EffectInstanceInfoEvent</code> object.
	 * @param source The object that originated the event.
	 */
	public
	EffectInstanceInfoEvent(Object source, int instanceId) {
		super(source);
		this.instanceId = instanceId;
	}
	
	public int
	getEffectInstanceId() { return instanceId; }
}
