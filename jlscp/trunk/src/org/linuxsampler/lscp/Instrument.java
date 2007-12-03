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

/**
 *
 * @author Grigor Iliev
 */
public interface Instrument {
	/**
	 * Gets the name of this instrument.
	 * @return The name of this instrument.
	 */
	public String getName();
	
	/**
	 * Sets the name of this instrument.
	 * @param name The name of this instrument.
	 */
	public void setName(String name);
	
	/**
	 * Returns the absolute path name of the instrument file.
	 * @return The absolute path name of the instrument file.
	 */
	public String getFilePath();
	
	/**
	 * Sets the absolute path name of the instrument file.
	 * @param path Specifies the absolute path name of the instrument file.
	 */
	public void setFilePath(String path);
	
	/**
	 * Returns the index of the instrument in the instrument file.
	 * @return The index of the instrument in the instrument file.
	 */
	public int getInstrumentIndex();
	
	/**
	 * Sets the index of the instrument in the instrument file.
	 * @param idx The index of the instrument in the instrument file.
	 */
	public void setInstrumentIndex(int idx);
	
	/**
	 * Returns the format family of the instrument.
	 **/
	public String getFormatFamily();
	
	/**
	 * Returns the format version of the instrument.
	 **/
	public String getFormatVersion();
	
	/**
	 * Gets the name of the sampler engine to be used to load the instrument.
	 * @return The name of the sampler engine to be used to load the instrument.
	 */
	public String getEngine();
}
