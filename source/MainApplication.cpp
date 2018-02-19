#include <iostream>
#include "MainApplication.hpp"
#include "NewPlayerWindow.hpp"

MainApplication::MainApplication(std::vector<Player>& players_list)
: Gtk::Application("org.gtkmm.example.main_menu"),
  m_mainWinPtr(NULL),
  players_list(players_list)
{
  Glib::set_application_name("Main Menu Example");
}

Glib::RefPtr<MainApplication> MainApplication::create(std::vector<Player>& players_list)
{
  return Glib::RefPtr<MainApplication>(new MainApplication(players_list));
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
  auto win = new MainWindow(this->players_list);
  m_mainWinPtr = win;

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
  if (m_mainWinPtr)
    m_mainWinPtr->updateTreeView();
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
  auto win = new NewPlayerWindow(this->players_list);

  //Make sure that the application runs for as long this window is still open:
  add_window(*win);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  win->signal_hide().connect(sigc::bind<Gtk::Window*>(
    sigc::mem_fun(*this, &MainApplication::on_window_hide), win));

  win->set_modal(true);

  std::vector<Gtk::Window*> windows = get_windows();
  if (m_mainWinPtr) {
    win->set_transient_for(*m_mainWinPtr);
  }
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
