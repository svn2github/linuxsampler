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

//Construct an empty resultset
//Default index is -1 meaning the resultset doesn't have an index
LSCPResultSet::LSCPResultSet(int index) {
	result_index = index;
	count = 0;
	storage = "";
	result_type = result_type_success;
}

//Construct a resultset with a single line
//Default index is -1 meaning the resultset doesn't have an index
LSCPResultSet::LSCPResultSet(String Value, int index) {
	result_index = index;
	count = 1;
	storage = Value + "\r\n";
	result_type = result_type_success;
}

//Add a label/value pair to the resultset
//Values could be of different types for now supports String, int and float.
void LSCPResultSet::Add(String Label, String Value) {
	if (count == -1)
        	throw LinuxSamplerException("Attempting to change already produced resultset");
	if (result_type != result_type_success)
		throw LinuxSamplerException("Attempting to create illegal resultset");
	storage = storage + Label + ": " + Value + "\r\n";
        count++;
}

void LSCPResultSet::Add(int Value) {
	Add(ToString(Value));
}

void LSCPResultSet::Add(String Label, int Value) {
	Add(Label, ToString(Value));
}

void LSCPResultSet::Add(String Label, float Value) {
	std::stringstream ss; //fixme: had issues with template and float?!
	ss << Value;
	Add(Label, ss.str());
}

//Add a single string to the resultset
void LSCPResultSet::Add(String Value) {
	if (result_type != result_type_success)
		throw LinuxSamplerException("Attempting to create illegal resultset");
	if (count == -1)
        	throw LinuxSamplerException("Attempting to change already produced resultset");
	if (count != 0)
		throw LinuxSamplerException("Attempting to create illegal resultset");
	storage = Value + "\r\n";
        count = 1;
}

//Generate an error result set from an exception.
//Per LSCP spec, error result is a sinle line in the following format:
//ERR:<CODE>:Message text\r\n
//This method will be used to generate unknown errors only (code 0)
//To generate errors with other codes as well as warnings use other methods (below).
//Because this is an unknown error, this method will also print message to the stderr.
void LSCPResultSet::Error(LinuxSamplerException e) {
        e.PrintMessage();
	Error(e.Message());
}

//This will construct an error with a string and error code
//code has a default of 0
//String has a default of "Undefined Error"
void LSCPResultSet::Error (String message, int code) {
        //Even though this is must be a single line resultset we won't throw
        //anything here because this is already part of exception handling.
        //We'll just 'forget' all previous results (if any) from this resultset.
	result_type = result_type_error;
        storage = "ERR:" + ToString(code) + ":" + message + "\r\n";
        count = 1;
}

//This will construct a warning with a string and error code
//code has a default of 0
//String has a default of "Undefined Error"
void LSCPResultSet::Warning (String message, int code) {
	//FIXME: DO we want warnings as part of the resultset or
	//do we want them to work like errors??? For now, make them work like errors.
	result_type = result_type_warning;
	if (result_index == -1)
        	storage = "WRN:" + ToString(code) + ":" + message + "\r\n";
	else
        	storage = "WRN[" + ToString(result_index) + "]:" + ToString(code) + ":" + message + "\r\n";
        count = 1;
}

//Produce resultset
String LSCPResultSet::Produce(void) {
	//FIXME: I'm assuming that only a sinle like "OK" can have index
	if (count == 0) //When there is nothing in the resultset we just send "OK" to ack the request
		if (result_index == -1)
			return "OK\r\n";
		else
			return "OK[" + ToString(result_index) + "]\r\n";
	if (count == 1) //Single line results are just that, single line
		return storage;
	//Multiline results MUST end with a line with a single dot
	return storage + ".\r\n";
}
