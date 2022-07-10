#ifndef PACMAN_FORM_H
#define PACMAN_FORM_H

#include "Application.h"

class Form {
public:
    Form();

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
};


#endif //PACMAN_FORM_H
