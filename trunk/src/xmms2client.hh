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
		
		unsigned int volume;
		
		Gtk::TreeModel::Row row;

		struct TrackDB {
			bool scroll;
			bool hidden;
			unsigned int mute;
			unsigned int id;
			unsigned int count;
			unsigned int status;
			unsigned int duration;
			string duration_formated;
			unsigned int playtime;
			string artist;
			string album;
			string title;
			string banner;
		};
		
		map<unsigned int, struct TrackDB> current_playlist;
		map<unsigned int, struct TrackDB>::iterator iter_current_playlists;
		
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
		bool balance_channels(const Xmms::Dict& dict );
		bool update_volume(const Xmms::Dict& dict );
		void set_volume(unsigned int vol);
		bool set_status(unsigned int status);
		bool update_status(unsigned int status);
		Xmms::Client client_;
};
#endif
