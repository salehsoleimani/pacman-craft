#include "Form.h"

//Form::Form() {
//    this->mapFileName = mapFileName;
//    window = nullptr;
//    initWindow();
//    initGrid();
//}

//Form::~Form() {
//}

//void Form::initWindow() {
//    window = new sf::RenderWindow(Config::videoMode, Config::appName, Config::style);
//    window->setFramerateLimit(Config::windowFrameRate);
//}

//bool Form::isRunning() const {
//    return window->isOpen();
//}

//void Form::display() {
//    if (window == nullptr) initWindow();
//    while (isRunning()) {
//        update();
//        window->clear(Colors::colorBlue);
//        render();
//
//
//        window->display();
//    }
//}