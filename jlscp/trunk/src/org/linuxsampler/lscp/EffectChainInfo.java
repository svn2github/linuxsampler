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

package org.linuxsampler.lscp;

/**
 *
 * @author Grigor Iliev
 */
public class EffectChainInfo {
	private int chainId = -1;
	protected EffectInstanceInfo[] effectInstances;
	
	public
	EffectChainInfo() { this(null); }

	public
	EffectChainInfo(EffectInstanceInfo[] instances) {
		effectInstances = instances;
	}
	
	/**
	 * Gets the numerical ID of the chain.
	 * @return The numerical ID of the chain or -1 if the ID is not set.
	 */
	public int
	getChainId() { return chainId; }
	
	/** Sets the numerical ID of the chain. */
	public void
	setChainId(int id) { chainId = id; }
	
	public int
	getEffectInstanceCount() { return effectInstances.length; }
	
	public EffectInstanceInfo
	getEffectInstance(int idx) { return effectInstances[idx]; }
}
