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
public class SendEffectChainInfoEvent extends java.util.EventObject {
	private int audioDeviceId = -1;
	private int chainId = -1;
	private int instanceCount = -1;
	
	/**
	 * Constructs an <code>SendEffectChainInfoEvent</code> object.
	 * @param source The object that originated the event.
	 */
	public
	SendEffectChainInfoEvent(Object source, int audioDeviceId, int chainId, int instanceCount) {
		super(source);
		this.audioDeviceId = audioDeviceId;
		this.chainId = chainId;
		this.instanceCount = instanceCount;
	}
	
	public int
	getAudioDeviceId() { return audioDeviceId; }
	
	public int
	getChainId() { return chainId; }
	
	public int
	getInstanceCount() { return instanceCount; }
}
