#ifndef PACMAN_APPLICATION_H
#define PACMAN_APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <stack>

#include "Form.h"
#include "Values.h"
#include "MainForm.h"
#include "OptionsForm.h"
#include "GameForm.h"

class Application {
public:
    Application() {
        window.create(Config::videoMode, Config::appName, Config::style);
        window.setFramerateLimit(Config::windowFrameRate);

        forms.push(new MainForm());
    }

    ~Application() {
        while (!this->forms.empty()) popForm();
    }

    void run() {

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                currentForm()->pollEvents(event,&window);
            }
            currentForm()->update();
            window.clear(Colors::colorBlue);
            currentForm()->render(&window);
            window.display();
        }
    }

    void pushForm(Form *form) {
        this->forms.push(form);
    }

    void popForm() {
        delete this->forms.top();
        this->forms.pop();
    }

    void changeForm(Form *form) {
        if (!this->forms.empty())
            popForm();
        pushForm(form);
    }

    Form *currentForm() {
        if (this->forms.empty()) return nullptr;
        return this->forms.top();
    }

private:
    sf::RenderWindow window;

    stack<Form *> forms;
};

#endif //PACMAN_APPLICATION_H
