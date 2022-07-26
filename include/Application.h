#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>
#include <cmath>
#include "Values.h"
#include "Form.h"


class Application {
public:
    Application() {
        window.create(Config::videoMode, Config::appName, Config::style);
        window.setFramerateLimit(Config::windowFrameRate);
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {

            sf::Time dt = clock.restart();

            currentForm()->update(&window,dt);

            window.clear(Colors::colorBlue);
            //draw walls background
            currentForm()->clear(&window);
            currentForm()->render(&window);

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

    ~Application() {
        while (!forms.empty()) popForm();
    }

private:
    sf::RenderWindow window;

    deque<Form *> forms;
};


#endif //PACMAN_APPLICATION_H
