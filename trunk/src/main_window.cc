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

main_window::main_window(): client_ ( "Ruckus" )
{
        client_.connect( std::getenv( "XMMS_PATH" ) );
        client_.playback.currentID()( Xmms::bind( &main_window::my_current_id, this ), Xmms::bind( &main_window::error_handler, this ) );
        client_.setMainloop( new Xmms::GMainloop( client_.getConnection() ) );
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
	client_.playback.getStatus();
//	client_.playback.getStatus()( Xmms::bind( &main_window::set_play_pause, this ) );
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

bool main_window::my_current_id( const unsigned int& id )
{
        std::cout << "Currently playing ID is " << id << std::endl;
        client_.medialib.getInfo( id )( Xmms::bind( &main_window::my_get_info, this ), Xmms::bind( &main_window::error_handler, this ) );

        return false;
}

bool main_window::my_get_info( const Xmms::Dict& dict )
{
        std::string title = "<span font_desc=\"20\"><b>" + dict.get<std::string> ("title") + "</b></span>";
	std::string aa = "<b>" + dict.get<std::string> ("artist") + " - " + dict.get<std::string> ("album") + "</b>";
        song_title->set_label(title);
        artist_album->set_label(aa);
        std::cout << dict["artist"] << std::endl;
        std::cout << dict["album"] << std::endl;
        std::cout << dict["title"] << std::endl;
//      g_main_loop_quit( ml_ );
        return false;
}

bool main_window::error_handler( const std::string& error )
{
        std::cout << "Error" << " - " << error << std::endl;
        return false;
}

bool main_window::set_play_pause( const std::string& status )
{
        std::cout << status << std::endl;
        return false;
}
