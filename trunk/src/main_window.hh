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
	bool on_progressbar_button_press_event(GdkEventButton *ev);
	bool on_progressbar_button_release_event(GdkEventButton *ev);
	void on_fullscreen_button_toggled();
	void on_quit_button_clicked();
	void on_button_play_clicked();
	void on_button_pause_clicked();
	void on_button_stop_clicked();
	void on_button_skip_back_clicked();
	void on_button_rewind_clicked();
	void on_button_fastforward_clicked();
	void on_refresh_button_clicked();
	void on_button_skip_forward_clicked();

	bool my_signal_playtime( const unsigned int& pt );
	bool my_broadcast_current_id( const unsigned int& id );
	bool error_handler( const std::string& error );
	std::string remove_amp( std::string& string );
	bool set_play_pause( unsigned int status );
	bool set_info( const Xmms::Dict& dict );

	unsigned int curr_duration;

public:
	main_window();
	Xmms::Client client_;
};
#endif
