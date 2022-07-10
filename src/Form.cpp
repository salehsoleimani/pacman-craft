#include "Form.h"

Form::Form() {
    window = nullptr;
    initWindow();
}

Form::~Form() {
    if (window != nullptr) delete window;
}

void Form::initWindow() {
    Application &app = Application::getInstance();

    window = new sf::RenderWindow(app.videoMode, app.appName, app.style);
    window->setFramerateLimit(app.windowFrameRate);
}

bool Form::isRunning() const {
    return window->isOpen();
}

void Form::display() {
    while (isRunning()) {
        update();
        render();
    }
}