#include "GameForm.h"

GameForm::GameForm() : Form("../res/map.txt") {

    initTexts();
    initSprites();
}

void GameForm::pollEvents(sf::Event &event, sf::RenderWindow *window, Application *context) {
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window).x,
                                              sf::Mouse::getPosition((*window)).y);
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (btnBack->getGlobalBounds().contains(mousePosition) ||
                    btnBackIc.getGlobalBounds().contains(mousePosition)) {
                    if (!dialog)
                        dialog = new DialogView("Pause", "you want to Quit?", "Yes", window->getSize(), [&]() -> void {
                            context->pushForm(new MainForm());
                            dialog = nullptr;
                        });
                } else if (dialog) { dialog->pollEvents(event, window); }
            }
            break;
        case sf::Event::KeyPressed:
            pacman->pollEvents(event);
            break;

    }

}


void GameForm::update(sf::RenderWindow *window) {
    if (dialog == nullptr)
        pacman->update();
}

void GameForm::render(sf::RenderWindow *window) {
    txtRecord->render(window);
    txtScore->render(window);
    btnBack->render(window);
    pacman->render(window);
    window->draw(btnBackIc);
    if (dialog != nullptr)
        dialog->render(window);
}

void GameForm::initTexts() {
    txtScore = new TextView("score\n1200", {251, 21});
    txtRecord = new TextView("high score\n3421", {380, 21});
    btnBack = new TextView("pause\nto menu", {82, 21});
    btnBack->setCharacterSize(Font::smallFontSize);
    txtScore->setCharacterSize(Font::smallFontSize);
    txtRecord->setCharacterSize(Font::smallFontSize);
}

GameForm::~GameForm() {
    delete pacman;
}

void GameForm::initSprites() {

    auto *icBackTexture = new sf::Texture;
    icBackTexture->loadFromFile("../res/icons/ic_back.png");
    btnBackIc.setPosition({30, (btnBack->getGlobalBounds().top + btnBack->getGlobalBounds().height) / 2});
    btnBackIc.setTexture(*icBackTexture);

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            if (board[i][j] == 'P') {
                pacman = new Pacman(j, i, board);
                //i dont know why but without this print line the view doesnt render:)
//                cout << pacman->getPosition().x << pacman->getPosition().y << endl;
            }
        }
    }
}
