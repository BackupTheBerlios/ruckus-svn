#include <gtkmm.h>
#include "xmms2client.hh"
using namespace std;
#ifndef _RUCKUSGUI_HH
#  include "ruckusGUI_glade.hh"
#  define _RUCKUSGUI_HH

class ruckusGUI : public ruckusGUI_glade
{
	bool on_progressbar_button_release_event(GdkEventButton *ev);
	bool on_progressbar_button_press_event(GdkEventButton *ev);
	void on_button_vol_up_clicked();
	void on_button_mute_clicked();
	void on_button_vol_down_clicked();
	void on_button_previous_clicked();
	void on_button_rewind_clicked();
	void on_button_play_pause_clicked();
	void on_button_forward_clicked();
	void on_button_next_clicked();
	void on_fullscreen_button_toggled();
	void on_quit_button_clicked();
	
	bool error_handler(const string& error);
	
	public:
		void init();
		
		string remove_amp(string& string);

		class PlaylistModel : public Gtk::TreeModel::ColumnRecord
		{
			public:
		
			PlaylistModel()
			{ add(m_col_id); add(m_col_title); add(m_col_album); add(m_col_artist);}
			Gtk::TreeModelColumn<string> m_col_id;
			Gtk::TreeModelColumn<string> m_col_title;
			Gtk::TreeModelColumn<string> m_col_album;
			Gtk::TreeModelColumn<string> m_col_artist;
  		};

  		PlaylistModel m_PModel;
		Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
		Gtk::CellRendererText m_cellrenderer_id;
		Gtk::TreeView::Column m_treeviewcolumn_id;
		Gtk::CellRendererText m_cellrenderer_title;
		Gtk::TreeView::Column m_treeviewcolumn_title;
		Gtk::CellRendererText m_cellrenderer_album;
		Gtk::TreeView::Column m_treeviewcolumn_album;
		Gtk::CellRendererText m_cellrenderer_artist;
		Gtk::TreeView::Column m_treeviewcolumn_artist;
		  
		void display_playtime();
		void display_track_title();
		void display_position();
		void display_volume();
		void* scroll_trackinfo();
		string convert_msec_to_time(unsigned int time);
		sigc::connection scroll_timer;
		
	private:
        xmms2client *px2c;
         
	public:
		ruckusGUI(xmms2client *x2c);
		~ruckusGUI();
};
#endif
