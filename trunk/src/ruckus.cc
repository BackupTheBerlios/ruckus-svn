#include <config.h>
#include <gtkmm/main.h>
#include <pthread.h>
#include <sched.h>

#include "xmms2client.hh"
#include "ruckusGUI.hh"

xmms2client *px2c;
ruckusGUI *pgui;

int main(int argc, char **argv)
{
	Gtk::Main m(&argc, &argv);
	px2c = new xmms2client();
	pgui = new ruckusGUI(px2c);
	px2c->connectGUI(pgui);
	px2c->init();
	m.run(*pgui);
	delete pgui;
	delete px2c;
	return 0;
}
