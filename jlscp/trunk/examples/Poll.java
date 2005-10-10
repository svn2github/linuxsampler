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

import java.util.logging.Handler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.util.logging.StreamHandler;

import org.linuxsampler.lscp.*;


/**
 * Displays information about the current state of running LinuxSampler instance.
 * @author Grigor Iliev
 */
public class Poll {
	public static void
	main(String[] args) {
		initLogger();
		Client client = new Client();
		
		try {
			client.connect();
			
			poll(client);
			
			client.disconnect();
			System.exit(0);
		} catch(Exception x) {
			x.printStackTrace();
		}
		
		System.exit(-1);
	}
	
	private static void
	poll(Client client) throws java.io.IOException, LscpException, LSException {
		ServerInfo si = client.getServerInfo();
		System.out.print("Sampler description: ");
		System.out.println(si.getDescription());
		System.out.print("Sampler version: ");
		System.out.println(si.getVersion());
		System.out.print("LSCP protocol version: ");
		System.out.println(si.getProtocolVersion());
		System.out.println();
		
		System.out.print("Number of available audio output drivers: ");
		System.out.println(client.getAudioOutputDriverCount());
		System.out.println();
		
		System.out.println("Available audio output drivers: ");
		AudioOutputDriver[] aodS = client.getAudioOutputDrivers();
		showList(aodS);
		
		System.out.println();
		
		for(AudioOutputDriver d : aodS) {
			showDriverInfo(d);
			for(Parameter p : d.getParameters()) showParameterInfo(p);
			System.out.println();
		}
		
		
		System.out.print("Number of audio output devices: ");
		System.out.println(client.getAudioOutputDeviceCount());
		
		System.out.print("Numerical IDs of all created audio output devices: ");
		AudioOutputDevice[] audioDevices = client.getAudioOutputDevices();
		showCommaList(audioDevices);
		System.out.println();
		
		for(AudioOutputDevice d : audioDevices) {
			System.out.println();
			showAODeviceInfo(d);
			
			for(int j = 0; j < d.getChannelCount(); j++) {
				AudioOutputChannel aoc =
					client.getAudioOutputChannelInfo(d.getDeviceID(), j);
				System.out.println(" Channel: " + aoc.getName());
				if(aoc.isMixChannel()) System.out.println (
					" Mix channel destincation: " + aoc.getMixChannelDest()
				);
				if(aoc.hasAdditionalParameters()) {
					for(Parameter p : aoc.getAdditionalParameters())
						showParameterInfo(p);
				}
				
				System.out.println();
			}
		}
		
		System.out.print("Number of available MIDI input drivers: ");
		System.out.println(client.getMidiInputDriverCount());
		System.out.println();
		
		System.out.println("Available MIDI input drivers: ");
		MidiInputDriver[] midS = client.getMidiInputDrivers();
		showList(midS);
		
		for(MidiInputDriver d : midS) {
			showDriverInfo(d);
			for(Parameter p : d.getParameters()) showParameterInfo(p);
			System.out.println();
		}
		
		System.out.print("Number of MIDI input devices: ");
		System.out.println(client.getMidiInputDeviceCount());
		
		System.out.print("Numerical IDs of all created MIDI input devices: ");
		MidiInputDevice[] midiDevices = client.getMidiInputDevices();
		showCommaList(midiDevices);
		System.out.println();
		
		for(MidiInputDevice d : midiDevices) {
			System.out.println();
			showDeviceInfo(d);
		}
		
		System.out.print("Number of sampler channels: ");
		System.out.println(client.getSamplerChannelCount());
		System.out.println();
		
		System.out.print("Numerical IDs of all created sampler channels: ");
		Integer[] channels = client.getSamplerChannelIDs();
		showCommaList(channels);
		System.out.println();
		System.out.println();
		for(int i : channels) {
			showChannelInfo(client.getSamplerChannelInfo(i));
		}
		
		
		
		System.out.print("Number of available engines: ");
		System.out.println(client.getEngineCount());
		System.out.println();
		
		System.out.println("Available engines:");
		
		SamplerEngine[] engines = client.getEngines();
		showList(engines);
		
		for(SamplerEngine se : engines) showEngineInfo(se);
	}
	
	private static void
	showList(Object[] list) { showList(list, " - "); }
	
	private static void
	showList(Object[] list, String prefix) {
		for(Object o : list) System.out.println(prefix + o.toString());
	}
	
	private static void
	showCommaList(Object[] list) { showCommaList(list, ""); }
	
	private static void
	showCommaList(Object[] list, String prefix) {
		if(list.length == 0) {
			return;
		}
		System.out.print(prefix + "'" + list[0].toString() + "'");
		
		for(int i = 1; i < list.length; i++)
			System.out.print(", '" + list[i].toString() + "'");
	}
	
	private static void
	showDriverInfo(Driver drv) {
		System.out.println("Driver: " + drv.getName());
		System.out.println("Version: " + drv.getVersion());
		System.out.println("Description: " + drv.getDescription());
		System.out.println("Driver parameters: ");
		showList(drv.getParameters());
		
		System.out.println();
	}
	
	private static void
	showAODeviceInfo(AudioOutputDevice aoDevice) {
		showDeviceInfo(aoDevice);
		showParameterInfo(aoDevice.getChannelsParameter());
		
			
	}
	
	private static void
	showDeviceInfo(Device device) {
		System.out.println("Device ID: " + device.getDeviceID());
		System.out.println(" Driver: " + device.getDriverName());
		System.out.println(" Active: " + device.isActive());
		for(Parameter p : device.getAdditionalParameters()) showParameterInfo(p);
	}
	
	private static void
	showParameterInfo(Parameter p) {
		System.out.println(" Parameter: " + p.getName());
		System.out.println("  Type: " + p.getType().name());
		System.out.println("  Description: " + p.getDescription());
		if(p.hasDependances()) {
			System.out.println("  Depends on: ");
			showList(p.getDependances(), "   - ");
		}
		
		switch(p.getType()) {
		case BOOL:
			Parameter<Boolean> pb = (Parameter<Boolean>)p;
			
			showValue(pb.getValue());
			if(pb.hasPossibilities()) {
				System.out.println("  Possibilities: ");
				showList(pb.getPossibilities(), "   - ");
			}
			break;
		case FLOAT:
			Parameter<Float> pf = (Parameter<Float>)p;
			
			showValue(pf.getValue());
			if(pf.hasPossibilities()) {
				System.out.println("  Possibilities: ");
				showList(pf.getPossibilities(), "   - ");
			}
			break;
		case INT:
			Parameter<Integer> pi = (Parameter<Integer>)p;
			
			showValue(pi.getValue());
			if(pi.hasPossibilities()) {
				System.out.println("  Possibilities: ");
				showList(pi.getPossibilities(), "   - ");
			}
			break;
		case STRING:
			Parameter<String> ps = (Parameter<String>)p;
			
			showValue(ps.getValue());
			if(ps.hasPossibilities()) {
				System.out.println("  Possibilities: ");
				showList(ps.getPossibilities(), "   - ");
			}
			break;
		case BOOL_LIST:
			Parameter<Boolean[]> pbS = (Parameter<Boolean[]>)p;
			
			showListValue(pbS.getValue());
				
			if(pbS.hasPossibilities()) showPossibilities(pbS.getPossibilities());
			break;
		case FLOAT_LIST:
			Parameter<Float[]> pfS = (Parameter<Float[]>)p;
			
			showListValue(pfS.getValue());
				
			if(pfS.hasPossibilities()) showPossibilities(pfS.getPossibilities());
			break;
		case INT_LIST:
			Parameter<Integer[]> piS = (Parameter<Integer[]>)p;
			
			showListValue(piS.getValue());
				
			if(piS.hasPossibilities()) showPossibilities(piS.getPossibilities());
			break;
		case STRING_LIST:
			Parameter<String[]> psS = (Parameter<String[]>)p;
				
			showListValue(psS.getValue());
							
			if(p.hasPossibilities()) showPossibilities(psS.getPossibilities());
			break;
		default: throw new RuntimeException("Unknown parameter type");
		}
		
		System.out.println();
	}
	
	private static void
	showValue(Object o) { if(o != null) System.out.println("  Value: " + o); }
	
	private static void
	showListValue(Object[] objs) {
		if(objs != null) {
			System.out.print( "  Value: ");
			showCommaList(objs);
			System.out.println();
		}
	}
	
	private static void
	showPossibilities(Object[][] args) {
		System.out.println("  Possibilities: ");
		
		for(int i = 0; i < args.length; i++) {
			System.out.print("   " + (i + 1) + ") ");
			showCommaList(args[i]);
			System.out.println();
		}
	}
	
	private static void
	showChannelInfo(SamplerChannel channel) {
		System.out.println("Sampler channel ID: " + channel.getChannelID());
		System.out.println();
	}
	
	private static void
	showEngineInfo(SamplerEngine engine) {
		System.out.println("Engine: " + engine.getName());
		System.out.println("Version: " + engine.getVersion());
		System.out.println("Description: " + engine.getDescription());
		
		System.out.println();
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
