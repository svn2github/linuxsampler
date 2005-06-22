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

import java.io.IOException;

import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.UnknownHostException;

import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

import static org.linuxsampler.lscp.Parser.*;
import org.linuxsampler.lscp.event.*;


/**
 * This class is the abstraction representing a client endpoint for communication with LinuxSampler
 * instance. Since it implements all commands specified in the LSCP protocol v1.0, for more 
 * information look at the
 * <a href=http://www.linuxsampler.org/api/lscp-1.0.html>LSCP</a> specification.
 *
 * <p> The following code establishes connection to LinuxSampler instance and gets the
 * LinuxSampler version:
 * <pre>
 *	try {
 *		Client client = new Client();
 *		client.connect();
 *		
 *		String version = client.getServerInfo().getVersion();
 *		System.out.println(version);
 *		
 *		client.disconnect();
 *	} catch(Exception x) { x.printStackTrace(); }
 * </pre>
 * </p>
 *
 * <p>For more examples look at the <code>examples</code> directory
 * located in the <b>jlscp</b> distribution.</p>
 * 
 * All methods are thread safe.
 * @author  Grigor Iliev
 */
public class Client {
	private String address;
	private int port;
	private Socket sock = null;
	private int soTimeout = 10000;
	
	private LscpInputStream in = null;
	private LscpOutputStream out = null;
	
	private EventThread eventThread;
	
	class EventThread extends Thread {
		private boolean terminate = false;
		
		EventThread() { super("LSCP-Event-Thread"); }
		
		public void
		run() {
			while(!mustTerminate()) {
				try { processNotifications(); }
				catch(Exception x) {
					getLogger().log(Level.FINE, x.getMessage(), x);
				}
				try { synchronized(this) { wait(100); } }
				catch(Exception x) {
					getLogger().log(Level.FINE, x.getMessage(), x);
				}
			}
		}
	
		private synchronized boolean
		mustTerminate() { return terminate; }
		
		public synchronized void
		terminate() {
			terminate = true;
			this.notifyAll();
		}
	}
	
	/**
	 * Creates a new instance of Client with default server address and port.
	 * The default server address and port are 127.0.0.1:8888.
	 */
	public
	Client() { this("127.0.0.1"); }
	
	/**
	 * Creates a new instance of Client with the specified address and default port.
	 * The default port is 8888.
	 * @param address The address of linux sampler server.
	 */
	public
	Client(String address) { this(address, 8888); }
	
	/**
	 * Creates a new instance of Client with the specified address and port.
	 * @param address The address of the Linux Sampler.
	 * @param port The Linux Sampler port number.
	 */
	public
	Client(String address, int port) {
		setServerAddress(address);
		setServerPort(port);
		
		eventThread = new EventThread();
	}
	
	/**
	 * Specifies the jlscp version.
	 * @return The jlscp version. 
	 */
	public static String
	getClientVersion() {
		return Package.getPackage("org.linuxsampler.lscp").getImplementationVersion();
	}
	
	/**
	 * Gets the Linux Sampler address.
	 * @return The Linux Sampler address.
	 */
	public synchronized String
	getServerAddress() { return address; }
	
	/**
	 * Sets the Linux Sampler address.
	 * @param address The Linux Sampler address.
	 * If <code>address</code> is <code>null</code> sets to default address - 127.0.0.1.
	 */
	public synchronized void
	setServerAddress(String address) {
		this.address = (address == null ? "127.0.0.1" : address);
	}
	
	/**
	 * Gets the Linux Sampler port number.
	 * @return The Linux Sampler port number.
	 */
	public synchronized int
	getServerPort() { return port; }
	
	/**
	 * Sets the Linux Sampler port number.
	 * @param port The Linux Sampler port number.
	 */
	public synchronized void
	setServerPort(int port) { this.port = port; }
	
	/**
	 * Connects to the LinuxSampler. If there is already established connection then
	 * the currently available connection is closed berfore connecting.
	 * @throws LscpException If timeout occurs or any other I/O exception.
	 */
	public synchronized void
	connect() throws LscpException {
		if(sock != null) disconnect();
		
		// Initializing LSCP event thread
		if(eventThread.isAlive()) {
			getLogger().warning("LSCP event thread already running!");
			eventThread.terminate();
		}
		
		if(eventThread.getState() != Thread.State.NEW) eventThread = new EventThread();
		///////
		
		InetSocketAddress sockAddr = null;
		
		try { sockAddr = new InetSocketAddress(address, port); }
		catch(IllegalArgumentException x) {
			String s = String.valueOf(port);
			throw new LscpException(LscpI18n.getLogMsg("Client.invalidPort!", s), x);
		}
		
		if(sockAddr.isUnresolved()) throw new LscpException (
			LscpI18n.getLogMsg("Client.unknownHost!", address)
		);
		
		try {
			sock = new Socket();
			sock.bind(null);
			sock.connect(sockAddr, soTimeout);
			sock.setSoTimeout(soTimeout);
			
			in = new LscpInputStream(sock.getInputStream());
			out = new LscpOutputStream(sock.getOutputStream());
		} catch(SocketTimeoutException x) {
			throw new LscpException(LscpI18n.getLogMsg("Client.conTimeout!"), x);
		} catch(Exception x) {
			throw new LscpException (
				LscpI18n.getLogMsg("Client.connectionFailed!"), x
			);
		}
		
		String s = Package.getPackage("org.linuxsampler.lscp").getSpecificationVersion();
		String s2, sv, sv2;
		
		try {
			s2 = s.substring(0,  s.indexOf('.'));
			sv = getServerInfo().getProtocolVersion();
			sv2 = sv.substring(0,  sv.indexOf('.'));
		} catch(Exception x) {
			disconnect();
			
			throw new LscpException (
				LscpI18n.getLogMsg("Client.connectionFailed!"), x
			);
		}
		
		if(!sv2.equals(s2)) {
			disconnect();
			
			throw new LscpException (
				LscpI18n.getLogMsg("Client.incompatibleLscpVersion!", sv)
			);
		}
		
		s2 = s.substring(s.indexOf('.'));
		sv2 = sv.substring(sv.indexOf('.'));
		
		if(sv2.compareToIgnoreCase(s2) < 0) getLogger().info (
			LscpI18n.getLogMsg("Client.incompatibleLscpMinVersion!", sv)
		);
		
		if(hasSubscriptions()) eventThread.start();
		
		if(!llM.isEmpty()) subscribe("MISCELLANEOUS");
		if(!llBF.isEmpty()) subscribe("BUFFER_FILL");
		if(!llCC.isEmpty()) subscribe("CHANNEL_COUNT");
		if(!llCI.isEmpty()) subscribe("CHANNEL_INFO");
		if(!llSC.isEmpty()) subscribe("STREAM_COUNT");
		if(!llVC.isEmpty()) subscribe("VOICE_COUNT");
	}
	
	/**
	 * Closes the connection to LinuxSampler.
	 */
	public synchronized void
	disconnect() {
		try { if(sock != null) sock.close(); }
		catch(Exception x) { getLogger().log(Level.FINE, x.getMessage(), x); }
		sock = null;
		
		if(eventThread.getState() != Thread.State.NEW) {
			eventThread.terminate();
			eventThread = new EventThread();
		}
	}
	
	/**
	 * Determines whether the client is connected.
	 * @return <code>true</code> if there is established connection,
	 * <code>false</code> otherwise.
	 */
	public synchronized boolean
	isConnected() {
		if(sock == null) return false;
		else return sock.isConnected();
	}
	
	/**
	 * Verifies that there is established connection.
	 * @throws IOException If the connection is not established.
	 */
	private void
	verifyConnection() throws IOException {
		if(!isConnected())
			throw new IOException(LscpI18n.getLogMsg("Client.notConnected!"));
	}
	
	private String
	getLine() throws IOException, LscpException {
		String s;
		for(;;) {
			s = in.readLine();
			if(s.startsWith("NOTIFY:")) fireEvent(s.substring("NOTIFY:".length()));
			else break;
		}
		return s;
	}
	
	/** Processes the notifications send by LinuxSampler */
	private synchronized void
	processNotifications() throws IOException, LscpException {
		while(in.available() > 0) {
			String s = in.readLine();
			if(s.startsWith("NOTIFY:")) fireEvent(s.substring("NOTIFY:".length()));
			else getLogger().severe("Unknown notification format: " + s);
		}
	}
	
	/**
	 * Gets empty result set.
	 * @return <code>ResultSet</code> instance.
	 */
	private ResultSet
	getEmptyResultSet() throws IOException, LscpException, LSException { 
		return parseEmptyResultSet(getLine());
	}
	
	private ResultSet
	getSingleLineResultSet() throws IOException, LscpException, LSException { 
		ResultSet rs = new ResultSet();
		String ln = getLine();
		
		if(ln.startsWith("WRN")) {
			parseWarning(ln, rs);
			getLogger().warning(rs.getMessage());
			return rs;
		} else if(ln.startsWith("ERR")) {
			parseError(ln, rs);
			throw new LSException(rs.getCode(), rs.getMessage());
		} else {
			rs.setResult(ln);
			return rs;
		}
	}
	
	private ResultSet
	getMultiLineResultSet() throws IOException, LscpException, LSException {
		ResultSet rs = new ResultSet();
		String ln = getLine();
		
		if(ln.startsWith("WRN")) {
			parseWarning(ln, rs);
			getLogger().warning(rs.getMessage());
			return rs;
		} else if(ln.startsWith("ERR")) {
			parseError(ln, rs);
			throw new LSException(rs.getCode(), rs.getMessage());
		}
		
		while(!ln.equals(".")) {
			rs.addLine(ln);
			ln = getLine();
		}
		
		return rs;
	}
	
	private final Vector<BufferFillListener> llBF = new Vector<BufferFillListener>();
	private final Vector<ChannelCountListener> llCC = new Vector<ChannelCountListener>();
	private final Vector<ChannelInfoListener> llCI = new Vector<ChannelInfoListener>();
	private final Vector<MiscellaneousListener> llM = new Vector<MiscellaneousListener>();
	private final Vector<StreamCountListener> llSC = new Vector<StreamCountListener>();
	private final Vector<VoiceCountListener> llVC = new Vector<VoiceCountListener>();
	
	/**
	 * Determines whether there is at least one subscription for notification events.
	 * Do not forget to check for additional listeners if the LSCP specification 
	 * extends in the future.
	 * @return <code>true</code> if there is at least one subscription for notification events,
	 * <code>false</code> otherwise.
	 */
	private boolean
	hasSubscriptions() {
		return	!llBF.isEmpty() ||
			!llCC.isEmpty() ||
			!llCI.isEmpty() ||
			!llM.isEmpty()  ||
			!llSC.isEmpty() ||
			!llVC.isEmpty();
	}
	
	private void
	fireEvent(String s) {
		if(s.startsWith("CHANNEL_COUNT:")) {
			try {
				int i = Integer.parseInt(s.substring("CHANNEL_COUNT:".length()));
				ChannelCountEvent e = new ChannelCountEvent(this, i);
				for(ChannelCountListener l : llCC) l.channelCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, LscpI18n.getLogMsg("CommandFailed!"), x
				);
			}
		} else if(s.startsWith("VOICE_COUNT:")) {
			try {
				s = s.substring("VOICE_COUNT:".length());
				int i = s.indexOf(' ');
				if(i == -1) {
					getLogger().warning("Unknown VOICE_COUNT format");
					return;
				}
				int j = Integer.parseInt(s.substring(0, i));
				i = Integer.parseInt(s.substring(i + 1));
				VoiceCountEvent e = new VoiceCountEvent(this, j, i);
				for(VoiceCountListener l : llVC) l.voiceCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log(Level.WARNING, "Unknown VOICE_COUNT format", x);
			}
		} else if(s.startsWith("STREAM_COUNT:")) {
			try {
				s = s.substring("STREAM_COUNT:".length());
				int i = s.indexOf(' ');
				if(i == -1) {
					getLogger().warning("Unknown STREAM_COUNT format");
					return;
				}
				int j = Integer.parseInt(s.substring(0, i));
				i = Integer.parseInt(s.substring(i + 1));
				StreamCountEvent e = new StreamCountEvent(this, j, i);
				for(StreamCountListener l : llSC) l.streamCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log(Level.WARNING, "Unknown STREAM_COUNT format", x);
			}
		} else if(s.startsWith("BUFFER_FILL:")) {
			try {
				s = s.substring("BUFFER_FILL:".length());
				int i = s.indexOf(' ');
				if(i == -1) {
					getLogger().warning("Unknown STREAM_COUNT format");
					return;
				}
				int j = Integer.parseInt(s.substring(0, i));
				Vector<BufferFill> v = 
					getChannelBufferFillPercentage(s.substring(i + 1));
				BufferFillEvent e = new BufferFillEvent(this, j, v);
				for(BufferFillListener l : llBF) l.bufferFillChanged(e);
			} catch(Exception x) {
				getLogger().log(Level.WARNING, "Unknown STREAM_COUNT format", x);
			}
		} else if(s.startsWith("CHANNEL_INFO:")) {
			try {
				int i = Integer.parseInt(s.substring("CHANNEL_INFO:".length()));
				ChannelInfoEvent e = new ChannelInfoEvent(this, i);
				for(ChannelInfoListener l : llCI) l.channelInfoChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log(Level.WARNING, "Unknown STREAM_COUNT format", x);
			}
		} else if(s.startsWith("MISCELLANEOUS:")) {
			s = s.substring("MISCELLANEOUS:".length());
			MiscellaneousEvent e = new MiscellaneousEvent(this, s);
			for(MiscellaneousListener l : llM) l.miscEventOccured(e);
		}
	}
	
	private void
	subscribe(String event) {
		if(!isConnected()) return;
		
		if(!eventThread.isAlive()) eventThread.start();
		
		try {
			out.writeLine("SUBSCRIBE " + event);
			ResultSet rs = getEmptyResultSet();
		} catch(Exception x) {
			getLogger().log (
				Level.WARNING,
				LscpI18n.getLogMsg("Client.subscriptionFailed!", event),
				x
			);
		}
	}
	
	private void
	unsubscribe(String event) {
		if(!isConnected()) return;
		
		try {
			out.writeLine("UNSUBSCRIBE " + event);
			ResultSet rs = getEmptyResultSet();
		} catch(Exception x) {
			getLogger().log (
				Level.WARNING,
				LscpI18n.getLogMsg("Client.unsubscriptionFailed!", event),
				x
			);
		}
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>BufferFillListener</code> to register.
	 */
	public synchronized void
	addBufferFillListener(BufferFillListener l) {
		if(llBF.isEmpty()) subscribe("BUFFER_FILL");
		llBF.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>BufferFillListener</code> to remove.
	 */
	public synchronized void
	removeBufferFillListener(BufferFillListener l) {
		boolean b = llBF.remove(l);
		if(b && llBF.isEmpty()) unsubscribe("BUFFER_FILL");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ChannelCountListener</code> to register.
	 */
	public synchronized void
	addChannelCountListener(ChannelCountListener l) {
		if(llCC.isEmpty()) subscribe("CHANNEL_COUNT");
		llCC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ChannelCountListener</code> to remove.
	 */
	public synchronized void
	removeChannelCountListener(ChannelCountListener l) {
		boolean b = llCC.remove(l);
		if(b && llCC.isEmpty()) unsubscribe("CHANNEL_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ChannelInfoListener</code> to register.
	 */
	public synchronized void
	addChannelInfoListener(ChannelInfoListener l) {
		if(llCI.isEmpty()) subscribe("CHANNEL_INFO");
		llCI.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ChannelInfoListener</code> to remove.
	 */
	public synchronized void
	removeChannelInfoListener(ChannelInfoListener l) {
		boolean b = llCI.remove(l);
		if(b && llCI.isEmpty()) unsubscribe("CHANNEL_INFO");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>MiscellaneousListener</code> to register.
	 */
	public synchronized void
	addMiscellaneousListener(MiscellaneousListener l) {
		if(llM.isEmpty()) subscribe("MISCELLANEOUS");
		llM.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>MiscellaneousListener</code> to remove.
	 */
	public synchronized void
	removeMiscellaneousListener(MiscellaneousListener l) {
		boolean b = llM.remove(l);
		if(b && llM.isEmpty()) unsubscribe("MISCELLANEOUS");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>StreamCountListener</code> to register.
	 */
	public synchronized void
	addStreamCountListener(StreamCountListener l) {
		if(llSC.isEmpty()) subscribe("STREAM_COUNT");
		llSC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>StreamCountListener</code> to remove.
	 */
	public synchronized void
	removeStreamCountListener(StreamCountListener l) {
		boolean b = llSC.remove(l);
		if(b && llSC.isEmpty()) unsubscribe("STREAM_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>VoiceCountListener</code> to register.
	 */
	public synchronized void
	addVoiceCountListener(VoiceCountListener l) {
		if(llVC.isEmpty()) subscribe("VOICE_COUNT");
		llVC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>VoiceCountListener</code> to remove.
	 */
	public synchronized void
	removeVoiceCountListener(VoiceCountListener l) {
		boolean b = llVC.remove(l);
		if(b && llVC.isEmpty()) unsubscribe("VOICE_COUNT");
	}
	
	/**
	 * Gets the number of all audio output drivers currently 
	 * available for the LinuxSampler instance.
	 * @return The number of all audio output drivers currently 
	 * available for the LinuxSampler instance.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getAudioOutputDriverCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AVAILABLE_AUDIO_OUTPUT_DRIVERS");
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets all audio output drivers currently available for the LinuxSampler instance.
	 * 
	 * @return <code>AudioOutputDriver</code> array containing all audio output drivers
	 * currently available for the LinuxSampler instance.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized AudioOutputDriver[]
	getAudioOutputDrivers() throws IOException, LscpException, LSException {
		String[] drivers = getAudioOutputDriverNames();
		AudioOutputDriver[] aod = new AudioOutputDriver[drivers.length];
		
		for(int i = 0; i < aod.length; i++) aod[i] = getAudioOutputDriverInfo(drivers[i]);
		
		return aod;
	}
	
	/**
	 * Gets all audio output drivers currently available for the LinuxSampler instance.
	 * 
	 * @return <code>String</code> array containing all audio output drivers currently
	 * available for the LinuxSampler instance.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	private synchronized String[]
	getAudioOutputDriverNames() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST AVAILABLE_AUDIO_OUTPUT_DRIVERS");
		return parseList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets detailed information about a specific audio output driver.
	 * @param driverName The name of the audio output driver.
	 *
	 * @return An <code>AudioOutputDriver</code> object containing
	 * information about the specified audio output driver.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no driver with name <code>driverName</code>.
	 *
	 * @see #getAudioOutputDriverNames
	 */
	private synchronized AudioOutputDriver
	getAudioOutputDriverInfo(String driverName) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_DRIVER INFO " + driverName);
		ResultSet rs = getMultiLineResultSet();
		AudioOutputDriver aod = new AudioOutputDriver(rs.getMultiLineResult());
		aod.setName(driverName);
		
		for(String s : aod.getParameterNames())
			aod.addParameter(getAudioOutputDriverParameterInfo(driverName, s));
		
		return aod;
	}
	
	/**
	 * Gets detailed information about a specific audio output driver parameter.
	 * 
	 * @param driver The name of the audio output driver.
	 * @param param A specific parameter name for which information should be obtained.
	 * @param deplist An optional list of parameters on which the sought parameter 
	 * <code>param</code> depends on. <code>Parameter</code> instances can be 
	 * easily created using {@link ParameterFactory} factory.
	 *
	 * @return <code>Parameter</code> object containing
	 * information about the specified audio output driver parameter.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>driver</code> is not a valid driver name
	 * or <code>param</code> is not a valid parameter for the specified driver.
	 *
	 * @see #getAudioOutputDrivers
	 * @see #getAudioOutputDriverInfo
	 * @see ParameterFactory
	 */
	public synchronized Parameter
	getAudioOutputDriverParameterInfo(String driver, String param, Parameter... deplist)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		StringBuffer args = new StringBuffer(driver);
		args.append(' ').append(param);
		
		for(Parameter p : deplist)
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		
		out.writeLine("GET AUDIO_OUTPUT_DRIVER_PARAMETER INFO " + args.toString());
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		ParameterType type = parseType(lnS);
		boolean multi = parseMultiplicity(lnS);
		Parameter prm;
		
		switch(type) {
		case BOOL:
			if(!multi) prm = new BoolParameter(lnS);
			else prm = new BoolListParameter(lnS);
			prm.setName(param);
			return prm;
		case INT:
			if(!multi) prm = new IntParameter(lnS);
			else prm = new IntListParameter(lnS);
			prm.setName(param);
			return prm;
		case FLOAT:
			if(!multi) prm = new FloatParameter(lnS);
			else prm = new FloatListParameter(lnS);
			prm.setName(param);
			return prm;
		case STRING:
			if(!multi) prm = new StringParameter(lnS);
			else prm = new StringListParameter(lnS);
			prm.setName(param);
			return prm;
		default: throw new LscpException(LscpI18n.getLogMsg("Client.unknownPrmType!"));
		}
	}
	
	/**
	 * Creates a new audio output device for the desired audio output system.
	 * @param aoDriver The desired audio output system.
	 * @param paramList An optional list of driver specific parameters. <code>Parameter</code>
	 * instances can be easily created using {@link ParameterFactory} factory.
	 * @return The numerical ID of the newly created device.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the new audio output device failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #getAudioOutputDrivers
	 * @see #getAudioOutputDriverInfo
	 * @see ParameterFactory
	 */
	public synchronized int
	createAudioOutputDevice(String aoDriver, Parameter... paramList)
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		StringBuffer args = new StringBuffer(aoDriver);
		
		for(Parameter p : paramList)
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		
		out.writeLine("CREATE AUDIO_OUTPUT_DEVICE " + args.toString());
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Destroys already created audio output device.
	 * @param deviceID The ID of the audio output device to be destroyed.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the destroying of the audio output device failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #getAudioOutputDevices
	 */
	public synchronized void
	destroyAudioOutputDevice(int deviceID) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("DESTROY AUDIO_OUTPUT_DEVICE " + deviceID);
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of all created audio output devices.
	 * @return The current number of all created audio output devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getAudioOutputDeviceCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_DEVICES");
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
		
	/**
	 * Gets a list of numerical IDs of all created audio output devices.
	 * @return An <code>Integer</code> array with numerical IDs of 
	 * all created audio output devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized Integer[]
	getAudioOutputDevices() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST AUDIO_OUTPUT_DEVICES");
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets the current settings of a specific, already created audio output device.
	 *
	 * @param deviceID Specifies the numerical ID of the audio output device.
	 *
	 * @return An <code>AudioOutputDevice</code> instance containing information
	 * about the specified device.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no audio output device
	 * with device id <code>deviceID</code>.
	 *
	 * @see #getAudioOutputDevices
	 */
	public synchronized AudioOutputDevice
	getAudioOutputDeviceInfo(int deviceID) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_DEVICE INFO " + deviceID);
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		
		AudioOutputDevice aod = new AudioOutputDevice();
		Parameter<Integer> channels;
		Parameter<Integer> samplerate;
		
		String drv = getCategoryInfo(lnS, "DRIVER");
		aod.setDriverName(drv);
		
		for(String s : lnS) {
			if(s.startsWith("CHANNELS: ")) {
				channels = (Parameter<Integer>)
					getAudioOutputDriverParameterInfo(drv, "CHANNELS");
				
				s = s.substring("CHANNELS: ".length(), s.length());
				channels.parseValue(s);
				aod.setChannelsParameter(channels);
			} else if(s.startsWith("SAMPLERATE: ")) {
				samplerate = (Parameter<Integer>)
					getAudioOutputDriverParameterInfo(drv, "SAMPLERATE");
				
				s = s.substring("SAMPLERATE: ".length(), s.length());
				samplerate.parseValue(s);
				aod.setSampleRateParameter(samplerate);
			} else if(s.startsWith("ACTIVE: ")) {
				s = s.substring("ACTIVE: ".length(), s.length());
				aod.setActive(Boolean.parseBoolean(s));
			} else if(s.startsWith("DRIVER: ")) {
				
			} else {
				int i = s.indexOf(": ");
				if(i == -1) throw new LscpException (
					LscpI18n.getLogMsg("CommandFailed!")
				);
				
				Parameter prm = 
					getAudioOutputDriverParameterInfo(drv, s.substring(0, i));
				
				s = s.substring(i + 2);
				prm.parseValue(s);
				
				aod.addParameter(prm);
			}
		}
		
		return aod;
	}
	
	/**
	 * Alters a specific setting of a created audio output device.
	 * 
	 * @param deviceID The numerical ID of the audio output device.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no audio output device with numerical ID <code>deviceID</code>;
	 * <li>There is no device parameter with the specified name;
	 * <li>The device parameter is readonly;
	 * <li>The device parameter is from different type.
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputDeviceInfo
	 */
	public synchronized void
	setAudioOutputDeviceParameter(int deviceID, Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String kv = prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET AUDIO_OUTPUT_DEVICE_PARAMETER " + deviceID + ' ' + kv);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets information about an audio channel.
	 *
	 * @param deviceID The numerical ID of the audio output device.
	 * @param audioChn The audio channel number.
	 *
	 * @return An <code>AudioOutputChannel</code> instance containing the
	 * information about the specified audio output channel.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If
	 * <ul>
	 * <li>There is no audio output device with numerical ID <code>deviceID</code>;
	 * <li><code>audioChn</code> is not a valid channel number;
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputDeviceInfo
	 */
	public synchronized AudioOutputChannel
	getAudioOutputChannelInfo(int deviceID, int audioChn)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_CHANNEL INFO " + deviceID + ' ' + audioChn);
		
		ResultSet rs = getMultiLineResultSet();
		
		AudioOutputChannel aoc = new AudioOutputChannel();
		
		String[] lnS = rs.getMultiLineResult();
		for(String s : lnS) {
			if(s.startsWith("NAME: ")) {
				aoc.setName(s.substring("NAME: ".length()));
			} else if(s.startsWith("IS_MIX_CHANNEL: ")) {
				s = s.substring("IS_MIX_CHANNEL: ".length());
				
				aoc.setMixChannel(Boolean.parseBoolean(s));
			} else if(s.startsWith("MIX_CHANNEL_DESTINATION: ")) {
				s = s.substring("MIX_CHANNEL_DESTINATION: ".length());
				aoc.setMixChannelDest(parseInt(s));
			} else {
				int i = s.indexOf(": ");
				if(i == -1) throw new LscpException (
					LscpI18n.getLogMsg("CommandFailed!")
				);
				
				Parameter prm = getAudioOutputChannelParameterInfo (
					deviceID, audioChn, s.substring(0, i)
				);
				
				s = s.substring(i + 2);
				prm.parseValue(s);
				
				aoc.addParameter(prm);
			}
		}
		
		return aoc;
	}
	
	/**
	 * Gets detailed information about a specific audio output channel parameter.
	 * 
	 * @param devID The numerical ID of the audio output device.
	 * @param chan The audio channel number.
	 * @param param a specific channel parameter name for which information should be obtained.
	 *
	 * @return An <code>Parameter</code> instance containing
	 * information about the specified audio output channel parameter.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If
	 * <ul>
	 * <li><code>devID</code> is not a valid device ID;
	 * <li><code>chan</code> is not a valid channel number;
	 * <li>There is no channel parameter with the specified name.
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputChannelInfo
	 */
	public synchronized Parameter
	getAudioOutputChannelParameterInfo(int devID, int chan, String param)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = devID + ' ' + chan + ' ' + param;
		out.writeLine("GET AUDIO_OUTPUT_CHANNEL_PARAMETER INFO " + args);
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		ParameterType type = parseType(lnS);
		boolean multi = parseMultiplicity(lnS);
		Parameter prm;
		
		switch(type) {
		case BOOL:
			if(!multi) prm = new BoolParameter(lnS);
			else prm = new BoolListParameter(lnS);
			prm.setName(param);
			return prm;
		case INT:
			if(!multi) prm = new IntParameter(lnS);
			else prm = new IntListParameter(lnS);
			prm.setName(param);
			return prm;
		case FLOAT:
			if(!multi) prm = new FloatParameter(lnS);
			else prm = new FloatListParameter(lnS); 
			prm.setName(param);
			return prm;
		case STRING:
			if(!multi) prm = new StringParameter(lnS);
			else prm = new StringListParameter(lnS);
			prm.setName(param);
			return prm;
		default: throw new LscpException(LscpI18n.getLogMsg("Client.unknownPrmType!"));
		}
	}
	
	/**
	 * Alters a specific setting of an audio output channel.
	 * 
	 * @param devID The numerical ID of the audio device.
	 * @param chn The audio channel number.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no audio output device with numerical ID <code>devID</code>;
	 * <li><code>chn</code> is not a valid channel number;
	 * <li>There is no channel parameter with the specified name;
	 * <li>The channel parameter is readonly;
	 * <li>The channel parameter is from different type.
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputChannelInfo
	 */
	public synchronized void
	setAudioOutputChannelParameter(int devID, int chn,  Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = devID + ' ' + chn + ' ' + prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET AUDIO_OUTPUT_CHANNEL_PARAMETER " + args);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of all MIDI input drivers.
	 * @return The current number of all MIDI input drivers.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getMidiInputDriverCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AVAILABLE_MIDI_INPUT_DRIVERS");
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets all MIDI input drivers currently available for the LinuxSampler instance.
	 * 
	 * @return <code>MidiInputDriver</code> array containing all MIDI input drivers currently 
	 * available for the LinuxSampler instance.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized MidiInputDriver[]
	getMidiInputDrivers() throws IOException, LscpException, LSException {
		String[] drivers = getMidiInputDriverNames();
		MidiInputDriver[] mid = new MidiInputDriver[drivers.length];
		
		for(int i = 0; i < mid.length; i++) mid[i] = getMidiInputDriverInfo(drivers[i]);
		
		return mid;
	}
	
	/**
	 * Gets all MIDI input drivers currently available for the LinuxSampler instance.
	 * 
	 * @return <code>String</code> array containing all MIDI input drivers currently available
	 * for the LinuxSampler instance.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	private synchronized String[]
	getMidiInputDriverNames() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST AVAILABLE_MIDI_INPUT_DRIVERS");
		return parseList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets detailed information about a specific MIDI input driver.
	 * @param driverName The name of the MIDI input driver.
	 *
	 * @return A <code>MidiInputDriver</code> object containing
	 * information about the specified MIDI input driver.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no driver with name <code>driverName</code>.
	 *
	 * @see #getMidiInputDriverNames
	 */
	private synchronized MidiInputDriver
	getMidiInputDriverInfo(String driverName) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_DRIVER INFO " + driverName);
		ResultSet rs = getMultiLineResultSet();
		
		MidiInputDriver mid = new MidiInputDriver(rs.getMultiLineResult());
		mid.setName(driverName);
		
		for(String s : mid.getParameterNames())
			mid.addParameter(getMidiInputDriverParameterInfo(driverName, s));
		
		return mid;
	}
	
	/**
	 * Gets detailed information about a specific MIDI input driver parameter.
	 * 
	 * @param driver The name of the MIDI input driver.
	 * @param param a specific parameter name for which information should be obtained.
	 * @param deplist An optional list of parameters on which the sought parameter 
	 * <code>param</code> depends on. <code>Parameter</code> instances can be 
	 * easily created using {@link ParameterFactory} factory.
	 *
	 * @return A <code>Parameter</code> object containing
	 * information about the specified MIDI input driver parameter.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>driver</code> is not a valid driver name
	 * or <code>param</code> is not a valid parameter for the specified driver.
	 *
	 * @see #getMidiInputDrivers
	 * @see #getMidiInputDriverInfo
	 * @see ParameterFactory
	 */
	public synchronized Parameter
	getMidiInputDriverParameterInfo(String driver, String param, Parameter... deplist)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		StringBuffer args = new StringBuffer(driver);
		args.append(' ').append(param);
		
		for(Parameter p : deplist)
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		
		out.writeLine("GET MIDI_INPUT_DRIVER_PARAMETER INFO " + args.toString());
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		ParameterType type = parseType(lnS);
		boolean multi = parseMultiplicity(lnS);
		Parameter prm;
		
		switch(type) {
		case BOOL:
			if(!multi) prm = new BoolParameter(lnS);
			else prm = new BoolListParameter(lnS);
			prm.setName(param);
			return prm;
		case INT:
			if(!multi) prm = new IntParameter(lnS);
			else prm = new IntListParameter(lnS);
			prm.setName(param);
			return prm;
		case FLOAT:
			if(!multi) prm = new FloatParameter(lnS);
			else prm = new FloatListParameter(lnS);
			prm.setName(param);
			return prm;
		case STRING:
			if(!multi) prm = new StringParameter(lnS);
			else prm = new StringListParameter(lnS);
			prm.setName(param);
			return prm;
		default: throw new LscpException(LscpI18n.getLogMsg("Client.unknownPrmType!"));
		}
	}
	
	/**
	 * Creates a new MIDI input device.
	 * @param miDriver The desired MIDI input system.
	 * @param paramList An optional list of driver specific parameters. <code>Parameter</code>
	 * instances can be easily created using {@link ParameterFactory} factory.
	 * @return The numerical ID of the newly created device.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the new MIDI input device failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 *
	 * @see #getMidiInputDrivers
	 * @see #getMidiInputDriverInfo
	 * @see ParameterFactory
	 */
	public synchronized int
	createMidiInputDevice(String miDriver, Parameter... paramList) 
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		StringBuffer args = new StringBuffer(miDriver);
		
		for(Parameter p : paramList)
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		
		out.writeLine("CREATE MIDI_INPUT_DEVICE " + args.toString());
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Destroys already created MIDI input device.
	 * @param deviceID The numerical ID of the MIDI input device to be destroyed.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the destroying of the MIDI input device failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #createMidiInputDevice
	 * @see #getMidiInputDevices
	 */
	public synchronized void
	destroyMidiInputDevice(int deviceID) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("DESTROY MIDI_INPUT_DEVICE " + deviceID);
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of all created MIDI input devices.
	 * @return The current number of all created MIDI input devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getMidiInputDeviceCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_DEVICES");
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list of numerical IDs of all created MIDI input devices.
	 * @return An <code>Integer</code> array with numerical IDs of 
	 * all created MIDI input devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 *
	 * @see #createMidiInputDevice
	 * @see #destroyMidiInputDevice
	 */
	public synchronized Integer[]
	getMidiInputDevices() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST MIDI_INPUT_DEVICES");
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets the current settings of a specific, already created MIDI input device.
	 *
	 * @param deviceID Specifies the numerical ID of the MIDI input device.
	 *
	 * @return An <code>MidiInputDevice</code> instance containing information
	 * about the specified device.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no MIDI input device
	 * with device id <code>deviceID</code>.
	 *
	 * @see #getMidiInputDevices
	 */
	public synchronized MidiInputDevice
	getMidiInputDeviceInfo(int deviceID) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_DEVICE INFO " + deviceID);
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		
		MidiInputDevice mid = new MidiInputDevice();
		
		String drv = getCategoryInfo(lnS, "DRIVER");
		mid.setDriverName(drv);
		
		for(String s : lnS) {
			if(s.startsWith("DRIVER: ")) {
				
			} else if(s.startsWith("ACTIVE: ")) {
				s = s.substring("ACTIVE: ".length());
				mid.setActive(Boolean.parseBoolean(s));
			} else {
				int i = s.indexOf(": ");
				if(i == -1) throw new LscpException (
					LscpI18n.getLogMsg("CommandFailed!")
				);
				
				Parameter prm = 
					getMidiInputDriverParameterInfo(drv, s.substring(0, i));
				
				s = s.substring(i + 2);
				prm.parseValue(s);
				
				mid.addParameter(prm);
			}
		}
		
		return mid;
	}
	
	/**
	 * Alters a specific setting of a created MIDI input device.
	 * 
	 * @param deviceID The numerical ID of the MIDI input device.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no MIDI input device with numerical ID <code>deviceID</code>;
	 * <li>There is no device parameter with the specified name;
	 * <li>The device parameter is readonly;
	 * <li>The device parameter is from different type.
	 * </ul>
	 *
	 * @see #getMidiInputDevices
	 * @see #getMidiInputDeviceInfo
	 */
	public synchronized void
	setMidiInputDeviceParameter(int deviceID, Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String kv = prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET MIDI_INPUT_DEVICE_PARAMETER " + deviceID + ' ' + kv);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets detailed information about a specific MIDI input port.
	 * @param deviceID The numerical ID of the MIDI input device.
	 * @param midiPort The MIDI input port number.
	 *
	 * @return A <code>MidiPort</code> instance containing
	 * information about the specified MIDI input port.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no device with ID <code>deviceID</code> or
	 * if <code>midiPort</code> is not a valid MIDI port number.
	 *
	 * @see #getMidiInputDevices
	 */
	public synchronized MidiPort
	getMidiInputPortInfo(int deviceID, int midiPort) 
					throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_PORT INFO " + deviceID + " " + midiPort);
		ResultSet rs = getMultiLineResultSet();
		
		MidiPort mp = new MidiPort();
		String[] lnS = rs.getMultiLineResult();
		
		for(String s : lnS) {
			if(s.startsWith("NAME: ")) {
				mp.setName(s.substring("NAME: ".length()));
			} else {
				int i = s.indexOf(": ");
				if(i == -1) throw new LscpException (
					LscpI18n.getLogMsg("CommandFailed!")
				);
				
				Parameter prm = getMidiInputPortParameterInfo (
					deviceID, midiPort, s.substring(0, i)
				);
				
				s = s.substring(i + 2);
				prm.parseValue(s);
				
				mp.addParameter(prm);
			}
		}
		
		return mp;
	}
	
	/**
	 * Gets detailed information about a specific MIDI input port parameter.
	 * 
	 * @param deviceID The numerical ID of the MIDI input device.
	 * @param port The MIDI port number.
	 * @param param A specific parameter name for which information should be obtained.
	 *
	 * @return A <code>Parameter</code> instance containing
	 * information about the specified MIDI input port parameter.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no MIDI input device with numerical ID <code>deviceID</code>;
	 * <li> <code>port</code> is not a valid MIDI port number;
	 * <li><code>param</code> is not a valid parameter for the specified MIDI port.
	 * </ul>
	 *
	 * @see #getMidiInputDevices
	 * @see #getMidiInputPortInfo
	 */
	public synchronized Parameter
	getMidiInputPortParameterInfo(int deviceID, int port, String param)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = deviceID + " " + port + " " + param;
		out.writeLine("GET MIDI_INPUT_PORT_PARAMETER INFO " + args);
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		ParameterType type = parseType(lnS);
		boolean multi = parseMultiplicity(lnS);
		Parameter prm;
		
		switch(type) {
		case BOOL:
			if(!multi) prm = new BoolParameter(lnS);
			else prm = new BoolListParameter(lnS);
			prm.setName(param);
			return prm;
		case INT:
			if(!multi) prm = new IntParameter(lnS);
			else prm = new IntListParameter(lnS);
			prm.setName(param);
			return prm;
		case FLOAT:
			if(!multi) prm = new FloatParameter(lnS);
			else prm = new FloatListParameter(lnS);
			prm.setName(param);
			return prm;
		case STRING:
			if(!multi) prm = new StringParameter(lnS);
			else prm = new StringListParameter(lnS);
			prm.setName(param);
			return prm;
		default: throw new LscpException(LscpI18n.getLogMsg("Client.unknownPrmType!"));
		}
	}
	
	/**
	 * Alters a specific setting of a MIDI input port.
	 * 
	 * @param deviceID The numerical ID of the MIDI device.
	 * @param port The MIDI port number.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no MIDI device with numerical ID <code>deviceID</code>;
	 * <li><code>port</code> is not a valid MIDI port number;
	 * <li><code>prm</code> is not a valid parameter;
	 * <li>The parameter is readonly;
	 * <li>The parameter is from different type.
	 * </ul>
	 *
	 * @see #getMidiInputDevices
	 * @see #getMidiInputPortInfo
	 */
	public synchronized void
	setMidiInputPortParameter(int deviceID, int port,  Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = deviceID + ' ' + port + ' ' + 
			prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET MIDI_INPUT_PORT_PARAMETER " + args);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Loads and assigns an instrument to a sampler channel. Notice that this function will
	 * return after the instrument is fully loaded and the channel is ready to be used.
	 *  
	 * @param filename The name of the instrument file
	 * on the LinuxSampler instance's host system.
	 * @param instrIdx The index of the instrument in the instrument file.
	 * @param samplerChn The number of the sampler channel the instrument should be assigned to.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the loading of the instrument failed.
	 *
	 * @see #loadInstrument(String, int, int, boolean)
	 * @see #getSamplerChannels
	 */
	public synchronized void
	loadInstrument(String filename, int instrIdx, int samplerChn)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		loadInstrument(filename, instrIdx, samplerChn, false);
	}
	
	/**
	 * Loads and assigns an instrument to a sampler channel.
	 *
	 * @param filename The name of the instrument file
	 * on the LinuxSampler instance's host system.
	 * @param instrIdx The index of the instrument in the instrument file.
	 * @param samplerChn The number of the sampler channel the instrument should be assigned to.
	 * @param nonModal If <code>false</code> the function will return after the instrument
	 * has been fully loaded and the channel is ready to be used. If <code>true</code>
	 * the function returns immediately.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the loading of the instrument failed.
	 *
	 * @see #loadInstrument(String, int, int)
	 * @see #getSamplerChannels
	 */
	public synchronized void
	loadInstrument(String filename, int instrIdx, int samplerChn, boolean nonModal)
						throws IOException, LscpException, LSException {
		
		String cmd = nonModal ? "LOAD INSTRUMENT NON_MODAL " : "LOAD INSTRUMENT ";
		String args = '\'' + filename + "' " + instrIdx + ' ' + samplerChn;
		
		out.writeLine(cmd + args);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Loads a sampler engine to a specific sampler channel.
	 * @param engineName The name of the engine.
	 * @param samplerChn The number of the sampler channel
	 * the deployed engine should be assigned to.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the loading of the sampler engine failed.
	 * @see #getEngines
	 * @see #getSamplerChannels
	 */
	public synchronized void
	loadSamplerEngine(String engineName, int samplerChn)
					throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("LOAD ENGINE " + engineName + ' ' + samplerChn);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of all created sampler channels.
	 * @return The current number of all created sampler channels.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getSamplerChannelCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET CHANNELS");
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list with numerical IDs of all created sampler channels.
	 * @return An <code>Integer</code> array with numerical IDs of all created sampler channels.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #addSamplerChannel
	 * @see #removeSamplerChannel
	 */
	public synchronized Integer[]
	getSamplerChannels() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST CHANNELS");
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Adds a new sampler channel. This method will increment the sampler channel count by one
	 * and the new sampler channel will be appended to the end of the sampler channel list.
	 *
	 * @return The number of the newly created sampler channel.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the new sampler channel failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #removeSamplerChannel
	 */
	public synchronized int
	addSamplerChannel() throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("ADD CHANNEL");
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Removes the specified sampler channel.
	 *
	 * @param samplerChn The numerical ID of the sampler channel to be removed.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the sampler channel failed.
	 * @see #addSamplerChannel
	 * @see #getSamplerChannels
	 */
	public synchronized void
	removeSamplerChannel(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("REMOVE CHANNEL " + samplerChn);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the number of all available engines.
	 * @return The number of all available engines.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getEngineCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AVAILABLE_ENGINES");
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list of all available engines.
	 *
	 * @return <code>SamplerEngine</code> array containing all available engines.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized SamplerEngine[]
	getEngines() throws IOException, LscpException, LSException {
		String[] engines = getEngineNames();
		SamplerEngine[] se = new SamplerEngine[engines.length];
		
		for(int i = 0; i < engines.length; i++) se[i] = getEngineInfo(engines[i]);
		
		return se;
	}
	
	/**
	 * Gets a list of all available engines' names.
	 *
	 * @return <code>String</code> array with all available engines' names.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	private synchronized String[]
	getEngineNames() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST AVAILABLE_ENGINES");
		return parseStringList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets information about a specific sampler engine.
	 * @param engineName The name of the sampler engine.
	 *
	 * @return <code>SamplerEngine</code> instance containing
	 * information about the specified sampler engine.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no sampler engine with name <code>engineName</code>.
	 * @see #getEngineNames
	 */
	private synchronized SamplerEngine
	getEngineInfo(String engineName) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET ENGINE INFO " + engineName);
		ResultSet rs = getMultiLineResultSet();
		SamplerEngine se = new SamplerEngine(rs.getMultiLineResult());
		se.setName(engineName);
		return se;
	}
	
	/**
	 * Gets the current settings of the specified sampler channel.
	 * @param samplerChn The sampler channel number.
	 *
	 * @return <code>SamplerChannel</code> instance containing
	 * the current settings of the specified sampler channel.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no sampler channel with <code>samplerChn</code> number.
	 * @see #getSamplerChannels
	 */
	public synchronized SamplerChannel
	getSamplerChannelInfo(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET CHANNEL INFO " + samplerChn);
		ResultSet rs = getMultiLineResultSet();
		SamplerChannel sc = new SamplerChannel(rs.getMultiLineResult());
		sc.setChannelID(samplerChn);
		
		return sc;
	}
	
	/**
	 * Gets the current number of active voices on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @return The current number of active voices on the specified sampler channel.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no sampler channel with number <code>samplerChn</code>.
	 * @see #getSamplerChannels
	 */
	public synchronized int
	getChannelVoiceCount(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET CHANNEL VOICE_COUNT " + samplerChn);
		ResultSet rs = getSingleLineResultSet();
		
		return parseInt(rs.getResult());
	}
	
	/**
	 * Gets the current number of active disk streams on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @return The current number of active disk streams on the specified sampler channel
	 * or -1 if the engine doesn't support disk streaming.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no sampler channel with number <code>samplerChn</code>.
	 * @see #getSamplerChannels
	 */
	public synchronized int
	getChannelStreamCount(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET CHANNEL STREAM_COUNT " + samplerChn);
		ResultSet rs = getSingleLineResultSet();
		
		if(rs.getResult().equals("NA")) return -1;
		
		return parseInt(rs.getResult());
	}
	
	/**
	 *  Gets the current fill state of all disk streams on the specified sampler channel
	 * in bytes.
	 *
	 * @param samplerChn The sampler channel number.
	 * @return The current fill state of all disk streams on the specified sampler channel
	 * or <code>null</code> if the engine which is deployed doesn't support disk streaming.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no sampler channel with number <code>samplerChn</code>.
	 * @see #getChannelBufferFillPercentage
	 * @see #getSamplerChannels
	 */
	public synchronized Vector<BufferFill>
	getChannelBufferFillBytes(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET CHANNEL BUFFER_FILL BYTES " + samplerChn);
		ResultSet rs = getSingleLineResultSet();
		
		if(rs.getResult().equals("NA")) return null;
		
		Vector<BufferFill> v = new Vector<BufferFill>();
		String[] args = parseList(rs.getResult());
		
		for(String s : args) {
			if(s.charAt(0) != '[')
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
			int i = s.indexOf(']');
			if(i == -1) throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
			BufferFill bf = new BufferFill();
			bf.setStreamID(parseInt(s.substring(1, i)));
			bf.setValue(parseInt(s.substring(i + 1)));
			v.add(bf);
		}
		
		return v;
	}
	
	/**
	 *  Gets the current fill state of all disk streams on the specified sampler channel
	 * in percent.
	 *
	 * @param samplerChn The sampler channel number.
	 * @return The current fill state of all disk streams on the specified sampler channel
	 * or <code>null</code> if the engine which is deployed doesn't support disk streaming.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no sampler channel with number <code>samplerChn</code>.
	 * @see #getChannelBufferFillBytes
	 * @see #getSamplerChannels
	 */
	public synchronized Vector<BufferFill>
	getChannelBufferFillPercentage(int samplerChn)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET CHANNEL BUFFER_FILL PERCENTAGE " + samplerChn);
		ResultSet rs = getSingleLineResultSet();
		
		return getChannelBufferFillPercentage(rs.getResult());
	}
	
	private Vector<BufferFill>
	getChannelBufferFillPercentage(String ln) throws LscpException {
		if(ln.equals("NA")) return null;
		
		Vector<BufferFill> v = new Vector<BufferFill>();
		String[] args = parseList(ln);
		
		for(String s : args) {
			if(s.charAt(0) != '[')
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
			int i = s.indexOf(']');
			if(i == -1) throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
			if(s.charAt(s.length() - 1) != '%')
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			
			BufferFill bf = new BufferFill();
			bf.setStreamID(parseInt(s.substring(1, i)));
			bf.setValue(parseInt(s.substring(i + 1, s.length() - 1)));
			v.add(bf);
		}
		
		return v;
	}
	
	/**
	 * Sets the audio output device on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param devID The numerical ID of the audio output device.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>samplerChn</code> is not a valid channel number;
	 * <li><code>devID</code> is not a valid audio output device ID;
	 * </ul>
	 *
	 * @see #getSamplerChannels
	 * @see #getAudioOutputDevices
	 */
	public synchronized void
	setChannelAudioOutputDevice(int samplerChn, int devID)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("SET CHANNEL AUDIO_OUTPUT_DEVICE " + samplerChn + ' ' + devID);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the audio output channel on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param audioOut The sampler channel's audio output channel which should be rerouted.
	 * @param audioIn The audio channel of the selected audio output device
	 * where <code>audioOut</code> should be routed to.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>samplerChn</code> is not a valid channel number;
	 * <li>There is no engine assigned yet to the specified sampler channel.
	 * <li> There is no audio output device connected to the specified sampler channel.
	 * </ul>
	 *
	 * @see #getSamplerChannels
	 */
	public synchronized void
	setChannelAudioOutputChannel(int samplerChn, int audioOut, int audioIn)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = " " + samplerChn + ' ' + audioOut + ' ' + audioIn;
		out.writeLine("SET CHANNEL AUDIO_OUTPUT_CHANNEL" + args);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the MIDI input device on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param devID The numerical ID of the MIDI input device.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>samplerChn</code> is not a valid channel number;
	 * <li><code>devID</code> is not a valid MIDI input device ID;
	 * </ul>
	 *
	 * @see #getSamplerChannels
	 * @see #getMidiInputDevices
	 */
	public synchronized void
	setChannelMidiInputDevice(int samplerChn, int devID)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("SET CHANNEL MIDI_INPUT_DEVICE " + samplerChn + ' ' + devID);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the MIDI input port on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param port The MIDI input port number of 
	 * the MIDI input device connected to the specified sampler channel.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	setChannelMidiInputPort(int samplerChn, int port)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("SET CHANNEL MIDI_INPUT_PORT " + samplerChn + ' ' + port);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the MIDI input channel the specified sampler channel should listen to.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param midiChn The number of the new MIDI input channel where
	 * <code>samplerChn</code> should listen to or -1 to listen on all 16 MIDI channels.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	setChannelMidiInputChannel(int samplerChn, int midiChn)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = String.valueOf(samplerChn) + ' ';
		args += (midiChn == -1 ? "ALL" : String.valueOf(midiChn));
		out.writeLine("SET CHANNEL MIDI_INPUT_CHANNEL " + args);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the volume of the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param volume The new volume value.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number or if
	 * there is no engine assigned yet to the specified sampler channel.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	setChannelVolume(int samplerChn, float volume)
				throws IOException, LscpException, LSException {
	
		verifyConnection();
		out.writeLine("SET CHANNEL VOLUME " + samplerChn + ' ' + volume);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Resets the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number or if
	 * there is no engine assigned yet to the specified sampler channel.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	resetChannel(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("RESET CHANNEL " + samplerChn);
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Resets the whole sampler.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	resetSampler() throws IOException, LscpException {
		verifyConnection();
		out.writeLine("RESET");
		try { ResultSet rs = getEmptyResultSet(); }
		catch(LSException x) { getLogger().warning(x.getMessage()); }
	}
	
	/**
	 * Gets information about the LinuxSampler instance.
	 * 
	 * @return <code>ServerInfo</code> instance containing
	 * information about the LinuxSampler instance.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized ServerInfo
	getServerInfo() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET SERVER INFO");
		ResultSet rs = getMultiLineResultSet();
		return new ServerInfo(rs.getMultiLineResult());
	}
	
	/**
	 * Returns the logger for this library.
	 * @return The logger for this library.
	 */
	protected static Logger
	getLogger() { return Logger.getLogger("org.linuxsampler.lscp"); }
}
