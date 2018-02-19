#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <gtkmm.h>
#include "MainTreeView.hpp"
#include "Player.hpp"


class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow(std::vector<Player>& players_list);
  virtual ~MainWindow();

  void updateTreeView();

protected:
  std::vector<Player>& players_list;

  //Child widgets:
  Gtk::Box m_Box;
  Gtk::ButtonBox m_ButtonBox;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  Gtk::ScrolledWindow m_ScrolledWindow;
  MainTreeView m_TreeView;
};

#endif