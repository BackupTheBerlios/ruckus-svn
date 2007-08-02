#include "xmms2client.hh"
#include "ruckusGUI.hh"
#include <xmmsclient/xmmsclient++-glib.h>
#include <boost/bind.hpp>
#include <iostream>
#include <iterator>
#include <sstream>

using namespace std;
 
xmms2client::xmms2client(): client_ ( "Ruckus" )
{
	client_.connect( std::getenv( "XMMS_PATH" ) );
	client_.setMainloop( new Xmms::GMainloop( client_.getConnection() ) );
}

xmms2client::~xmms2client()
{
}

void xmms2client::connectGUI(ruckusGUI *gui)
{
	pgui = gui;
}

void xmms2client::collect_initial_data()
{
	client_.playlist.currentPos()( Xmms::bind( &xmms2client::get_current_playlist_position, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	
	client_.playlist.currentActive()( Xmms::bind( &xmms2client::get_current_playlist_name, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while(current_playlist_name.length()==0) {
		g_main_context_iteration(NULL, true);
	}
	
	client_.playlist.listEntries(current_playlist_name)( Xmms::bind( &xmms2client::get_current_playlist_tracks, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while((current_playlist_tracks.empty())) {
		g_main_context_iteration(NULL, true);
	}
	
	client_.playback.currentID()( Xmms::bind( &xmms2client::set_trackinfo_pre, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while(!(current_song_id)) {
		g_main_context_iteration(NULL, true);
	}

	/*while(!(current_playlist_position)) {
		g_main_context_iteration(NULL, true);
	}
	pgui->display_track_title();**/

	client_.playback.volumeGet()( Xmms::bind( &xmms2client::balance_channels, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastVolumeChanged()( Xmms::bind( &xmms2client::update_volume, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
}

void xmms2client::init()
{
	client_.playback.getStatus()( Xmms::bind( &xmms2client::set_status, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastStatus()( Xmms::bind( &xmms2client::update_status, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.getPlaytime()( Xmms::bind( &xmms2client::set_playtime, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.signalPlaytime()( Xmms::bind( &xmms2client::update_playtime, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastCurrentID()( Xmms::bind( &xmms2client::update_trackinfo_pre, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	//client_.playlist.list()( Xmms::bind( &xmms2client::get_list_of_playlists, this ), boost::bind( &xmms2client::error_handler, this, "playlist.list()", _1 ) );
}

bool xmms2client::set_trackinfo_pre( const unsigned int& id )
{
	current_song_id = id;
	if (current_song_id == 0)
	{
		current_song_id = current_playlist_tracks.at(0);
		current_playlist_position = 1;
	}
	cout << current_song_id << endl;
	cout << current_playlist_position << endl;
	return false;
}

bool xmms2client::get_list_of_playlists(const Xmms::List< string > &l_playlists)
{
	list_of_playlists.clear();
	for (l_playlists.first(); l_playlists.isValid(); ++l_playlists) {
		list_of_playlists.push_back(*l_playlists);
	}
	/*
	for (iter_list_of_playlists=list_of_playlists.begin(); iter_list_of_playlists != list_of_playlists.end(); iter_list_of_playlists++) {
		cout << *iter_list_of_playlists << endl;
	}
	**/
	return false;
}

bool xmms2client::get_current_playlist_name(const string &s_current_playlist_name)
{
	current_playlist_name = s_current_playlist_name;
	return false;
}

void xmms2client::update_playlist()
{
	int i = 0;
	while (i<current_playlist_count) {
		client_.medialib.getInfo( current_playlist_tracks.at(i) )( boost::bind( &xmms2client::set_current_playlist_tracks, this, i, _1 ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
		++ i;
	}
	while(current_playlist.size()<current_playlist_count) {
		g_main_context_iteration(NULL, true);
	}
	map<unsigned int, struct TrackDB>::iterator it = current_playlist.begin(), stop = current_playlist.end();
    for ( ; it != stop; it ++) {
    	TrackDB info = it->second;
    	row = *(pgui->m_refTreeModel->append());
    	stringstream pos, currid;
    	pos << it->first;
    	currid << info.id;
    	string color = "white";
    	if (info.id==current_song_id) {
    		color = "red";
    	}
    	row[pgui->m_PModel.m_col_id] = "<span foreground=\"" + color + "\" font_desc=\"10\"><b>[" + pos.str() + "/" + currid.str() + "]</b></span>";
    	string temp_title, temp_artist, temp_album;
		temp_title = pgui->remove_amp(info.title);
		temp_artist = pgui->remove_amp(info.artist);
		temp_album = pgui->remove_amp(info.album);
		row[pgui->m_PModel.m_col_title] = "<span foreground=\"" + color + "\" font_desc=\"14\"><b>" + temp_title + "</b></span>\n<span foreground=\"" + color + "\" font_desc=\"10\"><b>Artist: " + temp_artist + "</b></span>\n<span foreground=\"" + color + "\" font_desc=\"10\"><b>Album: " + temp_album + "</b></span>";
		pgui->playlist_view->show_all();
    }
}

bool xmms2client::get_current_playlist_tracks(const Xmms::List< unsigned int > &l_tracks)
{
	int i = 0;
	current_playlist_tracks.clear();
	for (l_tracks.first (); l_tracks.isValid (); ++l_tracks) {
		current_playlist_tracks.push_back(*l_tracks);
		++ i;
	}
	current_playlist_count = i;
	return false;
}

bool xmms2client::get_current_playlist_position( unsigned int position )
{
	current_playlist_position = position;
}

bool xmms2client::set_status( unsigned int status )
{
	//track_info.status = status;
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
	//track_info.status = status;
	client_.playback.broadcastStatus()( Xmms::bind( &xmms2client::update_status, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	return false;
}

bool xmms2client::set_trackinfo( const Xmms::Dict& dict )
{
	return false;
}

void xmms2client::get_playlist()
{
	client_.playlist.listEntries()( Xmms::bind( &xmms2client::get_current_playlist_tracks, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
}

bool xmms2client::set_current_playlist_tracks( const unsigned int i, const Xmms::Dict& dict )
{
	TrackDB track_info;
	track_info.id = dict.get<int> ("id");
	track_info.duration = dict.get<int> ("duration");
	track_info.duration_formated = pgui->convert_msec_to_time(dict.get<int> ("duration"));
	if (dict.contains("artist")) {
		track_info.artist = dict.get<string> ("artist");
	} else {
		track_info.artist = "None";
	}
	if (dict.contains("title")) {
		track_info.title = dict.get<string> ("title");
	} else {
		track_info.title = "None";
	}
	if (dict.contains("album")) {
		track_info.album = dict.get<string> ("album");
	} else {
		track_info.album = "None";
	}
	current_playlist.insert(map<unsigned int, struct TrackDB>::value_type(i,track_info));
}

bool xmms2client::update_current_playlist_tracks( const unsigned int i, const Xmms::Dict& dict )
{
}

bool xmms2client::update_trackinfo_pre( const unsigned int& id )
{
	client_.medialib.getInfo( id )( Xmms::bind( &xmms2client::update_trackinfo, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastCurrentID()( Xmms::bind( &xmms2client::update_trackinfo_pre, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	return false;
}

bool xmms2client::update_trackinfo( const Xmms::Dict& dict )
{
	//track_info.id = dict.get<int> ("id");
	//track_info.duration = dict.get<int> ("duration");
	//track_info.duration_formated = pgui->convert_msec_to_time(dict.get<int> ("duration"));
	if (dict.contains("artist"))
	{
		//track_info.artist = dict.get<string> ("artist");
	}
	else
	{
		//track_info.artist = "None";
	}
	if (dict.contains("title"))
	{
		//track_info.title = dict.get<string> ("title");
	}
	else
	{
		//track_info.title = "None";
	}
	return false;
}

bool xmms2client::set_playtime ( const unsigned int& pt )
{
	//track_info.playtime = pt;
	return false;
}

bool xmms2client::update_playtime ( const unsigned int& pt )
{
	//track_info.playtime = pt;
	pgui->display_playtime();
	pgui->display_position();
	client_.playback.signalPlaytime()( Xmms::bind( &xmms2client::update_playtime, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
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
	pgui->display_volume();
	return false;
}

bool xmms2client::update_volume (const Xmms::Dict& dict )
{
	volume = dict.get<uint32_t>("left");
	set_volume(volume);
	pgui->display_volume();
	client_.playback.broadcastVolumeChanged()( Xmms::bind( &xmms2client::update_volume, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	return false;
}

bool xmms2client::error_handler( const string& token, const string& error )
{
	cout << token << endl;
	if ((token=="client_.playlist.list()") & (error=="List out of range or empty list")) {
		cout << "There are no playlists" << endl;
	} else {
		cout << "Error" << " - " << error << endl;
	}
	return false;
}
