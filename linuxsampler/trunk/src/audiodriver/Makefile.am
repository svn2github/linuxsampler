INCLUDES = $(all_includes)
METASOURCES = AUTO

noinst_LTLIBRARIES = liblinuxsampleraudiodriver.la
liblinuxsampleraudiodriver_la_SOURCES = AudioChannel.cpp AudioChannel.h AudioOutputDevice.cpp AudioOutputDevice.h AudioOutputDeviceAlsa.cpp AudioOutputDeviceAlsa.h AudioOutputDeviceJack.cpp AudioOutputDeviceJack.h
liblinuxsampleraudiodriver_la_LDFLAGS = $(JACK_LIBS)
#liblinuxsampleraudiodriver_la_DEPENDENCIES = $(JACK_LIBS)
liblinuxsampleraudiodriver_la_LIBADD = -lasound
