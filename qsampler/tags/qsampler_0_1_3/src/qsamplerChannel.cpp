// qsamplerChannel.cpp
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

#include "qsamplerAbout.h"
#include "qsamplerChannel.h"

#include "qsamplerMainForm.h"
#include "qsamplerChannelForm.h"

#include <qfileinfo.h>
#include <qcombobox.h>

#ifdef CONFIG_LIBGIG
#include "gig.h"
#endif

#define QSAMPLER_INSTRUMENT_MAX 100


//-------------------------------------------------------------------------
// qsamplerChannel - Sampler channel structure.
//

// Constructor.
qsamplerChannel::qsamplerChannel ( qsamplerMainForm *pMainForm, int iChannelID )
{
	m_pMainForm  = pMainForm;
	m_iChannelID = iChannelID;

//  m_sEngineName       = noEngineName();
//  m_sInstrumentName   = noInstrumentName();
//  m_sInstrumentFile   = m_sInstrumentName;
	m_iInstrumentNr     = -1;
	m_iInstrumentStatus = -1;
	m_sMidiDriver       = "ALSA";
	m_iMidiDevice       = -1;
	m_iMidiPort         = -1;
	m_iMidiChannel      = -1;
	m_sAudioDriver      = "ALSA";
	m_iAudioDevice      = -1;
	m_fVolume           = 0.0;
	m_bMute             = false;
	m_bSolo             = false;
}

// Default destructor.
qsamplerChannel::~qsamplerChannel (void)
{
}


// Main application form accessor.
qsamplerMainForm *qsamplerChannel::mainForm(void) const
{
	return m_pMainForm;
}


// The global options settings delegated property.
qsamplerOptions *qsamplerChannel::options (void) const
{
	if (m_pMainForm == NULL)
		return NULL;

	return m_pMainForm->options();
}


// The client descriptor delegated property.
lscp_client_t *qsamplerChannel::client (void) const
{
	if (m_pMainForm == NULL)
		return NULL;

	return m_pMainForm->client();
}


// Create a new sampler channel, if not already.
bool qsamplerChannel::addChannel (void)
{
	if (client() == NULL)
		return false;

	// Are we a new channel?
	if (m_iChannelID < 0) {
		m_iChannelID = ::lscp_add_channel(client());
		if (m_iChannelID < 0) {
			appendMessagesClient("lscp_add_channel");
			appendMessagesError(QObject::tr("Could not add channel.\n\nSorry."));
		}   // Otherwise it's created...
		else appendMessages(QObject::tr("added."));
	}

	// Return whether we're a valid channel...
	return (m_iChannelID >= 0);
}


// Remove sampler channel.
bool qsamplerChannel::removeChannel (void)
{
	if (client() == NULL)
		return false;

	// Are we an existing channel?
	if (m_iChannelID >= 0) {
		if (::lscp_remove_channel(client(), m_iChannelID) != LSCP_OK) {
			appendMessagesClient("lscp_remove_channel");
			appendMessagesError(QObject::tr("Could not remove channel.\n\nSorry."));
		} else {
			// Otherwise it's removed.
			appendMessages(QObject::tr("removed."));
			m_iChannelID = -1;
		}
	}

	// Return whether we've removed the channel...
	return (m_iChannelID < 0);
}


// Channel-ID (aka Sammpler-Channel) accessors.
int qsamplerChannel::channelID (void) const
{
	return m_iChannelID;
}

void qsamplerChannel::setChannelID ( int iChannelID )
{
	m_iChannelID = iChannelID;
}


// Readable channel name.
QString qsamplerChannel::channelName (void) const
{
	return (m_iChannelID < 0 ? QObject::tr("New Channel") : QObject::tr("Channel %1").arg(m_iChannelID));
}


// Engine name accessors.
const QString& qsamplerChannel::engineName (void) const
{
	return m_sEngineName;
}

bool qsamplerChannel::loadEngine ( const QString& sEngineName )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_sEngineName == sEngineName)
		return true;

	if (::lscp_load_engine(client(), sEngineName.latin1(), m_iChannelID) != LSCP_OK) {
		appendMessagesClient("lscp_load_engine");
		return false;
	}
	appendMessages(QObject::tr("Engine: %1.").arg(sEngineName));

	m_sEngineName = sEngineName;
	return true;
}


// Instrument filename accessor.
const QString& qsamplerChannel::instrumentFile (void) const
{
	return m_sInstrumentFile;
}

// Instrument index accessor.
int qsamplerChannel::instrumentNr (void) const
{
	return m_iInstrumentNr;
}

// Instrument name accessor.
const QString& qsamplerChannel::instrumentName (void) const
{
	return m_sInstrumentName;
}

// Instrument status accessor.
int qsamplerChannel::instrumentStatus (void) const
{
	return m_iInstrumentStatus;
}

// Instrument file loader.
bool qsamplerChannel::loadInstrument ( const QString& sInstrumentFile, int iInstrumentNr )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (!isInstrumentFile(sInstrumentFile))
		return false;
	if (m_iInstrumentStatus == 100 && m_sInstrumentFile == sInstrumentFile && m_iInstrumentNr == iInstrumentNr)
		return true;

	if (::lscp_load_instrument_non_modal(client(), sInstrumentFile.latin1(), iInstrumentNr, m_iChannelID) != LSCP_OK) {
		appendMessagesClient("lscp_load_instrument");
		return false;
	}

	appendMessages(QObject::tr("Instrument: \"%1\" (%2).")
		.arg(sInstrumentFile).arg(iInstrumentNr));

	return setInstrument(sInstrumentFile, iInstrumentNr);
}


// Special instrument file/name/number settler.
bool qsamplerChannel::setInstrument ( const QString& sInstrumentFile, int iInstrumentNr )
{
	m_sInstrumentFile = sInstrumentFile;
	m_iInstrumentNr = iInstrumentNr;
#ifdef CONFIG_INSTRUMENT_NAME
	m_sInstrumentName = QString::null;  // We'll get it, maybe later, on channel_info...
#else
	m_sInstrumentName = getInstrumentName(sInstrumentFile, iInstrumentNr, true);
#endif
	m_iInstrumentStatus = 0;

	return true;
}


// MIDI driver type accessors (DEPRECATED).
const QString& qsamplerChannel::midiDriver (void) const
{
	return m_sMidiDriver;
}

bool qsamplerChannel::setMidiDriver ( const QString& sMidiDriver )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_sMidiDriver == sMidiDriver)
		return true;

	if (::lscp_set_channel_midi_type(client(), m_iChannelID, sMidiDriver.latin1()) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_midi_type");
		return false;
	}

	appendMessages(QObject::tr("MIDI driver: %1.").arg(sMidiDriver));

	m_sMidiDriver = sMidiDriver;
	return true;
}


// MIDI device accessors.
int qsamplerChannel::midiDevice (void) const
{
	return m_iMidiDevice;
}

bool qsamplerChannel::setMidiDevice ( int iMidiDevice )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_iMidiDevice == iMidiDevice)
		return true;

	if (::lscp_set_channel_midi_device(client(), m_iChannelID, iMidiDevice) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_midi_device");
		return false;
	}

	appendMessages(QObject::tr("MIDI device: %1.").arg(iMidiDevice));

	m_iMidiDevice = iMidiDevice;
	return true;
}


// MIDI port number accessor.
int qsamplerChannel::midiPort (void) const
{
	return m_iMidiPort;
}

bool qsamplerChannel::setMidiPort ( int iMidiPort )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_iMidiPort == iMidiPort)
		return true;

	if (::lscp_set_channel_midi_port(client(), m_iChannelID, iMidiPort) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_midi_port");
		return false;
	}

	appendMessages(QObject::tr("MIDI port: %1.").arg(iMidiPort));

	m_iMidiPort = iMidiPort;
	return true;
}


// MIDI channel accessor.
int qsamplerChannel::midiChannel (void) const
{
	return m_iMidiChannel;
}

bool qsamplerChannel::setMidiChannel ( int iMidiChannel )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_iMidiChannel == iMidiChannel)
		return true;

	if (::lscp_set_channel_midi_channel(client(), m_iChannelID, iMidiChannel) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_midi_channel");
		return false;
	}

	appendMessages(QObject::tr("MIDI channel: %1.").arg(iMidiChannel));

	m_iMidiChannel = iMidiChannel;
	return true;
}


// Audio device accessor.
int qsamplerChannel::audioDevice (void) const
{
	return m_iAudioDevice;
}

bool qsamplerChannel::setAudioDevice ( int iAudioDevice )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_iAudioDevice == iAudioDevice)
		return true;

	if (::lscp_set_channel_audio_device(client(), m_iChannelID, iAudioDevice) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_audio_device");
		return false;
	}

	appendMessages(QObject::tr("Audio device: %1.").arg(iAudioDevice));

	m_iAudioDevice = iAudioDevice;
	return true;
}


// Audio driver type accessors (DEPRECATED).
const QString& qsamplerChannel::audioDriver (void) const
{
	return m_sAudioDriver;
}

bool qsamplerChannel::setAudioDriver ( const QString& sAudioDriver )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_sAudioDriver == sAudioDriver)
		return true;

	if (::lscp_set_channel_audio_type(client(), m_iChannelID, sAudioDriver.latin1()) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_audio_type");
		return false;
	}

	appendMessages(QObject::tr("Audio driver: %1.").arg(sAudioDriver));

	m_sAudioDriver = sAudioDriver;
	return true;
}


// Channel volume accessors.
float qsamplerChannel::volume (void) const
{
	return m_fVolume;
}

bool qsamplerChannel::setVolume ( float fVolume )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && m_fVolume == fVolume)
		return true;

	if (::lscp_set_channel_volume(client(), m_iChannelID, fVolume) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_volume");
		return false;
	}

	appendMessages(QObject::tr("Volume: %1.").arg(fVolume));

	m_fVolume = fVolume;
	return true;
}


// Sampler channel mute state.
bool qsamplerChannel::channelMute (void) const
{
	return m_bMute;
}

bool qsamplerChannel::setChannelMute ( bool bMute )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && ((m_bMute && bMute) || (!m_bMute && !bMute)))
		return true;

#ifdef CONFIG_MUTE_SOLO
	if (::lscp_set_channel_mute(client(), m_iChannelID, bMute) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_mute");
		return false;
	}
	appendMessages(QObject::tr("Mute: %1.").arg((int) bMute));
	m_bMute = bMute;
	return true;
#else
	return false;
#endif
}


// Sampler channel solo state.
bool qsamplerChannel::channelSolo (void) const
{
	return m_bSolo;
}

bool qsamplerChannel::setChannelSolo ( bool bSolo )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 && ((m_bSolo && bSolo) || (!m_bSolo && !bSolo)))
		return true;

#ifdef CONFIG_MUTE_SOLO
	if (::lscp_set_channel_solo(client(), m_iChannelID, bSolo) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_solo");
		return false;
	}
	appendMessages(QObject::tr("Solo: %1.").arg((int) bSolo));
	m_bSolo = bSolo;
	return true;
#else
	return false;
#endif
}


// Audio routing accessors.
int qsamplerChannel::audioChannel ( int iAudioOut ) const
{
	return m_audioRouting[iAudioOut];
}

bool qsamplerChannel::setAudioChannel ( int iAudioOut, int iAudioIn )
{
	if (client() == NULL || m_iChannelID < 0)
		return false;
	if (m_iInstrumentStatus == 100 &&
			m_audioRouting[iAudioOut] == iAudioIn)
		return true;

	if (::lscp_set_channel_audio_channel(client(),
			m_iChannelID, iAudioOut, iAudioIn) != LSCP_OK) {
		appendMessagesClient("lscp_set_channel_audio_channel");
		return false;
	}

	appendMessages(QObject::tr("Audio Channel: %1 -> %2.")
		.arg(iAudioOut).arg(iAudioIn));

	m_audioRouting[iAudioOut] = iAudioIn;
	return true;
}

// The audio routing map itself.
const qsamplerChannelRoutingMap& qsamplerChannel::audioRouting (void) const
{
	return m_audioRouting;
}


// Istrument name remapper.
void qsamplerChannel::updateInstrumentName (void)
{
#ifndef CONFIG_INSTRUMENT_NAME
	m_sInstrumentName = getInstrumentName(m_sInstrumentFile,
		m_iInstrumentNr, (options() && options()->bInstrumentNames));
#endif
}


// Update whole channel info state.
bool qsamplerChannel::updateChannelInfo (void)
{
	if (client() == NULL || m_iChannelID < 0)
		return false;

	// Read channel information.
	lscp_channel_info_t *pChannelInfo = ::lscp_get_channel_info(client(), m_iChannelID);
	if (pChannelInfo == NULL) {
		appendMessagesClient("lscp_get_channel_info");
		appendMessagesError(QObject::tr("Could not get channel information.\n\nSorry."));
		return false;
	}

#ifdef CONFIG_INSTRUMENT_NAME
	// We got all actual instrument datum...
	m_sInstrumentFile = pChannelInfo->instrument_file;
	m_iInstrumentNr   = pChannelInfo->instrument_nr;
	m_sInstrumentName = pChannelInfo->instrument_name;
#else
	// First, check if intrument name has changed,
	// taking care that instrument name lookup might be expensive,
	// so we better make it only once and when really needed...
	if ((m_sInstrumentFile != pChannelInfo->instrument_file) ||
		(m_iInstrumentNr   != pChannelInfo->instrument_nr)) {
		m_sInstrumentFile = pChannelInfo->instrument_file;
		m_iInstrumentNr   = pChannelInfo->instrument_nr;
		updateInstrumentName();
	}
#endif
	// Cache in other channel information.
	m_sEngineName       = pChannelInfo->engine_name;
	m_iInstrumentStatus = pChannelInfo->instrument_status;
	m_iMidiDevice       = pChannelInfo->midi_device;
	m_iMidiPort         = pChannelInfo->midi_port;
	m_iMidiChannel      = pChannelInfo->midi_channel;
	m_iAudioDevice      = pChannelInfo->audio_device;
	m_fVolume           = pChannelInfo->volume;
#ifdef CONFIG_MUTE_SOLO
	m_bMute             = pChannelInfo->mute;
	m_bSolo             = pChannelInfo->solo;
#endif
	// Some sanity checks.
	if (m_sEngineName == "NONE" || m_sEngineName.isEmpty())
		m_sEngineName = QString::null;
	if (m_sInstrumentFile == "NONE" || m_sInstrumentFile.isEmpty()) {
		m_sInstrumentFile = QString::null;
		m_sInstrumentName = QString::null;
	}

	// Time for device info grabbing...
	lscp_device_info_t *pDeviceInfo;
	const QString sNone = QObject::tr("(none)");
	// Audio device driver type.
	pDeviceInfo = ::lscp_get_audio_device_info(client(), m_iAudioDevice);
	if (pDeviceInfo == NULL) {
		appendMessagesClient("lscp_get_audio_device_info");
		m_sAudioDriver = sNone;
	} else {
		m_sAudioDriver = pDeviceInfo->driver;
	}
	// MIDI device driver type.
	pDeviceInfo = ::lscp_get_midi_device_info(client(), m_iMidiDevice);
	if (pDeviceInfo == NULL) {
		appendMessagesClient("lscp_get_midi_device_info");
		m_sMidiDriver = sNone;
	} else {
		m_sMidiDriver = pDeviceInfo->driver;
	}

	// Set the audio routing map.
	m_audioRouting.clear();
	char **ppszRouting = pChannelInfo->audio_routing;
	for (int i = 0; ppszRouting && ppszRouting[i]; i++) {
		m_audioRouting[i] = ::atoi(ppszRouting[i]);
	}

	return true;
}


// Reset channel method.
bool qsamplerChannel::channelReset (void)
{
	if (client() == NULL || m_iChannelID < 0)
		return false;

	if (::lscp_reset_channel(client(), m_iChannelID) != LSCP_OK) {
		appendMessagesClient("lscp_reset_channel");
		return false;
	}

	appendMessages(QObject::tr("reset."));

	return true;
}


// Channel setup dialog form.
bool qsamplerChannel::channelSetup ( QWidget *pParent )
{
	bool bResult = false;

	appendMessages(QObject::tr("setup..."));

	qsamplerChannelForm *pChannelForm = new qsamplerChannelForm(pParent);
	if (pChannelForm) {
		pChannelForm->setup(this);
		bResult = pChannelForm->exec();
		delete pChannelForm;
	}

	return bResult;
}


// Redirected messages output methods.
void qsamplerChannel::appendMessages( const QString& s ) const
{
	if (m_pMainForm)
		m_pMainForm->appendMessages(channelName() + ' ' + s);
}

void qsamplerChannel::appendMessagesColor( const QString& s,
	const QString& c ) const
{
	if (m_pMainForm)
		m_pMainForm->appendMessagesColor(channelName() + ' ' + s, c);
}

void qsamplerChannel::appendMessagesText( const QString& s ) const
{
	if (m_pMainForm)
		m_pMainForm->appendMessagesText(channelName() + ' ' + s);
}

void qsamplerChannel::appendMessagesError( const QString& s ) const
{
	if (m_pMainForm)
		m_pMainForm->appendMessagesError(channelName() + "\n\n" + s);
}

void qsamplerChannel::appendMessagesClient( const QString& s ) const
{
	if (m_pMainForm)
		m_pMainForm->appendMessagesClient(channelName() + ' ' + s);
}


// Context menu event handler.
void qsamplerChannel::contextMenuEvent( QContextMenuEvent *pEvent )
{
	if (m_pMainForm)
		m_pMainForm->contextMenuEvent(pEvent);
}


// FIXME: Check whether a given file is an instrument file.
bool qsamplerChannel::isInstrumentFile ( const QString& sInstrumentFile )
{
	bool bResult = false;

	QFile file(sInstrumentFile);
	if (file.open(IO_ReadOnly)) {
		char achHeader[16];
		if (file.readBlock(achHeader, 16)) {
			bResult = (::memcmp(&achHeader[0], "RIFF", 4)     == 0
					&& ::memcmp(&achHeader[8], "DLS LIST", 8) == 0);
		}
		file.close();
	}

	return bResult;
}


// Retrieve the instrument list of a instrument file (.gig).
QStringList qsamplerChannel::getInstrumentList( const QString& sInstrumentFile,
	bool bInstrumentNames )
{
	QString sInstrumentName = QFileInfo(sInstrumentFile).fileName();
	QStringList instlist;

	if (isInstrumentFile(sInstrumentFile)) {
#ifdef CONFIG_LIBGIG
		if (bInstrumentNames) {
			RIFF::File *pRiff = new RIFF::File(sInstrumentFile.latin1());
			gig::File  *pGig  = new gig::File(pRiff);
			gig::Instrument *pInstrument = pGig->GetFirstInstrument();
			while (pInstrument) {
				instlist.append((pInstrument->pInfo)->Name.c_str());
				pInstrument = pGig->GetNextInstrument();
			}
			delete pGig;
			delete pRiff;
		}
		else
#endif
		for (int iInstrumentNr = 0; iInstrumentNr < QSAMPLER_INSTRUMENT_MAX; iInstrumentNr++)
			instlist.append(sInstrumentName + " [" + QString::number(iInstrumentNr) + "]");
	}
	else instlist.append(noInstrumentName());

	return instlist;
}


// Retrieve the spacific instrument name of a instrument file (.gig), given its index.
QString qsamplerChannel::getInstrumentName( const QString& sInstrumentFile,
	int iInstrumentNr, bool bInstrumentNames )
{
	QString sInstrumentName;

	if (isInstrumentFile(sInstrumentFile)) {
		sInstrumentName = QFileInfo(sInstrumentFile).fileName();
#ifdef CONFIG_LIBGIG
		if (bInstrumentNames) {
			RIFF::File *pRiff = new RIFF::File(sInstrumentFile.latin1());
			gig::File  *pGig  = new gig::File(pRiff);
			int iIndex = 0;
			gig::Instrument *pInstrument = pGig->GetFirstInstrument();
			while (pInstrument) {
				if (iIndex == iInstrumentNr) {
					sInstrumentName = (pInstrument->pInfo)->Name.c_str();
					break;
				}
				iIndex++;
				pInstrument = pGig->GetNextInstrument();
			}
			delete pGig;
			delete pRiff;
		}
		else
#endif
		sInstrumentName += " [" + QString::number(iInstrumentNr) + "]";
	}
	else sInstrumentName = noInstrumentName();

	return sInstrumentName;
}


// Common invalid name-helpers.
QString qsamplerChannel::noEngineName (void)
{
	return QObject::tr("(No engine)");
}

QString qsamplerChannel::noInstrumentName (void)
{
	return QObject::tr("(No instrument)");
}

QString qsamplerChannel::loadingInstrument (void) {
	return QObject::tr("(Loading instrument...)");
}



//-------------------------------------------------------------------------
// qsamplerChannelRoutingTable - Channel routing table.
//

// Constructor.
qsamplerChannelRoutingTable::qsamplerChannelRoutingTable (
	QWidget *pParent, const char *pszName )
	: QTable(pParent, pszName)
{
	// Set fixed number of columns.
	QTable::setNumCols(2);
	QTable::setShowGrid(false);
	QTable::setSorting(false);
	QTable::setFocusStyle(QTable::FollowStyle);
	QTable::setSelectionMode(QTable::NoSelection);
	// No vertical header.
	QTable::verticalHeader()->hide();
	QTable::setLeftMargin(0);
	// Initialize the fixed table column headings.
	QHeader *pHeader = QTable::horizontalHeader();
	pHeader->setLabel(0, tr("Sampler Channel"));
	pHeader->setLabel(1, tr("Device Channel"));
	// Set read-onlyness of each column
	QTable::setColumnReadOnly(0, true);
//	QTable::setColumnReadOnly(1, false); -- of course not.
	QTable::setColumnStretchable(1, true);
}

// Default destructor.
qsamplerChannelRoutingTable::~qsamplerChannelRoutingTable (void)
{
}


// Routing map table renderer.
void qsamplerChannelRoutingTable::refresh ( qsamplerDevice *pDevice,
	const qsamplerChannelRoutingMap& routing )
{
	if (pDevice == NULL)
		return;

	// Always (re)start it empty.
	QTable::setUpdatesEnabled(false);
	QTable::setNumRows(0);

	// The common device port item list.
	QStringList opts;
	qsamplerDevicePortList& ports = pDevice->ports();
	qsamplerDevicePort *pPort;
	for (pPort = ports.first(); pPort; pPort = ports.next()) {
		opts.append(pDevice->deviceTypeName()
			+ ' ' + pDevice->driverName()
			+ ' ' + pPort->portName());
	}

	// Those items shall have a proper pixmap...
	QPixmap pmChannel = QPixmap::fromMimeSource("qsamplerChannel.png");
	QPixmap pmDevice;
	switch (pDevice->deviceType()) {
	case qsamplerDevice::Audio:
		pmDevice = QPixmap::fromMimeSource("audio2.png");
		break;
	case qsamplerDevice::Midi:
		pmDevice = QPixmap::fromMimeSource("midi2.png");
		break;
	case qsamplerDevice::None:
		break;
	}

	// Fill the routing table...
	QTable::insertRows(0, routing.count());
	int iRow = 0;
	qsamplerChannelRoutingMap::ConstIterator iter;
	for (iter = routing.begin(); iter != routing.end(); ++iter) {
		QTable::setPixmap(iRow, 0, pmChannel);
		QTable::setText(iRow, 0, pDevice->deviceTypeName()
			+ ' ' + QString::number(iter.key()));
		qsamplerChannelRoutingComboBox *pComboItem =
			new qsamplerChannelRoutingComboBox(this, opts, pmDevice);
		pComboItem->setCurrentItem(iter.data());
		QTable::setItem(iRow, 1, pComboItem);
		++iRow;
	}

	// Adjust optimal column widths.
	QTable::adjustColumn(0);
	QTable::adjustColumn(1);

	QTable::setUpdatesEnabled(true);
	QTable::updateContents();
}


// Commit any pending editing.
void qsamplerChannelRoutingTable::flush (void)
{
	if (QTable::isEditing())
	    QTable::endEdit(QTable::currEditRow(), QTable::currEditCol(), true, true);
}


//-------------------------------------------------------------------------
// qsamplerChannelRoutingComboBox - Custom combo box for routing table.
//

// Constructor.
qsamplerChannelRoutingComboBox::qsamplerChannelRoutingComboBox (
	QTable *pTable, const QStringList& list, const QPixmap& pixmap )
	: QTableItem(pTable, QTableItem::WhenCurrent, QString::null, pixmap),
	m_list(list)
{
	m_iCurrentItem = 0;
}

// Public accessors.
void qsamplerChannelRoutingComboBox::setCurrentItem ( int iCurrentItem )
{
	m_iCurrentItem = iCurrentItem;

	QTableItem::setText(m_list[iCurrentItem]);
}

int qsamplerChannelRoutingComboBox::currentItem (void) const
{
	return m_iCurrentItem;
}

// Virtual implemetations.
QWidget *qsamplerChannelRoutingComboBox::createEditor (void) const
{
	QComboBox *pComboBox = new QComboBox(QTableItem::table()->viewport());
	QObject::connect(pComboBox, SIGNAL(activated(int)),
		QTableItem::table(), SLOT(doValueChanged()));
	for (QStringList::ConstIterator iter = m_list.begin();
			iter != m_list.end(); iter++) {
		pComboBox->insertItem(QTableItem::pixmap(), *iter);
	}
	pComboBox->setCurrentItem(m_iCurrentItem);
	return pComboBox;
}

void qsamplerChannelRoutingComboBox::setContentFromEditor ( QWidget *pWidget )
{
	if (pWidget->inherits("QComboBox")) {
		QComboBox *pComboBox = (QComboBox *) pWidget;
		m_iCurrentItem = pComboBox->currentItem();
		QTableItem::setText(pComboBox->currentText());
	}
	else QTableItem::setContentFromEditor(pWidget);
}


// end of qsamplerChannel.cpp
