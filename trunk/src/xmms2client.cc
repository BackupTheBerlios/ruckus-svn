#include "xmms2client.hh"
#include "ruckusGUI.hh"
#include <xmmsclient/xmmsclient++-glib.h>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>

using namespace std;
 
xmms2client::xmms2client(): client_ ( "Ruckus" )
{
	client_.connect( std::getenv( "XMMS_PATH" ) );
	client_.setMainloop( new Xmms::GMainloop( client_.getConnection() ) );
	track_info.duration = 9999999;
}

xmms2client::~xmms2client()
{
}

void xmms2client::connectGUI(ruckusGUI *gui)
{
	pgui = gui;
}

void xmms2client::init()
{
	track_info.up_to_date = false;
	track_info.scroll = false;
	client_.playback.getStatus()( Xmms::bind( &xmms2client::set_status, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.broadcastStatus()( Xmms::bind( &xmms2client::update_status, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.currentID()( Xmms::bind( &xmms2client::set_trackinfo_pre, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.getPlaytime()( Xmms::bind( &xmms2client::set_playtime, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.volumeGet()( Xmms::bind( &xmms2client::balance_channels, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.broadcastCurrentID()( Xmms::bind( &xmms2client::update_trackinfo_pre, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.signalPlaytime()( Xmms::bind( &xmms2client::update_playtime, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.broadcastVolumeChanged()( Xmms::bind( &xmms2client::update_volume, this ), Xmms::bind( &xmms2client::error_handler, this ) );
}

bool xmms2client::set_trackinfo_pre( const unsigned int& id )
{
	if (id != 0)
	{
		client_.medialib.getInfo( id )( Xmms::bind( &xmms2client::set_trackinfo, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	} else
	{
		client_.playback.start();
		client_.playback.pause();
		client_.playback.currentID()( Xmms::bind( &xmms2client::set_trackinfo_pre, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	}
	return false;
}

bool xmms2client::set_status( unsigned int status )
{
	track_info.status = status;
	if ((status == 0) || (status == 2))
	{
		pgui->label_play_pause->set_markup("<span foreground=\"white\" font_desc=\"12\"><b>Play</b></span>");
		pgui->image_pause->hide();
	} 
	else if (status == 1)
	{
		pgui->label_play_pause->set_markup("<span foreground=\"white\" font_desc=\"12\"><b>Pause</b></span>");
		pgui->image_play->hide();
	}
	return false;
}

bool xmms2client::update_status( unsigned int status )
{
	track_info.status = status;
	client_.playback.broadcastStatus()( Xmms::bind( &xmms2client::update_status, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	return false;
}

bool xmms2client::set_trackinfo( const Xmms::Dict& dict )
{
	track_info.id = dict.get<int> ("id");
	track_info.duration = dict.get<int> ("duration");
	track_info.duration_formated = pgui->convert_msec_to_time(dict.get<int> ("duration"));
	if (dict.contains("artist"))
	{
		track_info.artist = dict.get<string> ("artist");
	}
	else
	{
		track_info.artist = "None";
	}
	if (dict.contains("title"))
	{
		track_info.title = dict.get<string> ("title");
	}
	else
	{
		track_info.title = "None";
	}
	track_info.up_to_date = true;
	pgui->init();
	return false;
}

void xmms2client::get_playlist()
{
	client_.playlist.listEntries()( Xmms::bind( &xmms2client::get_current_queue, this ), Xmms::bind( &xmms2client::error_handler, this ) );
}

bool xmms2client::set_playlist( const Xmms::Dict& dict )
{
	row = *(pgui->m_refTreeModel->append());
	string temp;
	stringstream id;
	id << dict.get<int> ("id");
	row[pgui->m_PModel.m_col_id] = "<span foreground=\"white\" font_desc=\"16\"><b>" + id.str() + "</b></span>";
	if (dict.contains("title"))
	{
		temp = dict.get<string> ("title");
		temp = pgui->remove_amp(temp);
		row[pgui->m_PModel.m_col_title] = "<span foreground=\"white\" font_desc=\"16\"><b>" + temp + "</b></span>";
	}
	else
	{
		row[pgui->m_PModel.m_col_title] = "<span foreground=\"white\" font_desc=\"16\"><b>None</b></span>";
	}
	if (dict.contains("artist"))
	{
		temp = dict.get<string> ("artist");
		temp = pgui->remove_amp(temp);
		row[pgui->m_PModel.m_col_artist] = "<span foreground=\"white\" font_desc=\"16\"><b>" + temp + "</b></span>";
	}
	else
	{
		row[pgui->m_PModel.m_col_artist] = "<span foreground=\"white\" font_desc=\"16\"><b>None</b></span>";
	}
	if (dict.contains("album"))
	{
		temp = dict.get<string> ("album");
		temp = pgui->remove_amp(temp);
		row[pgui->m_PModel.m_col_album] = "<span foreground=\"white\" font_desc=\"16\"><b>" + temp + "</b></span>";
	}
	else
	{
		row[pgui->m_PModel.m_col_album] = "<span foreground=\"white\" font_desc=\"16\"><b>None</b></span>";
	}
}

bool xmms2client::update_trackinfo_pre( const unsigned int& id )
{
	client_.medialib.getInfo( id )( Xmms::bind( &xmms2client::update_trackinfo, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	client_.playback.broadcastCurrentID()( Xmms::bind( &xmms2client::update_trackinfo_pre, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	return false;
}

bool xmms2client::update_trackinfo( const Xmms::Dict& dict )
{
	track_info.id = dict.get<int> ("id");
	track_info.duration = dict.get<int> ("duration");
	track_info.duration_formated = pgui->convert_msec_to_time(dict.get<int> ("duration"));
	if (dict.contains("artist"))
	{
		track_info.artist = dict.get<string> ("artist");
	}
	else
	{
		track_info.artist = "None";
	}
	if (dict.contains("title"))
	{
		track_info.title = dict.get<string> ("title");
	}
	else
	{
		track_info.title = "None";
	}
	track_info.up_to_date = true;
	pgui->display_track_title();
	return false;
}

bool xmms2client::set_playtime ( const unsigned int& pt )
{
	track_info.playtime = pt;
	return false;
}

bool xmms2client::update_playtime ( const unsigned int& pt )
{
	track_info.playtime = pt;
	pgui->display_playtime();
	pgui->display_position();
	client_.playback.signalPlaytime()( Xmms::bind( &xmms2client::update_playtime, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	return false;
}

void xmms2client::set_volume(unsigned int vol)
{
	client_.playback.volumeSet("left",vol);
	client_.playback.volumeSet("right",vol);
}

bool xmms2client::balance_channels (const Xmms::Dict& dict )
{
	volume = dict.get<uint32_t>("left");
	set_volume(volume);
	if (volume == 0)
	{
		pgui->image_nomute->show();
		pgui->image_mute->hide();
		pgui->label_mute->set_markup("<span foreground=\"white\"><b>Unmute</b></span>");
	}
	else
	{
		pgui->image_nomute->hide();
		pgui->image_mute->show();
		pgui->label_mute->set_markup("<span foreground=\"white\"><b>Mute</b></span>");
	}
	return false;
}

bool xmms2client::update_volume (const Xmms::Dict& dict )
{
	volume = dict.get<uint32_t>("left");
	set_volume(volume);
	pgui->display_volume();
	client_.playback.broadcastVolumeChanged()( Xmms::bind( &xmms2client::update_volume, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	return false;
}

bool xmms2client::get_current_queue(const Xmms::List< unsigned int > &list)
{
	for (list.first (); list.isValid (); ++list) {
		client_.medialib.getInfo( *list )( Xmms::bind( &xmms2client::set_playlist, this ), Xmms::bind( &xmms2client::error_handler, this ) );
	}
	return false;
}

bool xmms2client::error_handler( const string& error )
{
	cout << "Error" << " - " << error << endl;
	return false;
}
