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

import org.linuxsampler.lscp.*;


/**
 * This class creates one MIDI input device, one audio output device and one sampler channel.
 * Then set the MIDI input device and the audio output device of the created sampler channel
 * with the newly created devices. Loads sampler engine and the specified instrument.
 * @author Grigor Iliev
 */
public class CreateChannel {
	public static void
	main(String[] args) {
		if(args.length != 2) {
			System.out.println("Usage: CreateChannel instrument-file instrument-index");
			return;
		}
		
		initLogger();
		Client client = new Client();
		
		try {
			client.connect();
			
			int mDev, aDev, chn;
			
			// Creates new MIDI input device using the first availble MIDI driver
			mDev =client.createMidiInputDevice (
				client.getMidiInputDrivers()[0].getName()
			);
			
			// Creates new audio output device using the first audio output driver
			aDev = client.createAudioOutputDevice (
				client.getAudioOutputDrivers()[0].getName()
			);
			
			// Creates new sampler channel
			chn = client.addSamplerChannel();
			
			// Setting the MIDI input device of the channel
			client.setChannelMidiInputDevice(chn,  mDev);
			
			// Setting the audio output device of the channel
			client.setChannelAudioOutputDevice(chn, aDev);
			
			// Setting the engine type 
			client.loadSamplerEngine(client.getEngines()[0].getName(), chn);
			
			// Loading instrument
			client.loadInstrument(args[0], Integer.parseInt(args[1]), chn);
			
			client.disconnect();
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
