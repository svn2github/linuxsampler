INCLUDES = $(all_includes)
METASOURCES = AUTO

AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

if HAVE_ALSA
alsa_src  = MidiInputDeviceAlsa.cpp MidiInputDeviceAlsa.h
alsa_ladd = -lasound
else
alsa_src  =
alsa_ladd =
endif

noinst_LTLIBRARIES = liblinuxsamplermididriver.la
liblinuxsamplermididriver_la_SOURCES = MidiInputDevice.cpp MidiInputDevice.h MidiInputDeviceFactory.h MidiInputDeviceFactory.cpp MidiInputPort.cpp MidiInputPort.h $(alsa_src)
liblinuxsamplermididriver_la_LIBADD = $(alsa_ladd)
