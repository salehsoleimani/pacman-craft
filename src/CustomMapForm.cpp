#include "CustomMapForm.h"
#include <iostream>

CustomMapForm::CustomMapForm(Application &context) : Form("../res/custom_map.txt", context, -90) {
    initTexts();
    initButtons();

    //drawing blank fileds is common for all forms
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            if (board[i][j] == GameObject::ObjectType::BLANK) {
                blanks.push_back(new BlankTile({j * Dimensions::wallSize.x,
                                                i * Dimensions::wallSize.y - 90}));
            }
        }
    }
}

CustomMapForm::~CustomMapForm() {
    for (auto blank: blanks) delete blank;
    delete txtGuide;
    delete btnPlay;
}

void CustomMapForm::initButtons() {
    btnPlay = new ButtonView("play", {463, 679}, ButtonView::ButtonSize::SMALL, [&]() -> void {

        File output("../res/new_map.txt");
        output.open(ios::out);


        File input("../res/custom_map.txt");
        input.open(ios::in);

        int index = 0;

        for (int i = 0; i < 26; ++i) {
            string line = input.getline();
            for (int j = 0; j < line.size(); ++j) {
                GameObject::ObjectType objectType = blanks[i][j].objectType;
                objectType = objectType;
                if (line[j] == 'Z') {
                    switch (blanks[index]->getObjectType()) {
                        case GameObject::ObjectType::WALL:
                            output << 'W';
                            break;
                        case GameObject::ObjectType::PACMAN:
                            output << 'A';
                            break;
                        case GameObject::ObjectType::PELLET:
                            output << 'F';
                            break;
                        case GameObject::ObjectType::PELLET_POWER:
                            output << 'S';
                            break;
                        case GameObject::ObjectType::INKY:
                            output << 'I';
                            break;
                        case GameObject::ObjectType::BLINKY:
                            output << 'B';
                            break;
                        case GameObject::ObjectType::CLYDE:
                            output << 'C';
                            break;
                        case GameObject::ObjectType::PINKY:
                            output << 'P';
                            break;
                        case GameObject::ObjectType::HEART:
                            output << 'H';
                            break;
                        case GameObject::ObjectType::EMPTY:
                        case GameObject::ObjectType::BLANK:
                        case GameObject::ObjectType::INIT:
                            output << 'E';
                            break;
                    }
                    index++;
                } else {
                    output << line[j];
                }
            }
            if (i != 25)
                output << "\n";
        }
        output.close();
        input.close();

        getApplicationContext().pushForm(new GameForm(getApplicationContext(), "../res/new_map.txt"));
        //pop main menu
        getApplicationContext().resetGame();
        //pop the custom game itself
        getApplicationContext().resetGame();
        getApplicationContext().getDialog().hide();
    });
}

void CustomMapForm::initTexts() {
    txtGuide = new TextView("-I inky    -P pinky    -C clyde\n"
                            "-W wall  -S power   -B blinky  \n"
                            "-A pacman   -P pellet   -Z undo", {30, 684});
    txtGuide->setCharacterSize(Font::smallFontSize);
    txtGuide->setFillColor(sf::Color::White);
}

void CustomMapForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {

    btnPlay->eventHandler(event, sf::Vector2f(sf::Mouse::getPosition(*window)));

    switch (event.type) {
        case sf::Event::MouseButtonPressed: {
            GameObject::ObjectType temp = GameObject::ObjectType::INIT;

            switch (lastEnteredKey) {
                case sf::Keyboard::W: // WALL
                    temp = GameObject::ObjectType::WALL;
                    break;
                case sf::Keyboard::A: //PACMAN
                    temp = GameObject::ObjectType::PACMAN;
                    break;
                case sf::Keyboard::F: //Normal Food
                    temp = GameObject::ObjectType::PELLET;
                    break;
                case sf::Keyboard::S ://Power food
                    temp = GameObject::ObjectType::PELLET_POWER;
                    break;
                case sf::Keyboard::E:
                    temp = GameObject::ObjectType::EMPTY;
                    break;
                case sf::Keyboard::I:
                    temp = GameObject::ObjectType::INKY;
                    break;
                case sf::Keyboard::P:
                    temp = GameObject::ObjectType::PINKY;
                    break;
                case sf::Keyboard::B:
                    temp = GameObject::ObjectType::BLINKY;
                    break;
                case sf::Keyboard::C:
                    temp = GameObject::ObjectType::CLYDE;
                    break;
                case sf::Keyboard::Z:
                    temp = GameObject::ObjectType::BLANK;
                default:
                    break;
            }

            for (auto tile: blanks) {
                //modify board too

                sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));

                sf::FloatRect globalBounds = tile->getGlobalBounds();
                if (globalBounds.contains(mousePosition)) {
                    tile->setObjectType(temp);
                }
            }
            break;
        }
        case sf::Event::KeyPressed: {
            lastEnteredKey = event.key.code;
            break;
        }
        default:
            break;
    }
}

void CustomMapForm::update(sf::RenderWindow *window, const sf::Time &dt) {
}

void CustomMapForm::render(sf::RenderWindow *window) {
    txtGuide->render(window);
    btnPlay->render(window);
    for (auto blank: blanks) blank->render(window);
}