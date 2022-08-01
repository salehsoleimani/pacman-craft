#include "Pacman.h"
#include "GameForm.h"
#include <random>
#include "Inky.h"
#include "Blinky.h"
#include "Clyde.h"
#include "Pinky.h"

GameForm::GameForm(Application &context) : Form("../res/map.txt", context) {
    initGame();
    initSprites();
    dialog.create("Welcome!", "arrow keys to move", "continue",
                  [&]() -> void {
                      dialog.hide();
                  }).show();
}

GameForm::~GameForm() {
    delete pacman;
    for (auto snack: snacks) delete snack;
    for (auto ghost: ghosts) delete ghost;
    delete heartTexture;
    delete txtRecord;
    delete btnBack;
    delete txtScore;
    if (score > highScore)
        storeRecord();
}

void GameForm::storeRecord() {
    try {
        File file("../res/high_score.txt");
        file.open(ios::out);
        file << score;
    } catch (file_open_exception ex) {
        cerr << "error reading highscore";
    }
}

void GameForm::readRecord() {
    try {
        File file("../res/high_score.txt");
        file.open(ios::in);
        file.seekg(0);
        file.clear();
        string line = file.getline();
        highScore = stoul(line);
    } catch (const file_open_exception &ex) {
        cerr << "error reading record" << endl;
        highScore = 0;
    }
}

void GameForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {
    sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window).x,
                                              sf::Mouse::getPosition((*window)).y);
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (dialog.isVisible()) {
                    dialog.pollEvents(event, window);
                }
                if (!dialog.isVisible())
                    if (btnBack->getGlobalBounds().contains(mousePosition) ||
                        btnBackIc.getGlobalBounds().contains(mousePosition)) {
                        dialog.create("Pause", "pause the game", "okay", "cancel",
                                      [&]() -> void {
                                          getApplicationContext().pushForm(
                                                  new MainForm(getApplicationContext()));
                                          dialog.hide();
                                      },
                                      [&]() -> void {
                                          dialog.hide();
                                      }).show();
                    }
            }
            break;
        case sf::Event::KeyPressed:
            pacman->pollEvents(event);
            break;

    }
}

void GameForm::update(sf::RenderWindow *window, const sf::Time &dt) {

    //if pacman ate all snacks rearrange board - reach to next level
    if (eatenSnacks == snacksCount) {
        dialog.create("Victory", "reached level " + to_string(level + 1), "Hooray!",
                      [&]() -> void {
                          dialog.hide();
                          level++;
                          resetBoard();
                      }).show();
    }

    if (isFruitVisible) fruitTimer += dt.asSeconds();

    if (fruitTimer >= 10 && isFruitVisible) {
        fruitTimer = 0;
        delete snacks.back();
        snacks.pop_back();
        isFruitVisible = false;
    }

    if ((eatenSnacks >= 70 && fruitsCount == 0) || (eatenSnacks >= 170 && fruitsCount == 1)) {
        fruitsCount++;
        isFruitVisible = true;
        vector<Snack *> randomSnacks;
        for (auto snack: snacks) {
            if (snack->isEaten())
                randomSnacks.push_back(snack);
        }
        std::shuffle(randomSnacks.begin(), randomSnacks.end(), std::mt19937(std::random_device()()));

        Fruit::FruitType fruitType = Fruit::FruitType::APPLE;

        if (level >= 241) fruitType = Fruit::FruitType::BANANA;
        else if (level >= 225) fruitType = Fruit::FruitType::GRAPES;
        else if (level >= 192) fruitType = Fruit::FruitType::PEACH;
        else if (level >= 129) fruitType = Fruit::FruitType::CHERRY;
        else if (level >= 65) fruitType = Fruit::FruitType::STRAWBERRY;

        Fruit *newFruit = new Fruit(randomSnacks[0]->getPosition(), fruitType);
        newFruit->setRelativePosition(randomSnacks[0]->getRelativePosition());
        snacks.push_back(newFruit);
    }

    txtRecord->setString("high score\n" + to_string(highScore));

    if (!dialog.isVisible()) {
        pacman->update(dt);

        for (auto snack: snacks)
            if (snack) snack->update(dt);

        for (auto ghost: ghosts)
            if (ghost) ghost->update(dt);

        txtScore->setString("score\n" + to_string(this->score));
    }
}

void GameForm::render(sf::RenderWindow *window) {
    txtRecord->render(window);
    txtScore->render(window);
    btnBack->render(window);
    for (auto snack: snacks) snack->render(window);
    for (auto ghost: ghosts) ghost->render(window);
    for (auto heart: hearts) window->draw(heart);
    pacman->render(window);
    window->draw(btnBackIc);
    if (dialog.isVisible())
        dialog.render(window);
}

list<Snack *> &GameForm::getSnacks() {
    return snacks;
}

list<Ghost *> &GameForm::getGhosts() {
    return ghosts;
}

void GameForm::raiseScore(int score) {
    this->score += score;
    if (score <= 50)
        eatenSnacks++;
}

void GameForm::lose() {
    sf::sleep(sf::milliseconds(300));
    int lives = hearts.size();
    if (lives > 1) {
        hearts.pop_back();
        delete pacman;
        pacman = new Pacman(pacmanPosition, this);
        score -= 20;
    } else {
        dialog.create("Game Over!", "you lose", "continue",
                      [&]() -> void {
                          level = 1;
                          resetBoard();
                          initGame();
                          score = 0;
                          dialog.hide();
                      }).show();
    }
}

void GameForm::resetBoard() {
    isFruitVisible = false;
    fruitTimer = 0;
    if (score > highScore)
        storeRecord();
    readRecord();
    for (auto snack: snacks) delete snack;
    for (auto ghost: ghosts) delete ghost;
    snacks.clear();
    ghosts.clear();
    initSprites();
    eatenSnacks = 0;
    fruitsCount = 0;
}

void GameForm::initGame() {
    score = 0;
    readRecord();

    txtScore = new TextView("score\n0", {251, 21});
    txtRecord = new TextView("high score\n" + to_string(highScore), {380, 21});
    btnBack = new TextView("pause\nto menu", {82, 21});
    btnBack->setCharacterSize(Font::smallFontSize);
    txtScore->setCharacterSize(Font::smallFontSize);
    txtRecord->setCharacterSize(Font::smallFontSize);

    auto *icBackTexture = new sf::Texture;
    icBackTexture->loadFromFile("../res/icons/ic_back.png");
    btnBackIc.setPosition({30, (btnBack->getGlobalBounds().top + btnBack->getGlobalBounds().height) / 2});
    btnBackIc.setTexture(*icBackTexture);

    heartTexture = new sf::Texture;
    heartTexture->loadFromFile("../res/sprites/heart.png");
    heartTexture->setSmooth(true);

    sf::Sprite heartSprite(*heartTexture);

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            sf::Vector2f position = sf::Vector2f{j * Dimensions::wallSize.x, i * Dimensions::wallSize.x};
            if (board[i][j] == GameObject::ObjectType::HEART) {
                heartSprite.setPosition(position);
                hearts.push_back(heartSprite);
            }
        }
    }
}

void GameForm::initSprites() {
    snacksCount = 0;

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            Pellet *snack = nullptr;
            sf::Vector2f position = sf::Vector2f{j * Dimensions::wallSize.x, i * Dimensions::wallSize.x};
            switch (board[i][j]) {
                case GameObject::ObjectType::PACMAN:
                    pacman = new Pacman(position, this);
                    pacmanPosition = position;
                    break;
                case GameObject::ObjectType::FOOD: //normal foods
                    snacksCount++;
                    snack = new Pellet(position, Pellet::PelletType::NORMAL);
                    snack->setRelativePosition(sf::Vector2f(sf::Vector2i{j, i}));
                    snacks.push_back(snack);
                    break;
                case GameObject::ObjectType::FOOD_POWER: //power foods
                    snacksCount++;
                    snack = new Pellet(position, Pellet::PelletType::POWER);
                    snack->setRelativePosition(sf::Vector2f(sf::Vector2i{j, i}));
                    snacks.push_back(snack);
                    break;
                case GameObject::ObjectType::INKY:
                    ghosts.push_back(new Inky(position, this));
                    break;
                case GameObject::ObjectType::BLINKY:
                    ghosts.push_back(new Blinky(position, this));
                    break;
                case GameObject::ObjectType::CLYDE:
                    ghosts.push_back(new Clyde(position, this));
                    break;
                case GameObject::ObjectType::PINKY:
                    ghosts.push_back(new Pinky(position, this));
                    break;
            }
        }
    }
}

unsigned GameForm::getLevel() const {
    return level;
}
