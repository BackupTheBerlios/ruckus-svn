// generated 2007/7/30 12:38:04 EDT by rmh3093@Redman.brcg.net
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/rmh3093/ruckus/ruckus.glade
// for gtk 2.10.13 and gtkmm 2.10.9
//
// Please modify the corresponding derived classes in ./src/ruckusGUI.hh and./src/ruckusGUI.cc

#ifndef _RUCKUSGUI_GLADE_HH
#  define _RUCKUSGUI_GLADE_HH

// Since all your widgets were private I made them all public.
// To differentiate between accessable (e.g. entries, output labels)
// and unaccessible widgets (e.g. static labels, containers)
// you should use the 'visibility' property (only visible in C++ mode)


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/image.h>
#include <gtkmm/scale.h>
#include <gtkmm/button.h>
#include <gtkmm/alignment.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/treeview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/notebook.h>

class ruckusGUI_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * ruckusGUI;
        class Gtk::Label * label_trackinfo;
        class Gtk::HBox * hbox215;
        class Gtk::Frame * frame36;
        class Gtk::EventBox * song_info_eventbox;
        class Gtk::Image * image24;
        class Gtk::Frame * frame37;
        class Gtk::VBox * vbox19;
        class Gtk::Label * play_time;
        class Gtk::HScale * progressbar;
        class Gtk::Label * label_duration;
        class Gtk::HBox * hbox214;
        class Gtk::Frame * frame35;
        class Gtk::Image * image16;
        class Gtk::Label * label7;
        class Gtk::VBox * vbox9;
        class Gtk::Button * button_previous;
        class Gtk::Frame * frame38;
        class Gtk::Alignment * align_previous;
        class Gtk::Image * image17;
        class Gtk::Label * label15;
        class Gtk::VBox * vbox10;
        class Gtk::Button * button_rewind;
        class Gtk::Frame * frame39;
        class Gtk::Alignment * align_rewind;
        class Gtk::Image * image_play;
        class Gtk::Image * image_pause;
        class Gtk::HBox * hbox216;
        class Gtk::Label * label_play_pause;
        class Gtk::VBox * vbox11;
        class Gtk::Button * button_play_pause;
        class Gtk::Frame * frame40;
        class Gtk::Alignment * align_play_pause;
        class Gtk::Image * image19;
        class Gtk::Label * label17;
        class Gtk::VBox * vbox12;
        class Gtk::Button * button_forward;
        class Gtk::Frame * frame41;
        class Gtk::Alignment * align_forward;
        class Gtk::Image * image20;
        class Gtk::Label * label18;
        class Gtk::VBox * vbox13;
        class Gtk::Button * button_next;
        class Gtk::Frame * frame42;
        class Gtk::Alignment * align_next;
        class Gtk::HBox * hbox12;
        class Gtk::VBox * vbox20;
        class Gtk::Alignment * align_playback;
        class Gtk::VBox * vbox17;
        class Gtk::HBox * hbox17;
        class Gtk::ProgressBar * volume_progressbar;
        class Gtk::Frame * frame46;
        class Gtk::Alignment * alignment15;
        class Gtk::Image * image21;
        class Gtk::Label * label21;
        class Gtk::VBox * vbox14;
        class Gtk::Button * button_vol_up;
        class Gtk::Frame * frame43;
        class Gtk::Alignment * alignment22;
        class Gtk::Image * image_mute;
        class Gtk::Image * image_nomute;
        class Gtk::HBox * hbox217;
        class Gtk::Label * label_mute;
        class Gtk::VBox * vbox15;
        class Gtk::Button * button_mute;
        class Gtk::Frame * frame44;
        class Gtk::Alignment * alignment23;
        class Gtk::Image * image22;
        class Gtk::Label * label19;
        class Gtk::VBox * vbox16;
        class Gtk::Button * button_vol_down;
        class Gtk::Frame * frame45;
        class Gtk::Alignment * alignment24;
        class Gtk::VBox * vbox5;
        class Gtk::HBox * hbox15;
        class Gtk::HBox * hbox14;
        class Gtk::VBox * vbox1;
        class Gtk::EventBox * eventbox_main;
        class Gtk::Label * player_label;
        class Gtk::Frame * frame47;
        class Gtk::TreeView * playlist_view;
        class Gtk::ScrolledWindow * scrolledwindow4;
        class Gtk::Button * button1;
        class Gtk::Button * button2;
        class Gtk::Button * button3;
        class Gtk::VBox * vbox21;
        class Gtk::Alignment * align_playlist_buttons;
        class Gtk::HBox * hbox218;
        class Gtk::EventBox * eventbox_playlist;
        class Gtk::Label * playlist_label;
        class Gtk::Frame * frame48;
        class Gtk::TreeView * treeview2;
        class Gtk::ScrolledWindow * scrolledwindow2;
        class Gtk::Label * albums_label;
        class Gtk::Frame * frame49;
        class Gtk::TreeView * treeview3;
        class Gtk::ScrolledWindow * scrolledwindow3;
        class Gtk::Label * artists_label;
        class Gtk::Frame * frame50;
        class Gtk::Image * image1;
        class Gtk::Label * fullscreen_togglebutton_label;
        class Gtk::HBox * hbox1;
        class Gtk::Alignment * alignment5;
        class Gtk::ToggleButton * fullscreen_button;
        class Gtk::Image * image11;
        class Gtk::Label * label1;
        class Gtk::HBox * hbox11;
        class Gtk::Alignment * alignment12;
        class Gtk::Button * quit_button;
        class Gtk::VBox * vbox2;
        class Gtk::Label * settings_label;
        class Gtk::Frame * frame51;
        class Gtk::Notebook * notebook1;
protected:
        
        ruckusGUI_glade();
        
        ~ruckusGUI_glade();
private:
        virtual bool on_progressbar_button_release_event(GdkEventButton *ev) = 0;
        virtual bool on_progressbar_button_press_event(GdkEventButton *ev) = 0;
        virtual void on_button_previous_clicked() = 0;
        virtual void on_button_rewind_clicked() = 0;
        virtual void on_button_play_pause_clicked() = 0;
        virtual void on_button_forward_clicked() = 0;
        virtual void on_button_next_clicked() = 0;
        virtual void on_button_vol_up_clicked() = 0;
        virtual void on_button_mute_clicked() = 0;
        virtual void on_button_vol_down_clicked() = 0;
        virtual void on_fullscreen_button_toggled() = 0;
        virtual void on_quit_button_clicked() = 0;
};
#endif
