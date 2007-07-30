bin_PROGRAMS = ruckus

ruckus_SOURCES = \
	ruckus.cc \
	xmms2client.cc \
	ruckusGUI_glade.cc \
	ruckusGUI.cc 

noinst_HEADERS = \
	xmms2client.hh \
	ruckusGUI_glade.hh \
	ruckusGUI.hh

AM_CXXFLAGS = -I/usr/include/xmms2 -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include @GTKMM_CFLAGS@ 
AM_LDFLAGS = -lxmmsclient -lxmmsclient++ -lxmmsclient-glib -lxmmsclient++-glib -lglib-2.0 -lpthread
ruckus_LDADD = @LIBS@ @GTKMM_LIBS@ 
