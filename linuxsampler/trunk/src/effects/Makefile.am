INCLUDES = $(all_includes)
AM_CXXFLAGS = -Wreturn-type -ffast-math $(CXX_CPU_SWITCH)

liblinuxsamplereffectsincludedir = $(includedir)/linuxsampler/effects
liblinuxsamplereffectsinclude_HEADERS = \
	Effect.h \
	EffectChain.h

noinst_LTLIBRARIES = liblinuxsamplereffects.la
liblinuxsamplereffects_la_SOURCES = \
	Effect.cpp Effect.h \
	EffectChain.cpp EffectChain.h
