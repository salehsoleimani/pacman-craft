#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>
#include <cmath>
#include "Values.h"
#include "Form.h"
#include "DialogView.h"

//main state-machine for game
class Application {
public:
    //setting up window
    Application();

    //game-loop
    void run();

    //functions used to switch between states
    Form *currentForm();

    void pushForm(Form *form) {
        forms.push_back(form);
    }

    void popForm();

    //reset button in options menu
    void resetGame();

    void pushFront(Form *form);

    DialogView &getDialog();

    ///deleting Form pointers from memory
    ~Application();

private:
    sf::RenderWindow window;

    deque<Form *> forms;

    DialogView dialog;
};


#endif //PACMAN_APPLICATION_H
