#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <deque>

#include "Values.h"
#include "Form.h"


class Application {
public:
    Application() {
        window.create(Config::videoMode, Config::appName, Config::style);
        window.setFramerateLimit(Config::windowFrameRate);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                currentForm()->pollEvents(event, &window, this);
            }
            currentForm()->update();
            window.clear(Colors::colorBlue);
            currentForm()->clear(&window);
            currentForm()->render(&window);

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

    void resetGame(Form *form) {
        delete forms.front();
        forms.pop_front();
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
