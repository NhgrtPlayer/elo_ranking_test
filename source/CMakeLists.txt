set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Werror -std=c++17")

link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ../header )

add_executable(
	elo_ranking_generator
	main.cpp
	MainWindow.cpp
	NewPlayerWindow.cpp
	MainTreeView.cpp
	MainApplication.cpp
	Player.cpp
)

target_link_libraries(elo_ranking_generator 
    ${GTKMM_LIBRARIES})