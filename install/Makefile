# Default values
DESTDIR ?=
PREFIX ?=

# If PREFIX is not set, default to /usr/local
ifeq ($(PREFIX),)
    prefix := /usr/local
else
    prefix := $(DESTDIR)$(PREFIX)
endif

# Destination bin directory
dest := $(prefix)/bin


help:
	###############################################
	@echo This is a makefile to install faust2smartphone.
	@echo Tap sudo make install to install
	@echo The files will install in the folder of FAUST
	@echo Make sure you have install Faust first
	###############################################

# Install rule
install:
	##################################
	@echo "Installing faust2smartphone to $(dest)"
	##################################
	#### Smart Hand Computer tool ####
	##################################
	install faust2smartphone $(dest)
	rm -rf $(prefix)/share/faust/smartphone
	cp -r smartphone $(prefix)/share/faust/

	##############################
	#### Install Motion Files ####
	##############################
	rm -rf $(prefix)/include/faust/audio/audio_m.h
	rm -rf $(prefix)/include/faust/audio/motion-audio.h
	rm -rf $(prefix)/include/faust/dsp/faust-poly-engine_m.h
	rm -rf $(prefix)/include/faust/dsp/faust-motion-engine.h
	cp -r motion/audio_m.h $(prefix)/include/faust/audio
	cp -r motion/motion-audio.h $(prefix)/include/faust/audio
	cp -r motion/faust-motion-engine.h $(prefix)/include/faust/dsp
	cp -r motion/faust-poly-engine_m.h $(prefix)/include/faust/dsp

	########################################
	#### Install faustapi version Allen ####
	########################################
	install faust2api_a $(dest)
	rm -rf $(prefix)/share/faust/api-allen
	cp -r api-allen $(prefix)/share/faust/


uninstall:

	#### Uninstall faust2smartphone ####
	rm -rf $(prefix)/include/faust/audio/audio_m.h
	rm -rf $(prefix)/include/faust/audio/motion-audio.h
	rm -rf $(prefix)/include/faust/dsp/faust-poly-engine_m.h
	rm -rf $(prefix)/include/faust/dsp/faust-motion-engine.h
	rm -rf $(prefix)/share/faust/api-allen
	rm -rf $(prefix)/share/faust/smartphone
	rm -f $(dest)/faust2api_a
	rm -f $(dest)/faust2smartphone
