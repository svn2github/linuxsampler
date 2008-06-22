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
jack_src      = AudioOutputDeviceJack.cpp AudioOutputDeviceJack.h
jack_lflags   = $(JACK_LIBS)
jack_includes = $(JACK_CFLAGS)
else
jack_src      =
jack_lflags   =
jack_includes =
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

if HAVE_ASIO
asio_includes = -I@ASIOSDK_BASEDIR@/asiosdk2/common -I@ASIOSDK_BASEDIR@/asiosdk2/host -I@ASIOSDK_BASEDIR@/asiosdk2/host/pc
asio_3rd_party_src = @ASIOSDK_BASEDIR@/asiosdk2/common/asio.cpp @ASIOSDK_BASEDIR@/asiosdk2/common/asio.h @ASIOSDK_BASEDIR@/asiosdk2/host/asiodrivers.cpp @ASIOSDK_BASEDIR@/asiosdk2/host/asiodrivers.h @ASIOSDK_BASEDIR@/asiosdk2/host/pc/asiolist.cpp @ASIOSDK_BASEDIR@/asiosdk2/host/pc/asiolist.h
asio_src  = AudioOutputDeviceAsio.cpp AudioOutputDeviceAsio.h iasiothiscallresolver.cpp iasiothiscallresolver.h
asio_ladd =
else
asio_src  =
asio_3rd_party_src =
asio_includes  =
asio_ladd =
endif

liblinuxsampleraudiodriverincludedir = $(includedir)/linuxsampler/drivers/audio
liblinuxsampleraudiodriverinclude_HEADERS = \
	AudioChannel.h \
	AudioOutputDevice.h

INCLUDES = $(all_includes) $(arts_includes) $(asio_includes) $(jack_includes)

noinst_LTLIBRARIES = liblinuxsampleraudiodriver.la
liblinuxsampleraudiodriver_la_SOURCES = \
	AudioChannel.cpp AudioChannel.h \
	AudioOutputDevice.cpp AudioOutputDevice.h \
	AudioOutputDeviceFactory.cpp AudioOutputDeviceFactory.h \
	$(alsa_src) $(jack_src) $(arts_src) $(asio_src)
nodist_liblinuxsampleraudiodriver_la_SOURCES = \
	$(asio_3rd_party_src)
liblinuxsampleraudiodriver_la_LIBADD = $(alsa_ladd) $(arts_ladd)
liblinuxsampleraudiodriver_la_LDFLAGS = $(jack_lflags)
