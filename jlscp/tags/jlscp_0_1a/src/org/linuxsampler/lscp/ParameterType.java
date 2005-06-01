/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005 Grigor Kirilov Iliev
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
 * Represents the parameter type.
 * @author  Grigor Iliev
 */
public enum ParameterType {
	/** Indicates that the parameter contains boolean value */
	BOOL,
	/** Indicates that the parameter contains integer value */
	INT,
	/** Indicates that the parameter contains float value */
	FLOAT,
	/** Indicates that the parameter contains string value */
	STRING,
	/** Indicates that the parameter contains list of boolean values */
	BOOL_LIST,
	/** Indicates that the parameter contains list of integer values */
	INT_LIST,
	/** Indicates that the parameter contains list of float values */
	FLOAT_LIST,
	/** Indicates that the parameter contains list of string values */
	STRING_LIST
}
