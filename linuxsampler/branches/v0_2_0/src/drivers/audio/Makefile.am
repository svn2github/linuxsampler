INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -ffast-math -march=$(target_cpu) -mcpu=$(target_cpu)

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

noinst_LTLIBRARIES = liblinuxsampleraudiodriver.la
liblinuxsampleraudiodriver_la_SOURCES = AudioChannel.cpp AudioChannel.h AudioOutputDevice.cpp AudioOutputDevice.h AudioOutputDeviceFactory.h AudioOutputDeviceFactory.cpp $(alsa_src) $(jack_src)
liblinuxsampleraudiodriver_la_LIBADD = $(alsa_ladd)
liblinuxsampleraudiodriver_la_LDFLAGS = $(jack_lflags)
