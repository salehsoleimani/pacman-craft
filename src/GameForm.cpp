#include "Pacman.h"
#include "GameForm.h"
#include "Inky.h"

GameForm::GameForm() : Form("../res/map.txt") {

    initTexts();
    initSprites();
}

GameForm::~GameForm() {
    if (score > highScore)
        try {
            File file("high_score.txt");
            file.open(ios::out);
            file << score;
        } catch (file_open_exception ex) {
            cerr << "error reading highscore";
        }
    delete pacman;
    for (auto food: foods) delete food;
    if (dialog) delete dialog;
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
                        dialog = new DialogView("Pause", "pause the game", "okay", "cancel", window->getSize(),
                                                [&]() -> void {
                                                    context->pushForm(new MainForm());
                                                    delete dialog;
                                                    dialog = nullptr;
                                                },
                                                [&]() -> void {
                                                    delete dialog;
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
    ifstream f(string("high_score.txt").c_str());
    if (!f.good()) highScore = 0;
    txtRecord->setString("high score\n" + to_string(highScore));
    if (!dialog) {
        pacman->update(dt);

        for (auto food: foods)
            food->update(dt);

        txtScore->setString("score\n" + to_string(this->score));
    }
}

void GameForm::render(sf::RenderWindow *window) {
    txtRecord->render(window);
    txtScore->render(window);
    btnBack->render(window);
    for (auto food: foods) food->render(window);
    for (auto ghost: ghosts) ghost->render(window);
    pacman->render(window);
    window->draw(btnBackIc);
    if (dialog)
        dialog->render(window);
}

void GameForm::initTexts() {
    try {
        File file("high_score.txt");
        file.open(ios::in);
        highScore = stoi(file.getline());
    } catch (file_open_exception ex) {
        highScore = 0;
    }

    txtScore = new TextView("score\n0", {251, 21});
    txtRecord = new TextView("high score\n" + to_string(highScore), {380, 21});
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
            sf::Vector2f position = sf::Vector2f{j * Dimensions::wallSize.x, i * Dimensions::wallSize.x};
            switch (board[i][j]) {
                case GameObject::ObjectType::PACMAN:
                    pacman = new Pacman(position, this);
                    break;
                case GameObject::ObjectType::FOOD: //normal foods
                    food = new Food(position, Food::FoodType::NORMAL);
                    food->setRelativePosition(sf::Vector2f(sf::Vector2i{j, i}));
                    foods.push_back(food);
                    break;
                case GameObject::ObjectType::FOOD_POWER: //power foods
                    food = new Food(position, Food::FoodType::POWER);
                    food->setRelativePosition(sf::Vector2f(sf::Vector2i{j, i}));
                    foods.push_back(food);
                    break;
                case GameObject::ObjectType::INKY:
                    ghosts.push_back(new Inky(position,this));
                    break;
            }
        }
    }
}

const vector<Food *> &GameForm::getFoods() const {
    return foods;
}

const vector<Ghost *> &GameForm::getGhosts() const {
    return ghosts;
}

void GameForm::raiseScore(int score) {
    this->score += score;
}