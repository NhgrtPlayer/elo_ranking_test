#include <iostream>
#include "main.h"

MainTreeView::MainTreeView(std::vector<Player>& players_list) :
  players_list(players_list)
{
  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  set_model(m_refTreeModel);

  //Fill the TreeView's model
  updateTreeView();

  //Add the TreeView's view columns:
  append_column("Rank", m_Columns.m_col_rank);
  append_column("ID", m_Columns.m_col_id);
  append_column("Name", m_Columns.m_col_name);
  append_column("Elo", m_Columns.m_col_elo);
  append_column("K Coefficient", m_Columns.m_col_kcoeff);

  //Fill popup menu:
  auto item = Gtk::manage(new Gtk::MenuItem("_Edit", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &MainTreeView::on_menu_file_popup_edit_player) );
  m_Menu_Popup.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("_Add a Result", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &MainTreeView::on_menu_file_popup_add_result) );
  m_Menu_Popup.append(*item);

  item = Gtk::manage(new Gtk::MenuItem("_Remove", true));
  item->signal_activate().connect(
    sigc::mem_fun(*this, &MainTreeView::on_menu_file_popup_remove_player) );
  m_Menu_Popup.append(*item);

  m_Menu_Popup.accelerate(*this);
  m_Menu_Popup.show_all(); //Show all menu items when the menu pops up
}

MainTreeView::~MainTreeView()
{
}

void MainTreeView::updateTreeView()
{
  int i = 1;
  sort_ranking(this->players_list);
  m_refTreeModel->clear();
  // FILL THE TREEVIEW FROM THE MAIN PLAYERS LIST
  Gtk::TreeModel::Row row;
  auto it = this->players_list.begin();

  while (it != this->players_list.end())
  {
    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_rank] = i;
    row[m_Columns.m_col_id] = it->getID();
    row[m_Columns.m_col_name] = it->getName();
    row[m_Columns.m_col_elo] = it->getElo();
    row[m_Columns.m_col_kcoeff] = it->getKCoeff();
    it++;
    i += (it != this->players_list.end() && it->getElo() < (it - 1)->getElo());
  }
}

bool MainTreeView::on_button_press_event(GdkEventButton* button_event)
{
  bool return_value = false;

  //Call base class, to allow normal handling,
  //such as allowing the row to be selected by the right-click:
  return_value = TreeView::on_button_press_event(button_event);

  //Then do our custom stuff:
  if( (button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3) )
  {
    m_Menu_Popup.popup(button_event->button, button_event->time);
    // m_Menu_Popup.popup_at_pointer((GdkEvent*)button_event);

    // Menu::popup_at_pointer() is new in gtkmm 3.22.
    // If you have an older revision, try this:
    //m_Menu_Popup.popup(button_event->button, button_event->time);
  }

  return return_value;
}

void MainTreeView::on_menu_file_popup_edit_player()
{
  std::cout << "Edit Player was selected." << std::endl;

  auto refSelection = get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      int id = (*iter)[m_Columns.m_col_id];
      std::cout << "  Selected ID=" << id << std::endl;
    }
  }
}

void MainTreeView::on_menu_file_popup_add_result()
{
  std::cout << "Add a Result was selected." << std::endl;

  auto refSelection = get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      int id = (*iter)[m_Columns.m_col_id];
      std::cout << "  Selected ID=" << id << std::endl;
    }
  }
}

void MainTreeView::on_menu_file_popup_remove_player()
{
  std::cout << "Remove Player was selected." << std::endl;

  auto refSelection = get_selection();
  if(refSelection)
  {
    Gtk::TreeModel::iterator iter = refSelection->get_selected();
    if(iter)
    {
      int id = (*iter)[m_Columns.m_col_id];
      std::cout << "  Selected ID=" << id << std::endl;
      for (int i = 0; i < this->players_list.size(); ++i)
      {
        if (this->players_list[i].getID() == id) {
          this->players_list.erase(this->players_list.begin() + i);
          this->updateTreeView();
          return ;
        }
      }
    }
  }
}