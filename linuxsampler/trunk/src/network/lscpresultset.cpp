/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003, 2004 by Benno Senoner and Christian Schoenebeck   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 ***************************************************************************/

/*********************************************************
 * This class helps to constuct valid resultsets per
 * LSCP protocol specification
 *
 * Valid results include:
 * OK - to ack the request
 * Single line to ack the requests and give status
 * Several lines of information in the following format:
 * LABEL0: VALUE0
 * LABEL1: VALUE1
 * VALELx: VALUEx
 * .
 *
 * ******************************************************/

#include "lscpresultset.h"
#include "../common/LinuxSamplerException.h"

//Construct an empty resultset
LSCPResultSet::LSCPResultSet(void) {
	count = 0;
	storage = "";
}

//Construct a resultset with a single line
LSCPResultSet::LSCPResultSet(String Value) {
	count = 1;
	storage = Value + "\r\n";
}

//Add a label/value pair to the resultset
//Values could be of different types for now supports String, int and float.
void LSCPResultSet::Add(String Label, String Value) {
	if (count == -1)
        	throw LinuxSamplerException("Attempting to change already produced resultset");
	storage = storage + Label + ": " + Value + "\r\n";
        count++;
}

void LSCPResultSet::Add(String Label, int Value) {
        char temp[16];
	snprintf(temp, sizeof(temp), "%i", Value);
	Add(Label, temp);
}

void LSCPResultSet::Add(String Label, float Value) {
        char temp[16];
	snprintf(temp, sizeof(temp), "%10.4f", Value);
	Add(Label, temp);
}

//Add a single string to the resultset
void LSCPResultSet::Add(String Value) {
	if (count == -1)
        	throw LinuxSamplerException("Attempting to change already produced resultset");
	if (count != 0)
		throw LinuxSamplerException("Attempting to create illegal resultset");
	storage = Value + "\r\n";
        count = 1;
}

//Produce resultset
String LSCPResultSet::Produce(void) {
	if (count == 0) //When there is nothing in the resultset we just send "OK" to ack the request
		return "OK\r\n";
	if (count == 1) //Single line results are just that, single line
		return storage;
	//Multiline results MUST end with a line with a single dot
	return storage + ".\r\n";
}
