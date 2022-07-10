#ifndef PACMAN_MAINFORM_H
#define PACMAN_MAINFORM_H

#include "Application.h"

class MainForm {
public:
    MainForm();

    ~MainForm();

    void display();

private:
    sf::RenderWindow *window;
    sf::Event event;

    bool isRunning() const;

    void pollEvents();

    void update();

    void render();

    void initWindow();
};


#endif //PACMAN_MAINFORM_H
