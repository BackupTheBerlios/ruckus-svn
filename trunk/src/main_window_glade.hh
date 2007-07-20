// generated 2007/7/20 0:48:58 EDT by rmh3093@Redman.brcg.net
// using glademm V2.6.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/rmh3093/ruckus/ruckus.glade
// for gtk 2.10.13 and gtkmm 2.10.9
//
// Please modify the corresponding derived classes in ./src/main_window.hh and./src/main_window.cc

#ifndef _MAIN_WINDOW_GLADE_HH
#  define _MAIN_WINDOW_GLADE_HH

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
#include <gtkmm/eventbox.h>
#include <gtkmm/alignment.h>
#include <gtkmm/frame.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/scale.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/treeview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/notebook.h>

class main_window_glade : public Gtk::Window
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Window * main_window;
        class Gtk::Label * song_title;
        class Gtk::Label * artist_album;
        class Gtk::VBox * vbox3;
        class Gtk::EventBox * song_info_eventbox;
        class Gtk::Alignment * alignment11;
        class Gtk::Frame * frame3;
        class Gtk::DrawingArea * drawingarea3;
        class Gtk::Label * play_time;
        class Gtk::Alignment * alignment10;
        class Gtk::Frame * frame2;
        class Gtk::DrawingArea * drawingarea4;
        class Gtk::HBox * hbox10;
        class Gtk::DrawingArea * drawingarea1;
        class Gtk::HScale * progressbar;
        class Gtk::DrawingArea * drawingarea2;
        class Gtk::HBox * hbox2;
        class Gtk::Image * image6;
        class Gtk::HBox * hbox3;
        class Gtk::Alignment * alignment2;
        class Gtk::Button * button_skip_back;
        class Gtk::Image * image7;
        class Gtk::HBox * hbox4;
        class Gtk::Alignment * alignment3;
        class Gtk::Button * button_rewind;
        class Gtk::Image * play_image;
        class Gtk::Image * pause_image;
        class Gtk::HBox * hbox5;
        class Gtk::Alignment * alignment4;
        class Gtk::Button * button_play;
        class Gtk::Image * image9;
        class Gtk::HBox * hbox8;
        class Gtk::Alignment * alignment7;
        class Gtk::Button * button_fastforward;
        class Gtk::Image * image10;
        class Gtk::HBox * hbox9;
        class Gtk::Alignment * alignment8;
        class Gtk::Button * button_skip_forward;
        class Gtk::HButtonBox * hbuttonbox1;
        class Gtk::VBox * vbox1;
        class Gtk::Label * player_label;
        class Gtk::TreeView * treeview1;
        class Gtk::ScrolledWindow * scrolledwindow1;
        class Gtk::Label * playlist_label;
        class Gtk::TreeView * treeview2;
        class Gtk::ScrolledWindow * scrolledwindow2;
        class Gtk::Label * albums_label;
        class Gtk::TreeView * treeview3;
        class Gtk::ScrolledWindow * scrolledwindow3;
        class Gtk::Label * artists_label;
        class Gtk::Image * image1;
        class Gtk::Label * fullscreen_togglebutton_label;
        class Gtk::HBox * hbox1;
        class Gtk::Alignment * alignment1;
        class Gtk::ToggleButton * togglebutton1;
        class Gtk::VBox * vbox2;
        class Gtk::Label * settings_label;
        class Gtk::Notebook * notebook1;
protected:
        
        main_window_glade();
        
        ~main_window_glade();
private:
        virtual bool on_progressbar_button_release_event(GdkEventButton *ev) = 0;
        virtual bool on_progressbar_button_press_event(GdkEventButton *ev) = 0;
        virtual void on_button_skip_back_clicked() = 0;
        virtual void on_button_rewind_clicked() = 0;
        virtual void on_button_play_clicked() = 0;
        virtual void on_button_fastforward_clicked() = 0;
        virtual void on_button_skip_forward_clicked() = 0;
        virtual void on_togglebutton1_toggled() = 0;
};
#endif
