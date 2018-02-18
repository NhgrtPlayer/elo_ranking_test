#ifndef _MAIN_HPP_
#define _MAIN_HPP_

class NewPlayerWindow : public Gtk::Window
{
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
  NewPlayerWindow();
  virtual ~NewPlayerWindow() {}

};

#endif