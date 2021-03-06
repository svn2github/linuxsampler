// qsamplerChannel.h
//
/****************************************************************************
   Copyright (C) 2003-2005, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*****************************************************************************/

#ifndef __qsamplerChannel_h
#define __qsamplerChannel_h

#include <qobject.h>

#include <lscp/client.h>
#include <lscp/device.h>

#include "qsamplerOptions.h"

class qsamplerMainForm;


//-------------------------------------------------------------------------
// qsamplerChannel - Sampler channel structure.
//

class qsamplerChannel
{
public:

	// Constructor.
	qsamplerChannel(qsamplerMainForm *pMainForm, int iChannelID = -1);
	// Default destructor.
	~qsamplerChannel();

	// Main application form accessor.
	qsamplerMainForm *mainForm() const;

	// Main application options accessor.
	qsamplerOptions *options() const;

	// LSCP client descriptor accessor.
	lscp_client_t * client() const;

	// Add/remove sampler channel methods.
	bool     addChannel();
	bool     removeChannel();

	// Sampler channel ID accessors.
	int      channelID() const;
	void     setChannelID(int iChannelID);

	// Readable channel name.
	QString  channelName() const;

	// Engine name property.
	const QString& engineName() const;
	bool     loadEngine(const QString& sEngineName);

	// Instrument file and index.
	const QString& instrumentFile() const;
	int      instrumentNr() const;
	const QString& instrumentName() const;
	int      instrumentStatus() const;

	// Instrument file loader.
	bool     loadInstrument(const QString& sInstrumentFile, int iInstrumentNr);
	// Special instrument file/name/number settler.
	bool     setInstrument(const QString& sInstrumentFile, int iInstrumentNr);

	// MIDI input driver (DEPRECATED).
	const QString& midiDriver() const;
	bool     setMidiDriver(const QString& sMidiDriver);

	// MIDI input device.
	int      midiDevice() const;
	bool     setMidiDevice(int iMidiDevice);

	// MIDI input port.
	int      midiPort() const;
	bool     setMidiPort(int iMidiPort);

	// MIDI input channel.
	int      midiChannel() const;
	bool     setMidiChannel(int iMidiChannel);

	// Audio output driver (DEPRECATED).
	const QString& audioDriver() const;
	bool     setAudioDriver(const QString& sAudioDriver);

	// Audio output device.
	int      audioDevice() const;
	bool     setAudioDevice(int iAudioDevice);

	// Sampler channel volume.
	float    volume() const;
	bool     setVolume(float fVolume);

	// Istrument name remapper.
	void     updateInstrumentName();

	// Channel info structure map executive.
	bool     updateChannelInfo();

	// Channel setup dialog form.
	bool     channelSetup(QWidget *pParent);

	// Reset channel method.
	bool     channelReset();

	// Message logging methods (brainlessly mapped to main form's).
	void     appendMessages       (const QString & s) const;
	void     appendMessagesColor  (const QString & s, const QString & c) const;
	void     appendMessagesText   (const QString & s) const;
	void     appendMessagesError  (const QString & s) const;
	void     appendMessagesClient (const QString & s) const;

	// Context menu event handler.
	void contextMenuEvent(QContextMenuEvent *pEvent);

	// Common (invalid) name-helpers.
	static QString noEngineName();
	static QString noInstrumentName();
	static QString loadingInstrument();

	// Check whether a given file is an instrument file.
	static bool isInstrumentFile (const QString& sInstrumentFile);

	// Retrieve the available instrument name(s) of an instrument file (.gig).
	static QString getInstrumentName (const QString& sInstrumentFile,
							int iInstrumentNr, bool bInstrumentNames);
	static QStringList getInstrumentList (const QString& sInstrumentFile,
							bool bInstrumentNames);

private:

	// Main application form reference.
	qsamplerMainForm *m_pMainForm;

	// Unique channel identifier.
	int     m_iChannelID;

	// Sampler channel info map.
	QString m_sEngineName;
	QString m_sInstrumentName;
	QString m_sInstrumentFile;
	int     m_iInstrumentNr;
	int     m_iInstrumentStatus;
	QString m_sMidiDriver;
	int     m_iMidiDevice;
	int     m_iMidiPort;
	int     m_iMidiChannel;
	QString m_sAudioDriver;
	int     m_iAudioDevice;
	float   m_fVolume;
};

#endif  // __qsamplerChannel_h


// end of qsamplerChannel.h
