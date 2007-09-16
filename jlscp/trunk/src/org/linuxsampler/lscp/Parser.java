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

import java.io.IOException;

import java.util.Vector;


/**
 * This class contains only helper functions that are used from the other classes in this library.
 * @author  Grigor Iliev
 */
public final class Parser {
	/** Forbits the instantiatrion of this class */
	private Parser() { }
	
	/**
	 * Parses an integer value.
	 * @param s The integer value to be parsed.
	 * @throws LscpException If the string does not contain valid integer value.
	 */
	protected static int
	parseInt(String s) throws LscpException {
		try { return Integer.parseInt(s); }
		catch(NumberFormatException x) {
			throw new LscpException(LscpI18n.getLogMsg("Parser.notInt!", s), x);
		}
	}
	
	/**
	 * Parses a float value.
	 * @param s The float value to be parsed.
	 * @throws LscpException If the string does not contain valid float value.
	 */
	protected static float
	parseFloat(String s) throws LscpException {
		try { return Float.parseFloat(s); }
		catch(NumberFormatException x) {
			throw new LscpException(LscpI18n.getLogMsg("Parser.notFloat!", s));
		}
	}
	
	/**
	 * Parses a comma separated list.
	 *
	 * @param list The comma separated list.
	 * @return A <code>String</code> array containing all items in the list.
	 */
	protected static String[]
	parseList(String list) { return parseList(list, ','); }
	
	/**
	 * Parses a list.
	 * @param list The list to parse.
	 * @param separator Provides the character used as separator.
	 * @return A <code>String</code> array containing all items in the list.
	 */
	protected static String[]
	parseList(String list, char separator) {
		if(list == null || list.length() == 0) return new String[0];
		int pos = 0;
		int idx;
		Vector<String> v = new Vector<String>();
		while((idx = list.indexOf(separator, pos)) > 0) {
			v.add(list.substring(pos, idx));
			pos = idx + 1;
		}
		
		if(pos < list.length()) v.add(list.substring(pos));
		return v.toArray(new String[v.size()]);
	}
	
	/**
	 * Parses a comma separated list with boolean values.
	 *
	 * @param list The comma separated list with boolean values.
	 * @return A <code>Boolean</code> array containing all items in the list.
	 */
	protected static Boolean[]
	parseBoolList(String list) {
		String[] ar = parseList(list);
		
		Boolean[] bar = new Boolean[ar.length];
		for(int i = 0; i < ar.length; i++) {
			bar[i] = Boolean.parseBoolean(ar[i]);
		}
		
		return bar;
	}
	
	/**
	 * Parses a comma separated list with integer values.
	 *
	 * @param list The comma separated list with integer values.
	 * @return A <code>Integer</code> array containing all items in the list.
	 *
	 * @throws LscpException if the list contains value(s) from different type.
	 */
	protected static Integer[]
	parseIntList(String list) throws LscpException { return parseIntList(list, ','); }
	
	/**
	 * Parses a list of integer values.
	 *
	 * @param list The list of integer values.
	 * @param separator Provides the character used as separator.
	 * @return A <code>Integer</code> array containing all items in the list.
	 *
	 * @throws LscpException if the list contains value(s) from different type.
	 */
	protected static Integer[]
	parseIntList(String list, char separator) throws LscpException {
	String[] ar = parseList(list, separator);
		
		Integer[] iar = new Integer[ar.length];
		for(int i = 0; i < ar.length; i++) iar[i] = parseInt(ar[i]);
		
		return iar;
	}
	
	/**
	 * Parses a comma separated list with float values.
	 *
	 * @param list The comma separated list with float values.
	 * @return A <code>Float</code> array containing all items in the list.
	 *
	 * @throws LscpException if the list contains value(s) from different type.
	 */
	protected static Float[]
	parseFloatList(String list) throws LscpException {
		String[] ar = parseList(list);
		
		Float[] far = new Float[ar.length];
		for(int i = 0; i < ar.length; i++) far[i] = parseFloat(ar[i]);
		
		return far;
	}
	
	/**
	 * Parses a comma separated list whose items are not encapsulated into apostrophes.
	 * @param list The comma separated list.
	 * @return A <code>String</code> array containing all items in the list.
	 * @throws LscpException if the list is broken.
	 */
	protected static String[]
	parseStringList(String list) throws LscpException {
		list = removeQuotation(list);
		return parseList(list);
	}
	
	/**
	 * Parses a comma separated string list, which elements contains escaped sequences.
	 * @param list The list to parse.
	 * @return A <code>String</code> array containing all items in the list.
	 */
	protected static String[]
	parseEscapedStringList(String list) throws LscpException {
		return parseEscapedStringList(list, ',');
	}
	
	/**
	 * Parses a string list, which elements contains escaped sequences.
	 * @param list The list to parse.
	 * @param separator Provides the character used as separator.
	 * @return A <code>String</code> array containing all items in the list.
	 */
	protected static String[]
	parseEscapedStringList(String list, char separator) throws LscpException {
		if(list == null || list.length() == 0) return new String[0];
		int q1 = 0, q2 = 0;
		Vector<String> v = new Vector<String>();
		
		for(;;) {
			if(list.charAt(q1) != '\'')
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			q2 = findApostrophe(list, q1 + 1);
			if(q2 == -1) throw new LscpException(LscpI18n.getLogMsg("Parser.EOL!"));
			v.add(list.substring(q1 + 1, q2));
			
			if(q2 + 1 >= list.length()) break;
			
			if(list.charAt(q2 + 1) != separator)
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			q1 = q2 + 2;
			if(q1 >= list.length())
				throw new LscpException(LscpI18n.getLogMsg("Parser.EOL!"));
		}
		
		return v.toArray(new String[v.size()]);
	}
	
	/**
	 * Returns the index of the first occurrence of a non-escaped apostrophe
	 * in the specified string, starting at <b>index</b>, or -1 if nothing is found.
	 */
	private static int
	findApostrophe(String s, int index) {
		return findNonEscapedChar(s, index, '\'');
	}
	
	/**
	 * Parses a comma separated list whose items are encapsulated into apostrophes.
	 * @param list The comma separated list.
	 * @return A <code>String</code> array containing all items in the list.
	 * @throws LscpException if the list is broken.
	 */
	protected static String[]
	parseQuotedStringList(String list) throws LscpException {
		return parseQuotedStringList(list, ',');
	}
	
	/**
	 * Parses a list whose items are encapsulated into apostrophes.
	 * @param list The list of strings.
	 * @param separator Provides the character used as separator.
	 * @return A <code>String</code> array containing all items in the list.
	 * @throws LscpException if the list is broken.
	 */
	protected static String[]
	parseQuotedStringList(String list, char separator) throws LscpException {
		if(list == null || list.length() == 0) return new String[0];
		int q1 = 0, q2 = 0;
		Vector<String> v = new Vector<String>();
		
		for(;;) {
			if(list.charAt(q1) != '\'')
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			q2 = list.indexOf('\'', q1 + 1);
			if(q2 == -1) throw new LscpException(LscpI18n.getLogMsg("Parser.EOL!"));
			v.add(list.substring(q1 + 1, q2));
			
			if(q2 + 1 >= list.length()) break;
			
			if(list.charAt(q2 + 1) != separator)
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			q1 = q2 + 2;
			if(q1 >= list.length())
				throw new LscpException(LscpI18n.getLogMsg("Parser.EOL!"));
		}
		
		return v.toArray(new String[v.size()]);
	}
	
	protected static String[][]
	parseListOfStringLists(String list) throws LscpException {
		if(list.length() == 0) return new String[0][0];
		
		String[][] s2S;
		if(!list.startsWith("''") && !list.startsWith("\"\"")) {
			s2S = new String[1][];
			s2S[0] = parseQuotedStringList(list);
			return s2S;
		}
			
		int i = 0, i2 = 0;
		Vector<String> v = new Vector<String>();
		
		for(;;) {
			i2 = getEndListIndex(i, list);
			v.add(list.substring(i + 1, i2));
			if(i2 == list.length() - 1) break;
			if(list.charAt(i2 + 1) != ',')
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			i = i2 + 2;
		}
		
		s2S = new String[v.size()][];
		for(i = 0; i < v.size(); i++) s2S[i] = parseQuotedStringList(v.get(i));
		
		return s2S;
	}
	
	/**
	 * Parses a comma separated list whose items are encapsulated into curly braces.
	 *
	 * @param list The comma separated list.
	 * @return A <code>String</code> array containing all items in the list.
	 *
	 * @throws LscpException if the list is broken.
	 */
	protected static String[]
	parseArray(String list) throws LscpException {
		if(list == null || list.length() == 0) return new String[0];
		int q1 = 0, q2 = 0;
		Vector<String> v = new Vector<String>();
		
		for(;;) {
			if(list.charAt(q1) != '{')
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			q2 = list.indexOf('}', q1 + 1);
			if(q2 == -1) throw new LscpException(LscpI18n.getLogMsg("Parser.EOL!"));
			v.add(list.substring(q1 + 1, q2));
			
			if(q2 + 1 >= list.length()) break;
			
			if(list.charAt(q2 + 1) != ',')
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			q1 = q2 + 2;
			if(q1 >= list.length())
				throw new LscpException(LscpI18n.getLogMsg("Parser.EOL!"));
		}
		
		return v.toArray(new String[v.size()]);
	}
	
	/** Helper function used by <code>parseListOfStringLists</code>. */
	private static int
	getEndListIndex(int start, String list) throws LscpException {
		int i = start + 1;
		char q = list.charAt(0); // quote symbol
		if(list.charAt(start) != q)
			throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
		
		if(list.charAt(i) == '\'') { // Check for empty list
			if(i == list.length() - 1 || list.charAt(i + 1) == ',') return i;
		}
		
		for(;;) {
			if(list.charAt(i) != q)
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			i = list.indexOf(q, i + 1);
			if(i == -1 || i == list.length() - 1)
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			
			if(list.charAt(i + 1) == q) return i + 1;
				
			if(list.charAt(i + 1) != ',')
				throw new LscpException(LscpI18n.getLogMsg("Parser.brokenList!"));
			i += 2;
		}
	}
	
	
	/**
	 * Gets the type of the parameter represented by the specified result set.
	 * @param resultSet A <code>String</code> array containing the information categories
	 * of a multi-line result set.
	 * @return The type of the parameter represented by the specified result set or 
	 * <code>null</code> if the specified result set does not contain 
	 * <code>TYPE</code> category.
	 */
	protected static ParameterType
	parseType(String[] resultSet) {
		if(resultSet == null || resultSet.length == 0) return null;
		for(String s : resultSet) {
			if(s.startsWith("TYPE: ")) {
				String type = s.substring("TYPE: ".length(), s.length());
				if(type.equals("BOOL")) return ParameterType.BOOL;
				if(type.equals("INT")) return ParameterType.INT;
				if(type.equals("FOAT")) return ParameterType.FLOAT;
				if(type.equals("STRING")) return ParameterType.STRING;
			}
		}
		return null;
	}
	
	/**
	 * Determines whether the parameter represented by the specified result set allows
	 * only one value or a list of values.
	 * @param resultSet A <code>String</code> array containing the information categories
	 * of a multi-line result set.
	 * @return <code>false</code> if the parameter represented by the specified result set
	 *  allows only one value and <code>true</code> if allows a list of values.
	 */
	protected static Boolean
	parseMultiplicity(String[] resultSet) {
		if(resultSet == null || resultSet.length == 0) return null;
		
		for(String s : resultSet) {
			if(s.startsWith("MULTIPLICITY: ")) return Boolean.parseBoolean (
				s.substring("MULTIPLICITY: ".length(), s.length())
			);
		}
		
		return null;
	}
	
	/**
	 * Parses an empty result set and returns an appropriate <code>ResultSet</code> object.
	 * Notice that the result set may be of type warning or error.
	 * @param ln A <code>String</code> representing the single line result set to be parsed.
	 * @return A <code>ResultSet</code> object.
	 * @throws LscpException If LSCP protocol error occurs.
	 * @throws LSException If the LinuxSampler instance returns error message.
	 */
	protected static ResultSet
	parseEmptyResultSet(String ln) throws LscpException, LSException {
		ResultSet rs = new ResultSet();
		
		if(ln.equals("OK")) {
			return rs;
		} else if(ln.startsWith("OK[") && ln.endsWith("]")) {
			ln = ln.substring("OK[".length(), ln.length() - 1);
			try {
				rs.setIndex(Integer.parseInt(ln));
				return rs;
			} catch(NumberFormatException x) {
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
			}
		} else if(ln.startsWith("WRN")) {
			parseWarning(ln, rs);
			Client.getLogger().warning(rs.getMessage());
			return rs;
		} else if(ln.startsWith("ERR:")) {
			parseError(ln, rs);
			throw new LSException(rs.getCode(), rs.getMessage());
		}
		
		throw new LscpException(LscpI18n.getLogMsg("CommandFailed!") );
	}
	
	/**
	 * Parses warning message.
	 * @param ln The warning message to be parsed.
	 * @param rs A <code>ResultSet</code> instance where the warning must be stored.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	protected static void
	parseWarning(String ln, ResultSet rs) throws LscpException {
		if(!ln.startsWith("WRN"))
			throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
		int i, j;
		rs.setWarning(true);
		
		if(ln.charAt(3) == '[') {
			i = ln.indexOf(']');
			if(i == -1) throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
			try { 
				j = Integer.parseInt(ln.substring("WRN[".length(), i));
				rs.setIndex(j);
			} catch(NumberFormatException x) {
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
			}
			
			if(ln.charAt(i + 1) != ':')
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
		}
		
		i = ln.indexOf(':');
		if(i == -1) throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
		j = ln.indexOf(':', i + 1);
		if(j == -1) throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
		
		try { rs.setCode(Integer.parseInt(ln.substring(i + 1, j))); }
		catch(NumberFormatException x) {
			throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
		}
		
		rs.setMessage(ln.substring(j + 1));
	}
	
	/**
	 * Parses error message.
	 * @param ln The error message to be parsed.
	 * @param rs A <code>ResultSet</code> instance where the error must be stored.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	protected static void
	parseError(String ln, ResultSet rs) throws LscpException {
		if(!ln.startsWith("ERR:"))
			throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
		
		int i = ln.indexOf(':', "ERR:".length());
		if(i == -1) throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
		
		try { rs.setCode(Integer.parseInt(ln.substring("ERR:".length(), i))); }
		catch(NumberFormatException x) {
			throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"), x);
		}
		
		rs.setMessage(ln.substring(i + 1));
	}
	
	/**
	 * Gets the info character string to the specified information category.
	 * @param resultSet A <code>String</code> array containing the information categories
	 * of a multi-line result set.
	 * @param category Specifies the category whose info character string to be returned.
	 * @return The info character string to the specified information category or
	 * <code>null</code> if the specified result set does not contain that category.
	 */
	protected static String
	getCategoryInfo(String[] resultSet, String category) {
		String c = category + ": ";
		for(String s : resultSet) 
			if(s.startsWith(c)) return s.substring(c.length(), s.length());
			
		return null;
	}
	
	/**
	 * Eliminates the quotation marks if the string is quoted.
	 * @return New string without quotation marks if the string is quoted; else
	 * the same string is returned.
	 */
	protected static String
	removeQuotation(String s) {
		if(s == null || s.length() < 2) return s;
		char q = s.charAt(0);
		char q2 = s.charAt(s.length() - 1);
		if((q == '\'' && q2 == '\'') || (q == '"' && q2 == '"'))
			return s.substring(1, s.length() - 1);
		
		return s;
	}
	
	/**
	 * Returns the provided string with added escape sequences where necessary.
	 */
	public static String
	toEscapedString(Object obj) {
		String s = obj.toString();
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i < s.length(); i++) {
			switch(s.charAt(i)) {
				case '\n': sb.append("\\n");  break;
				case '\r': sb.append("\\r");  break;
				case '\f': sb.append("\\f");  break;
				case '\t': sb.append("\\t");  break;
				case 0x0B: sb.append("\\v");  break;
				case '\'': sb.append("\\'");  break;
				case '\"': sb.append("\\\""); break;
				case '\\': sb.append("\\\\"); break;
				default  : sb.append(s.charAt(i));
			}
		}
		
		return sb.toString();
	}
	
	/**
	 * Returns the provided file name with added escape sequences where necessary.
	 */
	public static String
	toEscapedFileName(Object obj) {
		String s = obj.toString();
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i < s.length(); i++) {
			switch(s.charAt(i)) {
				case '/' : sb.append("\\x2f"); break;
				case '\n': sb.append("\\n");   break;
				case '\r': sb.append("\\r");   break;
				case '\f': sb.append("\\f");   break;
				case '\t': sb.append("\\t");   break;
				case 0x0B: sb.append("\\v");   break;
				case '\'': sb.append("\\'");   break;
				case '\"': sb.append("\\\"");  break;
				case '\\': sb.append("\\\\");  break;
				default  : sb.append(s.charAt(i));
			}
		}
		
		return sb.toString();
	}
	
	/**
	 * Removes the escape sequences from the specified file name
	 * @return The provided file name with removed escape sequences.
	 */
	public static String
	toNonEscapedFileName(Object obj) {
		return toNonEscapedString(obj);
	}
	
	/**
	 * Removes the escape sequences from the string <code>obj.toString()</code>.
	 * @return The provided text with removed escape sequences.
	 */
	public static String
	toNonEscapedString(Object obj) {
		String s = obj.toString();
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i < s.length(); i++) {
			char c = s.charAt(i);
			if(c == '\\') {
				if(i >= s.length()) {
					Client.getLogger().info("Broken escape sequence!");
					break;
				}
				char c2 = s.charAt(++i);
				if(c2 == '\'')      sb.append('\'');
				else if(c2 == '"')  sb.append('"');
				else if(c2 == '\\') sb.append('\\');
				else if(c2 == 'r')  sb.append('\r');
				else if(c2 == 'n')  sb.append('\n');
				else if(c2 == 'f')  sb.append('\f');
				else if(c2 == 't')  sb.append('\t');
				else if(c2 == 'v')  sb.append((char)0x0B);
				else if(c2 == 'x') {
					Character ch = getHexEscapeSequence(s, i + 1);
					if(ch != null) sb.append(ch.charValue());
					i += 2;
				} else if(c2 >= '0' && c2 <= '9') {
					Character ch = getOctEscapeSequence(s, i);
					if(ch != null) sb.append(ch.charValue());
					i += 2;
				} else Client.getLogger().info("Unknown escape sequence \\" + c2);
			} else {
				sb.append(c);
			}
		}
		
		return sb.toString();
	}
	
	private static Character
	getHexEscapeSequence(String s, int index) {
		Character c = null;
		
		if(index + 1 >= s.length()) {
			Client.getLogger().info("Broken escape sequence");
			return c;
		}
		
		try { c = (char)Integer.parseInt(s.substring(index, index + 2), 16); }
		catch(Exception x) { Client.getLogger().info("Broken escape sequence!"); }
		
		return c;
	}
	
	private static Character
	getOctEscapeSequence(String s, int index) {
		Character c = null;
		
		if(index + 2 >= s.length()) {
			Client.getLogger().info("Broken escape sequence");
			return c;
		}
		
		try { c = (char)Integer.parseInt(s.substring(index, index + 3), 8); }
		catch(Exception x) { Client.getLogger().info("Broken escape sequence!"); }
		
		return c;
	}
	
	/**
	 * Determines whether the character at the specified position
	 * is escaped with backslash.
	 */
	public static boolean
	isEscaped(String s, int index) {
		if (index < 0 || index >= s.length()) return false;
		int count = 0;
		for (int i = index - 1; i >= 0; i--) {
			if (s.charAt(i) != '\\') break;
			count++;
		}
		return count % 2 != 0;
	}
	
	/**
	 * Returns the index of the first occurrence of the specified non-escaped character
	 * in the specified string, starting at <b>index</b>, or -1 if nothing is found.
	 */
	private static int
	findNonEscapedChar(String s, int index, char c) {
		if(s == null) return -1;
		int pos = index;
		if (pos < 0 || pos >= s.length()) return -1;
		
		for(;;) {
			int i = s.indexOf(c, pos);
			if (i == -1) break;
			if (!isEscaped(s, i)) return i;
			pos = i + 1;
			if (pos >= s.length()) break;
		}
		
		return -1;
	}
	
	/**
	 * Returns the index of the first occurrence of a file separator
	 * in the specified escaped path, starting at <b>index</b>, or -1 if nothing is found.
	 */
	private static int
	findFileSeparator(String path, int index) {
		return findNonEscapedChar(path, index, '/');
	}
	
	/**
	 * Gets the position of the last file separator in the specified
	 * escaped path, or -1 if failed.
	 */
	private static int
	getLastFileSeparator(String path) {
		if(path == null || path.length() == 0) return -1;
		int pos = path.length() - 1;
		
		for(;;) {
			pos = path.lastIndexOf('/', pos);
			if(pos == -1) return -1;
			if(!isEscaped(path, pos)) return pos;
			pos--;
		}
	}
	
	/**
	 * Determines whether the specified escaped path ends with a file separator.
	 */
	protected static boolean
	hasEndingFileSeparator(String path) {
		if(path == null || path.length() < 2) return false;
		
		int last = path.length() - 1;
		if(path.charAt(last) == '/' && !isEscaped(path, last)) return true;
		
		return false;
	}
	
	/**
	 * If the specified escaped path ends with a file separator,
	 * a new string is returned with the ending file separator removed.
	 */
	protected static String
	removeEndingFileSeparator(String path) {
		if(path == null || path.length() < 2) return path;
		
		int last = path.length() - 1;
		if(path.charAt(last) == '/' && !isEscaped(path, last)) {
			path = path.substring(0, path.length() - 1);
		}
		
		return path;
	}
	
	/**
	 * Gets the parent directory of the specified escaped path.
	 */
	public static String
	getParentDirectory(String path) {
		if(path == null || path.length() == 0) return null;
		if(path.charAt(0) != '/') return null;
		if(path.length() == 1) return null;
		
		path = removeEndingFileSeparator(path);
		
		int i = getLastFileSeparator(path);
		if(i == 0) return "/";
		return path.substring(0, i);
	}
	
	/**
	 * Extracts the file name from the specified escaped path.
	 * If the path does not ends with a file name, <code>null</code> is returned.
	 */
	public static String
	getFileName(String path) {
		if(path == null || path.length() < 2) return null;
		int i = getLastFileSeparator(path);
		if(i == -1) return null;
		if(i == path.length() - 1) return null;
		return path.substring(i + 1);
	}
	
	/**
	 * Returns an array containing all directories in the specified escaped path.
	 */
	public static String[]
	getDirectoryList(String path) {
		if(path == null || path.length() == 0) return null;
		if(path.charAt(0) != '/') return null;
		Vector<String> v = new Vector<String>();
		v.add("/");
		if(path.length() == 1) return v.toArray(new String[v.size()]);
		
		if(!hasEndingFileSeparator(path)) path += "/";
		int i = 1;
		int j = findFileSeparator(path, i);
		
		while(j != -1) {
			v.add(path.substring(i, j));
			
			i = j + 1;
			if(i >= path.length()) return v.toArray(new String[v.size()]);
			j = findFileSeparator(path, i);
		}
		
		return null;
	}
}
