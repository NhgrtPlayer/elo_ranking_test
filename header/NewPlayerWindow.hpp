#ifndef _NEWPLAYERWINDOW_HPP_
#define _NEWPLAYERWINDOW_HPP_

#include "Player.hpp"

class NewPlayerWindow : public Gtk::Window
{
  std::vector<Player>& players_list;
protected:
  //Signal handlers:
  void new_player_button_clicked();
  void cancel_button_clicked();

  //Member widgets:
  Gtk::Box VBox;
  Gtk::Box HBox_entries;
  Gtk::Box HBox_buttons;
  Gtk::Entry new_player_name_entry;
  Gtk::Entry new_player_elo_entry;
  Gtk::Entry new_player_kcoeff_entry;
  Gtk::Button new_player_confirm_button;
  Gtk::Button new_player_cancel_button;

public:
  NewPlayerWindow(std::vector<Player>&);
  virtual ~NewPlayerWindow() {}

};

#endif