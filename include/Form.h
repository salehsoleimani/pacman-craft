#ifndef PACMAN_FORM_H
#define PACMAN_FORM_H

#include "Application.h"

class Form {
public:
    Form(string mapFileName);

    ~Form();

    void display();

protected:
    sf::RenderWindow *window;
    sf::Event event;

    bool isRunning() const;

    virtual void pollEvents() = 0;

    virtual void update() = 0;

    virtual void render() = 0;

    void initWindow();

private:
    string mapFileName;

    void initGrid();

    vector<Wall *> walls;

    array<array<char, 19>, 26> board;
};


#endif //PACMAN_FORM_H
