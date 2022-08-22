#include "CustomMapForm.h"

CustomMapForm::CustomMapForm(Application &context) : Form("../res/custom_map.txt", context, -90) {
    initTexts();
    initButtons();
}

CustomMapForm::~CustomMapForm() {
    delete txtGuide;
    delete btnPlay;
}

void CustomMapForm::initButtons() {
    btnPlay = new ButtonView("play", {463, 679}, ButtonView::ButtonSize::SMALL, [&]() -> void {
        getApplicationContext().pushForm(new GameForm(getApplicationContext(), "../res/custom_map.txt"));
        //pop main menu
        getApplicationContext().resetGame();
        //pop the custom game itself
        getApplicationContext().resetGame();
        getApplicationContext().getDialog().hide();
    });
}

void CustomMapForm::initTexts() {
    txtGuide = new TextView("key codes:\n"
                            "-W wall         -F pellet\n"
                            "-P power        ", {30, 684});
    txtGuide->setCharacterSize(Font::smallFontSize);
    txtGuide->setFillColor(sf::Color::White);
}

void CustomMapForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {
    btnPlay->eventHandler(event, sf::Vector2f(sf::Mouse::getPosition(*window)));
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        default:
            break;
    }
}

void CustomMapForm::update(sf::RenderWindow *window, const sf::Time &dt) {
}

void CustomMapForm::render(sf::RenderWindow *window) {
    txtGuide->render(window);
    btnPlay->render(window);
}