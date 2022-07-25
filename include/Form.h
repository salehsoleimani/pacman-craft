#ifndef PACMAN_FORM_H
#define PACMAN_FORM_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <iostream>
#include <vector>
#include "Wall.h"
#include "Food.h"
#include "Values.h"
#include "File.h"

using namespace std;

class Application;

class Form {
public:
    Form(string);

    virtual ~Form();

    //to poll events from Application window to forms
    virtual void pollEvents(sf::Event &, sf::RenderWindow *, Application *) = 0;

    virtual void update(sf::RenderWindow *,const sf::Time&) = 0;

    virtual void render(sf::RenderWindow *) = 0;

    //draw background walls based on map
    virtual void clear(sf::RenderWindow *window);

    const array<array<char, 19>, 26> &getBoard() const;

private:
    void initGrid();

    vector<Wall *> walls;

    //initizalized by class constructor
    string mapFileName;

protected:
    //we need this in GameForm for drawing other entities
    array<array<char, 19>, 26> board;
};


#endif //PACMAN_FORM_H
