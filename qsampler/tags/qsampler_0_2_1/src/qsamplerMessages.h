// qsamplerMessages.h
//
/****************************************************************************
   Copyright (C) 2004-2007, rncbc aka Rui Nuno Capela. All rights reserved.
   Copyright (C) 2007, Christian Schoenebeck

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __qsamplerMessages_h
#define __qsamplerMessages_h

#include <QDockWidget>

class QSocketNotifier;
class QTextEdit;

namespace QSampler {

//-------------------------------------------------------------------------
// QSampler::Messages - Messages log dockable window.
//

class Messages : public QDockWidget
{
	Q_OBJECT

public:

	// Constructor.
	Messages(QWidget *pParent);
	// Destructor.
	~Messages();

	// Stdout/stderr capture accessors.
	bool isCaptureEnabled();
	void setCaptureEnabled(bool bCapture);

	// Message font accessors.
	QFont messagesFont();
	void setMessagesFont(const QFont & font);

	// Maximum number of message lines accessors.
	int messagesLimit();
	void setMessagesLimit(int iMessagesLimit);

	// The main utility methods.
	void appendMessages(const QString& s);
	void appendMessagesColor(const QString& s, const QString &c);
	void appendMessagesText(const QString& s);

	// Stdout capture functions.
	void appendStdoutBuffer(const QString& s);
	void flushStdoutBuffer();

	// History reset.
	void clear();

signals:

	void visibilityChanged(bool bVisible);

protected slots:

	// overridden method of QWidget
	void showEvent(QShowEvent* event);

	// Stdout capture slot.
	void stdoutNotify(int fd);

private:

	// The maximum number of message lines.
	int m_iMessagesLines;
	int m_iMessagesLimit;
	int m_iMessagesHigh;

	// The textview main widget.
	QTextEdit *m_pTextView;

	// Stdout capture variables.
	QSocketNotifier *m_pStdoutNotifier;
	QString          m_sStdoutBuffer;
	int              m_fdStdout[2];
};

} // namespace QSampler

#endif  // __qsamplerMessages_h


// end of qsamplerMessages.h
