#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>
#include <cmath>
#include "Values.h"
#include "Form.h"

//main state-machine for game
class Application {
public:
    //setting up window
    Application() {
        window.create(Config::videoMode, Config::appName, Config::style);
        window.setFramerateLimit(Config::windowFrameRate);
    }

    //game-loop
    void run() {
        sf::Clock clock;
        while (window.isOpen()) {

            //calculating dt(delta time) between frames
            sf::Time dt = clock.restart();

            //update
            currentForm()->update(&window,dt);

            //render
            window.clear(Colors::colorBlue);
            //draw walls background
            currentForm()->clear(&window);
            currentForm()->render(&window);

            //handle events
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                //abstract event handler in Form class
                currentForm()->pollEvents(event, &window, this);
            }

            window.display();

        }
    }

    //functions used to switch between states
    Form *currentForm() {
        if (forms.empty()) return nullptr;
        return forms.back();
    }

    void pushForm(Form *form) {
        forms.push_back(form);
    }

    void popForm() {
        delete forms.back();
        forms.pop_back();
    }

    //reset button in options menu
    void resetGame() {
        delete forms.front();
        forms.pop_front();
    }

    void pushFront(Form *form){
        forms.push_front(form);
    }

    ///deleting Form pointers from memory
    ~Application() {
        while (!forms.empty()) popForm();
    }

private:
    sf::RenderWindow window;

    deque<Form *> forms;
};


#endif //PACMAN_APPLICATION_H
