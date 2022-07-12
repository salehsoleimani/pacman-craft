#include "Application.h"

//static member initializations
const sf::Color Application::colorBlue = sf::Color(10, 7, 67);
const sf::Color Application::colorWall = sf::Color(28, 145, 229);
const sf::Color Application::colorCyan = sf::Color(175, 255, 228);

const sf::Vector2f Application::wallSize = {30, 30};
const int Application::WALL_ROW = 26;
const int Application::WALL_COL = 19;

const int Application::bigFontSize = 46;
const int Application::mediumFontSize = 36;
const int Application::smallFontSize = 20;


Application &Application::getInstance() {
    static Application instance;
    return instance;
}
