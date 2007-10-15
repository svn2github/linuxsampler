METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

if HAVE_ALSA
alsa_src  = AudioOutputDeviceAlsa.cpp AudioOutputDeviceAlsa.h
alsa_ladd = -lasound
else
alsa_src  =
alsa_ladd =
endif

if HAVE_JACK
jack_src    = AudioOutputDeviceJack.cpp AudioOutputDeviceJack.h
jack_lflags = $(JACK_LIBS)
else
jack_src    =
jack_lflags =
endif

if HAVE_ARTS
arts_src      = AudioOutputDeviceArts.cpp AudioOutputDeviceArts.h
arts_ladd     = @ARTS_LIBS@
arts_includes = @ARTS_CFLAGS@
else
arts_src      =
arts_ladd     =
arts_includes =
endif

liblinuxsampleraudiodriverincludedir = $(includedir)/linuxsampler/drivers/audio
liblinuxsampleraudiodriverinclude_HEADERS = \
	AudioChannel.h \
	AudioOutputDevice.h

INCLUDES = $(all_includes) $(arts_includes)

noinst_LTLIBRARIES = liblinuxsampleraudiodriver.la
liblinuxsampleraudiodriver_la_SOURCES = \
	AudioChannel.cpp AudioChannel.h \
	AudioOutputDevice.cpp AudioOutputDevice.h \
	AudioOutputDeviceFactory.cpp AudioOutputDeviceFactory.h \
	$(alsa_src) $(jack_src) $(arts_src)
liblinuxsampleraudiodriver_la_LIBADD = $(alsa_ladd) $(arts_ladd)
liblinuxsampleraudiodriver_la_LDFLAGS = $(jack_lflags)
