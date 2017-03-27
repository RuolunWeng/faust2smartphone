DESTDIR ?=
PREFIX ?= /usr/local

MAKEFILE := Makefile.unix

prefix := $(DESTDIR)$(PREFIX)
dest   := $(prefix)/bin

help:
	###############################################
	@echo This is a makefile to install faust2smartphone.
	@echo Tap sudo make install to install
	@echo The files will install in the folder of FAUST
	@echo Make sure you have install Faust first
	###############################################
install:

	##################################      
	#### Install faust2smartphone ####
	##################################
	install faust2smartphone $(dest)	
	rm -rf $(prefix)/share/faust/smartphone
	cp -r smartphone $(prefix)/share/faust/
	
	##############################    
	#### Install Motion Files ####
	##############################
	cp -r motion/audio2.h $(prefix)/include/faust/audio
	cp -r motion/motion-audio.h $(prefix)/include/faust/audio
	cp -r motion/faust-motion-engine.h $(prefix)/include/faust/dsp
	cp -r motion/faust-poly-engine_a.h $(prefix)/include/faust/dsp
	
	########################################
	#### Install faustapi version Allen ####
	########################################
	install faust2api_a $(dest)
	cp -r api-allen $(prefix)/share/faust/
	

uninstall:
	
	#### Uninstall faust2smartphone ####
	rm -rf $(prefix)/share/faust/smartphone
	rm -f $(dest)/faust2api_a	
	rm -f $(dest)/faust2smartphone
	