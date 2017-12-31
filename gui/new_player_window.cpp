/*#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>*/
#include <gtkmm.h>
#include <iostream>

class NewPlayerWindow : public Gtk::Window
{
protected:
  //Signal handlers:
  void new_player_button_clicked();

  //Member widgets:
  Gtk::Box VBox;
  Gtk::Box HBox_entries;
  Gtk::Box HBox_confirm_button;
  Gtk::Entry new_player_name_entry;
  Gtk::Entry new_player_elo_entry;
  Gtk::Entry new_player_kcoeff_entry;
  Gtk::Button new_player_confirm_button;

public:
  NewPlayerWindow();
  virtual ~NewPlayerWindow() {}

};

NewPlayerWindow::NewPlayerWindow() :
  VBox(Gtk::ORIENTATION_VERTICAL),
  new_player_confirm_button("Add New Player")   // creates a new button with label "Hello World".
{
  // Sets the border width and title of the window.
  Gtk::Window::set_border_width(10);
  Gtk::Window::set_title("Add a new Player");

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  new_player_confirm_button.signal_clicked().connect(sigc::mem_fun(*this,
              &NewPlayerWindow::new_player_button_clicked));

  // Text entries setup
  new_player_name_entry.set_max_length(50);
  new_player_name_entry.set_text("New Player Name");
  new_player_name_entry.set_has_frame(true);

  new_player_elo_entry.set_max_length(5);
  new_player_elo_entry.set_text("1000");

  new_player_kcoeff_entry.set_max_length(3);
  new_player_kcoeff_entry.set_text("32");

  // This packs the buttons into the Horizontal Box and adds it to the vertical box
  // Then we add the Vertical Box in the Window (a container)
  HBox_entries.add(new_player_name_entry);
  HBox_entries.add(new_player_elo_entry);
  HBox_entries.add(new_player_kcoeff_entry);
  HBox_entries.set_spacing(10);
  HBox_entries.set_homogeneous(false);
  HBox_confirm_button.add(new_player_confirm_button);
  VBox.add(HBox_entries);
  VBox.add(HBox_confirm_button);
  Gtk::Window::add(VBox);

  // The final step is to display this newly created widget...
  // new_player_confirm_button.show();
  // new_player_name_entry.show();
  Gtk::Window::show_all_children();
}

void NewPlayerWindow::new_player_button_clicked()
{
  std::cout << "Hello World" << std::endl;
  std::cout << "Player name : " << this->new_player_name_entry.get_text() << std::endl;
  std::cout << "Player elo : " << this->new_player_elo_entry.get_text() << std::endl;
  std::cout << "Player kcoeff : " << this->new_player_kcoeff_entry.get_text() << std::endl;

}

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  NewPlayerWindow new_player_window;

  //Shows the window and returns when it is closed.
  return (app->run(new_player_window));
}
