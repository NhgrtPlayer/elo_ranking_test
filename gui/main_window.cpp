#include <iostream>
#include <gtkmm.h>
#include "main.hpp"

class MainTreeView : public Gtk::TreeView
{
public:
  MainTreeView();
  virtual ~MainTreeView();

protected:
  // Override Signal handler:
  // Alternatively, use signal_button_press_event().connect_notify()
  bool on_button_press_event(GdkEventButton* button_event) override;

  //Signal handler for popup menu items:
  void on_menu_file_popup_edit_player();
  void on_menu_file_popup_add_result();
  void on_menu_file_popup_remove_player();

  void updateTreeView();

  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()
    { add(m_col_id); add(m_col_name); add(m_col_elo); add(m_col_kcoeff); }

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

void MainTreeView::updateTreeView()
{
  // FILL THE TREEVIEW FROM THE MAIN PLAYERS LIST
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "right-click on this";
  row[m_Columns.m_col_elo] = 1000;
  row[m_Columns.m_col_kcoeff] = 40;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "or this";
  row[m_Columns.m_col_elo] = 1000;
  row[m_Columns.m_col_kcoeff] = 40;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "or this, for a popup context menu";
  row[m_Columns.m_col_elo] = 1000;
  row[m_Columns.m_col_kcoeff] = 40;
}

MainTreeView::MainTreeView()
{
  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  set_model(m_refTreeModel);

  //Fill the TreeView's model
  updateTreeView();

  //Add the TreeView's view columns:
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
    }
  }
}

class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow();
  virtual ~MainWindow();

protected:

  //Child widgets:
  Gtk::Box m_Box;
  Gtk::ButtonBox m_ButtonBox;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  Gtk::ScrolledWindow m_ScrolledWindow;
  MainTreeView m_TreeView;
};

MainWindow::MainWindow()
: Gtk::ApplicationWindow(),
  m_Box(Gtk::ORIENTATION_VERTICAL)
{
  set_title("Main menu example");
  set_border_width(5);
  set_default_size(450, 600);

  // MainApplication displays the menubar. Other stuff, such as a toolbar,
  // is put into the box.
  add(m_Box);

  //Create the toolbar and add it to a container widget:

  m_refBuilder = Gtk::Builder::create();

  Glib::ustring ui_info =
    "<!-- Generated with glade 3.18.3 -->"
    "<interface>"
    "  <requires lib='gtk+' version='3.4'/>"
    "  <object class='GtkToolbar' id='toolbar'>"
    "    <property name='visible'>True</property>"
    "    <property name='can_focus'>False</property>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_new'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Create a New List</property>"
    "        <property name='action_name'>app.newlist</property>"
    "        <property name='icon_name'>document-new</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_open'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Open a List</property>"
    "        <property name='action_name'>app.openlist</property>"
    "        <property name='icon_name'>document-open</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_save'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Save current List</property>"
    "        <property name='action_name'>app.save</property>"
    "        <property name='icon_name'>document-save</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_saveas'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Save current List As...</property>"
    "        <property name='action_name'>app.saveas</property>"
    "        <property name='icon_name'>document-save-as</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_quit'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Quit</property>"
    "        <property name='action_name'>app.quit</property>"
    "        <property name='icon_name'>application-exit</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='button_addplayer'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Add a Player</property>"
    "        <property name='action_name'>app.add_player</property>"
    "        <property name='icon_name'>contact-new</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='button_removeplayer'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Remove a Player</property>"
    "        <property name='action_name'>app.remove_player</property>"
    "        <property name='icon_name'>user-trash</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='button_addresult'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Add a Result</property>"
    "        <property name='action_name'>app.add_result</property>"
    "        <property name='icon_name'>document-properties</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_about'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>About</property>"
    "        <property name='action_name'>app.about</property>"
    "        <property name='icon_name'>help-about</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "  </object>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building toolbar failed: " << ex.what();
  }

  Gtk::Toolbar* toolbar = nullptr;
  m_refBuilder->get_widget("toolbar", toolbar);
  if (!toolbar)
    g_warning("GtkToolbar not found");
  else
    m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);

  m_ScrolledWindow.add(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_Box.pack_start(m_ScrolledWindow);
  m_Box.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

  show_all_children();
}

MainWindow::~MainWindow()
{
}

class MainApplication : public Gtk::Application
{
protected:
  MainApplication();

public:
  static Glib::RefPtr<MainApplication> create();

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
};

MainApplication::MainApplication()
: Gtk::Application("org.gtkmm.example.main_menu")
{
  Glib::set_application_name("Main Menu Example");
}

Glib::RefPtr<MainApplication> MainApplication::create()
{
  return Glib::RefPtr<MainApplication>(new MainApplication());
}

void MainApplication::on_startup()
{
  //Call the base class's implementation:
  Gtk::Application::on_startup();

  //Create actions for menus and toolbars.
  //We can use add_action() because Gtk::Application derives from Gio::ActionMap.

  //File menu:
  add_action("newlist", sigc::mem_fun(*this, &MainApplication::on_menu_file_new_list));
  add_action("openlist", sigc::mem_fun(*this, &MainApplication::on_menu_file_open_list));
  add_action("save", sigc::mem_fun(*this, &MainApplication::on_menu_file_save_list));
  add_action("saveas", sigc::mem_fun(*this, &MainApplication::on_menu_file_save_list_as));
  add_action("quit", sigc::mem_fun(*this, &MainApplication::on_menu_file_quit));

  //Players manu:
  add_action("add_player", sigc::mem_fun(*this, &MainApplication::on_menu_players_add));
  add_action("remove_player", sigc::mem_fun(*this, &MainApplication::on_menu_players_remove));
  add_action("add_result", sigc::mem_fun(*this, &MainApplication::on_menu_players_result));

  //Help menu:
  add_action("how", sigc::mem_fun(*this, &MainApplication::on_menu_help_how));
  add_action("about", sigc::mem_fun(*this, &MainApplication::on_menu_help_about));

  m_refBuilder = Gtk::Builder::create();

  //Layout the actions in a menubar and an application menu:
  Glib::ustring ui_info =
    "<interface>"
    "  <!-- menubar -->"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_New List</attribute>"
    "          <attribute name='action'>app.newlist</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Open List</attribute>"
    "          <attribute name='action'>app.openlist</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;o</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Save</attribute>"
    "          <attribute name='action'>app.save</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;s</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Save _As</attribute>"
    "          <attribute name='action'>app.saveas</attribute>"
    "          <attribute name='accel'>&lt;Shift&gt;&lt;Primary&gt;s</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>app.quit</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Players</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Add a Player</attribute>"
    "          <attribute name='action'>app.add_player</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Remove a Player</attribute>"
    "          <attribute name='action'>app.remove_player</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Add a _Result</attribute>"
    "          <attribute name='action'>app.add_result</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_How to use</attribute>"
    "          <attribute name='action'>app.how</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_About</attribute>"
    "          <attribute name='action'>app.about</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building menus failed: " << ex.what();
  }

  //Get the menubar and the app menu, and add them to the application:
  auto object = m_refBuilder->get_object("menubar");
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);

  if (!gmenu) {
    g_warning("GMenu not found");
  }
  else {
    set_menubar(gmenu);
  }
}

void MainApplication::on_activate()
{
  // std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void MainApplication::create_window()
{
  auto win = new MainWindow();

  //Make sure that the application runs for as long this window is still open:
  add_window(*win);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  win->signal_hide().connect(sigc::bind<Gtk::Window*>(
    sigc::mem_fun(*this, &MainApplication::on_window_hide), win));

  win->show_all();
}

void MainApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void MainApplication::on_menu_file_new_list()
{
  std::cout << "New list must be created." << '\n';
}

void MainApplication::on_menu_file_open_list()
{
  std::cout << "Open a list." << '\n';
}

void MainApplication::on_menu_file_save_list()
{
  std::cout << "Save current list." << '\n';
}

void MainApplication::on_menu_file_save_list_as()
{
  std::cout << "Save current list as..." << '\n';
}

void MainApplication::on_menu_file_quit()
{
  std::cout << G_STRFUNC << std::endl;
  quit(); // Not really necessary, when Gtk::Widget::hide() is called.

  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window.
  std::vector<Gtk::Window*> windows = get_windows();

  if (windows.size() > 0)
  {
    for (int i = windows.size() - 1; i >= 0; --i)
    {
      windows[i]->hide();
    }
  }
}

void MainApplication::on_menu_players_add()
{
  std::cout << "App|Players|Add was selected." << std::endl;
  auto win = new NewPlayerWindow();

  //Make sure that the application runs for as long this window is still open:
  add_window(*win);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  win->signal_hide().connect(sigc::bind<Gtk::Window*>(
    sigc::mem_fun(*this, &MainApplication::on_window_hide), win));


  win->set_modal(true);
  win->set_transient_for(*this);
  win->show_all();
}

void MainApplication::on_menu_players_remove()
{
  std::cout << "App|Players|Remove was selected." << std::endl;
}

void MainApplication::on_menu_players_result()
{
  std::cout << "App|Players|Results was selected." << std::endl;
}

void MainApplication::on_menu_help_how()
{
  std::cout << "App|Help|How to Use was selected." << std::endl;
}

void MainApplication::on_menu_help_about()
{
  std::cout << "App|Help|About was selected." << std::endl;
}

int main(int argc, char* argv[])
{
  auto application = MainApplication::create();

  // Start the application, showing the initial window,
  // and opening extra windows for any files that it is asked to open,
  // for instance as a command-line parameter.
  // run() will return when the last window has been closed by the user.
  const int status = application->run(argc, argv);
  return (status);
}