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

class Application;

class Form {
public:
    Form(string);

    virtual ~Form();

    virtual void pollEvents(sf::Event &, sf::RenderWindow *, Application *) = 0;

    virtual void update() = 0;

    virtual void render(sf::RenderWindow *) = 0;

    virtual void clear(sf::RenderWindow *window);

private:
    void initGrid();

    vector<Wall *> walls;

    array<array<char, 19>, 26> board;

    string mapFileName;
};


#endif //PACMAN_FORM_H
