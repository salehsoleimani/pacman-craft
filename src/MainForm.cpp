#include "MainForm.h"

void MainForm::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
        }

    }
}

void MainForm::update() {
    pollEvents();
}

void MainForm::render() {
    window->clear(Application::colorBlue);
    window->display();
}