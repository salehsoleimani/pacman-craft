#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <array>
#include "File.h"
#include "Wall.h"

using namespace std;

enum class ALIGN{
    CENTER,
    CENTER_VERTICAL,
    CENTER_HORIZONTAL,
    LEFT,
    RIGHT,
    BOTTOM,
    TOP
};

//singleton class for accessing some helper method, variables
class Application {
public:
    Application(const Application &) = delete;

    void operator=(const Application &) = delete;

    static Application &getInstance();

    // Window params.
    const sf::VideoMode videoMode = {570, 780};
    const int windowFrameRate = 60;
    const string appName = "Pacman";

    //view dimensions
    static const sf::Vector2f wallSize;
    static const int WALL_ROW;
    static const int WALL_COL;

    //font
    static const int smallFontSize;
    static const int bigFontSize;
    static const int mediumFontSize;

    const sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;

    //colors
    static const sf::Color colorBlue;
    static const sf::Color colorCyan;
    static const sf::Color colorWall;

private:
    Application() = default;
};


#endif //PACMAN_APPLICATION_H
