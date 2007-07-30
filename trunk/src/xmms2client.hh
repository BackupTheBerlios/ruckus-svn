#include <gtkmm.h>
using namespace std;
#ifndef _XMMS2CLIENT_HH
#  define _XMMS2CLIENT_HH
#  include <xmmsclient/xmmsclient++.h>
class ruckusGUI;
class xmms2client
{
	private:
		ruckusGUI *pgui;
		
	public:
		xmms2client();
		~xmms2client();
		
		unsigned int volume;
		
		Gtk::TreeModel::Row row;

		struct TrackDB {
			bool up_to_date;
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
			string title;
			string banner;
		} track_info;
		
		void connectGUI(ruckusGUI *gui);
		void init();
		void get_playlist();
		bool set_trackinfo_pre(const unsigned int& id);
		bool set_trackinfo(const Xmms::Dict& dict);
		bool set_playlist(const Xmms::Dict& dict);
		bool update_trackinfo_pre(const unsigned int& id);
		bool update_trackinfo(const Xmms::Dict& dict);
		bool set_playtime(const unsigned int& pt);
		bool update_playtime(const unsigned int& pt);
		bool error_handler(const std::string& error);
		bool balance_channels(const Xmms::Dict& dict );
		bool update_volume(const Xmms::Dict& dict );
		void set_volume(unsigned int vol);
		bool set_status(unsigned int status);
		bool update_status(unsigned int status);
		bool get_current_queue(const Xmms::List< unsigned int > &list);
		Xmms::Client client_;
};
#endif
