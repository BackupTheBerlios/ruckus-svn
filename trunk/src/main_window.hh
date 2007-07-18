// generated 2007/7/13 10:43:00 EDT by rmh3093@Redman.brcg.net
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.hh_new

#include <xmmsclient/xmmsclient++.h>

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _main_window_HH
#  include "main_window_glade.hh"
#  define _main_window_HH
class main_window : public main_window_glade
{
	void on_togglebutton1_toggled();
	void on_button_play_clicked();
	void on_button_pause_clicked();
	void on_button_stop_clicked();
	void on_button_skip_back_clicked();
	void on_button_rewind_clicked();
	void on_button_fastforward_clicked();
	void on_refresh_button_clicked();
	void on_button_skip_forward_clicked();

	bool my_current_id( const unsigned int& id );
	bool my_broadcast_current_id( const unsigned int& id );
	bool error_handler( const std::string& error );
	bool set_play_pause( unsigned int status );
	bool set_info( const Xmms::Dict& dict );
	bool refresh_info( const Xmms::Dict& dict );

public:
	main_window();
	Xmms::Client client_;
};
#endif
