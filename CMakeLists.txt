cmake_minimum_required(VERSION 3.21)
project(Pacman)

set(CMAKE_CXX_STANDARD 11)

add_executable(Pacman main.cpp src/MainForm.cpp src/Form.cpp src/GameForm.cpp src/File.cpp src/TextView.cpp src/Wall.cpp src/MainForm.cpp src/MenuView.cpp)
include_directories(/usr/local/include include)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Pacman sfml-system sfml-window sfml-graphics sfml-audio sfml-network)