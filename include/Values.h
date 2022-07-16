#ifndef PACMAN_VALUES_H
#define PACMAN_VALUES_H


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//config
namespace Config {
// Window params.
    const sf::VideoMode videoMode = {570, 780};
    const int windowFrameRate = 60;
    const std::string appName = "Pacman";

    const sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
}

//colors
namespace Colors {
    static const sf::Color colorBlue = sf::Color(10, 7, 67);
    static const sf::Color colorCyan = sf::Color(175, 255, 228);
    static const sf::Color colorWall = sf::Color(28, 145, 229);
    static const sf::Color colorActive = sf::Color(255, 234, 0);
    static const sf::Color colorShadow = sf::Color(238, 35, 39);
    static const sf::Color colorTransparent = sf::Color(0, 0, 0, 76);
}

//font
namespace Font {
    static const int smallFontSize = 20;
    static const int regularFontSize = 26;
    static const int bigFontSize = 46;
    static const int mediumFontSize = 36;
}

//view dimensions
namespace Dimensions {
    static const float margin = 48;
    static const float shadowOffset = 6;
    static const sf::Vector2f wallSize = {30, 30};
    static const int WALL_ROW = 26;
    static const int WALL_COL = 19;
    static const sf::Vector2f BUTTON_SIZE_SMALL = {138, 74};
    static const sf::Vector2f BUTTON_SIZE_BIG = {298, 74};
}


#endif //PACMAN_VALUES_H
