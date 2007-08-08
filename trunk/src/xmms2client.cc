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
	client_.quit();
}

void xmms2client::connectGUI(ruckusGUI *gui)
{
	pgui = gui;
}

void xmms2client::collect_initial_data()
{
	volume_state = false;
	current_track_state = false;
	current_track_ready = true;
	playback_status_state = false;
	current_playlist_position = false;
	client_.playlist.currentActive()( Xmms::bind( &xmms2client::get_current_playlist_name, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while(current_playlist_name.length()==0) {
		g_main_context_iteration(NULL, true);
	}
	cout << "Current Playlist Name: " << current_playlist_name << endl;
	
	client_.playlist.listEntries(current_playlist_name)( Xmms::bind( &xmms2client::get_current_playlist_tracks, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while((current_playlist_tracks.empty())) {
		g_main_context_iteration(NULL, true);
	}
	cout << "Current Playlist Tracks: " << current_playlist_tracks.size() << endl;
	
	client_.playback.currentID()( Xmms::bind( &xmms2client::set_trackinfo_pre, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while(current_song_id==0) {
		g_main_context_iteration(NULL, true);
	}
	cout << "Current Song ID: " << current_song_id << endl;
	
	while(current_track_state == false) {
		g_main_context_iteration(NULL, true);
		cout << "waiting" << endl;
	}
	
	if (current_track_ready == false) {
		current_playlist_position = 0;
		playback_playtime = 0;
		playback_status = 0;
	} else {
		client_.playlist.currentPos()( Xmms::bind( &xmms2client::get_current_playlist_position, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
		while(current_playlist_position_state == false) {
			g_main_context_iteration(NULL, true);
		}
		client_.playback.getPlaytime()( Xmms::bind( &xmms2client::set_playtime, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
		while(!(playback_playtime)) {
			g_main_context_iteration(NULL, true);
		}
		client_.playback.getStatus()( Xmms::bind( &xmms2client::set_status, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
		while(playback_status_state == false) {
			g_main_context_iteration(NULL, true);
		}
	}
	cout << "Current Playlist Position: " << current_playlist_position << endl;
	cout << "Current Playtime: " << playback_playtime << endl;
	cout << "Current Playback Status: " << playback_status << endl;
	
	client_.medialib.getInfo( current_song_id )( Xmms::bind( &xmms2client::get_track_info, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while(!(current_track_info.id)) {
		g_main_context_iteration(NULL, true);
	}
	cout << "Current Song Title: " << current_track_info.title << endl;

	client_.playback.volumeGet()( Xmms::bind( &xmms2client::set_volume, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	while(volume_state == false) {
		g_main_context_iteration(NULL, true);
	}
	cout << "Current Volume: " << volume << endl;
}

void xmms2client::init()
{
	client_.playback.broadcastVolumeChanged()( Xmms::bind( &xmms2client::update_volume, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastStatus()( Xmms::bind( &xmms2client::update_status, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.signalPlaytime()( Xmms::bind( &xmms2client::update_playtime, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastCurrentID()( Xmms::bind( &xmms2client::update_track_info_pre, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
}

bool xmms2client::set_trackinfo_pre( const unsigned int& id )
{
	if (id == 0) {
		current_song_id = current_playlist_tracks.at(0);
		current_track_state = true;
		current_track_ready = false;

	} else {
		current_song_id = id;
		current_track_state = true;
	}
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
	/*while (i<current_playlist_count) {
		client_.medialib.getInfo( current_playlist_tracks.at(i) )( boost::bind( &xmms2client::set_current_playlist_tracks, this, i, _1 ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
		++ i;
	}**/
	while(current_playlist.size()<current_playlist_count) {
		g_main_context_iteration(NULL, true);
	}
	map<unsigned int, struct TrackINFO>::iterator it = current_playlist.begin(), stop = current_playlist.end();
    for ( ; it != stop; it ++) {
    	TrackINFO info = it->second;
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
		pgui->playlist_view->show_all_children();
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
	current_playlist_position_state = true;
	return false;
}

bool xmms2client::set_status( unsigned int status )
{
	playback_status = status;
	playback_status_state = true;
	return false;
}

bool xmms2client::update_status( unsigned int status )
{
	playback_status = status;
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

bool xmms2client::get_track_info( const Xmms::Dict& dict )
{
	current_track_info.id = dict.get<int> ("id");
	current_track_info.duration = dict.get<int> ("duration");
	current_track_info.duration_formated = pgui->convert_msec_to_time(dict.get<int> ("duration"));
	if (dict.contains("artist")) {
		current_track_info.artist = dict.get<string> ("artist");
	} else {
		current_track_info.artist = "None";
	}
	if (dict.contains("title")) {
		current_track_info.title = dict.get<string> ("title");
	} else {
		current_track_info.title = "None";
	}
	if (dict.contains("album")) {
		current_track_info.album = dict.get<string> ("album");
	} else {
		current_track_info.album = "None";
	}
	return false;
}

bool xmms2client::update_track_info( const Xmms::Dict& dict )
{
	pgui->scroll_timer.disconnect();
	current_track_info.id = dict.get<int> ("id");
	current_track_info.duration = dict.get<int> ("duration");
	current_track_info.duration_formated = pgui->convert_msec_to_time(dict.get<int> ("duration"));
	if (dict.contains("artist")) {
		current_track_info.artist = dict.get<string> ("artist");
	} else {
		current_track_info.artist = "None";
	}
	if (dict.contains("title")) {
		current_track_info.title = dict.get<string> ("title");
	} else {
		current_track_info.title = "None";
	}
	if (dict.contains("album")) {
		current_track_info.album = dict.get<string> ("album");
	} else {
		current_track_info.album = "None";
	}
	pgui->display_track_title();
	pgui->start_scrolling();
	return false;
}

bool xmms2client::update_track_info_pre( const unsigned int& id )
{
	client_.medialib.getInfo( id )( Xmms::bind( &xmms2client::update_track_info, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	client_.playback.broadcastCurrentID()( Xmms::bind( &xmms2client::update_track_info_pre, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	return false;
}

bool xmms2client::set_playtime ( const unsigned int& pt )
{
	playback_playtime = pt;
	return false;
}

bool xmms2client::update_playtime ( const unsigned int& pt )
{
	playback_playtime = pt;
	pgui->display_playtime();
	pgui->display_position();
	client_.playback.signalPlaytime()( Xmms::bind( &xmms2client::update_playtime, this ), boost::bind( &xmms2client::error_handler, this, "0", _1 ) );
	return false;
}

void xmms2client::volume_set(unsigned int vol)
{
	client_.playback.volumeSet("left",vol);
	client_.playback.volumeSet("right",vol);
}

bool xmms2client::set_volume (const Xmms::Dict& dict )
{
	volume = dict.get<uint32_t>("left");
	volume_set(volume);
	volume_state = true;
	return false;
}

bool xmms2client::update_volume (const Xmms::Dict& dict )
{
	volume = dict.get<uint32_t>("left");
	volume_set(volume);
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
