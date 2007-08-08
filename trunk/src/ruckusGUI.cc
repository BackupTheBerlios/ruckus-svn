#include "ruckusGUI.hh"
#include <gdkmm/pixbufloader.h>
#include <iostream>
#include <sstream>

ruckusGUI::ruckusGUI(xmms2client *x2c)
{
	px2c = x2c;
	string button_color = "gray32";
	string button_color_h = "gray48";
	volume_progressbar->modify_fg(Gtk::STATE_NORMAL, Gdk::Color("white"));
	volume_progressbar->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("black"));
	volume_progressbar->modify_bg(Gtk::STATE_SELECTED, Gdk::Color("gray16"));
	volume_progressbar->set_orientation((Gtk::ProgressBarOrientation)2);
	alignment15->set_padding(5,0,0,0);
	align_playlist_buttons->set_padding(0,10,0,0);
	song_info_eventbox->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("gray32"));
	eventbox_main->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("black"));
	eventbox_playlist->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("black"));
	progressbar->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("black"));
	progressbar->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color("gray32"));
	//progressbar->modify_bg(Gtk::STATE_ACTIVE, Gdk::Color("red"));
	button_previous->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	align_previous->set_padding(0,0,0,5);
	button_rewind->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	align_rewind->set_padding(0,0,5,5);
	button_play_pause->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	align_play_pause->set_padding(0,0,5,5);
	button_forward->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	align_forward->set_padding(0,0,5,5);
	button_next->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	align_next->set_padding(0,0,5,0);
	button_vol_up->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	button_mute->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	button_vol_down->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	button_previous->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_rewind->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_play_pause->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_forward->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_next->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_vol_up->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_mute->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_vol_down->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_plup->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_pljmp->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_pldn->modify_bg(Gtk::STATE_PRELIGHT, Gdk::Color(button_color_h));
	button_plup->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	button_pljmp->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	button_pldn->modify_bg(Gtk::STATE_NORMAL, Gdk::Color(button_color));
	notebook1->modify_bg(Gtk::STATE_NORMAL, Gdk::Color("gray12"));
	notebook1->modify_bg(Gtk::STATE_ACTIVE, Gdk::Color("black"));
	align_playback->set_padding(5,0,0,0);
	m_refTreeModel = Gtk::ListStore::create(m_PModel);
	playlist_view->set_model(m_refTreeModel);
	m_treeviewcolumn_id.set_title("Track ID");
  	m_treeviewcolumn_id.pack_start(m_cellrenderer_id);
  	m_treeviewcolumn_id.add_attribute(m_cellrenderer_id, "markup", m_PModel.m_col_id);
  	m_cellrenderer_id.set_property("background_set", true);
  	m_cellrenderer_id.set_property("ypad", 5);
  	m_cellrenderer_id.set_property("xpad", 5);
	m_cellrenderer_id.set_property("xalign", .5);
  	playlist_view->append_column(m_treeviewcolumn_id);
  	m_treeviewcolumn_title.set_title("Title");
  	m_treeviewcolumn_title.pack_start(m_cellrenderer_title);
  	m_treeviewcolumn_title.add_attribute(m_cellrenderer_title, "markup", m_PModel.m_col_title);
  	m_cellrenderer_title.set_property("background_set", true);
  	m_cellrenderer_title.set_property("ypad", 5);
  	m_cellrenderer_title.set_property("xpad", 5);
  	playlist_view->append_column(m_treeviewcolumn_title);
}

ruckusGUI::~ruckusGUI()
{
}

bool ruckusGUI::on_progressbar_button_release_event(GdkEventButton *ev)
{  return 0;
}

bool ruckusGUI::on_progressbar_button_press_event(GdkEventButton *ev)
{  return 0;
}

void ruckusGUI::on_button_vol_up_clicked()
{
	if ((px2c->volume+4)>100)
		px2c->volume = 100;
	else
		px2c->volume = (px2c->volume+4);
	px2c->volume_set(px2c->volume);
}

void ruckusGUI::on_button_mute_clicked()
{
	if ((px2c->volume > 0 ) & (px2c->playback_mute > 0))
		px2c->playback_mute = 0;
		
	if (px2c->playback_mute == 0)
	{
		px2c->playback_mute = px2c->volume;
		px2c->volume_set(0);
		image_nomute->show();
		image_mute->hide();
		label_mute->set_markup("<span foreground=\"white\"><b>Unmute</b></span>");
	} 
	else
	{
		px2c->volume_set(px2c->playback_mute);
		px2c->playback_mute = 0;
		image_nomute->hide();
		image_mute->show();
		label_mute->set_markup("<span foreground=\"white\"><b>Mute</b></span>");
	}
}

void ruckusGUI::on_button_vol_down_clicked()
{
	if (((int)px2c->volume-4)<0)
		px2c->volume = 0;
	else
		px2c->volume = (px2c->volume-4);
	px2c->volume_set(px2c->volume);
}

void ruckusGUI::on_button_previous_clicked()
{ 
	px2c->client_.playlist.setNextRel(-1);
	px2c->client_.playback.tickle();
}

void ruckusGUI::on_button_rewind_clicked()
{  
}

void ruckusGUI::on_button_play_pause_clicked()
{
	if ( (px2c->playback_status == 0 | px2c->playback_status == 2 ) )
	{
		px2c->client_.playback.start();
		label_play_pause->set_markup("<span foreground=\"white\" font_desc=\"12\"><b>Pause</b></span>");
		image_pause->show();
		image_play->hide();
	}
	if ( px2c->playback_status == 1 )
	{
		px2c->client_.playback.pause();
		label_play_pause->set_markup("<span foreground=\"white\" font_desc=\"12\"><b>Play</b></span>");
		image_pause->hide();
		image_play->show();
	}
}

void ruckusGUI::on_button_forward_clicked()
{
}

void ruckusGUI::on_button_next_clicked()
{
	px2c->client_.playlist.setNextRel(1);
	px2c->client_.playback.tickle();  
}

void ruckusGUI::on_fullscreen_button_toggled()
{
	if (fullscreen_button->get_active()) {
		fullscreen();
		fullscreen_togglebutton_label->set_label("UnFullscreen");
	} else {
		unfullscreen();
 		fullscreen_togglebutton_label->set_label("Fullscreen");
	}
	fullscreen_togglebutton_label->show();  
}

void ruckusGUI::on_quit_button_clicked()
{
	ruckusGUI::hide();
}

string ruckusGUI::remove_amp( string& string )
{
	size_t pos = 0;
	while ( (pos=string.find("&", pos)) != string::npos)
	{
		string.replace(pos,1,"&amp;");
		pos++;
	}
	return string;
}

void ruckusGUI::start_scrolling()
{
	scroll_timer = Glib::signal_timeout().connect( sigc::mem_fun(*this, &ruckusGUI::scroll_trackinfo),200);
}

void ruckusGUI::display_track_title ()
{
	string temp;
	stringstream trackid;
	trackid << px2c->current_playlist_position;
	temp = "***  " + trackid.str() + ".   " + px2c->current_track_info.artist + " - " + px2c->current_track_info.title + "          ";
	px2c->current_track_info.banner = remove_amp(temp);
	string _banner = "<span foreground=\"white\" font_desc=\"18\"><b>" + px2c->current_track_info.banner + "</b></span>";
	label_trackinfo->set_markup(_banner);
	temp = "<span font_desc=\"12\" foreground=\"white\"><b>" + px2c->current_track_info.duration_formated + "</b></span>";
	label_duration->set_markup(temp);
	start_scrolling();
}

string ruckusGUI::convert_msec_to_time(unsigned int time)
{
	int hours, minutes, seconds;
	hours = (time/(60*60*1000))%24;
	minutes = (time/(60*1000))%60;
	seconds = (time/1000)%60;
	char buffer[8];
	sprintf(buffer,"%.2i:%.2i:%.2i",hours,minutes,seconds);
	return buffer;
}

void ruckusGUI::display_playtime()
{
	string temp = "<span font_desc=\"12\" foreground=\"white\"><b>" + convert_msec_to_time(px2c->playback_playtime) + "</b></span>";
	play_time->set_markup(temp);
}

void ruckusGUI::display_position()
{
	progressbar->set_range(0,px2c->current_track_info.duration);
	progressbar->set_value(px2c->playback_playtime);
}

void ruckusGUI::display_volume()
{
	double vol_fraction = (double)px2c->volume/100;
	char vol_text[sizeof(px2c->volume)];
	sprintf(vol_text,"%i",px2c->volume);
	volume_progressbar->set_text(vol_text);
	volume_progressbar->set_fraction(vol_fraction);
}

void* ruckusGUI::scroll_trackinfo()
{
	scroll_timer.disconnect();
	if (px2c->playback_status == 1)
	{
		int xml = 0;
		string banner_temp = px2c->current_track_info.banner;
		char buffer = banner_temp.at(0);
		banner_temp.erase(0,1);
		banner_temp = banner_temp + buffer;
		buffer = banner_temp.at(0);
		if (buffer == '&')
		{
			xml = 1;
			while(xml == 1)
			{
				banner_temp.erase(0,1);
				banner_temp = banner_temp + buffer;
				buffer = banner_temp.at(0);
				if (buffer== ';')
					xml=0;
			}
			banner_temp.erase(0,1);
			banner_temp = banner_temp + buffer;
		}
		px2c->current_track_info.banner = banner_temp;
		string _banner = "<span foreground=\"white\" font_desc=\"18\"><b>" + px2c->current_track_info.banner + "</b></span>";
		label_trackinfo->set_markup(_banner);
	}
	scroll_timer = Glib::signal_timeout().connect( sigc::mem_fun(*this, &ruckusGUI::scroll_trackinfo),200);
}

void ruckusGUI::init()
{
	if (px2c->volume == 0)
	{
		image_nomute->show();
		image_mute->hide();
		label_mute->set_markup("<span foreground=\"white\"><b>Unmute</b></span>");
	}
	else
	{
		image_nomute->hide();
		image_mute->show();
		label_mute->set_markup("<span foreground=\"white\"><b>Mute</b></span>");
	}
	display_volume();
	
	if ((px2c->playback_status == 0) || (px2c->playback_status == 2))
	{
		label_play_pause->set_markup("<span foreground=\"white\" font_desc=\"12\"><b>Play</b></span>");
		image_pause->hide();
	} 
	else if (px2c->playback_status == 1)
	{
		label_play_pause->set_markup("<span foreground=\"white\" font_desc=\"12\"><b>Pause</b></span>");
		image_play->hide();
	}
	
	display_track_title();
	display_playtime();
	display_position();
	
	//px2c->update_playlist();
	
	//px2c->get_playlist();
}

bool ruckusGUI::error_handler( const string& error )
{
	cout << "Error" << " - " << error << endl;
	return false;
}
