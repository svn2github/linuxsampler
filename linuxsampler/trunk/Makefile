CPP=g++
CC=gcc

CCOPTS=-pedantic -O3 -g -march=i686 -Wall

#LIB=-l

all: linuxsampler

linuxsampler:	linuxsampler.o RIFF.o DLS.o gig.o global.o stream.o diskthread.o audiothread.o audioio.o voice.o midiin.o thread.o
	$(CPP) $(LNOPTS) -o linuxsampler linuxsampler.o RIFF.o DLS.o gig.o global.o stream.o diskthread.o audiothread.o audioio.o voice.o midiin.o thread.o -lm -lpthread $(LIB) -lasound

linuxsampler.o:	linuxsampler.cpp
	$(CPP) $(CCOPTS) -c linuxsampler.cpp

global.o:	global.cpp
	$(CPP) $(CCOPTS) -c global.cpp

diskthread.o:	diskthread.cpp ringbuffer.h
	$(CPP) $(CCOPTS) -c diskthread.cpp

audiothread.o:	audiothread.cpp ringbuffer.h
	$(CPP) $(CCOPTS) -c audiothread.cpp

audioio.o:	audioio.cpp
	$(CPP) $(CCOPTS) -c audioio.cpp

voice.o:	voice.cpp ringbuffer.h
	$(CPP) $(CCOPTS) -c voice.cpp

stream.o:	stream.cpp ringbuffer.h
	$(CPP) $(CCOPTS) -c stream.cpp

midiin.o:	midiin.cpp ringbuffer.h
	$(CPP) $(CCOPTS) -c midiin.cpp

thread.o:	thread.cpp
	$(CPP) $(CCOPTS) -c thread.cpp

gig.o:		gig.cpp
	$(CPP) $(CCOPTS) -c gig.cpp

DLS.o:		DLS.cpp
	$(CPP) $(CCOPTS) -c DLS.cpp

RIFF.o:		RIFF.cpp
	$(CPP) $(CCOPTS) -c RIFF.cpp

clean:
	rm -vf linuxsampler *.o

