#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <array>
#include <unordered_map>
#include <functional>
#include "File.h"
#include "Wall.h"
#include "TextView.h"

using namespace std;

//singleton class for accessing some helper method, variables
class Application {
public:
    Application(const Application &) = delete;

    void operator=(const Application &) = delete;

    static Application &getInstance() {
        static Application instance;
        return instance;
    }


    // Window params.
    const sf::VideoMode videoMode = {570, 780};
    const int windowFrameRate = 60;
    const string appName = "Pacman";

    const sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;

private:
    Application() = default;

};

//colors
namespace Colors {
    static const sf::Color colorBlue = sf::Color(10, 7, 67);
    static const sf::Color colorCyan = sf::Color(175, 255, 228);
    static const sf::Color colorWall = sf::Color(28, 145, 229);
    static const sf::Color colorActive = sf::Color(255, 234, 0);
}

//font
namespace Font {
    static const int smallFontSize = 20;
    static const int bigFontSize = 46;
    static const int mediumFontSize = 36;
}

//view dimensions
namespace Dimensions {
    static const float margin = 30;
    static const sf::Vector2f wallSize = {30, 30};
    static const int WALL_ROW = 26;
    static const int WALL_COL = 19;
}

#endif //PACMAN_APPLICATION_H
