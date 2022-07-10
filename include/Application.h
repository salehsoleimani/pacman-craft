#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

//singleton class for accessing some helper method, variables
class Application {
public:
    Application(const Application &) = delete;

    void operator=(const Application &) = delete;

    static Application &getInstance();

    // Window params.
    const sf::VideoMode videoMode = {582, 774};
    const int windowFrameRate = 60;
    const string appName = "Pacman";

    const sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;

    //colors
    static const sf::Color colorBlue;

private:
    Application() = default;
};


#endif //PACMAN_APPLICATION_H
