#include "Application.h"

Application::Application() {
    window.create(Config::videoMode, Config::appName, Config::style);
    window.setFramerateLimit(Config::windowFrameRate);
}

void Application::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        //calculating dt(delta time) between frames
        sf::Time dt = clock.restart();

        //update
        if (!dialog.isVisible())
            currentForm()->update(&window, dt);

        //render
        window.clear(Colors::colorBlue);
        //draw walls background
        currentForm()->clear(&window);
        currentForm()->render(&window);

        if (dialog.isVisible())
            dialog.render(&window);

        //handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            //close window btn
            if (event.type == sf::Event::Closed)
                window.close();

            if (dialog.isVisible())
                dialog.pollEvents(event, &window);
            else {
                //abstract event handler in Form class
                currentForm()->pollEvents(event, &window);
            }
        }
        window.display();
    }
}

Form *Application::currentForm() {
    if (forms.empty()) return nullptr;
    return forms.back();
}

void Application::popForm() {
    delete forms.back();
    forms.pop_back();
}

void Application::resetGame() {
    delete forms.front();
    forms.pop_front();
}

void Application::pushFront(Form *form) {
    forms.push_front(form);
}

Application::~Application() {
    while (!forms.empty()) popForm();
}

DialogView &Application::getDialog() {
    return dialog;
}
