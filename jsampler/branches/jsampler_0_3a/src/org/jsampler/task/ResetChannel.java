/*
 *   JSampler - a java front-end for LinuxSampler
 *
 *   Copyright (C) 2005, 2006 Grigor Kirilov Iliev
 *
 *   This file is part of JSampler.
 *
 *   JSampler is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2
 *   as published by the Free Software Foundation.
 *
 *   JSampler is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with JSampler; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA  02111-1307  USA
 */

package org.jsampler.task;

import java.util.logging.Level;

import org.jsampler.CC;
import org.jsampler.HF;

import static org.jsampler.JSI18n.i18n;


/**
 * This task resets the specified sampler channel.
 * @author Grigor Iliev
 */
public class ResetChannel extends EnhancedTask {
	private int channel;
	
	/**
	 * Creates new instance of <code>ResetChannel</code>.
	 * @param channel The numerical ID of the channel to reset.
	 */
	public
	ResetChannel(int channel) {
		setTitle("ResetChannel_task");
		setDescription(i18n.getMessage("ResetChannel.description", channel));
		
		this.channel = channel;
	}
	
	/** The entry point of the task. */
	public void
	run() {
		try { CC.getClient().resetChannel(channel); }
		catch(Exception x) {
			setErrorMessage(getDescription() + ": " + HF.getErrorMessage(x));
			CC.getLogger().log(Level.FINE, getErrorMessage(), x);
		}
	}
}
