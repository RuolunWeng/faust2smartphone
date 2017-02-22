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
	