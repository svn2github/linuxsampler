/*
 *   jlscp - a java LinuxSampler control protocoll API
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
 * The listener interface for receiving events about the fill state of the disk stream buffers.
 *
 * @author  Grigor Iliev
 */
public interface BufferFillListener extends java.util.EventListener {
	/**
	 * Invoked when the fill state of a disk stream buffer has changed.
	 */
	public void bufferFillChanged(BufferFillEvent e);
}
