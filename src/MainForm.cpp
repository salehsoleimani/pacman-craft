#include "MainForm.h"

MainForm::MainForm() {
    window = nullptr;
    initWindow();
}

MainForm::~MainForm() {
    if (window != nullptr) delete window;
}

void MainForm::initWindow() {
    Application &app = Application::getInstance();

    window = new sf::RenderWindow(app.videoMode, app.appName, app.style);
    window->setFramerateLimit(app.windowFrameRate);
}

bool MainForm::isRunning() const {
    return window->isOpen();
}

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

void MainForm::display() {
    while (isRunning()) {
        update();
        render();
    }
}