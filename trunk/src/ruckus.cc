// generated 2007/7/18 0:00:02 EDT by rmh3093@Redman.brcg.net
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to ruckus.cc_new

// This file is for your program, I won't touch it again!

#include <gtkmm/main.h>
#include "config.h"

#include "main_window.hh"

int main(int argc, char **argv)
{
	Gtk::Main m(&argc, &argv);
	main_window *mw = new class main_window();
	m.run(*mw);
	delete mw;
	return 0;
}
