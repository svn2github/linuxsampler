/*
 *   jlscp - a java LinuxSampler control protocol API
 *
 *   Copyright (C) 2005-2008 Grigor Iliev <grigor@grigoriliev.com>
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
import java.io.OutputStream;

import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;

import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.linuxsampler.lscp.event.*;

import static org.linuxsampler.lscp.Parser.*;


/**
 * This class is the abstraction representing a client endpoint for communication with LinuxSampler
 * instance. Since it implements all commands specified in the LSCP protocol v1.3, for more 
 * information look at the
 * <a href=http://www.linuxsampler.org/api/lscp-1.3.html>LSCP</a> specification.
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
	private int soTimeout = 20000;
	
	private LscpInputStream in = null;
	private LscpOutputStream out = null;
	
	private EventThread eventThread;
	
	private boolean printOnlyMode = false;
	
	class EventThread extends Thread {
		private Vector<String> queue = new Vector<String>();
		private boolean terminate = false;
		
		EventThread() { super("LSCP-Event-Thread"); }
		
		@Override
		public void
		run() {
			while(!mustTerminate()) {
				try {
					processQueue();
					processNotifications();
				} catch(Exception x) {
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
		
		public synchronized void
		scheduleNotification(String s) { queue.add(s); }
		
		private void
		processQueue() {
			String[] notifications = popAllNotifications();
			for(String n : notifications) fireEvent(n);
		}
		
		private synchronized String[]
		popAllNotifications() {
			String[] notifications = queue.toArray(new String[queue.size()]);
			queue.removeAllElements();
			return notifications;
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
	 * Creates a new instance of Client.
	 * @param printOnlyMode Determines whether the client will be in print-only mode.
	 */
	public
	Client(boolean printOnlyMode) {
		if(printOnlyMode) setPrintOnlyMode(true);
	}
	
	private boolean extendedCharacterEscaping = true;
	
	/**
	 * Sets whether strings sent to LinuxSampler should be more aggressively escaped.
	 */
	public synchronized void
	setExtendedCharacterEscaping(boolean b) { extendedCharacterEscaping = b; }
	
	/**
	 * Determines whether strings sent to LinuxSampler should be more aggressively escaped.
	 */
	public synchronized boolean
	getExtendedCharacterEscaping() { return extendedCharacterEscaping; }
	
	/**
	 * @see java.net.Socket#setSoTimeout
	 */
	public synchronized void
	setSoTimeout(int timeout) {
		soTimeout = timeout;
		
		try { if(sock != null) sock.setSoTimeout(timeout); }
		catch(Exception x) { getLogger().log(Level.INFO, "Unable to set timeout", x); }
	}
	
	private String
	toEscapedText(String s) {
		s = toEscapedString(s);
		return conv(s);
	}
	
	private String
	toEscapedFsEntry(String s) {
		s = toEscapedFileName(s);
		return conv(s);
	}
	
	/**
	 * Applies an extended character escaping to the specified string if needed.
	 */
	private String
	conv(String s) {
		return getExtendedCharacterEscaping() ? toExtendedEscapeSequence(s) : s;
	}
	
	/**
	 * Determines whether the client is in print-only mode.
	 * Print-only mode means that the client will just print all
	 * LSCP commands to the specified output stream or to the standard output stream
	 * (<code>java.lang.System.out</code>) if no output stream is specified,
	 * without taking any further actions. Thus, in print-only mode all returned
	 * values by <code>Client</code>'s methods are meaningless and should be discarded.
	 * @return <code>true</code> if the client is in
	 * print-only mode, <code>false</code> otherwise.
	 * @see #setPrintOnlyModeOutputStream
	 */
	public synchronized boolean
	getPrintOnlyMode() { return printOnlyMode; }
	
	/**
	 * Sets the print-only mode. Note that in print-only mode all returned
	 * values by <code>Client</code>'s methods are meaningless and should be discarded.
	 * The default output stream in print-only mode is <code>java.lang.System.out</code>.
	 * @param b If <code>true</code> all LSCP commands will be sent
	 * to the specified output stream or to the standard output stream
	 * (<code>java.lang.System.out</code>) if no output stream is specified,
	 * and no further actions will be taken.
	 * @throws IllegalStateException If the client is connected.
	 * @see #setPrintOnlyModeOutputStream
	 */
	public synchronized void
	setPrintOnlyMode(boolean b) {
		if(printOnlyMode == b) return;
		if(isConnected()) throw new IllegalStateException();
		
		printOnlyMode = b;
		if(b) out = new LscpOutputStream(System.out);
	}
	
	/**
	 * Sets the output stream to be used in print-only mode.
	 * @param out The output stream to be used in print-only mode.
	 * @throws IllegalStateException If the client is not in print-only mode.
	 * @throws IllegalArgumentException if <code>out</code> is <code>null</code>.
	 * @see #setPrintOnlyMode
	 */
	public synchronized void
	setPrintOnlyModeOutputStream(OutputStream out) {
		if(!getPrintOnlyMode()) throw new IllegalStateException("Not in print-only mode");
		if(out == null) throw new IllegalArgumentException("out must be non-null");
		this.out = new LscpOutputStream(out);
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
		if(getPrintOnlyMode()) return;
		
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
			sock.setTcpNoDelay(true);
			
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
		if(!llAODC.isEmpty()) subscribe("AUDIO_OUTPUT_DEVICE_COUNT");
		if(!llAODI.isEmpty()) subscribe("AUDIO_OUTPUT_DEVICE_INFO");
		if(!llMIDC.isEmpty()) subscribe("MIDI_INPUT_DEVICE_COUNT");
		if(!llMIDI.isEmpty()) subscribe("MIDI_INPUT_DEVICE_INFO");
		if(!llBF.isEmpty()) subscribe("BUFFER_FILL");
		if(!llCC.isEmpty()) subscribe("CHANNEL_COUNT");
		if(!llCI.isEmpty()) subscribe("CHANNEL_INFO");
		if(!llFSC.isEmpty()) subscribe("FX_SEND_COUNT");
		if(!llFSI.isEmpty()) subscribe("FX_SEND_INFO");
		if(!llSC.isEmpty()) subscribe("STREAM_COUNT");
		if(!llVC.isEmpty()) subscribe("VOICE_COUNT");
		if(!llTSC.isEmpty()) subscribe("TOTAL_STREAM_COUNT");
		if(!llTVC.isEmpty()) subscribe("TOTAL_VOICE_COUNT");
		if(!llMIMC.isEmpty()) subscribe("MIDI_INSTRUMENT_MAP_COUNT");
		if(!llMIMI.isEmpty()) subscribe("MIDI_INSTRUMENT_MAP_INFO");
		if(!llMIC.isEmpty()) subscribe("MIDI_INSTRUMENT_COUNT");
		if(!llMII.isEmpty()) subscribe("MIDI_INSTRUMENT_INFO");
		if(!llDMD.isEmpty()) subscribe("DEVICE_MIDI");
		if(!llCMD.isEmpty()) subscribe("CHANNEL_MIDI");
		if(!llID.isEmpty()) {
			subscribe("DB_INSTRUMENT_DIRECTORY_COUNT");
			subscribe("DB_INSTRUMENT_DIRECTORY_INFO");
			subscribe("DB_INSTRUMENT_COUNT");
			subscribe("DB_INSTRUMENT_INFO");
			subscribe("DB_INSTRUMENTS_JOB_INFO");
		}
		if(!llGI.isEmpty()) subscribe("GLOBAL_INFO");
	}
	
	/**
	 * Closes the connection to LinuxSampler.
	 */
	public synchronized void
	disconnect() {
		if(getPrintOnlyMode()) return;
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
		if(getPrintOnlyMode()) return;
		
		if(!isConnected())
			throw new IOException(LscpI18n.getLogMsg("Client.notConnected!"));
	}
	
	private String
	getLine() throws IOException, LscpException {
		String s;
		for(;;) {
			s = in.readLine();
			if(s.startsWith("NOTIFY:")) {
				eventThread.scheduleNotification(s.substring("NOTIFY:".length()));
			}
			else break;
		}
		return s;
	}
	
	/** Processes the notifications sent by LinuxSampler */
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
	
	/** Audio output device count listeners */
	private final Vector<ItemCountListener> llAODC = new Vector<ItemCountListener>();
	/** Audio output device info listeners */
	private final Vector<ItemInfoListener> llAODI = new Vector<ItemInfoListener>();
	private final Vector<BufferFillListener> llBF = new Vector<BufferFillListener>();
	private final Vector<ChannelCountListener> llCC = new Vector<ChannelCountListener>();
	private final Vector<ChannelInfoListener> llCI = new Vector<ChannelInfoListener>();
	private final Vector<FxSendCountListener> llFSC = new Vector<FxSendCountListener>();
	private final Vector<FxSendInfoListener> llFSI = new Vector<FxSendInfoListener>();
	private final Vector<MiscellaneousListener> llM = new Vector<MiscellaneousListener>();
	/** MIDI input device count listeners */
	private final Vector<ItemCountListener> llMIDC = new Vector<ItemCountListener>();
	/** MIDI input device info listeners */
	private final Vector<ItemInfoListener> llMIDI = new Vector<ItemInfoListener>();
	private final Vector<StreamCountListener> llSC = new Vector<StreamCountListener>();
	private final Vector<VoiceCountListener> llVC = new Vector<VoiceCountListener>();
	private final Vector<TotalStreamCountListener> llTSC = new Vector<TotalStreamCountListener>();
	private final Vector<TotalVoiceCountListener> llTVC = new Vector<TotalVoiceCountListener>();
	
	/** MIDI instrument map count listeners */
	private final Vector<ItemCountListener> llMIMC = new Vector<ItemCountListener>();
	/** MIDI instrument map info listeners */
	private final Vector<ItemInfoListener> llMIMI = new Vector<ItemInfoListener>();
	/** MIDI instrument count listeners */
	private final Vector<MidiInstrumentCountListener> llMIC =
		new Vector<MidiInstrumentCountListener>();
	/** MIDI instrument info listeners */
	private final Vector<MidiInstrumentInfoListener> llMII =
		new Vector<MidiInstrumentInfoListener>();
	private final Vector<DeviceMidiDataListener> llDMD = new Vector<DeviceMidiDataListener>();
	private final Vector<ChannelMidiDataListener> llCMD = new Vector<ChannelMidiDataListener>();
	private final Vector<InstrumentsDbListener> llID = new Vector<InstrumentsDbListener>();
	private final Vector<GlobalInfoListener> llGI = new Vector<GlobalInfoListener>();
	
	
	/**
	 * Determines whether there is at least one subscription for notification events.
	 * Do not forget to check for additional listeners if the LSCP specification 
	 * is extended in the future.
	 * @return <code>true</code> if there is at least one subscription for notification events,
	 * <code>false</code> otherwise.
	 */
	private boolean
	hasSubscriptions() {
		return	!llAODC.isEmpty() ||
			!llAODI.isEmpty() ||
			!llBF.isEmpty()   ||
			!llCC.isEmpty()   ||
			!llCI.isEmpty()   ||
			!llFSC.isEmpty()  ||
			!llFSI.isEmpty()  ||
			!llM.isEmpty()    ||
			!llMIDC.isEmpty() ||
			!llMIDI.isEmpty() ||
			!llSC.isEmpty()   ||
			!llVC.isEmpty()   ||
			!llTSC.isEmpty()  ||
			!llTVC.isEmpty()  ||
			!llMIMC.isEmpty() ||
			!llMIMI.isEmpty() ||
			!llMIC.isEmpty()  ||
			!llMII.isEmpty()  ||
			!llDMD.isEmpty()  ||
			!llCMD.isEmpty()  ||
			!llID.isEmpty()   ||
			!llGI.isEmpty();
	}
	
	private synchronized void
	fireDeviceMidiDataEvent(String s) {
		try {
			String[] list = parseList(s, ' ');
			if(list.length != 5) {
				getLogger().warning("Unknown DEVICE_MIDI format");
				return;
			}
			
			int dev = parseInt(list[0]);
			int port = parseInt(list[1]);
			
			MidiDataEvent.Type type = parseMidiDataType(list[2]);
			if(type == null) return;
			
			int note = parseInt(list[3]);
			int velocity = parseInt(list[4]);
			
			DeviceMidiDataEvent e = new DeviceMidiDataEvent(this, type, note, velocity);
			e.setDeviceId(dev);
			e.setPortId(port);
			for(DeviceMidiDataListener l : llDMD) l.midiDataArrived(e);
		} catch(LscpException x) {
			getLogger().log (
				Level.WARNING, LscpI18n.getLogMsg("CommandFailed!"), x
			);
		}
	}
	
	private synchronized void
	fireChannelMidiDataEvent(String s) {
		try {
			String[] list = parseList(s, ' ');
			if(list.length != 4) {
				getLogger().warning("Unknown CHANNEL_MIDI format");
				return;
			}
			
			int channel = parseInt(list[0]);
			
			MidiDataEvent.Type type = parseMidiDataType(list[1]);
			if(type == null) return;
			
			int note = parseInt(list[2]);
			int velocity = parseInt(list[3]);
			
			ChannelMidiDataEvent e = new ChannelMidiDataEvent(this, type, note, velocity);
			e.setChannelId(channel);
			for(ChannelMidiDataListener l : llCMD) l.midiDataArrived(e);
		} catch(LscpException x) {
			getLogger().log (
				Level.WARNING, LscpI18n.getLogMsg("CommandFailed!"), x
			);
		}
	}
	
	private MidiDataEvent.Type
	parseMidiDataType(String s) {
		if("NOTE_ON".equals(s)) return MidiDataEvent.Type.NOTE_ON;
		if("NOTE_OFF".equals(s)) return MidiDataEvent.Type.NOTE_OFF;
		
		getLogger().warning("Unknown MIDI data type: " + s);
		return null;
	}
	
	private synchronized void
	fireEvent(String s) {
		// Sort by priority
		
		 if(s.startsWith("CHANNEL_MIDI:")) {
			s = s.substring("CHANNEL_MIDI:".length());
			fireChannelMidiDataEvent(s);
		} else if(s.startsWith("DEVICE_MIDI:")) {
			s = s.substring("DEVICE_MIDI:".length());
			fireDeviceMidiDataEvent(s);
		} else if(s.startsWith("DB_INSTRUMENT_DIRECTORY_COUNT:")) {
			s = s.substring("DB_INSTRUMENT_DIRECTORY_COUNT:".length());
			InstrumentsDbEvent e = new InstrumentsDbEvent(this, s);
			for(InstrumentsDbListener l : llID) l.directoryCountChanged(e);
		} else if(s.startsWith("DB_INSTRUMENT_DIRECTORY_INFO:")) {
			InstrumentsDbEvent e;
			s = s.substring("DB_INSTRUMENT_DIRECTORY_INFO:".length());
			if(s.startsWith("NAME ")) {
				String[] list;
				try {
					s = s.substring("NAME ".length());
					list = parseEscapedStringList(s, ' ');
					if(list.length != 2) throw new LscpException();
					list[1] = toNonEscapedString(list[1]);
					e = new InstrumentsDbEvent(this, list[0], list[1]);
					for(InstrumentsDbListener l : llID) {
						l.directoryNameChanged(e);
					}
				} catch(LscpException x) {
					getLogger().log (
						Level.WARNING,
						LscpI18n.getLogMsg("CommandFailed!"),
						x
					);
				}
			} else {
				e = new InstrumentsDbEvent(this, s);
				for(InstrumentsDbListener l : llID) l.directoryInfoChanged(e);
			}
		} else if(s.startsWith("DB_INSTRUMENT_COUNT:")) {
			s = s.substring("DB_INSTRUMENT_COUNT:".length());
			InstrumentsDbEvent e = new InstrumentsDbEvent(this, s);
			for(InstrumentsDbListener l : llID) l.instrumentCountChanged(e);
		} else if(s.startsWith("DB_INSTRUMENT_INFO:")) {
			InstrumentsDbEvent e;
			s = s.substring("DB_INSTRUMENT_INFO:".length());
			if(s.startsWith("NAME ")) {
				String[] list;
				try {
					s = s.substring("NAME ".length());
					list = parseEscapedStringList(s, ' ');
					if(list.length != 2) throw new LscpException();
					list[1] = toNonEscapedString(list[1]);
					e = new InstrumentsDbEvent(this, list[0], list[1]);
					for(InstrumentsDbListener l : llID) {
						l.instrumentNameChanged(e);
					}
				} catch(LscpException x) {
					getLogger().log (
						Level.WARNING,
						LscpI18n.getLogMsg("CommandFailed!"),
						x
					);
				}
			} else {
				e = new InstrumentsDbEvent(this, s);
				for(InstrumentsDbListener l : llID) l.instrumentInfoChanged(e);
			}
		} else if(s.startsWith("DB_INSTRUMENTS_JOB_INFO:")) {
			s = s.substring("DB_INSTRUMENTS_JOB_INFO:".length());
			try {
				int i = Integer.parseInt(s);
				InstrumentsDbEvent e = new InstrumentsDbEvent(this, i);
				for(InstrumentsDbListener l : llID) l.jobStatusChanged(e);
			} catch(NumberFormatException x) {
				s = "Unknown DB_INSTRUMENTS_JOB_INFO format";
				getLogger().log(Level.WARNING, s, x);
			}
			
		} else if(s.startsWith("CHANNEL_COUNT:")) {
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
				Integer[] i = parseIntList(s, ' ');
				if(i.length != 2) {
					getLogger().warning("Unknown VOICE_COUNT format");
					return;
				}
				VoiceCountEvent e = new VoiceCountEvent(this, i[0], i[1]);
				for(VoiceCountListener l : llVC) l.voiceCountChanged(e);
			} catch(Exception x) {
				getLogger().log(Level.WARNING, "Unknown VOICE_COUNT format", x);
			}
		} else if(s.startsWith("STREAM_COUNT:")) {
			try {
				s = s.substring("STREAM_COUNT:".length());
				Integer[] i = parseIntList(s, ' ');
				if(i.length != 2) {
					getLogger().warning("Unknown STREAM_COUNT format");
					return;
				}
				StreamCountEvent e = new StreamCountEvent(this, i[0], i[1]);
				for(StreamCountListener l : llSC) l.streamCountChanged(e);
			} catch(Exception x) {
				getLogger().log(Level.WARNING, "Unknown STREAM_COUNT format", x);
			}
		} else if(s.startsWith("BUFFER_FILL:")) {
			try {
				s = s.substring("BUFFER_FILL:".length());
				int i = s.indexOf(' ');
				if(i == -1) {
					getLogger().warning("Unknown BUFFER_FILL format");
					return;
				}
				int j = Integer.parseInt(s.substring(0, i));
				Vector<BufferFill> v = 
					getChannelBufferFillPercentage(s.substring(i + 1));
				BufferFillEvent e = new BufferFillEvent(this, j, v);
				for(BufferFillListener l : llBF) l.bufferFillChanged(e);
			} catch(Exception x) {
				getLogger().log(Level.WARNING, "Unknown BUFFER_FILL format", x);
			}
		} else if(s.startsWith("CHANNEL_INFO:")) {
			try {
				int i = Integer.parseInt(s.substring("CHANNEL_INFO:".length()));
				ChannelInfoEvent e = new ChannelInfoEvent(this, i);
				for(ChannelInfoListener l : llCI) l.channelInfoChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log(Level.WARNING, "Unknown CHANNEL_INFO format", x);
			}
		} else if(s.startsWith("TOTAL_STREAM_COUNT:")) {
			try {
				s = s.substring("TOTAL_STREAM_COUNT:".length());
				int i = Integer.parseInt(s);
				TotalStreamCountEvent e = new TotalStreamCountEvent(this, i);
				for(TotalStreamCountListener l : llTSC) l.totalStreamCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown TOTAL_STREAM_COUNT format", x
				);
			}
		} else if(s.startsWith("TOTAL_VOICE_COUNT:")) {
			try {
				s = s.substring("TOTAL_VOICE_COUNT:".length());
				int i = Integer.parseInt(s);
				TotalVoiceCountEvent e = new TotalVoiceCountEvent(this, i);
				for(TotalVoiceCountListener l : llTVC) l.totalVoiceCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown TOTAL_VOICE_COUNT format", x
				);
			}
		} else if(s.startsWith("AUDIO_OUTPUT_DEVICE_COUNT:")) {
			try {
				s = s.substring("AUDIO_OUTPUT_DEVICE_COUNT:".length());
				int i = Integer.parseInt(s);
				ItemCountEvent e = new ItemCountEvent(this, i);
				for(ItemCountListener l : llAODC) l.itemCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown AUDIO_OUTPUT_DEVICE_COUNT format", x
				);
			}
		} else if(s.startsWith("AUDIO_OUTPUT_DEVICE_INFO:")) {
			try {
				s = s.substring("AUDIO_OUTPUT_DEVICE_INFO:".length());
				int i = Integer.parseInt(s);
				ItemInfoEvent e = new ItemInfoEvent(this, i);
				for(ItemInfoListener l : llAODI) l.itemInfoChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown AUDIO_OUTPUT_DEVICE_INFO format", x
				);
			}
		} else if(s.startsWith("MIDI_INPUT_DEVICE_COUNT:")) {
			try {
				s = s.substring("MIDI_INPUT_DEVICE_COUNT:".length());
				int i = Integer.parseInt(s);
				ItemCountEvent e = new ItemCountEvent(this, i);
				for(ItemCountListener l : llMIDC) l.itemCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown MIDI_INPUT_DEVICE_COUNT format", x
				);
			}
		} else if(s.startsWith("MIDI_INPUT_DEVICE_INFO:")) {
			try {
				s = s.substring("MIDI_INPUT_DEVICE_INFO:".length());
				int i = Integer.parseInt(s);
				ItemInfoEvent e = new ItemInfoEvent(this, i);
				for(ItemInfoListener l : llMIDI) l.itemInfoChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown MIDI_INPUT_DEVICE_INFO format", x
				);
			}
		} else if(s.startsWith("MIDI_INSTRUMENT_MAP_COUNT:")) {
			try {
				s = s.substring("MIDI_INSTRUMENT_MAP_COUNT:".length());
				int i = Integer.parseInt(s);
				ItemCountEvent e = new ItemCountEvent(this, i);
				for(ItemCountListener l : llMIMC) l.itemCountChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown MIDI_INSTRUMENT_MAP_COUNT format", x
				);
			}
		} else if(s.startsWith("MIDI_INSTRUMENT_MAP_INFO:")) {
			try {
				s = s.substring("MIDI_INSTRUMENT_MAP_INFO:".length());
				int i = Integer.parseInt(s);
				ItemInfoEvent e = new ItemInfoEvent(this, i);
				for(ItemInfoListener l : llMIMI) l.itemInfoChanged(e);
			} catch(NumberFormatException x) {
				getLogger().log (
					Level.WARNING, "Unknown MIDI_INSTRUMENT_MAP_INFO format", x
				);
			}
		} else if(s.startsWith("MIDI_INSTRUMENT_COUNT:")) {
			try {
				s = s.substring("MIDI_INSTRUMENT_COUNT:".length());
				Integer[] i = parseIntList(s, ' ');
				if(i.length != 2) {
					getLogger().warning("Unknown MIDI_INSTRUMENT_COUNT format");
					return;
				}
				
				MidiInstrumentCountEvent e =
					new MidiInstrumentCountEvent(this, i[0], i[1]);
				
				for(MidiInstrumentCountListener l : llMIC) {
					l.instrumentCountChanged(e);
				}
			} catch(Exception x) {
				getLogger().log (
					Level.WARNING, "Unknown MIDI_INSTRUMENT_COUNT format", x
				);
			}
		} else if(s.startsWith("MIDI_INSTRUMENT_INFO:")) {
			try {
				s = s.substring("MIDI_INSTRUMENT_INFO:".length());
				Integer[] i = parseIntList(s, ' ');
				if(i.length != 3) {
					getLogger().warning("Unknown MIDI_INSTRUMENT_INFO format");
					return;
				}
				
				MidiInstrumentInfoEvent e =
					new MidiInstrumentInfoEvent(this, i[0], i[1], i[2]);
				for(MidiInstrumentInfoListener l : llMII) {
					l.instrumentInfoChanged(e);
				}
			} catch(Exception x) {
				getLogger().log (
					Level.WARNING, "Unknown MIDI_INSTRUMENT_INFO format", x
				);
			}
		} else if(s.startsWith("FX_SEND_COUNT:")) {
			try {
				s = s.substring("FX_SEND_COUNT:".length());
				Integer[] i = parseIntList(s, ' ');
				if(i.length != 2) {
					getLogger().warning("Unknown FX_SEND_COUNT format");
					return;
				}
				
				FxSendCountEvent e = new FxSendCountEvent(this, i[0], i[1]);
				
				for(FxSendCountListener l : llFSC) l.fxSendCountChanged(e);
			} catch(Exception x) {
				getLogger().log(Level.WARNING, "Unknown FX_SEND_COUNT format", x);
			}
		} else if(s.startsWith("FX_SEND_INFO:")) {
			try {
				s = s.substring("FX_SEND_INFO:".length());
				Integer[] i = parseIntList(s, ' ');
				if(i.length != 2) {
					getLogger().warning("Unknown FX_SEND_INFO format");
					return;
				}
				
				FxSendInfoEvent e = new FxSendInfoEvent(this, i[0], i[1]);
				for(FxSendInfoListener l : llFSI) {
					l.fxSendInfoChanged(e);
				}
			} catch(Exception x) {
				getLogger().log(Level.WARNING, "Unknown FX_SEND_INFO format", x);
			}
		} else if(s.startsWith("GLOBAL_INFO:")) {
			handleGlobalInfoEvent(s.substring("GLOBAL_INFO:".length()));
		} else if(s.startsWith("MISCELLANEOUS:")) {
			s = s.substring("MISCELLANEOUS:".length());
			MiscellaneousEvent e = new MiscellaneousEvent(this, s);
			for(MiscellaneousListener l : llM) l.miscEventOccured(e);
		}
	}
	
	private void
	handleGlobalInfoEvent(String s) {
		try {
			if(s.startsWith("VOLUME ")) {
				float f = Float.parseFloat(s.substring("VOLUME ".length()));
				GlobalInfoEvent e = new GlobalInfoEvent(this, f);
				for(GlobalInfoListener l : llGI) l.volumeChanged(e);
			} else if(s.startsWith("VOICES ")) {
				int i = Integer.parseInt(s.substring("VOICES ".length()));
				GlobalInfoEvent e = new GlobalInfoEvent(this, i, -1);
				for(GlobalInfoListener l : llGI) l.voiceLimitChanged(e);
			} else if(s.startsWith("STREAMS ")) {
				int i = Integer.parseInt(s.substring("STREAMS ".length()));
				GlobalInfoEvent e = new GlobalInfoEvent(this, -1, i);
				for(GlobalInfoListener l : llGI) l.streamLimitChanged(e);
			} else {
				getLogger().info("Unknown GLOBAL_INFO format: " + s);
			}
		} catch(NumberFormatException x) {
			getLogger().log(Level.WARNING, "Unknown GLOBAL_INFO format", x);
		}
	}
	
	private void
	subscribe(String event) {
		if(!getPrintOnlyMode()) {
			if(!isConnected()) return;
		
			if(!eventThread.isAlive()) eventThread.start();
		}
		
		try {
			out.writeLine("SUBSCRIBE " + event);
			if(!getPrintOnlyMode()) getEmptyResultSet();
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
		if(!getPrintOnlyMode() && !isConnected()) return;
		
		try {
			out.writeLine("UNSUBSCRIBE " + event);
			if(!getPrintOnlyMode()) getEmptyResultSet();
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
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ItemCountListener</code> to register.
	 */
	public synchronized void
	addAudioDeviceCountListener(ItemCountListener l) {
		if(llAODC.isEmpty()) subscribe("AUDIO_OUTPUT_DEVICE_COUNT");
		llAODC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ItemCountListener</code> to remove.
	 */
	public synchronized void
	removeAudioDeviceCountListener(ItemCountListener l) {
		boolean b = llAODC.remove(l);
		if(b && llAODC.isEmpty()) unsubscribe("AUDIO_OUTPUT_DEVICE_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ItemInfoListener</code> to register.
	 */
	public synchronized void
	addAudioDeviceInfoListener(ItemInfoListener l) {
		if(llAODI.isEmpty()) subscribe("AUDIO_OUTPUT_DEVICE_INFO");
		llAODI.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ItemInfoListener</code> to remove.
	 */
	public synchronized void
	removeAudioDeviceInfoListener(ItemInfoListener l) {
		boolean b = llAODI.remove(l);
		if(b && llAODI.isEmpty()) unsubscribe("AUDIO_OUTPUT_DEVICE_INFO");
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
	 * @param l The <code>FxSendCountListener</code> to register.
	 */
	public synchronized void
	addFxSendCountListener(FxSendCountListener l) {
		if(llFSC.isEmpty()) subscribe("FX_SEND_COUNT");
		llFSC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>FxSendCountListener</code> to remove.
	 */
	public synchronized void
	removeFxSendCountListener(FxSendCountListener l) {
		boolean b = llFSC.remove(l);
		if(b && llFSC.isEmpty()) unsubscribe("FX_SEND_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>FxSendInfoListener</code> to register.
	 */
	public synchronized void
	addFxSendInfoListener(FxSendInfoListener l) {
		if(llFSI.isEmpty()) subscribe("FX_SEND_INFO");
		llFSI.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>FxSendInfoListener</code> to remove.
	 */
	public synchronized void
	removeFxSendInfoListener(FxSendInfoListener l) {
		boolean b = llFSI.remove(l);
		if(b && llFSI.isEmpty()) unsubscribe("FX_SEND_INFO");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ItemCountListener</code> to register.
	 */
	public synchronized void
	addMidiDeviceCountListener(ItemCountListener l) {
		if(llMIDC.isEmpty()) subscribe("MIDI_INPUT_DEVICE_COUNT");
		llMIDC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ItemCountListener</code> to remove.
	 */
	public synchronized void
	removeMidiDeviceCountListener(ItemCountListener l) {
		boolean b = llMIDC.remove(l);
		if(b && llMIDC.isEmpty()) unsubscribe("MIDI_INPUT_DEVICE_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ItemInfoListener</code> to register.
	 */
	public synchronized void
	addMidiDeviceInfoListener(ItemInfoListener l) {
		if(llMIDI.isEmpty()) subscribe("MIDI_INPUT_DEVICE_INFO");
		llMIDI.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ItemInfoListener</code> to remove.
	 */
	public synchronized void
	removeMidiDeviceInfoListener(ItemInfoListener l) {
		boolean b = llMIDI.remove(l);
		if(b && llMIDI.isEmpty()) unsubscribe("MIDI_INPUT_DEVICE_INFO");
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
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>TotalStreamCountListener</code> to register.
	 */
	public synchronized void
	addTotalStreamCountListener(TotalStreamCountListener l) {
		if(llTSC.isEmpty()) subscribe("TOTAL_STREAM_COUNT");
		llTSC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>TotalStreamCountListener</code> to remove.
	 */
	public synchronized void
	removeTotalStreamCountListener(TotalStreamCountListener l) {
		boolean b = llTSC.remove(l);
		if(b && llTSC.isEmpty()) unsubscribe("TOTAL_STREAM_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>TotalVoiceCountListener</code> to register.
	 */
	public synchronized void
	addTotalVoiceCountListener(TotalVoiceCountListener l) {
		if(llTVC.isEmpty()) subscribe("TOTAL_VOICE_COUNT");
		llTVC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>TotalVoiceCountListener</code> to remove.
	 */
	public synchronized void
	removeTotalVoiceCountListener(TotalVoiceCountListener l) {
		boolean b = llTVC.remove(l);
		if(b && llTVC.isEmpty()) unsubscribe("TOTAL_VOICE_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ItemCountListener</code> to register.
	 */
	public synchronized void
	addMidiInstrumentMapCountListener(ItemCountListener l) {
		if(llMIMC.isEmpty()) subscribe("MIDI_INSTRUMENT_MAP_COUNT");
		llMIMC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ItemCountListener</code> to remove.
	 */
	public synchronized void
	removeMidiInstrumentMapCountListener(ItemCountListener l) {
		boolean b = llMIMC.remove(l);
		if(b && llMIMC.isEmpty()) unsubscribe("MIDI_INSTRUMENT_MAP_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ItemInfoListener</code> to register.
	 */
	public synchronized void
	addMidiInstrumentMapInfoListener(ItemInfoListener l) {
		if(llMIMI.isEmpty()) subscribe("MIDI_INSTRUMENT_MAP_INFO");
		llMIMI.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ItemInfoListener</code> to remove.
	 */
	public synchronized void
	removeMidiInstrumentMapInfoListener(ItemInfoListener l) {
		boolean b = llMIMI.remove(l);
		if(b && llMIMI.isEmpty()) unsubscribe("MIDI_INSTRUMENT_MAP_INFO");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>MidiInstrumentCountListener</code> to register.
	 */
	public synchronized void
	addMidiInstrumentCountListener(MidiInstrumentCountListener l) {
		if(llMIC.isEmpty()) subscribe("MIDI_INSTRUMENT_COUNT");
		llMIC.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>MidiInstrumentCountListener</code> to remove.
	 */
	public synchronized void
	removeMidiInstrumentCountListener(MidiInstrumentCountListener l) {
		boolean b = llMIC.remove(l);
		if(b && llMIC.isEmpty()) unsubscribe("MIDI_INSTRUMENT_COUNT");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>MidiInstrumentInfoListener</code> to register.
	 */
	public synchronized void
	addMidiInstrumentInfoListener(MidiInstrumentInfoListener l) {
		if(llMII.isEmpty()) subscribe("MIDI_INSTRUMENT_INFO");
		llMII.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>MidiInstrumentInfoListener</code> to remove.
	 */
	public synchronized void
	removeMidiInstrumentInfoListener(MidiInstrumentInfoListener l) {
		boolean b = llMII.remove(l);
		if(b && llMII.isEmpty()) unsubscribe("MIDI_INSTRUMENT_INFO");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>DeviceMidiDataListener</code> to register.
	 */
	public synchronized void
	addDeviceMidiDataListener(DeviceMidiDataListener l) {
		if(llDMD.isEmpty()) subscribe("DEVICE_MIDI");
		llDMD.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>DeviceMidiDataListener</code> to remove.
	 */
	public synchronized void
	removeDeviceMidiDataListener(DeviceMidiDataListener l) {
		boolean b = llDMD.remove(l);
		if(b && llDMD.isEmpty()) unsubscribe("DEVICE_MIDI");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>ChannelMidiDataListener</code> to register.
	 */
	public synchronized void
	addChannelMidiDataListener(ChannelMidiDataListener l) {
		if(llCMD.isEmpty()) subscribe("CHANNEL_MIDI");
		llCMD.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>ChannelMidiDataListener</code> to remove.
	 */
	public synchronized void
	removeChannelMidiDataListener(ChannelMidiDataListener l) {
		boolean b = llCMD.remove(l);
		if(b && llCMD.isEmpty()) unsubscribe("CHANNEL_MIDI");
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>InstrumentsDbListener</code> to register.
	 */
	public synchronized void
	addInstrumentsDbListener(InstrumentsDbListener l) {
		if(llID.isEmpty()) {
			subscribe("DB_INSTRUMENT_DIRECTORY_COUNT");
			subscribe("DB_INSTRUMENT_DIRECTORY_INFO");
			subscribe("DB_INSTRUMENT_COUNT");
			subscribe("DB_INSTRUMENT_INFO");
			subscribe("DB_INSTRUMENTS_JOB_INFO");
		}
		llID.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>InstrumentsDbListener</code> to remove.
	 */
	public synchronized void
	removeInstrumentsDbListener(InstrumentsDbListener l) {
		boolean b = llID.remove(l);
		if(b && llID.isEmpty()) {
			unsubscribe("DB_INSTRUMENT_DIRECTORY_COUNT");
			unsubscribe("DB_INSTRUMENT_DIRECTORY_INFO");
			unsubscribe("DB_INSTRUMENT_COUNT");
			unsubscribe("DB_INSTRUMENT_INFO");
			unsubscribe("DB_INSTRUMENTS_JOB_INFO");
		}
	}
	
	/**
	 * Registers the specified listener for receiving event messages.
	 * Listeners can be registered regardless of the connection state.
	 * @param l The <code>GlobalInfoListener</code> to register.
	 */
	public synchronized void
	addGlobalInfoListener(GlobalInfoListener l) {
		if(llGI.isEmpty()) subscribe("GLOBAL_INFO");
		llGI.add(l);
	}
	
	/**
	 * Removes the specified listener.
	 * Listeners can be removed regardless of the connection state.
	 * @param l The <code>GlobalInfoListener</code> to remove.
	 */
	public synchronized void
	removeGlobalInfoListener(GlobalInfoListener l) {
		boolean b = llGI.remove(l);
		if(b && llGI.isEmpty()) unsubscribe("GLOBAL_INFO");
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
		
		if(getPrintOnlyMode()) return -1;
		
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
		if(getPrintOnlyMode()) return null;
		
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
		if(getPrintOnlyMode()) return null;
		return parseList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets detailed information about a specific audio output driver.
	 * @param driverName The name of the audio output driver.
	 * @param depList An optional list of dependences parameters.
	 * @return An <code>AudioOutputDriver</code> object containing
	 * information about the specified audio output driver.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no driver with name <code>driverName</code>.
	 *
	 * @see #getAudioOutputDriverNames
	 */
	public synchronized AudioOutputDriver
	getAudioOutputDriverInfo(String driverName, Parameter... depList) 
					throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_DRIVER INFO " + driverName);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		AudioOutputDriver aod = new AudioOutputDriver(rs.getMultiLineResult());
		aod.setName(driverName);
		
		for(String s : aod.getParameterNames())
			aod.addParameter(getAudioOutputDriverParameterInfo(driverName, s, depList));
		
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
		
		for(Parameter p : deplist) {
			if(p == null || p.getName() == null || p.getValue() == null) continue;
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		}
		
		out.writeLine("GET AUDIO_OUTPUT_DRIVER_PARAMETER INFO " + args.toString());
		if(getPrintOnlyMode()) return null;
		
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
			prm.setValue(prm.getDefault());
			return prm;
		case INT:
			if(!multi) prm = new IntParameter(lnS);
			else prm = new IntListParameter(lnS);
			prm.setName(param);
			prm.setValue(prm.getDefault());
			return prm;
		case FLOAT:
			if(!multi) prm = new FloatParameter(lnS);
			else prm = new FloatListParameter(lnS);
			prm.setName(param);
			prm.setValue(prm.getDefault());
			return prm;
		case STRING:
			if(!multi) prm = new StringParameter(lnS);
			else prm = new StringListParameter(lnS);
			prm.setName(param);
			prm.setValue(prm.getDefault());
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
		
		for(Parameter p : paramList) {
			if(p == null || p.getName() == null || p.getValue() == null) continue;
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		}
		
		out.writeLine("CREATE AUDIO_OUTPUT_DEVICE " + args.toString());
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Destroys already created audio output device.
	 * @param deviceId The ID of the audio output device to be destroyed.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the destroying of the audio output device failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #getAudioOutputDevices
	 */
	public synchronized void
	destroyAudioOutputDevice(int deviceId) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("DESTROY AUDIO_OUTPUT_DEVICE " + deviceId);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/** 
	 * Enables/disables the specified audio output device.
	 * @param deviceId The ID of the audio output device to be enabled/disabled.
	 * @param enable If <code>true</code> the audio output device is enabled,
	 * else the device is disabled.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If there is no audio output
	 * device with numerical ID <code>deviceId</code>.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public void
	enableAudioOutputDevice(int deviceId, boolean enable)
				throws IOException, LSException, LscpException {
		
		setAudioOutputDeviceParameter(deviceId, new BoolParameter("ACTIVE", enable));
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
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
		
	/**
	 * Gets a list of all created audio output devices.
	 * @return An <code>AudioOutputDevice</code> array 
	 * providing all created audio output devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized AudioOutputDevice[]
	getAudioOutputDevices() throws IOException, LscpException, LSException {
		Integer[] idS = getAudioOutputDeviceIDs();
		if(getPrintOnlyMode()) return null;
		
		AudioOutputDevice[] devices = new AudioOutputDevice[idS.length];
		
		for(int i = 0; i < devices.length; i++)
			devices[i] = getAudioOutputDeviceInfo(idS[i]);
		
		return devices;
	}
	
	/**
	 * Gets a list of numerical IDs of all created audio output devices.
	 * @return An <code>Integer</code> array providing the numerical IDs of 
	 * all created audio output devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized Integer[]
	getAudioOutputDeviceIDs() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST AUDIO_OUTPUT_DEVICES");
		if(getPrintOnlyMode()) return null;
		
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets the current settings of a specific, already created audio output device.
	 *
	 * @param deviceId Specifies the numerical ID of the audio output device.
	 *
	 * @return An <code>AudioOutputDevice</code> instance containing information
	 * about the specified device.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no audio output device
	 * with device id <code>deviceId</code>.
	 *
	 * @see #getAudioOutputDevices
	 */
	public synchronized AudioOutputDevice
	getAudioOutputDeviceInfo(int deviceId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_DEVICE INFO " + deviceId);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		
		AudioOutputDevice aod = new AudioOutputDevice();
		aod.setDeviceId(deviceId);
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
				int count = channels.getValue() > 0 ? channels.getValue() : 0;
				AudioOutputChannel[] aoc = new AudioOutputChannel[count];
				for(int i = 0; i < count; i++) {
					aoc[i] = getAudioOutputChannelInfo(deviceId, i);
				}
				aod.setAudioChannels(aoc);
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
	 * @param deviceId The numerical ID of the audio output device.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no audio output device with numerical ID <code>deviceId</code>;
	 * <li>There is no device parameter with the specified name;
	 * <li>The device parameter is readonly;
	 * <li>The device parameter is from different type.
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputDeviceInfo
	 */
	public synchronized void
	setAudioOutputDeviceParameter(int deviceId, Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String kv = prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET AUDIO_OUTPUT_DEVICE_PARAMETER " + deviceId + ' ' + kv);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Changes the channel number of the speicifed audio output device.
	 * @param deviceId The numerical ID of the audio output device.
	 * @param channels The new number of audio output channels.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no device with ID <code>deviceId</code> or
	 * if <code>channels</code> number is out of range.
	 *
	 * @see #getAudioOutputChannelInfo
	 */
	public synchronized void
	setAudioOutputChannelCount(int deviceId, int channels)
					throws IOException, LscpException, LSException {
		
		setAudioOutputDeviceParameter(deviceId, new IntParameter("CHANNELS", channels));
	}
	
	/**
	 * Gets information about an audio channel.
	 *
	 * @param deviceId The numerical ID of the audio output device.
	 * @param audioChn The audio channel number.
	 *
	 * @return An <code>AudioOutputChannel</code> instance containing the
	 * information about the specified audio output channel.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If
	 * <ul>
	 * <li>There is no audio output device with numerical ID <code>deviceId</code>;
	 * <li><code>audioChn</code> is not a valid channel number;
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputDeviceInfo
	 */
	public synchronized AudioOutputChannel
	getAudioOutputChannelInfo(int deviceId, int audioChn)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET AUDIO_OUTPUT_CHANNEL INFO " + deviceId + ' ' + audioChn);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		
		AudioOutputChannel aoc = new AudioOutputChannel();
		
		String[] lnS = rs.getMultiLineResult();
		for(String s : lnS) {
			if(s.startsWith("NAME: ")) {
				s = s.substring("NAME: ".length());
				Parameter<String> prm = getAudioOutputChannelParameterInfo (
					deviceId, audioChn, "NAME"
				);
				prm.setValue(removeQuotation(s));
				aoc.setNameParameter(prm);
			} else if(s.startsWith("IS_MIX_CHANNEL: ")) {
				s = s.substring("IS_MIX_CHANNEL: ".length());
				Parameter<Boolean> prm = getAudioOutputChannelParameterInfo (
					deviceId, audioChn, "IS_MIX_CHANNEL"
				);
				prm.setValue(Boolean.parseBoolean(s));
				aoc.setMixChannelParameter(prm);
			} else if(s.startsWith("MIX_CHANNEL_DESTINATION: ")) {
				s = s.substring("MIX_CHANNEL_DESTINATION: ".length());
				Parameter<Integer> prm = getAudioOutputChannelParameterInfo (
					deviceId, audioChn, "MIX_CHANNEL_DESTINATION"
				);
				prm.setValue(parseInt(s));
				aoc.setMixChannelDestParameter(prm);
			} else {
				int i = s.indexOf(": ");
				if(i == -1) throw new LscpException (
					LscpI18n.getLogMsg("CommandFailed!")
				);
				
				Parameter prm = getAudioOutputChannelParameterInfo (
					deviceId, audioChn, s.substring(0, i)
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
	 * @param devId The numerical ID of the audio output device.
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
	 * <li><code>devId</code> is not a valid device ID;
	 * <li><code>chan</code> is not a valid channel number;
	 * <li>There is no channel parameter with the specified name.
	 * </ul>
	 *
	 * @see #getAudioOutputDevices
	 * @see #getAudioOutputChannelInfo
	 */
	public synchronized Parameter
	getAudioOutputChannelParameterInfo(int devId, int chan, String param)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = devId + " " + chan + " " + param;
		out.writeLine("GET AUDIO_OUTPUT_CHANNEL_PARAMETER INFO " + args);
		if(getPrintOnlyMode()) return null;
		
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
	 * @param devId The numerical ID of the audio device.
	 * @param chn The audio channel number.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no audio output device with numerical ID <code>devId</code>;
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
	setAudioOutputChannelParameter(int devId, int chn,  Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = devId + " " + chn + " " + prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET AUDIO_OUTPUT_CHANNEL_PARAMETER " + args);
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return -1;
		
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
		if(getPrintOnlyMode()) return null;
		
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
		if(getPrintOnlyMode()) return null;
		
		return parseList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets detailed information about a specific MIDI input driver.
	 * @param driverName The name of the MIDI input driver.
	 * @param depList An optional list of dependences parameters.
	 * @return A <code>MidiInputDriver</code> object containing
	 * information about the specified MIDI input driver.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no driver with name <code>driverName</code>.
	 *
	 * @see #getMidiInputDriverNames
	 */
	public synchronized MidiInputDriver
	getMidiInputDriverInfo(String driverName, Parameter... depList)
					throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_DRIVER INFO " + driverName);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		
		MidiInputDriver mid = new MidiInputDriver(rs.getMultiLineResult());
		mid.setName(driverName);
		
		for(String s : mid.getParameterNames())
			mid.addParameter(getMidiInputDriverParameterInfo(driverName, s, depList));
		
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
		
		for(Parameter p : deplist) {
			if(p == null || p.getName() == null || p.getValue() == null) continue;
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		}
		
		out.writeLine("GET MIDI_INPUT_DRIVER_PARAMETER INFO " + args.toString());
		if(getPrintOnlyMode()) return null;
		
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
			prm.setValue(prm.getDefault());
			return prm;
		case INT:
			if(!multi) prm = new IntParameter(lnS);
			else prm = new IntListParameter(lnS);
			prm.setName(param);
			prm.setValue(prm.getDefault());
			return prm;
		case FLOAT:
			if(!multi) prm = new FloatParameter(lnS);
			else prm = new FloatListParameter(lnS);
			prm.setName(param);
			prm.setValue(prm.getDefault());
			return prm;
		case STRING:
			if(!multi) prm = new StringParameter(lnS);
			else prm = new StringListParameter(lnS);
			prm.setName(param);
			prm.setValue(prm.getDefault());
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
		
		for(Parameter p : paramList) {
			if(p == null || p.getName() == null || p.getValue() == null) continue;
			args.append(' ').append(p.getName()).append('=').append(p.getStringValue());
		}
		
		out.writeLine("CREATE MIDI_INPUT_DEVICE " + args.toString());
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Destroys already created MIDI input device.
	 * @param deviceId The numerical ID of the MIDI input device to be destroyed.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the destroying of the MIDI input device failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #createMidiInputDevice
	 * @see #getMidiInputDevices
	 */
	public synchronized void
	destroyMidiInputDevice(int deviceId) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("DESTROY MIDI_INPUT_DEVICE " + deviceId);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/** 
	 * Enables/disables the specified MIDI input device.
	 * @param deviceId The ID of the MIDI input device to be enabled/disabled.
	 * @param enable If <code>true</code> the MIDI input device is enabled,
	 * else the device is disabled.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If there is no MIDI input
	 * device with numerical ID <code>deviceId</code>.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public void
	enableMidiInputDevice(int deviceId, boolean enable)
				throws IOException, LSException, LscpException {
		
		setMidiInputDeviceParameter(deviceId, new BoolParameter("ACTIVE", enable));
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
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list of all created MIDI input devices.
	 * @return A <code>MidiInputDevice</code> array 
	 * providing all created MIDI input devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 *
	 * @see #createMidiInputDevice
	 * @see #destroyMidiInputDevice
	 */
	public synchronized MidiInputDevice[]
	getMidiInputDevices() throws IOException, LscpException, LSException {
		Integer[] idS = getMidiInputDeviceIDs();
		if(getPrintOnlyMode()) return null;
		
		MidiInputDevice[] devices = new MidiInputDevice[idS.length];
		
		for(int i = 0; i < devices.length; i++)
			devices[i] = getMidiInputDeviceInfo(idS[i]);
		
		return devices;
	}
	
	/**
	 * Gets a list of numerical IDs of all created MIDI input devices.
	 * @return An <code>Integer</code> array providing the numerical IDs of
	 * all created MIDI input devices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 *
	 * @see #createMidiInputDevice
	 * @see #destroyMidiInputDevice
	 */
	public synchronized Integer[]
	getMidiInputDeviceIDs() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST MIDI_INPUT_DEVICES");
		if(getPrintOnlyMode()) return null;
		
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets the current settings of a specific, already created MIDI input device.
	 *
	 * @param deviceId Specifies the numerical ID of the MIDI input device.
	 *
	 * @return A <code>MidiInputDevice</code> instance containing information
	 * about the specified device.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no MIDI input device
	 * with device id <code>deviceId</code>.
	 *
	 * @see #getMidiInputDevices
	 */
	public synchronized MidiInputDevice
	getMidiInputDeviceInfo(int deviceId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_DEVICE INFO " + deviceId);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		
		MidiInputDevice mid = new MidiInputDevice();
		mid.setDeviceId(deviceId);
		
		String drv = getCategoryInfo(lnS, "DRIVER");
		mid.setDriverName(drv);
		
		for(String s : lnS) {
			if(s.startsWith("DRIVER: ")) {
				
			} else if(s.startsWith("ACTIVE: ")) {
				s = s.substring("ACTIVE: ".length());
				mid.setActive(Boolean.parseBoolean(s));
			} else if(s.startsWith("PORTS: ")) {
				s = s.substring("PORTS: ".length());
				
				Parameter<Integer> ports = (Parameter<Integer>)
					getMidiInputDriverParameterInfo(drv, "PORTS");
				
				ports.parseValue(s);
				mid.setPortsParameter(ports);
				
				int j = ports.getValue();
				MidiPort[] midiPorts = new MidiPort[j > 0 ? j : 0];
				
				for(int i = 0; i < midiPorts.length; i++)
					midiPorts[i] = getMidiInputPortInfo(deviceId, i);
				
				mid.setMidiPorts(midiPorts);
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
	 * @param deviceId The numerical ID of the MIDI input device.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no MIDI input device with numerical ID <code>deviceId</code>;
	 * <li>There is no device parameter with the specified name;
	 * <li>The device parameter is readonly;
	 * <li>The device parameter is from different type.
	 * </ul>
	 *
	 * @see #getMidiInputDevices
	 * @see #getMidiInputDeviceInfo
	 */
	public synchronized void
	setMidiInputDeviceParameter(int deviceId, Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String kv = prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET MIDI_INPUT_DEVICE_PARAMETER " + deviceId + ' ' + kv);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	
	/**
	 * Changes the port number of the speicified MIDI input device.
	 * @param deviceId The numerical ID of the MIDI input device.
	 * @param ports The new number of MIDI input ports.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no device with ID <code>deviceId</code> or
	 * if <code>ports</code> number is out of range.
	 *
	 * @see #getMidiInputPortInfo
	 */
	public synchronized void
	setMidiInputPortCount(int deviceId, int ports)
					throws IOException, LscpException, LSException {
		
		setMidiInputDeviceParameter(deviceId, new IntParameter("PORTS", ports));
	}
	
	/**
	 * Gets detailed information about a specific MIDI input port.
	 * @param deviceId The numerical ID of the MIDI input device.
	 * @param midiPort The MIDI input port number.
	 *
	 * @return A <code>MidiPort</code> instance containing
	 * information about the specified MIDI input port.
	 *
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no device with ID <code>deviceId</code> or
	 * if <code>midiPort</code> is not a valid MIDI port number.
	 *
	 * @see #getMidiInputDevices
	 */
	public synchronized MidiPort
	getMidiInputPortInfo(int deviceId, int midiPort) 
					throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET MIDI_INPUT_PORT INFO " + deviceId + " " + midiPort);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		
		MidiPort mp = new MidiPort();
		String[] lnS = rs.getMultiLineResult();
		
		for(String s : lnS) {
			if(s.startsWith("NAME: ")) {
				s = s.substring("NAME: ".length());
				Parameter prm = getMidiInputPortParameterInfo (
					deviceId, midiPort, "NAME"
				);
				prm.setValue(removeQuotation(s));
				mp.setNameParameter(prm);
			} else {
				int i = s.indexOf(": ");
				if(i == -1) throw new LscpException (
					LscpI18n.getLogMsg("CommandFailed!")
				);
				
				Parameter prm = getMidiInputPortParameterInfo (
					deviceId, midiPort, s.substring(0, i)
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
	 * @param deviceId The numerical ID of the MIDI input device.
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
	 * <li>There is no MIDI input device with numerical ID <code>deviceId</code>;
	 * <li> <code>port</code> is not a valid MIDI port number;
	 * <li><code>param</code> is not a valid parameter for the specified MIDI port.
	 * </ul>
	 *
	 * @see #getMidiInputDevices
	 * @see #getMidiInputPortInfo
	 */
	public synchronized Parameter
	getMidiInputPortParameterInfo(int deviceId, int port, String param)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = deviceId + " " + port + " " + param;
		out.writeLine("GET MIDI_INPUT_PORT_PARAMETER INFO " + args);
		if(getPrintOnlyMode()) return null;
		
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
	 * @param deviceId The numerical ID of the MIDI device.
	 * @param port The MIDI port number.
	 * @param prm A <code>Parameter</code> instance containing the name of the parameter
	 * and the new value for this parameter.
	 *
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li>There is no MIDI device with numerical ID <code>deviceId</code>;
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
	setMidiInputPortParameter(int deviceId, int port,  Parameter prm) 
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = deviceId + " " + port + " " + 
			prm.getName() + '=' + prm.getStringValue();
		out.writeLine("SET MIDI_INPUT_PORT_PARAMETER " + args);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Adds a new MIDI instrument map.
	 * @param name The name of this MIDI instrument map.
	 * @return The number of the newly MIDI instrument map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the new MIDI instrument map failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #removeMidiInstrumentMap
	 */
	public synchronized int
	addMidiInstrumentMap(String name) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("ADD MIDI_INSTRUMENT_MAP '" + toEscapedText(name) + "'");
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Removes the specified MIDI instrument map.
	 * @param mapId The numerical ID of the MIDI instrument map to be removed.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the MIDI instrument map failed.
	 * @see #addMidiInstrumentMap
	 * @see #getMidiInstrumentMapIDs
	 */
	public synchronized void
	removeMidiInstrumentMap(int mapId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("REMOVE MIDI_INSTRUMENT_MAP " + mapId);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Removes the all MIDI instrument maps.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the MIDI instrument maps failed.
	 */
	public synchronized void
	removeAllMidiInstrumentMaps() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("REMOVE MIDI_INSTRUMENT_MAP ALL");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of all MIDI instrument maps.
	 * @return The current number of all MIDI instrument maps.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getMidiInstrumentMapCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INSTRUMENT_MAPS");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list of numerical IDs of all created MIDI instrument maps.
	 * @return An <code>Integer</code> array providing the numerical IDs of
	 * all created MIDI instrument maps.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #addMidiInstrumentMap
	 * @see #removeMidiInstrumentMap
	 */
	public synchronized Integer[]
	getMidiInstrumentMapIDs() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST MIDI_INSTRUMENT_MAPS");
		if(getPrintOnlyMode()) return null;
		
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets the current settings of a specific, already created MIDI instrument map.
	 * @param mapId Specifies the numerical ID of the MIDI instrument map.
	 * @return A <code>MidiInstrumentMapInfo</code> instance containing information
	 * about the specified device.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If there is no MIDI instrument map
	 * with map id <code>mapId</code>.
	 * @see #getMidiInstrumentMaps
	 */
	public synchronized MidiInstrumentMapInfo
	getMidiInstrumentMapInfo(int mapId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INSTRUMENT_MAP INFO " + mapId);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		
		String[] lnS = rs.getMultiLineResult();
		
		String name = "";
		boolean b = false;
		
		for(String s : lnS) {
			if(s.startsWith("NAME: ")) {
				name = toNonEscapedString(s.substring("NAME: ".length()));
			} else if(s.startsWith("DEFAULT: ")) {
				b = Boolean.parseBoolean(s.substring("DEFAULT: ".length()));
			} else {
				 getLogger().info(LscpI18n.getLogMsg("unknownLine", s));
			}
		}
		
		return new MidiInstrumentMapInfo(mapId, name, b);
	}
	
	/**
	 * Gets an information of all created MIDI instrument maps.
	 * @return A <code>MidiInstrumentMap</code> array 
	 * providing information for all created MIDI instrument maps.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #addMidiInstrumentMap
	 * @see #removeMidiInstrumentMap
	 */
	public synchronized MidiInstrumentMapInfo[]
	getMidiInstrumentMaps() throws IOException, LscpException, LSException {
		Integer[] idS = getMidiInstrumentMapIDs();
		if(getPrintOnlyMode()) return null;
		
		MidiInstrumentMapInfo[] maps = new MidiInstrumentMapInfo[idS.length];
		
		for(int i = 0; i < maps.length; i++)
			maps[i] = getMidiInstrumentMapInfo(idS[i]);
		
		return maps;
	}
	
	/**
	 * Sets the name of the specified MIDI instrument map.
	 * @param mapId The numerical ID of the MIDI instrument map.
	 * @param name The new name for the specified MIDI instrument map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>mapId</code> is not a valid MIDI
	 * instrument map number or <code>name</code> is not a valid name;
	 */
	public synchronized void
	setMidiInstrumentMapName(int mapId, String name)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		name = toEscapedText(name);
		out.writeLine("SET MIDI_INSTRUMENT_MAP NAME " +  + mapId + " '" + name + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	
	
	/**
	 * Creates or replaces a MIDI instrument map entry.
	 * @param mapId The ID of the map, where this instrument should be mapped.
	 * @param entry Specifies the position of the MIDI instrument in the MIDI instrument map.
	 * @param info Provides the needed information of the
	 * MIDI instrument, which will be mapped to the specified MIDI instrument map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the mapping failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #unmapMidiInstrument
	 */
	public synchronized void
	mapMidiInstrument(int mapId, MidiInstrumentEntry entry, MidiInstrumentInfo info) 
					throws IOException, LSException, LscpException {
		mapMidiInstrument(mapId, entry, info, false);
	}
	
	/**
	 * Creates or replaces a MIDI instrument map entry.
	 * @param mapId The ID of the map, where this instrument should be mapped.
	 * @param entry Specifies the position of the MIDI instrument in the MIDI instrument map.
	 * @param info Provides the needed information of the
	 * MIDI instrument, which will be mapped to the specified MIDI instrument map.
	 * @param nonModal If <code>true</code> the function returns immediately
	 * and the mapping is established in the background.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the mapping failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #unmapMidiInstrument
	 */
	public synchronized void
	mapMidiInstrument(int mapId, MidiInstrumentEntry entry, MidiInstrumentInfo info, boolean nonModal) 
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		StringBuffer cmd = new StringBuffer("MAP MIDI_INSTRUMENT ");
		if(nonModal) cmd.append("NON_MODAL ");
		cmd.append(mapId).append(' ');
		cmd.append(entry.getMidiBank()).append(' ');
		cmd.append(entry.getMidiProgram()).append(' ');
		cmd.append(info.getEngine()).append(" '");
		cmd.append(conv(info.getFilePath())).append("' ");
		cmd.append(info.getInstrumentIndex()).append(' ');
		cmd.append(info.getVolume());
		if(!info.getLoadMode().name().equals("DEFAULT")) {
			cmd.append(' ').append(info.getLoadMode().name());
		}
		
		if(info.getName() != null) {
			String s = toEscapedText(info.getName());
			cmd.append(" '").append(s).append("'");
		}
		
		out.writeLine(cmd.toString());
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Removes an entry MIDI instrument map.
	 * @param mapId The ID of the map, from which
	 * the specified MIDI instrument should be removed.
	 * @param entry The entry to remove from the specified MIDI instrument map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the unmapping failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #mapMidiInstrument
	 */
	public synchronized void
	unmapMidiInstrument(int mapId, MidiInstrumentEntry entry) 
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		StringBuffer cmd = new StringBuffer("UNMAP MIDI_INSTRUMENT ");
		cmd.append(mapId).append(' ');
		cmd.append(entry.getMidiBank()).append(' ');
		cmd.append(entry.getMidiProgram());
		
		out.writeLine(cmd.toString());
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of all MIDI instrument in all maps.
	 * @return The current number of all MIDI instrument in all maps.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getMidiInstrumentCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INSTRUMENTS ALL");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets the current number of MIDI instrument in the specified map.
	 * @param mapId The ID of the map.
	 * @return The current number of MIDI instrument in the specified map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getMidiInstrumentCount(int mapId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET MIDI_INSTRUMENTS " + String.valueOf(mapId));
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets all MIDI instrument from all maps.
	 * @return A <code>MidiInstrumentInfo</code> array providing
	 * all MIDI instruments from all MIDI instrument maps.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized MidiInstrumentInfo[]
	getMidiInstruments() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST MIDI_INSTRUMENTS ALL");
		if(getPrintOnlyMode()) return null;
		
		String[] entries = parseArray(getSingleLineResultSet().getResult());
		
		return getMidiInstruments(entries);
	}
	
	/**
	 * Gets all MIDI instrument entries contained int the specified MIDI instrument map.
	 * @param mapId The ID of the map, which instruments should be obtained.
	 * @return An int array providing all MIDI instrument entries
	 * in the specified MIDI instrument map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int[][]
	getMidiInstrumentEntries(int mapId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST MIDI_INSTRUMENTS " + String.valueOf(mapId));
		if(getPrintOnlyMode()) return null;
		
		String[] entries = parseArray(getSingleLineResultSet().getResult());
		int[][] e = new int[entries.length][3];
		
		for(int i = 0; i < entries.length; i++) {
			Integer[] vals = parseIntList(entries[i]);
			if(vals.length != 3) {
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			}
			
			e[i][0] = vals[0];
			e[i][1] = vals[1];
			e[i][2] = vals[2];
		}
		
		return e;
	}
	
	/**
	 * Gets all MIDI instruments contained int the specified MIDI instrument map.
	 * @param mapId The ID of the map, which instruments should be obtained.
	 * @return A <code>MidiInstrumentInfo</code> array providing
	 * all MIDI instruments in the specified MIDI instrument map.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized MidiInstrumentInfo[]
	getMidiInstruments(int mapId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST MIDI_INSTRUMENTS " + String.valueOf(mapId));
		if(getPrintOnlyMode()) return null;
		
		String[] entries = parseArray(getSingleLineResultSet().getResult());
		
		return getMidiInstruments(entries);
	}
	
	private MidiInstrumentInfo[]
	getMidiInstruments(String[] entries) throws IOException, LscpException, LSException {
		Vector<MidiInstrumentInfo> v = new Vector<MidiInstrumentInfo>();
		
		for(String s : entries) {
			Integer[] vals = parseIntList(s);
			if(vals.length != 3) {
				throw new LscpException(LscpI18n.getLogMsg("CommandFailed!"));
			}
			
			v.add(getMidiInstrumentInfo(vals[0], vals[1], vals[2]));
		}
		
		return v.toArray(new MidiInstrumentInfo[v.size()]);
	}
	
	/**
	 * Gets the current settings of the specified MIDI instrument.
	 * @param mapId The ID of the map.
	 * @param bank The index of the MIDI bank.
	 * @param program The MIDI program number of the instrument.
	 * @return <code>MidiInstrumentInfo</code> instance containing
	 * the current settings of the specified MIDI instrument.
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified MIDI instrument is missing.
	 */
	public synchronized MidiInstrumentInfo
	getMidiInstrumentInfo(int mapId, int bank, int program)
					throws IOException, LscpException, LSException {
	
		verifyConnection();
		requestMidiInstrumentInfo(mapId, bank, program);
		return getMidiInstrumentInfoResponse(mapId, bank, program);
	}
	
	private void
	requestMidiInstrumentInfo(int mapId, int bank, int program) throws IOException {
		StringBuffer cmd = new StringBuffer("GET MIDI_INSTRUMENT INFO ");
		cmd.append(mapId).append(' ');
		cmd.append(bank).append(' ');
		cmd.append(program);
		
		out.writeLine(cmd.toString());
	}
	
	private MidiInstrumentInfo
	getMidiInstrumentInfoResponse(int mapId, int bank, int program)
					throws IOException, LscpException, LSException {
		
		if(getPrintOnlyMode()) return null;
		ResultSet rs = getMultiLineResultSet();
		MidiInstrumentEntry entry = new MidiInstrumentEntry(bank, program);
		return new MidiInstrumentInfo(mapId, entry, rs.getMultiLineResult());
	}
	
	/**
	 * Loads and assigns an instrument to a sampler channel. Notice that this function will
	 * return after the instrument is fully loaded and the channel is ready to be used.
	 * @param filename The name of the instrument file
	 * on the LinuxSampler instance's host system.
	 * @param instrIdx The index of the instrument in the instrument file.
	 * @param samplerChn The number of the sampler channel the instrument should be assigned to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the loading of the instrument failed.
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
		String args = '\'' + conv(filename) + "' " + instrIdx + ' ' + samplerChn;
		
		out.writeLine(cmd + args);
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list of all created sampler channels.
	 * @return A <code>SamplerChannel</code> array providing all created sampler channels.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #addSamplerChannel
	 * @see #removeSamplerChannel
	 */
	public synchronized SamplerChannel[]
	getSamplerChannels() throws IOException, LscpException, LSException {
		Integer[] idS = getSamplerChannelIDs();
		if(getPrintOnlyMode()) return null;
		
		SamplerChannel[] channels = new SamplerChannel[idS.length];
		
		for(int i = 0; i < channels.length; i++)
			channels[i] = getSamplerChannelInfo(idS[i]);
		
		return channels;
	}
	
	/**
	 * Gets a list with numerical IDs of all created sampler channels.
	 * @return An <code>Integer</code> array providing
	 * the numerical IDs of all created sampler channels.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #addSamplerChannel
	 * @see #removeSamplerChannel
	 */
	public synchronized Integer[]
	getSamplerChannelIDs() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST CHANNELS");
		if(getPrintOnlyMode()) return null;
		
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
		if(getPrintOnlyMode()) return -1;
		
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
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return -1;
		
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
		if(getPrintOnlyMode()) return null;
		
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
		if(getPrintOnlyMode()) return null;
		
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
		if(getPrintOnlyMode()) return null;
		
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
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		SamplerChannel sc = new SamplerChannel(rs.getMultiLineResult());
		sc.setChannelId(samplerChn);
		if(sc.getEngine() != null) sc.setEngine(getEngineInfo(sc.getEngine().getName()));
		
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
		if(getPrintOnlyMode()) return -1;
		
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
		if(getPrintOnlyMode()) return -1;
	
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
		if(getPrintOnlyMode()) return null;
		
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
			bf.setStreamId(parseInt(s.substring(1, i)));
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
		if(getPrintOnlyMode()) return null;
		
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
			bf.setStreamId(parseInt(s.substring(1, i)));
			bf.setValue(parseInt(s.substring(i + 1, s.length() - 1)));
			v.add(bf);
		}
		
		return v;
	}
	
	/**
	 * Sets the audio output device on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param devId The numerical ID of the audio output device.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>samplerChn</code> is not a valid channel number;
	 * <li><code>devId</code> is not a valid audio output device ID;
	 * </ul>
	 *
	 * @see #getSamplerChannels
	 * @see #getAudioOutputDevices
	 */
	public synchronized void
	setChannelAudioOutputDevice(int samplerChn, int devId)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("SET CHANNEL AUDIO_OUTPUT_DEVICE " + samplerChn + ' ' + devId);
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the MIDI input device on the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param devId The numerical ID of the MIDI input device.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>samplerChn</code> is not a valid channel number;
	 * <li><code>devId</code> is not a valid MIDI input device ID;
	 * </ul>
	 *
	 * @see #getSamplerChannels
	 * @see #getMidiInputDevices
	 */
	public synchronized void
	setChannelMidiInputDevice(int samplerChn, int devId)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("SET CHANNEL MIDI_INPUT_DEVICE " + samplerChn + ' ' + devId);
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the MIDI instrument map to be used on the specified sampler channel.
	 * 
	 * @param samplerChn The sampler channel number.
	 * @param mapId Specifies the numerical ID of the MIDI instrument
	 * map to assign. To remove the current map binding use <code>-1</code>.
	 * To set the current map to be the default map use <code>-2</code>.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>samplerChn</code> is not a valid channel number;
	 * <li><code>mapId</code> is not a valid MIDI instrument map ID;
	 * </ul>
	 *
	 * @see #getSamplerChannels
	 * @see #getMidiInstrumentMaps
	 */
	public synchronized void
	setChannelMidiInstrumentMap(int samplerChn, int mapId)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String s;
		if(mapId == -1) {
			s = " NONE";
		} else if(mapId == -2) {
			s = " DEFAULT";
		} else {
			s = " " + String.valueOf(mapId);
		}
		out.writeLine("SET CHANNEL MIDI_INSTRUMENT_MAP " + samplerChn + s);
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Mute/unmute the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param mute If <code>true</code> the specified channel is muted, else the channel
	 * is unmuted.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number or if
	 * there is no engine assigned yet to the specified sampler channel.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	setChannelMute(int samplerChn, boolean mute)
				throws IOException, LscpException, LSException {
	
		verifyConnection();
		out.writeLine("SET CHANNEL MUTE " + samplerChn + ' ' + (mute ? 1 : 0));
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Solo/unsolo the specified sampler channel.
	 *
	 * @param samplerChn The sampler channel number.
	 * @param solo <code>true</code> to solo the specified channel, <code>false</code> 
	 * otherwise.
	 * 
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number or if
	 * there is no engine assigned yet to the specified sampler channel.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	setChannelSolo(int samplerChn, boolean solo)
				throws IOException, LscpException, LSException {
	
		verifyConnection();
		out.writeLine("SET CHANNEL SOLO " + samplerChn + ' ' + (solo ? 1 : 0));
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Creates an additional effect send on the specified sampler channel.
	 * @param channel The sampler channel, on which a new effect send should be added.
	 * @param midiCtrl Defines the MIDI controller, which
	 * will be able alter the effect send level.
	 * @return The unique ID of the newly created effect send entity.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the effect send failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #destroyFxSend
	 */
	public synchronized int
	createFxSend(int channel, int midiCtrl)
			throws IOException, LSException, LscpException {
		
		return createFxSend(channel, midiCtrl, null);
	}
	
	/**
	 * Creates an additional effect send on the specified sampler channel.
	 * @param channel The sampler channel, on which the effect send should be created on.
	 * @param midiCtrl Defines the MIDI controller, which can alter the effect send level.
	 * @param name The name of the effect send entity. The name does not have to be unique.
	 * @return The unique ID of the newly created effect send entity.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the effect send failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #destroyFxSend
	 */
	public synchronized int
	createFxSend(int channel, int midiCtrl, String name)
			throws IOException, LSException, LscpException {
		
		verifyConnection();
		String s = String.valueOf(channel) + " " + String.valueOf(midiCtrl);
		if(name != null) s += " '" + toEscapedText(name) + "'";
		out.writeLine("CREATE FX_SEND " + s);
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		
		return rs.getIndex();
	}
	
	/**
	 * Destroys the specified effect send on the specified sampler channel.
	 * @param channel The sampler channel, from which
	 * the specified effect send should be removed.
	 * @param fxSend The ID of the effect send that should be removed.
	 * @throws LSException If some other error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #createFxSend
	 */
	public synchronized void
	destroyFxSend(int channel, int fxSend)
			throws IOException, LSException, LscpException {
		
		verifyConnection();
		String s = String.valueOf(channel) + " " + String.valueOf(fxSend);
		out.writeLine("DESTROY FX_SEND " + s);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the current number of effect sends on the specified sampler channel.
	 * @param channel The ID of the sampler channel.
	 * @return The current number of effect sends on the specified sampler channels.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getFxSoundCount(int channel) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET FX_SENDS " + String.valueOf(channel));
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets a list of all created effect sends on the specified sampler channel.
	 * @param channel The sampler channel number.
	 * @return A <code>FxSend</code> array providing all created
	 * effect sends on the specified sampler channel.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>channel</code> is not a valid sampler channel ID.
	 * @see #createFxSend
	 * @see #destroyFxSend
	 */
	public synchronized FxSend[]
	getFxSends(int channel) throws IOException, LscpException, LSException {
		Integer[] idS = getFxSendIDs(channel);
		if(getPrintOnlyMode()) return null;
		
		FxSend[] fxSends = new FxSend[idS.length];
		
		for(int i = 0; i < fxSends.length; i++)
			fxSends[i] = getFxSendInfo(channel, idS[i]);
		
		return fxSends;
	}
	
	/**
	 * Gets a list of effect sends on the specified sampler channel.
	 * @param channel The sampler channel number.
	 * @return An <code>Integer</code> array providing
	 * the numerical IDs of all effect sends on the specified sampler channel.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>channel</code> is not a valid sampler channel ID.
	 * @see #createFxSend
	 * @see #destroyFxSend
	 */
	public synchronized Integer[]
	getFxSendIDs(int channel) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST FX_SENDS " + channel);
		if(getPrintOnlyMode()) return null;
		
		return parseIntList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets the current settings of the specified effect send entity.
	 * @param channel The sampler channel number.
	 * @param fxSend The numerical ID of the effect send entity.
	 * @return <code>FxSend</code> instance containing
	 * the current settings of the specified effect send entity.
	 * @throws IOException If an I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the sampler channel and/or the effect send number are invalid.
	 */
	public synchronized FxSend
	getFxSendInfo(int channel, int fxSend) throws IOException, LscpException, LSException {
		verifyConnection();
		String s = String.valueOf(channel) + " " + String.valueOf(fxSend);
		out.writeLine("GET FX_SEND INFO " + s);
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		FxSend fxs = new FxSend(rs.getMultiLineResult());
		fxs.setFxSendId(fxSend);
		
		return fxs;
	}
	
	/**
	 * Sets the name of the specified effect send.
	 * @param channel The sampler channel number.
	 * @param fxSend The numerical ID of the effect send entity.
	 * @param name The new name for the specified effect send.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>channel</code> is not a valid channel
	 * number or <code>fxSend</code> is not a valid effect send ID;
	 */
	public synchronized void
	setFxSendName(int channel, int fxSend, String name)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = " " + channel + " " + fxSend + " '" + toEscapedText(name) + "'";
		out.writeLine("SET FX_SEND NAME" + args);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the destination of an effect send's audio channel in the specified sampler channel.
	 * @param channel The sampler channel number.
	 * @param fxSend The numerical ID of the effect send entity to be rerouted.
	 * @param audioSrc The numerical ID of the effect send's audio output channel,
	 * which should be rerouted.
	 * @param audioDst The audio channel of the selected audio output device
	 * where <code>audioSrc</code> should be routed to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>channel</code> is not a valid channel number;
	 * <li><code>fxSend</code> is not a valid effect send ID;
	 * <li>There is no engine assigned yet to the specified sampler channel;
	 * <li>There is no audio output device connected to the specified sampler channel.
	 * </ul>
	 */
	public synchronized void
	setFxSendAudioOutputChannel(int channel, int fxSend, int audioSrc, int audioDst)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = " " + channel + " " + fxSend + " " + audioSrc + " " + audioDst;
		out.writeLine("SET FX_SEND AUDIO_OUTPUT_CHANNEL" + args);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the MIDI controller, which will be able to modify
	 * the send level of the specified effect send in the specified sampler channel.
	 * @param channel The sampler channel number.
	 * @param fxSend The numerical ID of the effect send entity.
	 * @param midiCtrl The MIDI controller which shall be
	 * able to modify the effect send's send level.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If 
	 * <ul>
	 * <li><code>channel</code> is not a valid channel number;
	 * <li><code>fxSend</code> is not a valid effect send ID;
	 * <li><code>midiCtrl</code> is not a valid controller;
	 * </ul>
	 */
	public synchronized void
	setFxSendMidiController(int channel, int fxSend, int midiCtrl)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = " " + channel + " " + fxSend + " " + midiCtrl;
		out.writeLine("SET FX_SEND MIDI_CONTROLLER" + args);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sets the current send level of the specified
	 * effect send entity in the specified sampler channel.
	 * @param channel The sampler channel number.
	 * @param fxSend The numerical ID of the effect send entity.
	 * @param volume The new volume value (a value smaller than 1.0 means
	 * attenuation, whereas a value greater than 1.0 means amplification).
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized void
	setFxSendLevel(int channel, int fxSend, float volume)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String args = " " + channel + " " + fxSend + " " + String.valueOf(volume);
		out.writeLine("SET FX_SEND LEVEL" + args);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Starts an instrument editor for editing the loaded instrument
	 * on the specified sampler channel.
	 * @param samplerChn The sampler channel number.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number or if
	 * there is no instrument loaded on the specified sampler channel.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	editChannelInstrument(int samplerChn) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("EDIT CHANNEL INSTRUMENT " + samplerChn);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Sends a MIDI event to this sampler channel.
	 * @param samplerChn The sampler channel number.
	 * @param type The type of MIDI message to send.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If <code>samplerChn</code> is not a valid channel number or if
	 * there is no instrument loaded on the specified sampler channel.
	 * @see #getSamplerChannels
	 */
	public synchronized void
	sendChannelMidiData(int samplerChn, MidiDataEvent.Type type, int arg1, int arg2)
						throws IOException, LscpException, LSException {
		
		verifyConnection();
		StringBuffer sb = new StringBuffer();
		sb.append("SEND CHANNEL MIDI_DATA ");
		sb.append(type).append(" ").append(samplerChn).append(" ");
		sb.append(arg1).append(" ").append(arg2);
		
		out.writeLine(sb.toString());
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	
	
	/**
	 * Adds the specified directory to the instruments database.
	 * @param dir The absolute (escaped) path name of the directory to add.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the creation of the directory failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	addDbDirectory(String dir) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("ADD DB_INSTRUMENT_DIRECTORY '" + conv(dir) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Removes the specified directory from the instruments database.
	 * @param dir The absolute (escaped) path name of the directory to remove.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified directory is not
	 * empty or if the removal of the directory failed.
	 */
	public synchronized void
	removeDbDirectory(String dir) throws IOException, LscpException, LSException {
		removeDbDirectory(dir, false);
	}
	
	/**
	 * Removes the specified directory from the instruments database.
	 * @param dir The absolute path name of the directory to remove.
	 * @param force If <code>true</code> forces the removal of non-empty
	 * directory and all its content.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the directory failed.
	 */
	public synchronized void
	removeDbDirectory(String dir, boolean force)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String s = "REMOVE DB_INSTRUMENT_DIRECTORY ";
		if(force) s += "FORCE ";
		out.writeLine(s + "'" + conv(dir) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Removes the specified directories from the instruments database.
	 * @param dirs The absolute (escaped) path names of the directories to remove.
	 * @param force If <code>true</code> forces the removal of non-empty
	 * directories.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the directores failed.
	 */
	public synchronized void
	removeDbDirectories(String[] dirs, boolean force)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String cmd = "REMOVE DB_INSTRUMENT_DIRECTORY ";
		if(force) cmd += "FORCE ";
		
		for(String s : dirs) out.writeLine(cmd + "'" + conv(s) + "'");
		
		if(getPrintOnlyMode()) return;
		
		getEmptyResultSets(dirs.length, "Client.dirDeletionFailed!");
	}
	
	/**
	 * Gets the number of directories in the specified directory.
	 * @return The current number of directories in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getDbDirectoryCount(String dir) throws IOException, LscpException, LSException {
		return getDbDirectoryCount(dir, false);
	}
	
	/**
	 * Gets the number of directories in the specified directory.
	 * @return The current number of directories in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @param recursive If <code>true</code>, the number of all directories
	 * in the specified subtree will be returned.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getDbDirectoryCount(String dir, boolean recursive)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String s;
		if(recursive) s = "GET DB_INSTRUMENT_DIRECTORIES RECURSIVE '";
		else s = "GET DB_INSTRUMENT_DIRECTORIES '";
		out.writeLine(s + conv(dir) + "'");
		if(getPrintOnlyMode()) return -1;
		
		s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets the list of directories in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>String</code> array providing the names of
	 * all directories in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized String[]
	getDbDirectoryNames(String dir) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST DB_INSTRUMENT_DIRECTORIES '" + conv(dir) + "'");
		if(getPrintOnlyMode()) return null;
		
		String[] names = parseEscapedStringList(getSingleLineResultSet().getResult());
		for(int i = 0; i < names.length; i++) {
			names[i] = toNonEscapedString(names[i]);
		}
		return names;
	}
	
	/**
	 * Gets information about the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>DbDirectoryInfo</code> instance providing information
	 * about the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified directory is not found.
	 */
	public synchronized DbDirectoryInfo
	getDbDirectoryInfo(String dir) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET DB_INSTRUMENT_DIRECTORY INFO '" + conv(dir) + "'");
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		DbDirectoryInfo info = new DbDirectoryInfo(rs.getMultiLineResult());
		if(dir.equals("/")) {
			info.setName("/");
		} else {
			dir = removeEndingFileSeparator(dir);
		}
		String s = getFileName(dir);
		if(s != null) info.setName(toNonEscapedFileName(s));
		s = getParentDirectory(dir);
		if(s != null) info.setParentDirectoryPath(s);
		
		return info;
	}
	
	/**
	 * Gets the list of directories in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>DbDirectoryInfo</code> array providing
	 * information about all directories in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized DbDirectoryInfo[]
	getDbDirectories(String dir) throws IOException, LscpException, LSException {
		String[] dirS = getDbDirectoryNames(dir);
		if(!hasEndingFileSeparator(dir)) dir += "/";
		DbDirectoryInfo[] infoS = new DbDirectoryInfo[dirS.length];
		for(int i = 0; i < dirS.length; i++) {
			infoS[i] = getDbDirectoryInfo(conv(dir) + toEscapedFsEntry(dirS[i]));
		}
		return infoS;
	}
	
	/**
	 * Gets the list of directories in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>DbDirectoryInfo</code> array providing
	 * information about all directories in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 *
	public synchronized DbDirectoryInfo[]
	getDbDirectories(String dir) throws IOException, LscpException, LSException {
		String[] dirS = getDbDirectoryNames(conv(dir));
		if(dirS.length == 0) return new DbDirectoryInfo[0];
		
		if(dir.charAt(dir.length() - 1) != '/') dir += "/"; // FIXME: 
		
		for(int i = 0; i < dirS.length; i++) {
			out.writeLine("GET DB_INSTRUMENT_DIRECTORY INFO '" + conv(dir + dirS[i]) + "'");
		}
		
		if(getPrintOnlyMode()) return null;
		
		if(dir.length() > 1) dir = dir.substring(0, dir.length() - 1);
		StringBuffer sb = new StringBuffer();
		DbDirectoryInfo[] infoS = new DbDirectoryInfo[dirS.length];
		for(int i = 0; i < dirS.length; i++) {
			try {
				ResultSet rs = getMultiLineResultSet();
				infoS[i] = new DbDirectoryInfo(rs.getMultiLineResult());
				infoS[i].setName(dirS[i]);
				infoS[i].setParentDirectoryPath(dir);
			} catch (SocketTimeoutException e) {
				getLogger().log(Level.FINE, e.getMessage(), e);
				sb.append(e.getMessage()).append("\n");
				break;
			} catch (Exception e) {
				getLogger().log(Level.FINE, e.getMessage(), e);
				sb.append(e.getMessage()).append("\n");
			}
		}
		
		String details = sb.toString();
		if(details.length() > 0) {
			String err = LscpI18n.getLogMsg("Client.getInstrsInfoFailed!");
			throw new LSException(0, err, details);
		}
		
		return infoS;
	}*/
	
	/**
	 * Renames the specified directory.
	 * @param dir The absolute path name of the directory to rename.
	 * @param name The new name for the directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the renaming of the directory failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	renameDbDirectory(String dir, String name) throws IOException, LSException, LscpException {
		verifyConnection();
		name = toEscapedText(name);
		out.writeLine("SET DB_INSTRUMENT_DIRECTORY NAME '" + conv(dir) + "' '" + conv(name) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Moves the specified directory into the specified location.
	 * @param dir The absolute path name of the directory to move.
	 * @param dst The location where the directory will be moved to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	moveDbDirectory(String dir, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("MOVE DB_INSTRUMENT_DIRECTORY '" + conv(dir) + "' '" + conv(dst) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Moves the specified directories into the specified location.
	 * @param dirs The absolute path names of the directories to move.
	 * @param dst The location where the directories will be moved to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	moveDbDirectories(String dirs[], String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		for(String s : dirs) {
			out.writeLine("MOVE DB_INSTRUMENT_DIRECTORY '" + conv(s) + "' '" + conv(dst) + "'");
		}
		if(getPrintOnlyMode()) return;
		
		getEmptyResultSets(dirs.length, "Client.dirMovingFailed!");
	}
	
	/**
	 * Copies the specified directory into the specified location.
	 * @param dir The absolute path name of the directory to copy.
	 * @param dst The location where the directory will be copied to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	copyDbDirectory(String dir, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("COPY DB_INSTRUMENT_DIRECTORY '" + conv(dir) + "' '" + conv(dst) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Copies the specified directories into the specified location.
	 * @param dirs The absolute path names of the directories to copy.
	 * @param dst The location where the directories will be copied to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	copyDbDirectories(String[] dirs, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		for(String s : dirs) {
			out.writeLine("COPY DB_INSTRUMENT_DIRECTORY '" + conv(s) + "' '" + conv(dst) + "'");
		}
		if(getPrintOnlyMode()) return;
		
		getEmptyResultSets(dirs.length, "Client.dirCopyingFailed!");
	}
	
	/**
	 * Changes the description of the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @param desc The new description for the directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If failed to change the description.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	setDbDirectoryDescription(String dir, String desc)
				throws IOException, LSException, LscpException {
		
		verifyConnection();
		String s = "SET DB_INSTRUMENT_DIRECTORY DESCRIPTION '";
		out.writeLine(s + conv(dir) + "' '" + toEscapedText(desc) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	public static enum ScanMode {
		RECURSIVE, NON_RECURSIVE, FLAT
	}
	
	/**
	 * Adds the specified instrument to the specified instruments database directory.
	 * @param dbDir The absolute path name of the database directory in which the
	 * specified instrument will be added.
	 * @param filePath The absolute path name of the instrument file.
	 * @param instrIndex The index of the instrument (in the given instrument file) to add.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	addDbInstrument(String dbDir, String filePath, int instrIndex)
					throws IOException, LSException, LscpException {
		
		addDbInstrument(dbDir, filePath, instrIndex, false);
	}
	
	/**
	 * Adds the specified instrument to the specified instruments database directory.
	 * @param dbDir The absolute path name of the database directory in which the
	 * specified instrument will be added.
	 * @param filePath The absolute path name of the instrument file.
	 * @param instrIndex The index of the instrument (in the given instrument file) to add.
	 * @param background If <code>true</code>, the scan will be done
	 * in background and this method may return before the job is finished.
	 * @return If <code>background</code> is <code>true</code>, the ID
	 * of the scan job.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #addInstrumentsDbListener
	 */
	public synchronized int
	addDbInstrument(String dbDir, String filePath, int instrIndex, boolean background)
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		String s = "ADD DB_INSTRUMENTS";
		if(background) s += " NON_MODAL";
		s += " '" + conv(dbDir) + "' '" + conv(filePath) + "' ";
		out.writeLine(s + String.valueOf(instrIndex));
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		return rs.getIndex();
	}
	
	/**
	 * Adds the instruments in the specified file to the specified
	 * instruments database directory.
	 * @param dbDir The absolute path name of the database directory
	 * in which the the supported instruments will be added.
	 * @param filePath The absolute path name of the file to scan for instruments.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	addDbInstruments(String dbDir, String filePath)
					throws IOException, LSException, LscpException {
		
		addDbInstruments(dbDir, filePath, false);
	}
	
	/**
	 * Adds the instruments in the specified file to the specified
	 * instruments database directory.
	 * @param dbDir The absolute path name of the database directory
	 * in which the the supported instruments will be added.
	 * @param filePath The absolute path name of the file to scan for instruments.
	 * @param background If <code>true</code>, the scan will be done
	 * in background and this method may return before the job is finished.
	 * @return If <code>background</code> is <code>true</code>, the ID
	 * of the scan job.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #addInstrumentsDbListener
	 */
	public synchronized int
	addDbInstruments(String dbDir, String filePath, boolean background)
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		String s = "ADD DB_INSTRUMENTS";
		if(background) s += " NON_MODAL";
		out.writeLine(s + " '" + conv(dbDir) + "' '" + conv(filePath) + "'");
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		return rs.getIndex();
	}
	
	/**
	 * Adds the instruments in the specified file system directory
	 * to the specified instruments database directory.
	 * @param mode Determines the scanning mode. If RECURSIVE is
	 * specified, all supported instruments in the specified file system
	 * direcotry will be added to the specified instruments database
	 * directory, including the instruments in subdirectories
	 * of the supplied directory. If NON_RECURSIVE is specified,
	 * the instruments in the subdirectories will not be processed.
	 * If FLAT is specified, all supported instruments in the specified
	 * file system direcotry will be added, including the instruments in
	 * subdirectories of the supplied directory, but the respective
	 * subdirectory structure will not be recreated in the instruments
	 * database and all instruments will be added directly in the
	 * specified database directory.
	 * @param dbDir The absolute path name of the database directory
	 * in which the supported instruments will be added.
	 * @param fsDir The absolute path name of the file system directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	addDbInstruments(ScanMode mode, String dbDir, String fsDir)
					throws IOException, LSException, LscpException {
		
		addDbInstruments(mode, dbDir, fsDir, false);
	}
	
	/**
	 * Adds the instruments in the specified file system directory
	 * to the specified instruments database directory.
	 * @param mode Determines the scanning mode. If RECURSIVE is
	 * specified, all supported instruments in the specified file system
	 * direcotry will be added to the specified instruments database
	 * directory, including the instruments in subdirectories
	 * of the supplied directory. If NON_RECURSIVE is specified,
	 * the instruments in the subdirectories will not be processed.
	 * If FLAT is specified, all supported instruments in the specified
	 * file system direcotry will be added, including the instruments in
	 * subdirectories of the supplied directory, but the respective
	 * subdirectory structure will not be recreated in the instruments
	 * database and all instruments will be added directly in the
	 * specified database directory.
	 * @param dbDir The absolute path name of the database directory
	 * in which the supported instruments will be added.
	 * @param fsDir The absolute path name of the file system directory.
	 * @param background If <code>true</code>, the scan will be done
	 * in background and this method may return before the job is finished.
	 * @return If <code>background</code> is <code>true</code>, the ID
	 * of the scan job.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #addInstrumentsDbListener
	 */
	public synchronized int
	addDbInstruments(ScanMode mode, String dbDir, String fsDir, boolean background)
					throws IOException, LSException, LscpException {
		
		return addDbInstruments(mode, dbDir, fsDir, background, false);
	}
	
	/**
	 * Adds the instruments in the specified file system directory
	 * to the specified instruments database directory.
	 * @param mode Determines the scanning mode. If RECURSIVE is
	 * specified, all supported instruments in the specified file system
	 * direcotry will be added to the specified instruments database
	 * directory, including the instruments in subdirectories
	 * of the supplied directory. If NON_RECURSIVE is specified,
	 * the instruments in the subdirectories will not be processed.
	 * If FLAT is specified, all supported instruments in the specified
	 * file system direcotry will be added, including the instruments in
	 * subdirectories of the supplied directory, but the respective
	 * subdirectory structure will not be recreated in the instruments
	 * database and all instruments will be added directly in the
	 * specified database directory.
	 * @param dbDir The absolute path name of the database directory
	 * in which the supported instruments will be added.
	 * @param fsDir The absolute path name of the file system directory.
	 * @param background If <code>true</code>, the scan will be done
	 * in background and this method may return before the job is finished.
	 * @param insDir If <code>true</code> a drieectory is created for each
	 * instrument file.
	 * @return If <code>background</code> is <code>true</code>, the ID
	 * of the scan job.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @see #addInstrumentsDbListener
	 */
	public synchronized int
	addDbInstruments(ScanMode mode, String dbDir, String fsDir, boolean background, boolean insDir)
					throws IOException, LSException, LscpException {
		
		verifyConnection();
		StringBuffer sb = new StringBuffer("ADD DB_INSTRUMENTS");
		if(background) sb.append(" NON_MODAL");
		
		switch(mode) {
			case RECURSIVE:
				sb.append(" RECURSIVE");
				break;
			case NON_RECURSIVE:
				sb.append(" NON_RECURSIVE");
				break;
			case FLAT:
				sb.append(" FLAT");
				break;
		}
		if(insDir)
			sb.append(" FILE_AS_DIR");
		
		sb.append(" '").append(conv(dbDir)).append("' '");
		sb.append(conv(fsDir)).append("'");
		out.writeLine(sb.toString());
		if(getPrintOnlyMode()) return -1;
		
		ResultSet rs = getEmptyResultSet();
		return rs.getIndex();
	}

	/**
	 * Removes the specified instrument from the instruments database.
	 * @param instr The absolute path name of the instrument to remove.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the instrument failed.
	 */
	public synchronized void
	removeDbInstrument(String instr) throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("REMOVE DB_INSTRUMENT '" + conv(instr) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Removes the specified instruments from the instruments database.
	 * @param instrs The absolute path names of the instruments to remove.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the removing of the instruments failed.
	 */
	public synchronized void
	removeDbInstruments(String[] instrs) throws IOException, LscpException, LSException {
		verifyConnection();
		for(String s : instrs) {
			out.writeLine("REMOVE DB_INSTRUMENT '" + conv(s) + "'");
		}
		if(getPrintOnlyMode()) return;
		
		getEmptyResultSets(instrs.length, "Client.instrDeletionFailed!");
	}
	
	/**
	 * Gets the number of instruments in the specified directory.
	 * @return The current number of instruments in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getDbInstrumentCount(String dir) throws IOException, LscpException, LSException {
		return getDbInstrumentCount(dir, false);
	}
	
	/**
	 * Gets the number of instruments in the specified directory.
	 * @return The current number of instruments in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @param recursive If <code>true</code>, the number of all instruments
	 * in the specified subtree will be returned.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getDbInstrumentCount(String dir, boolean recursive)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		String s;
		if(recursive) s = "GET DB_INSTRUMENTS RECURSIVE '";
		else s = "GET DB_INSTRUMENTS '";
		out.writeLine(s + conv(dir) + "'");
		if(getPrintOnlyMode()) return -1;
		
		s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets the list of instruments in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>String</code> array providing the names of
	 * all instruments in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized String[]
	getDbInstrumentNames(String dir) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("LIST DB_INSTRUMENTS '" + conv(dir) + "'");
		if(getPrintOnlyMode()) return null;
		
		String[] names = parseEscapedStringList(getSingleLineResultSet().getResult());
		for(int i = 0; i < names.length; i++) {
			names[i] = toNonEscapedString(names[i]);
		}
		return names;
	}
	
	/**
	 * Gets information about the specified instrument.
	 * @param instr The absolute path name of the instrument.
	 * @return A <code>DbInstrumentInfo</code> instance providing information
	 * about the specified instrument.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified instrument is not found.
	 */
	public synchronized DbInstrumentInfo
	getDbInstrumentInfo(String instr) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET DB_INSTRUMENT INFO '" + conv(instr) + "'");
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		DbInstrumentInfo info = new DbInstrumentInfo(rs.getMultiLineResult());
		String s = getParentDirectory(instr);
		if(s != null) info.setDirectoryPath(s);
		s = getFileName(instr);
		if(s != null) info.setName(toNonEscapedFileName(s));
		
		return info;
	}
	
	/**
	 * Gets the list of instruments in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>DbInstrumentInfo</code> array providing
	 * information about all instruments in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized DbInstrumentInfo[]
	getDbInstruments(String dir) throws IOException, LscpException, LSException {
		String[] instrS = getDbInstrumentNames(dir);
		if(!hasEndingFileSeparator(dir)) dir += "/";
		
		DbInstrumentInfo[] infoS = new DbInstrumentInfo[instrS.length];
		for(int i = 0; i < instrS.length; i++) {
			infoS[i] = getDbInstrumentInfo(conv(dir) + toEscapedFsEntry(instrS[i]));
		}
		return infoS;
	}
	
	/**
	 * Gets the list of instruments in the specified directory.
	 * @param dir The absolute path name of the directory.
	 * @return A <code>DbInstrumentInfo</code> array providing
	 * information about all instruments in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 *
	public synchronized DbInstrumentInfo[]
	getDbInstruments(String dir) throws IOException, LscpException, LSException {
		String[] instrS = getDbInstrumentNames(dir);
		if(instrS.length == 0) return new DbInstrumentInfo[0];
		
		if(dir.charAt(dir.length() - 1) != '/') dir += "/"; FIXME: 
		
		for(int i = 0; i < instrS.length; i++) {
			out.writeLine("GET DB_INSTRUMENT INFO '" + conv(dir) + instrS[i] + "'");
		}
		
		if(getPrintOnlyMode()) return null;
		
		if(dir.length() > 1) dir = dir.substring(0, dir.length() - 1);
		StringBuffer sb = new StringBuffer();
		DbInstrumentInfo[] infoS = new DbInstrumentInfo[instrS.length];
		for(int i = 0; i < instrS.length; i++) {
			try {
				ResultSet rs = getMultiLineResultSet();
				infoS[i] = new DbInstrumentInfo(rs.getMultiLineResult());
				infoS[i].setName(instrS[i]);
				infoS[i].setDirectoryPath(dir);
			} catch (SocketTimeoutException e) {
				getLogger().log(Level.FINE, e.getMessage(), e);
				sb.append(e.getMessage()).append("\n");
				break;
			} catch (Exception e) {
				getLogger().log(Level.FINE, e.getMessage(), e);
				sb.append(e.getMessage()).append("\n");
			}
		}
		
		String details = sb.toString();
		if(details.length() > 0) {
			String err = LscpI18n.getLogMsg("Client.getInstrsInfoFailed!");
			throw new LSException(0, err, details);
		}
		
		return infoS;
	}*/
	
	/**
	 * Renames the specified instrument.
	 * @param instr The absolute path name of the instrument to rename.
	 * @param name The new name for the instrument.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the renaming of the instrument failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	renameDbInstrument(String instr, String name)
				throws IOException, LSException, LscpException {
		
		verifyConnection();
		name = toEscapedText(name);
		out.writeLine("SET DB_INSTRUMENT NAME '" + conv(instr) + "' '" + conv(name) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Moves the specified instrument into the specified location.
	 * @param instr The absolute path name of the instrument to move.
	 * @param dst The directory where the specified instrument will be moved to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	moveDbInstrument(String instr, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("MOVE DB_INSTRUMENT '" + conv(instr) + "' '" + conv(dst) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Moves the specified instruments into the specified location.
	 * @param instrs The absolute path names of the instruments to move.
	 * @param dst The directory where the specified instruments will be moved to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	moveDbInstruments(String[] instrs, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		for(String s : instrs) {
			out.writeLine("MOVE DB_INSTRUMENT '" + conv(s) + "' '" + conv(dst) + "'");
		}
		if(getPrintOnlyMode()) return;
		
		getEmptyResultSets(instrs.length, "Client.instrMovingFailed!");
	}
	
	/**
	 * Copies the specified instrument into the specified location.
	 * @param instr The absolute path name of the instrument to copy.
	 * @param dst The directory where the specified instrument will be copied to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	copyDbInstrument(String instr, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		out.writeLine("COPY DB_INSTRUMENT '" + conv(instr) + "' '" + conv(dst) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Copies the specified instruments into the specified location.
	 * @param instrs The absolute path name of the instruments to copy.
	 * @param dst The directory where the specified instruments will be copied to.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	copyDbInstruments(String[] instrs, String dst) throws IOException, LSException, LscpException {
		verifyConnection();
		for(String s : instrs) {
			out.writeLine("COPY DB_INSTRUMENT '" + conv(s) + "' '" + conv(dst) + "'");
		}
		if(getPrintOnlyMode()) return;
		
		getEmptyResultSets(instrs.length, "Client.instrCopyingFailed!");
	}
	
	/**
	 * Changes the description of the specified instrument.
	 * @param instr The absolute path name of the instrument.
	 * @param desc The new description for the instrument.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If failed to change the description.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	setDbInstrumentDescription(String instr, String desc)
				throws IOException, LSException, LscpException {
		
		verifyConnection();
		desc = toEscapedText(desc);
		out.writeLine("SET DB_INSTRUMENT DESCRIPTION '" + conv(instr) + "' '" + desc + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Substitutes all occurrences of the instrument file
	 * <code>oldPath</code> in the database, with <code>newPath</code>.
	 * @param oldPath The absolute path name of the instrument file to substitute.
	 * @param newPath The new absolute path name.
	 * @throws IOException If some I/O error occurs.
	 * @throws LSException If the operation failed.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 */
	public synchronized void
	setDbInstrumentFilePath(String oldPath, String newPath)
				throws IOException, LSException, LscpException {
		
		verifyConnection();
		out.writeLine("SET DB_INSTRUMENT FILE_PATH '" + conv(oldPath) + "' '" + conv(newPath) + "'");
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Finds all directories in the specified directory
	 * that corresponds to the specified search criterias.
	 * @param dir The absolute path name of the directory to search.
	 * @param query Provides the search criterias.
	 * @return A <code>DbDirectoryInfo</code> array providing
	 * information about all directories that are found in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized DbDirectoryInfo[]
	findDbDirectories(String dir, DbSearchQuery query)
				throws IOException, LscpException, LSException {
		
		return findDbDirectories(dir, query, false);
	}
	
	/**
	 * Finds all directories in the specified directory
	 * that corresponds to the specified search criterias.
	 * @param dir The absolute path name of the directory to search.
	 * @param query Provides the search criterias.
	 * @param nonRecursive If <code>true</code>, the search will be non-recursive.
	 * @return A <code>DbDirectoryInfo</code> array providing
	 * information about all directories that are found in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized DbDirectoryInfo[]
	findDbDirectories(String dir, DbSearchQuery query, boolean nonRecursive)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		StringBuffer sb = new StringBuffer();
		sb.append("FIND DB_INSTRUMENT_DIRECTORIES");
		if(nonRecursive) sb.append(" NON_RECURSIVE");
		sb.append(" '").append(conv(dir)).append("'");
		
		if(query.name != null && query.name.length() > 0) {
			sb.append(" NAME='").append(toEscapedText(query.name)).append("'");
		}
		
		String s = query.getCreatedAfter();
		String s2 = query.getCreatedBefore();
		if(s != null || s2 != null) {
			sb.append(" CREATED='");
			if(s != null) sb.append(s);
			sb.append("..");
			if(s2 != null) sb.append(s2);
			sb.append("'");
		}
		
		s = query.getModifiedAfter();
		s2 = query.getModifiedBefore();
		if(s != null || s2 != null) {
			sb.append(" MODIFIED='");
			if(s != null) sb.append(s);
			sb.append("..");
			if(s2 != null) sb.append(s2);
			sb.append("'");
		}
		
		if(query.description != null && query.description.length() > 0) {
			sb.append(" DESCRIPTION='");
			sb.append(toEscapedText(query.description)).append("'");
		}
		
		out.writeLine(sb.toString());
		if(getPrintOnlyMode()) return null;
		
		String[] dirS = parseEscapedStringList(getSingleLineResultSet().getResult());
		
		DbDirectoryInfo[] infoS = new DbDirectoryInfo[dirS.length];
		for(int i = 0; i < dirS.length; i++) {
			infoS[i] = getDbDirectoryInfo(dirS[i]);
		}
		return infoS;
	}
	
	/**
	 * Finds all instruments in the specified directory
	 * that corresponds to the specified search criterias.
	 * @param dir The absolute path name of the directory to search.
	 * @param query Provides the search criterias.
	 * @return A <code>DbInstrumentInfo</code> array providing
	 * information about all instruments that are found in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized DbInstrumentInfo[]
	findDbInstruments(String dir, DbSearchQuery query)
				throws IOException, LscpException, LSException {
		
		return findDbInstruments(dir, query, false);
	}
	
	/**
	 * Finds all instruments in the specified directory
	 * that corresponds to the specified search criterias.
	 * @param dir The absolute path name of the directory to search.
	 * @param query Provides the search criterias.
	 * @param nonRecursive If <code>true</code>, the search will be non-recursive.
	 * @return A <code>DbInstrumentInfo</code> array providing
	 * information about all instruments that are found in the specified directory.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified path name is invalid.
	 */
	public synchronized DbInstrumentInfo[]
	findDbInstruments(String dir, DbSearchQuery query, boolean nonRecursive)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		StringBuffer sb = new StringBuffer();
		sb.append("FIND DB_INSTRUMENTS");
		if(nonRecursive) sb.append(" NON_RECURSIVE");
		sb.append(" '").append(conv(dir)).append("'");
		
		if(query.name != null && query.name.length() > 0) {
			sb.append(" NAME='").append(toEscapedText(query.name)).append("'");
		}
		
		if(query.formatFamilies.size() > 0) {
			sb.append(" FORMAT_FAMILIES='").append(query.formatFamilies.get(0));
			for(int i = 1; i < query.formatFamilies.size(); i++) {
				sb.append(',').append(query.formatFamilies.get(i));
			}
			sb.append("'");
		}
		
		if(query.minSize != -1 || query.maxSize != -1) {
			sb.append(" SIZE='");
			if(query.minSize != -1) sb.append(query.minSize);
			sb.append("..");
			if(query.maxSize != -1) sb.append(query.maxSize);
			sb.append("'");
		}
		
		String s = query.getCreatedAfter();
		String s2 = query.getCreatedBefore();
		if(s != null || s2 != null) {
			sb.append(" CREATED='");
			if(s != null) sb.append(s);
			sb.append("..");
			if(s2 != null) sb.append(s2);
			sb.append("'");
		}
		
		s = query.getModifiedAfter();
		s2 = query.getModifiedBefore();
		if(s != null || s2 != null) {
			sb.append(" MODIFIED='");
			if(s != null) sb.append(s);
			sb.append("..");
			if(s2 != null) sb.append(s2);
			sb.append("'");
		}
		
		if(query.description != null && query.description.length() > 0) {
			sb.append(" DESCRIPTION='");
			sb.append(toEscapedText(query.description)).append("'");
		}
		
		if(query.instrumentType != DbSearchQuery.InstrumentType.BOTH) {
			sb.append(" IS_DRUM=");
			if(query.instrumentType == DbSearchQuery.InstrumentType.DRUM) {
				sb.append("'true'");
			} else {
				sb.append("'false'");
			}
		}
		
		if(query.product != null && query.product.length() > 0) {
			sb.append(" PRODUCT='").append(toEscapedText(query.product)).append("'");
		}
		
		if(query.artists != null && query.artists.length() > 0) {
			sb.append(" ARTISTS='").append(toEscapedText(query.artists)).append("'");
		}
		
		if(query.keywords != null && query.keywords.length() > 0) {
			sb.append(" KEYWORDS='");
			sb.append(toEscapedText(query.keywords)).append("'");
		}
		
		out.writeLine(sb.toString());
		if(getPrintOnlyMode()) return null;
		
		String[] instrS = parseEscapedStringList(getSingleLineResultSet().getResult());
		
		DbInstrumentInfo[] infoS = new DbInstrumentInfo[instrS.length];
		for(int i = 0; i < instrS.length; i++) {
			infoS[i] = getDbInstrumentInfo(instrS[i]);
		}
		return infoS;
	}
	
	/**
	 * Returns a list of all instrument files in the database
	 * that that don't exist in the filesystem.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If other error occurs.
	 */
	public synchronized String[]
	findLostDbInstrumentFiles() throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("FIND LOST DB_INSTRUMENT_FILES");
		if(getPrintOnlyMode()) return null;
		
		return parseEscapedStringList(getSingleLineResultSet().getResult());
	}
	
	/**
	 * Gets status information about the specified job.
	 * @param jobId The ID of the job.
	 * @return A <code>ScanJobInfo</code> instance providing information
	 * about the specified job.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified job is not found.
	 */
	public synchronized ScanJobInfo
	getDbInstrumentsJobInfo(int jobId) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET DB_INSTRUMENTS_JOB INFO " + String.valueOf(jobId));
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		ScanJobInfo info = new ScanJobInfo(rs.getMultiLineResult());
		
		return info;
	}
	
	/**
	 * Removes all instruments and directories and re-creates
	 * the instruments database structure.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the formatting of the instruments database failed.
	 */
	public synchronized void
	formatInstrumentsDb() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("FORMAT INSTRUMENTS_DB");
		if(getPrintOnlyMode()) return;
		
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
		if(getPrintOnlyMode()) return;
		
		try { ResultSet rs = getEmptyResultSet(); }
		catch(LSException x) { getLogger().warning(x.getMessage()); }
	}
	
	/**
	 * Gets the current number of all active streams.
	 * @return The current number of all active streams.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getTotalStreamCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET TOTAL_STREAM_COUNT");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets the current number of all active voices.
	 * @return The current number of all active voices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getTotalVoiceCount() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET TOTAL_VOICE_COUNT");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets the maximum number of active voices.
	 * @return The maximum number of active voices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getTotalVoiceCountMax() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET TOTAL_VOICE_COUNT_MAX");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
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
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		return new ServerInfo(rs.getMultiLineResult());
	}
	
	/**
	 * Gets the global volume of the sampler.
	 * @return The global volume of the sampler.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized float
	getVolume() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET VOLUME");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseFloat(s);
	}
	
	/**
	 * Sets the global volume of the sampler.
	 * @param volume The new volume value.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #getVolume
	 */
	public synchronized void
	setVolume(float volume) throws IOException, LscpException, LSException {
	
		verifyConnection();
		out.writeLine("SET VOLUME " + volume);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the global sampler-wide limit of maximum voices.
	 * @return The global sampler-wide limit of maximum voices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getGlobalVoiceLimit() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET VOICES");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Sets the global sampler-wide limit of maximum voices.
	 * @param maxVoices The new global limit of maximum voices.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #getVolume
	 */
	public synchronized void
	setGlobalVoiceLimit(int maxVoices) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("SET VOICES " + maxVoices);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the global sampler-wide limit of maximum disk streams.
	 * @return The global sampler-wide limit of maximum disk streams.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 */
	public synchronized int
	getGlobalStreamLimit() throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET STREAMS");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Sets the global sampler-wide limit for maximum disk streams.
	 * @param maxVoices The new global limit of maximum disk streams.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If some other error occurs.
	 * @see #getVolume
	 */
	public synchronized void
	setGlobalStreamLimit(int maxStreams) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("SET STREAMS " + maxStreams);
		if(getPrintOnlyMode()) return;
		
		ResultSet rs = getEmptyResultSet();
	}
	
	/**
	 * Gets the number of instruments in the specified instrument file.
	 * @param filename The absolute path name of the instrument file.
	 * @return The number of instruments in the specified instrument file.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the file is not found, or other error occur.
	 */
	public synchronized int
	getFileInstrumentCount(String filename) throws IOException, LscpException, LSException {
		verifyConnection();
		out.writeLine("GET FILE INSTRUMENTS '" + conv(filename) +"'");
		if(getPrintOnlyMode()) return -1;
		
		String s = getSingleLineResultSet().getResult();
		return parseInt(s);
	}
	
	/**
	 * Gets information about the instrument with index
	 * <code>instrIdx</code> in the specified instrument file.
	 * @param filename The absolute path name of the instrument file.
	 * @param instrIdx The index of the instrument in the specified instrument file.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If failed to retrieve information.
	 */
	public synchronized Instrument
	getFileInstrumentInfo(String filename, int instrIdx)
				throws IOException, LscpException, LSException {
		
		verifyConnection();
		out.writeLine("GET FILE INSTRUMENT INFO '" + conv(filename) + "' " + String.valueOf(instrIdx));
		if(getPrintOnlyMode()) return null;
		
		ResultSet rs = getMultiLineResultSet();
		Instrument instr = new FileInstrument(rs.getMultiLineResult()) { };
		
		return instr;
	}
	
	/**
	 * Gets the list of instruments in the specified instrument file.
	 * @param filename The absolute path name of the instrument file.
	 * @return An <code>Instrument</code> array providing
	 * information about all instruments in the specified instrument file.
	 * @throws IOException If some I/O error occurs.
	 * @throws LscpException If LSCP protocol corruption occurs.
	 * @throws LSException If the specified file name is invalid.
	 */
	public synchronized Instrument[]
	getFileInstruments(String filename) throws IOException, LscpException, LSException {
		int l = getFileInstrumentCount(filename);
		if(l < 0) return null;
		Instrument[] instrS = new FileInstrument[l];
		
		for(int i = 0; i < instrS.length; i++) {
			instrS[i] = getFileInstrumentInfo(filename, i);
		}
		return instrS;
	}
	
	private static class FileInstrument extends AbstractInstrument {
		FileInstrument(String[] resultSet) throws LscpException {
			super(resultSet);
		}
		
		public String
		getEngine() {
			// TODO: engine lookup?
			return getFormatFamily();
		}
		
		@Override
		public boolean
		parse(String s) throws LscpException {
			if(s.startsWith("PRODUCT: ") || s.startsWith("ARTISTS: ")) return true;
			return super.parse(s);
		}
	}
	
	private void
	getEmptyResultSets(int count, String err) throws LSException {
		StringBuffer sb = new StringBuffer();
		for(int i = 0; i < count; i++) {
			try { getEmptyResultSet(); }
			catch (SocketTimeoutException e) {
				getLogger().log(Level.FINE, e.getMessage(), e);
				sb.append(e.getMessage()).append("\n");
				break;
			} catch (Exception e) {
				getLogger().log(Level.FINE, e.getMessage(), e);
				sb.append(e.getMessage()).append("\n");
			}
		}
		
		String details = sb.toString();
		if(details.length() > 0) {
			String s = LscpI18n.getLogMsg(err);
			throw new LSException(0, s, details);
		}
	}
	
	/**
	 * Returns the logger for this library.
	 * @return The logger for this library.
	 */
	protected static Logger
	getLogger() { return Logger.getLogger("org.linuxsampler.lscp"); }
}
