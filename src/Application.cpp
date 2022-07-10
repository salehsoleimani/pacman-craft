#include "Application.h"

//static member initializations
const sf::Color Application::colorBlue = sf::Color(10, 7, 67);

Application &Application::getInstance() {
    static Application instance;
    return instance;
}
