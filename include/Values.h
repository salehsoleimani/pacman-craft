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
    const sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close | sf::Style::Default;
}

//colors
namespace Colors {
    const sf::Color colorBlue = sf::Color(10, 7, 67);
    const sf::Color colorCyan = sf::Color(175, 255, 228);
    const sf::Color colorWall = sf::Color(28, 145, 229);
    const sf::Color colorActive = sf::Color(255, 234, 0);
    const sf::Color colorShadow = sf::Color(238, 35, 39);
    const sf::Color colorTransparent = sf::Color(0, 0, 0, 76);
    const sf::Color colorDot = sf::Color(247, 191, 80);
}

//font
namespace Font {
    const int smallFontSize = 20;
    const int regularFontSize = 26;
    const int bigFontSize = 46;
    const int mediumFontSize = 36;
}

//view dimensions
namespace Dimensions {

    const float margin = 48;

    const float shadowOffset = 6;

    const sf::Vector2f wallSize = {30, 30};

    const int WALL_ROW = 26;
    const int WALL_COL = 19;

    static const sf::Vector2f BUTTON_SIZE_SMALL = {138, 74};
    static const sf::Vector2f BUTTON_SIZE_BIG = {298, 74};
}

namespace Path {

    const std::string fruit = "../res/sprites/fruits/";

    const float shadowOffset = 6;

    const sf::Vector2f wallSize = {30, 30};

    const int WALL_ROW = 26;
    const int WALL_COL = 19;

    const sf::Vector2f BUTTON_SIZE_SMALL = {138, 74};
    const sf::Vector2f BUTTON_SIZE_BIG = {298, 74};
}

enum class Directions {
    INIT = 0, UP = 1, DOWN = 3, LEFT = 2, RIGHT = 4
};

#endif //PACMAN_VALUES_H
