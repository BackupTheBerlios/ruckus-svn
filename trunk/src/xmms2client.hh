#include <gtkmm.h>
#include <list>
#include <vector>
#include <map>
using namespace std;
#ifndef _XMMS2CLIENT_HH
#  define _XMMS2CLIENT_HH
#  include <xmmsclient/xmmsclient++.h>
class ruckusGUI;
class xmms2client
{
	private:
		ruckusGUI *pgui;
		
		bool get_current_playlist_position( unsigned int status );
		
		bool get_current_playlist_name(const string &s_current_playlist_name);
		string current_playlist_name;
		
		bool get_current_playlist_tracks(const Xmms::List< unsigned int > &l_tracks);
		vector<unsigned int> current_playlist_tracks;

		bool get_track_info( const Xmms::Dict& dict );
		bool update_track_info_pre( const unsigned int& id );
		bool update_track_info( const Xmms::Dict& dict );
		
		bool set_current_playlist_tracks( const unsigned int i, const Xmms::Dict& dict );
		bool update_current_playlist_tracks( const unsigned int i, const Xmms::Dict& dict );
		unsigned int current_playlist_count;
				
		unsigned int current_song_id;
		
		bool get_list_of_playlists(const Xmms::List< string > &l_playlists);
		list<string> list_of_playlists;
		list<string>::iterator iter_list_of_playlists;
		
	public:
		xmms2client();
		~xmms2client();
		
		void update_playlist();
		unsigned int current_playlist_position;
		bool current_playlist_position_state;
		
		unsigned int playback_status;
		bool playback_status_state;
		
		unsigned int playback_mute;
		unsigned int playback_playtime;
		
		unsigned int volume;
		
		bool volume_state;
		
		Gtk::TreeModel::Row row;
		unsigned int count;
		
		bool current_track_state;
		bool current_track_ready;
		
		struct TrackINFO {
			unsigned int id;
			unsigned int duration;
			string artist;
			string album;
			string title;	
			string banner;
			string duration_formated;
		} current_track_info;
		
		map<unsigned int, struct TrackINFO> current_playlist;
		
		void connectGUI(ruckusGUI *gui);
		void init();
		void get_playlist();
		bool set_trackinfo_pre(const unsigned int& id);
		void collect_initial_data();
		bool set_trackinfo(const Xmms::Dict& dict);
		bool update_trackinfo_pre(const unsigned int& id);
		bool update_trackinfo(const Xmms::Dict& dict);
		bool set_playtime(const unsigned int& pt);
		bool update_playtime(const unsigned int& pt);
		bool error_handler(const string& token, const string& error);
		bool set_volume(const Xmms::Dict& dict );
		bool update_volume(const Xmms::Dict& dict );
		void volume_set(unsigned int vol);
		bool set_status(unsigned int status);
		bool update_status(unsigned int status);
		Xmms::Client client_;
};
#endif
