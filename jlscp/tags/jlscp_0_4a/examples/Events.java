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

import java.util.logging.Handler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.util.logging.StreamHandler;

import org.linuxsampler.lscp.BufferFill;
import org.linuxsampler.lscp.Client;
import org.linuxsampler.lscp.event.*;

/**
 * Listens for events.
 * @author Grigor Iliev
 */
public class Events {
	public static void
	main(String[] args) {
		initLogger();
		
		MyListener myListener = new MyListener();
		Client client = new Client();
		
		try {
			// Listeners can be added or removed regardless of the connection state.
			client.addBufferFillListener(myListener);
			client.addChannelCountListener(myListener);
			client.addChannelInfoListener(myListener);
			client.addMiscellaneousListener(myListener);
			
			client.connect();
			
			client.addStreamCountListener(myListener);
			client.addVoiceCountListener(myListener);
			
			System.out.println("Press 'Enter' to exit");
			System.in.read();
			
			client.removeBufferFillListener(myListener);
			client.removeChannelCountListener(myListener);
			client.removeChannelInfoListener(myListener);
			
			client.disconnect();
			
			client.removeMiscellaneousListener(myListener);
			client.removeStreamCountListener(myListener);
			client.removeVoiceCountListener(myListener);
			
			System.exit(0);
		} catch(Exception x) {
			x.printStackTrace();
		}
		
		System.exit(-1);
	}
	
	private static void
	initLogger() {
		final Handler handler = new StreamHandler(System.out, new SimpleFormatter());
		Logger.getLogger("org.linuxsampler.lscp").addHandler(handler);
		
		// Flushing logs on every second
		new java.util.Timer().schedule(new java.util.TimerTask() {
			public void
			run() { handler.flush(); }
		}, 1000, 1000);
	}
}

class MyListener implements
	BufferFillListener,
	ChannelCountListener,
	ChannelInfoListener,
	MiscellaneousListener,
	StreamCountListener,
	VoiceCountListener {
	
	/**
	 * Invoked when the fill state of a disk stream buffer has changed.
	 */
	public void
	bufferFillChanged(BufferFillEvent e) {
		System.out.println (
			"Buffer fill event occured on channel " + 
			e.getSamplerChannel()
		);
		for(BufferFill bf : e.getChannelBufferFillPercentage()) {
			System.out.println (
				"\tStream ID " + bf.getStreamId() + ": " + bf.getValue() + "%"
			);
		}
	}
	
	/** Invoked when the number of channels is changed. */
	public void
	channelCountChanged(ChannelCountEvent e) {
		System.out.println("The number of channels has changed to " + e.getChannelCount());
	}
	
	/** Invoked when changes to the sampler channel has occured. */
	public void
	channelInfoChanged(ChannelInfoEvent e) {
		System.out.println("Channel " + e.getSamplerChannel() + " has changed");
	}
	
	/** Invoked when miscellaneous and debugging events occurs. */
	public void
	miscEventOccured(MiscellaneousEvent e) {
		System.out.println("Miscellaneous event: " + e.getEventMessage());
	}
	
	/**
	 * Invoked when the number of active disk streams for a specific sampler channel is changed.
	 */
	public void
	streamCountChanged(StreamCountEvent e) {
		System.out.println (
			"The number of disk streams on channel " + e.getSamplerChannel() +
			" has changed to " + e.getStreamCount()
		);
	}
	
	/** Invoked when the number of active voices has changed. */
	public void
	voiceCountChanged(VoiceCountEvent e) {
		System.out.println (
			"The number of voices on channel " + e.getSamplerChannel() +
			" has changed to " + e.getVoiceCount()
		);
	}
}
