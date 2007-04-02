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
 * A semantic event which indicates changes to the global settings of the sampler.
 * @author Grigor Iliev
 */
public class GlobalInfoEvent extends java.util.EventObject {
	private float volume = 0;
	
	/**
	 * Constructs a <code>GlobalInfoEvent</code> object.
	 * @param source The object that originated the event.
	 */
	public
	GlobalInfoEvent(Object source) {
		super(source);
	}
	
	/**
	 * Constructs a <code>GlobalInfoEvent</code> object.
	 * @param source The object that originated the event.
	 * @param volume Specifies the new global volume of the sampler.
	 */
	public
	GlobalInfoEvent(Object source, float volume) {
		super(source);
		this.volume = volume;
	}
	
	/**
	 * Gets the new global volume value of the sampler.
	 * The returned value is only valid when {@link GlobalInfoListener#volumeChanged}
	 * event is fired.
	 * @return The new global volume value of the sampler.
	 */
	public float
	getVolume() { return volume; }
}
