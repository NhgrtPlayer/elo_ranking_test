#ifndef _MAINTREEVIEW_HPP_
#define _MAINTREEVIEW_HPP_

#include <gtkmm.h>
#include "Player.hpp"

class MainTreeView : public Gtk::TreeView
{
  std::vector<Player>& players_list;
public:
  MainTreeView(std::vector<Player>&);
  virtual ~MainTreeView();

  void updateTreeView();

protected:
  // Override Signal handler:
  // Alternatively, use signal_button_press_event().connect_notify()
  bool on_button_press_event(GdkEventButton* button_event) override;

  //Signal handler for popup menu items:
  void on_menu_file_popup_edit_player();
  void on_menu_file_popup_add_result();
  void on_menu_file_popup_remove_player();

  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_rank); add(m_col_id); add(m_col_name); add(m_col_elo); add(m_col_kcoeff); }

    Gtk::TreeModelColumn<unsigned int> m_col_rank;
    Gtk::TreeModelColumn<unsigned int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<unsigned int> m_col_elo;
    Gtk::TreeModelColumn<unsigned int> m_col_kcoeff;
  };

  ModelColumns m_Columns;

  //The Tree model:
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  Gtk::Menu m_Menu_Popup;
};

#endif