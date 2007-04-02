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
 * A semantic event which indicates that the
 * settings of a particular effect send have changed.
 * @author Grigor Iliev
 */
public class FxSendInfoEvent extends java.util.EventObject {
	private int channel;
	private int fxSend;
	
	/**
	 * Constructs a <code>FxSendInfoEvent</code> object.
	 * @param source The object that originated the event.
	 * @param channel The numerical ID of the sampler
	 * channel, containing the changed effect send.
	 * @param fxSend The numerical ID of the
	 * effect send, whose settings are changed.
	 */
	public
	FxSendInfoEvent(Object source, int channel, int fxSend) {
		super(source);
		this.channel = channel;
		this.fxSend = fxSend;
	}
	
	/**
	 * Gets the numerical ID of the sampler
	 * channel, containing the changed effect send.
	 * @return The numerical ID of the sampler
	 * channel, containing the changed effect send.
	 */
	public int
	getChannel() { return channel; }
	
	/**
	 * Gets the numerical ID of the effect send, whose settings are changed.
	 * @return The numerical ID of the effect send, whose settings are changed.
	 */
	public int
	getFxSend() { return fxSend; }
}
