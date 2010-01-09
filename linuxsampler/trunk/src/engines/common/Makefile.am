INCLUDES = $(all_includes) $(SNDFILE_CFLAGS) $(GIG_CFLAGS)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

noinst_LTLIBRARIES = liblinuxsamplercommonengine.la
liblinuxsamplercommonengine_la_SOURCES = \
	BiquadFilter.h \
	Event.cpp Event.h \
	Sample.h SampleManager.h SampleFile.cpp SampleFile.h \
	Stream.h StreamBase.cpp StreamBase.h \
	DiskThreadBase.cpp DiskThreadBase.h \
	Voice.h AbstractVoice.cpp AbstractVoice.h VoiceBase.h \
	MidiKeyboardManager.h \
	LFOBase.h \
	LFOTriangleDiHarmonic.h \
	LFOTriangleIntAbsMath.h \
	LFOTriangleIntMath.h \
	Resampler.h
liblinuxsamplercommonengine_la_LIBADD = $(SNDFILE_LIBS)
liblinuxsamplercommonengine_la_LDFLAGS = $(SNDFILE_CFLAGS)
