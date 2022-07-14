#ifndef PACMAN_FORM_H
#define PACMAN_FORM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <iostream>
#include <vector>
#include "Wall.h"
#include "Values.h"
#include "File.h"

using namespace std;

class Form {
public:
//    Form();

//    virtual ~Form();

//    void display();

//protected:
//    sf::Event event;

//    bool isRunning() const;

//    virtual void pollEvents() = 0;
    virtual Form *pollEvents(sf::Event &,sf::RenderWindow*) = 0;

    virtual void update() = 0;

    virtual void render(sf::RenderWindow *) = 0;

//    void initWindow();
//protected:
//    sf::RenderWindow *window;


};


#endif //PACMAN_FORM_H
