// generated 2007/7/13 10:43:00 EDT by rmh3093@Redman.brcg.net
// using glademm V2.6.0
//
// newer (non customized) versions of this file go to main_window.cc_new

// This file is for your program, I won't touch it again!

#include <xmmsclient/xmmsclient++.h>
#include <xmmsclient/xmmsclient++-glib.h>
#include <iostream>
#include <cstdlib>
#include "config.h"
#include "main_window.hh"
#include <boost/bind.hpp>
// #include <gdkmm/colormap.h> // Enable this to set colors

main_window::main_window(): client_ ( "Ruckus" )
{
        client_.connect( std::getenv( "XMMS_PATH" ) );
        client_.playback.currentID()( Xmms::bind( &main_window::my_current_id, this ), Xmms::bind( &main_window::error_handler, this ) );
        client_.playback.broadcastCurrentID()( Xmms::bind( &main_window::my_broadcast_current_id, this ), Xmms::bind( &main_window::error_handler, this ) );
        client_.playback.signalPlaytime()( Xmms::bind( &main_window::my_signal_playtime, this ), Xmms::bind( &main_window::error_handler, this ) );
        client_.setMainloop( new Xmms::GMainloop( client_.getConnection() ) );
//	song_info_eventbox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("blue"));
}

void main_window::on_togglebutton1_toggled()
{
	if (togglebutton1->get_active()) {
		fullscreen();
		fullscreen_togglebutton_label->set_label("UnFullscreen");
	} else {
		unfullscreen();
 		fullscreen_togglebutton_label->set_label("Fullscreen");
	}
	fullscreen_togglebutton_label->show();
}

void main_window::on_button_play_clicked()
{
	client_.playback.getStatus()( Xmms::bind( &main_window::set_play_pause, this ), Xmms::bind( &main_window::error_handler, this ) );
}

void main_window::on_button_skip_back_clicked()
{
	client_.playlist.setNextRel(-1);
	client_.playback.tickle();
}

void main_window::on_button_rewind_clicked()
{
}

void main_window::on_button_fastforward_clicked()
{
}

void main_window::on_button_skip_forward_clicked()
{
	client_.playlist.setNextRel(1);
	client_.playback.tickle();
}

void main_window::on_refresh_button_clicked()
{
}

bool main_window::my_signal_playtime( const unsigned int& pt )
{
	int hours, minutes, seconds;
	hours = (pt/(60*60*1000))%24;
	minutes = (pt/(60*1000))%60;
	seconds = (pt/1000)%60;
	char buffer[33];
	sprintf(buffer,"<span font_desc=\"16\"><b>%.2i:%.2i:%.2i</b></span>",hours,minutes,seconds);
	play_time->set_markup(buffer);
	client_.playback.signalPlaytime()( Xmms::bind( &main_window::my_signal_playtime, this ), Xmms::bind( &main_window::error_handler, this ) );
}

bool main_window::my_current_id( const unsigned int& id )
{
        std::cout << "Currently playing ID is " << id << std::endl;
        client_.medialib.getInfo( id )( Xmms::bind( &main_window::set_info, this ), Xmms::bind( &main_window::error_handler, this ) );
        return false;
}

bool main_window::my_broadcast_current_id( const unsigned int& id )
{
        std::cout << "Currently playing ID is " << id << std::endl;
        client_.medialib.getInfo( id )( Xmms::bind( &main_window::set_info, this ), Xmms::bind( &main_window::error_handler, this ) );
 		client_.playback.broadcastCurrentID()( Xmms::bind( &main_window::my_broadcast_current_id, this ), Xmms::bind( &main_window::error_handler, this ) );
        return false;
}

bool main_window::set_info( const Xmms::Dict& dict )
{
        std::string title = "<span font_desc=\"20\"><b>" + dict.get<std::string> ("title") + "</b></span>";
		std::string aa = "<span font_desc=\"16\"><b>" + dict.get<std::string> ("artist") + " - " + dict.get<std::string> ("album") + "</b></span>";
		size_t amp = aa.find("&");
		if (amp != std::string::npos)
			aa.replace(amp,1,"&amp;");
		amp = title.find("&");
		if (amp != std::string::npos)
			title.replace(amp,1,"&amp;");
        song_title->set_markup(title);
        artist_album->set_markup(aa);
        std::cout << title << std::endl;
        std::cout << aa << std::endl;
        return false;
}

bool main_window::error_handler( const std::string& error )
{
        std::cout << "Error" << " - " << error << std::endl;
        return false;
}

bool main_window::set_play_pause( unsigned int status )
{
	if ( (status == 0 | status == 2 ) )
		client_.playback.start();
	if ( status == 1 )
		client_.playback.pause();
		
	return false;
}
