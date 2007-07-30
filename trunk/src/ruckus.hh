#include "xmms2client.hh"
#include "ruckusGUI.hh"

class RuckusController
{
	public:
		RuckusController(int argc, char **argv);
		~RuckusController();
		
		xmms2client *x2c;
		ruckusGUI *gui;
};
