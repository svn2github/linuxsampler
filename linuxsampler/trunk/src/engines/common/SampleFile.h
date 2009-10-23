/***************************************************************************
 *                                                                         *
 *   LinuxSampler - modular, streaming capable sampler                     *
 *                                                                         *
 *   Copyright (C) 2003 - 2009 Christian Schoenebeck                       *
 *   Copyright (C) 2009 Grigor Iliev                                       *
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

#ifndef __LS_SAMPLEFILE_H__
#define __LS_SAMPLEFILE_H__

#include "Sample.h"

#include <sndfile.h>
#include "../../common/global.h"


namespace LinuxSampler {
    class SampleFile : public Sample {
        public:
            SampleFile(String File, bool DontClose = false);
            virtual ~SampleFile();

            String GetFile() { return File; }

            virtual String  GetName() { return File; }
            virtual int     GetSampleRate() { return SampleRate; }
            virtual int     GetChannelCount() { return ChannelCount; }
            virtual long    GetTotalFrameCount() { return TotalFrameCount; }
            virtual int     GetFrameSize() { return FrameSize; }

            virtual buffer_t  LoadSampleData();
            virtual buffer_t  LoadSampleData(unsigned long FrameCount);
            virtual buffer_t  LoadSampleDataWithNullSamplesExtension(uint NullFrameCount);
            virtual buffer_t  LoadSampleDataWithNullSamplesExtension(unsigned long FrameCount, uint NullFramesCount);
            virtual void      ReleaseSampleData();
            virtual buffer_t  GetCache();
            virtual long      Read(void* pBuffer, unsigned long FrameCount);

            virtual unsigned long ReadAndLoop (
                void*           pBuffer,
                unsigned long   FrameCount,
                PlaybackState*  pPlaybackState
            );

            virtual long SetPos(unsigned long FrameOffset);
            virtual long GetPos();

            void Open();
            void Close();

        private:
            String File;
            int    SampleRate;
            int    ChannelCount;
            int    Format;
            int    FrameSize;         ///< In bytes
            long   TotalFrameCount;

            SNDFILE* pSndFile;

            buffer_t RAMCache;        ///< Buffers samples (already uncompressed) in RAM.
            long SetPos(unsigned long FrameCount, int Whence);
    };
} // namespace LinuxSampler

#endif // __LS_SAMPLEFILE_H__
