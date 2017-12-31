#include <iostream>
#include <gtkmm.h>

class ExampleWindow : public Gtk::ApplicationWindow
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_menu_others();

  void on_menu_choices(const Glib::ustring& parameter);
  void on_menu_choices_other(int parameter);
  void on_menu_toggle();

  //Child widgets:
  Gtk::Box m_Box;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;

  //Two sets of choices:
  Glib::RefPtr<Gio::SimpleAction> m_refChoice;
  Glib::RefPtr<Gio::SimpleAction> m_refChoiceOther;

  Glib::RefPtr<Gio::SimpleAction> m_refToggle;
};

ExampleWindow::ExampleWindow()
: Gtk::ApplicationWindow(),
  m_Box(Gtk::ORIENTATION_VERTICAL)
{
  set_title("Main menu example");
  set_default_size(300, 100);

  // ExampleApplication displays the menubar. Other stuff, such as a toolbar,
  // is put into the box.
  add(m_Box);

  // Create actions for menus and toolbars.
  // We can use add_action() because Gtk::ApplicationWindow derives from Gio::ActionMap.
  // This Action Map uses a "win." prefix for the actions.
  // Therefore, for instance, "win.copy", is used in ExampleApplication::on_startup()
  // to layout the menu.

  //Edit menu:
  add_action("copy", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  add_action("paste", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  add_action("something", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

  //Choices menus, to demonstrate Radio items,
  //using our convenience methods for string and int radio values:
  m_refChoice = add_action_radio_string("choice",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_choices), "a");

  m_refChoiceOther = add_action_radio_integer("choiceother",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_choices_other), 1);

  m_refToggle = add_action_bool("sometoggle",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_toggle), false);

  //Help menu:
  add_action("about", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

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
    "        <property name='tooltip_text' translatable='yes'>New Standard</property>"
    "        <property name='action_name'>app.newstandard</property>"
    "        <property name='icon_name'>document-new</property>"
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
    "  </object>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building toolbar failed: " <<  ex.what();
  }

  Gtk::Toolbar* toolbar = nullptr;
  m_refBuilder->get_widget("toolbar", toolbar);
  if (!toolbar)
    g_warning("GtkToolbar not found");
  else
    m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_others()
{
  std::cout << "A menu item was selected." << std::endl;
}

void ExampleWindow::on_menu_choices(const Glib::ustring& parameter)
{
  //The radio action's state does not change automatically:
  m_refChoice->change_state(parameter);

  Glib::ustring message;
  if (parameter == "a")
    message = "Choice a was selected.";
  else
    message = "Choice b was selected.";

  std::cout << message << std::endl;
}

void ExampleWindow::on_menu_choices_other(int parameter)
{
  //The radio action's state does not change automatically:
  m_refChoiceOther->change_state(parameter);

  Glib::ustring message;
  if (parameter == 1)
    message = "Choice 1 was selected.";
  else
    message = "Choice 2 was selected.";

  std::cout << message << std::endl;
}

void ExampleWindow::on_menu_toggle()
{
  bool active = false;
  m_refToggle->get_state(active);

  //The toggle action's state does not change automatically:
  active = !active;
  m_refToggle->change_state(active);

  Glib::ustring message;
  if (active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active.";

  std::cout << message << std::endl;
}

class ExampleApplication : public Gtk::Application
{
protected:
  ExampleApplication();

public:
  static Glib::RefPtr<ExampleApplication> create();

protected:
  //Overrides of default signal handlers:
  void on_startup() override;
  void on_activate() override;

private:
  void create_window();

  void on_window_hide(Gtk::Window* window);
  void on_menu_file_new_generic();
  void on_menu_file_quit();
  void on_menu_help_about();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
};

ExampleApplication::ExampleApplication()
: Gtk::Application("org.gtkmm.example.main_menu")
{
  Glib::set_application_name("Main Menu Example");
}

Glib::RefPtr<ExampleApplication> ExampleApplication::create()
{
  return Glib::RefPtr<ExampleApplication>(new ExampleApplication());
}

void ExampleApplication::on_startup()
{
  //Call the base class's implementation:
  Gtk::Application::on_startup();

  //Create actions for menus and toolbars.
  //We can use add_action() because Gtk::Application derives from Gio::ActionMap.

  //File|New sub menu:
  add_action("newstandard",
    sigc::mem_fun(*this, &ExampleApplication::on_menu_file_new_generic));

  add_action("newfoo",
    sigc::mem_fun(*this, &ExampleApplication::on_menu_file_new_generic));

  add_action("newgoo",
    sigc::mem_fun(*this, &ExampleApplication::on_menu_file_new_generic));

  //File menu:
  add_action("quit", sigc::mem_fun(*this, &ExampleApplication::on_menu_file_quit));

  //Help menu:
  add_action("about", sigc::mem_fun(*this, &ExampleApplication::on_menu_help_about));

  m_refBuilder = Gtk::Builder::create();

  //Layout the actions in a menubar and an application menu:
  Glib::ustring ui_info =
    "<interface>"
    "  <!-- menubar -->"
    "  <menu id='menu-example'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Standard</attribute>"
    "          <attribute name='action'>app.newstandard</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Foo</attribute>"
    "          <attribute name='action'>app.newfoo</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Goo</attribute>"
    "          <attribute name='action'>app.newgoo</attribute>"
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
    "      <attribute name='label' translatable='yes'>_Edit</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Copy</attribute>"
    "          <attribute name='action'>win.copy</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;c</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Paste</attribute>"
    "          <attribute name='action'>win.paste</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;v</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Something</attribute>"
    "          <attribute name='action'>win.something</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Choices</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice _A</attribute>"
    "          <attribute name='action'>win.choice</attribute>"
    "          <attribute name='target'>a</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice _B</attribute>"
    "          <attribute name='action'>win.choice</attribute>"
    "          <attribute name='target'>b</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Other Choices</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice 1</attribute>"
    "          <attribute name='action'>win.choiceother</attribute>"
    "          <attribute name='target' type='i'>1</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice 2</attribute>"
    "          <attribute name='action'>win.choiceother</attribute>"
    "          <attribute name='target' type='i'>2</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Some Toggle</attribute>"
    "          <attribute name='action'>win.sometoggle</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_About</attribute>"
    "          <attribute name='action'>win.about</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    ""
    "  <!-- application menu -->"
    "  <menu id='appmenu'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Standard</attribute>"
    "          <attribute name='action'>app.newstandard</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Foo</attribute>"
    "          <attribute name='action'>app.newfoo</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Goo</attribute>"
    "          <attribute name='action'>app.newgoo</attribute>"
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
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <section>"
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
  auto object = m_refBuilder->get_object("menu-example");
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  object = m_refBuilder->get_object("appmenu");
  auto appMenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if (!(gmenu && appMenu)) {
    g_warning("GMenu or AppMenu not found");
  }
  else
  {
    set_app_menu(appMenu);
    set_menubar(gmenu);
  }
}

void ExampleApplication::on_activate()
{
  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void ExampleApplication::create_window()
{
  auto win = new ExampleWindow();

  //Make sure that the application runs for as long this window is still open:
  add_window(*win);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  win->signal_hide().connect(sigc::bind<Gtk::Window*>(
    sigc::mem_fun(*this, &ExampleApplication::on_window_hide), win));

  win->show_all();
}

void ExampleApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void ExampleApplication::on_menu_file_new_generic()
{
  std::cout << "A File|New menu item was selected." << std::endl;
}

void ExampleApplication::on_menu_file_quit()
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
    windows[0]->hide(); // In this simple case, we know there is only one window.
}

void ExampleApplication::on_menu_help_about()
{
  std::cout << "App|Help|About was selected." << std::endl;
}

int main(int argc, char* argv[])
{
  auto application = ExampleApplication::create();

  // Start the application, showing the initial window,
  // and opening extra windows for any files that it is asked to open,
  // for instance as a command-line parameter.
  // run() will return when the last window has been closed by the user.
  const int status = application->run(argc, argv);
  return (status);
}