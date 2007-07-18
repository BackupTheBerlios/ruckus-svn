# generated 2007/7/15 8:40:36 EDT by rmh3093@Redman.brcg.net
# using glademm V2.6.0
#
# newer (non customized) versions of this file go to Makefile.am_new

bin_PROGRAMS = ruckus

ruckus_SOURCES = \
	ruckus.cc \
	main_window_glade.cc \
	main_window.cc 

noinst_HEADERS = \
	main_window_glade.hh \
	main_window.hh 

AM_CXXFLAGS = -I/usr/include/xmms2 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include @GTKMM_CFLAGS@ 
AM_LDFLAGS = -lxmmsclient -lxmmsclient++ -lxmmsclient-glib -lxmmsclient++-glib -lglib-2.0
ruckus_LDADD = @LIBS@ @GTKMM_LIBS@ 
