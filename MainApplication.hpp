#ifndef _MAINAPPLICATION_HPP_
#define _MAINAPPLICATION_HPP_

#include <gtkmm.h>
#include "MainWindow.hpp"

#include "Player.hpp"

class MainApplication : public Gtk::Application
{
  std::vector<Player>& players_list;
protected:
  MainApplication(std::vector<Player>&);

public:
  static Glib::RefPtr<MainApplication> create(std::vector<Player>&);

protected:
  //Overrides of default signal handlers:
  void on_startup() override;
  void on_activate() override;

private:
  void create_window();

  void on_window_hide(Gtk::Window* window);
  void on_menu_file_new_generic();

  // File menu:
  void on_menu_file_new_list();
  void on_menu_file_open_list();
  void on_menu_file_save_list();
  void on_menu_file_save_list_as();
  void on_menu_file_quit();

  //Players menu:
  void on_menu_players_add();
  void on_menu_players_remove();
  void on_menu_players_result();

  // Help menu:
  void on_menu_help_how();
  void on_menu_help_about();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  MainWindow* m_mainWinPtr;
};

#endif