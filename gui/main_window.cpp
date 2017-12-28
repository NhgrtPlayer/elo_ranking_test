#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <iostream>

class MainWindow : public Gtk::Window
{
protected:
  //Signal handlers:
  void new_player_button_clicked();

  //Member widgets:
  Gtk::Button new_player_button;

public:
  MainWindow();
  virtual ~MainWindow() {}

};

MainWindow::MainWindow()
: new_player_button("New Player")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window.
  Gtk::Window::set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  new_player_button.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::new_player_button_clicked));

  // This packs the button into the Window (a container).
  Gtk::Window::add(new_player_button);

  // The final step is to display this newly created widget...
  new_player_button.show();
}

void MainWindow::new_player_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}

int main (int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  MainWindow main_window;

  //Shows the window and returns when it is closed.
  return (app->run(main_window));
}