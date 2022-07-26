#include "Pacman.h"
#include "GameForm.h"

GameForm::GameForm() : Form("../res/map.txt") {

    initTexts();
    initSprites();
}

GameForm::~GameForm() {
    delete pacman;
    for (auto food: foods) delete food;
    if (food)
        delete food;
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


void GameForm::update(sf::RenderWindow *window, const sf::Time &dt) {
    if (dialog == nullptr) {
        pacman->update(dt);
        for (auto food: foods) {
            food->update(dt);
        }
    }
}

void GameForm::render(sf::RenderWindow *window) {
    txtRecord->render(window);
    txtScore->render(window);
    btnBack->render(window);
    for (auto food: foods) food->render(window);
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

void GameForm::initSprites() {
    auto *icBackTexture = new sf::Texture;
    icBackTexture->loadFromFile("../res/icons/ic_back.png");
    btnBackIc.setPosition({30, (btnBack->getGlobalBounds().top + btnBack->getGlobalBounds().height) / 2});
    btnBackIc.setTexture(*icBackTexture);

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            switch (board[i][j]) {
                case GameObject::ObjectType::PACMAN:
                    pacman = new Pacman(sf::Vector2f{j * Dimensions::wallSize.x, i * Dimensions::wallSize.x}, this);
                    break;
                case GameObject::ObjectType::FOOD: //normal foods
                    food = new Food({j * Dimensions::wallSize.x,
                                     i * Dimensions::wallSize.y}, Food::FoodType::NORMAL);
                    food->setRelativePosition(sf::Vector2f(sf::Vector2i{j, i}));
                    foods.push_back(food);
                    break;
                case GameObject::ObjectType::FOOD_POWER: //power foods
                    food = new Food({j * Dimensions::wallSize.x,
                                     i * Dimensions::wallSize.y}, Food::FoodType::POWER);
                    food->setRelativePosition(sf::Vector2f(sf::Vector2i{j, i}));
                    foods.push_back(food);
                    break;
            }
        }
    }
}

const vector<Food *> &GameForm::getFoods() const {
    return foods;
}
