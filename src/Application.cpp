#include "Application.h"

//static member initializations
const sf::Color Application::colorBlue = sf::Color(10, 7, 67);
const sf::Color Application::colorWall = sf::Color(28, 145, 229);

const sf::Vector2f Application::wallSize = {30, 30};
const int Application::WALL_ROW = 22;
const int Application::WALL_COL = 19;

const int Application::smallFontSize = 20;


Application &Application::getInstance() {
    static Application instance;
    return instance;
}
