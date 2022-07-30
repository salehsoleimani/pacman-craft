#include "Pacman.h"
#include "GameForm.h"
#include <random>
#include "Inky.h"

GameForm::GameForm(Application &context) : Form("../res/map.txt", context) {
    initTexts();
    initSprites();
}

GameForm::~GameForm() {
    delete pacman;
    for (auto snack: snacks) delete snack;
    for (auto ghost: ghosts) delete ghost;
    delete heartTexture;
    delete dialog;
    delete txtRecord;
    delete btnBack;
    delete txtScore;
    if (score > highScore)
        try {
            File file("high_score.txt");
            file.open(ios::out);
            file << score;
        } catch (file_open_exception ex) {
            cerr << "error reading highscore";
        }
}

void GameForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {
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
                                                    getApplicationContext().pushForm(
                                                            new MainForm(getApplicationContext()));
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
    //if pacman ate all snacks rearrange board - reach to next level
    if (eatenSnacks == snacksCount) {
        level++;
        for (auto snack: snacks) delete snack;
        for (auto ghost: ghosts) delete ghost;
        snacks.clear();
        ghosts.clear();
        initSprites();
        eatenSnacks = 0;
        fruitsCount = 0;
    }

    if (isFruitVisible) fruitTimer += dt.asSeconds();

    if (fruitTimer >= 10 && isFruitVisible) {
        delete snacks.back();
        snacks.pop_back();
        isFruitVisible = false;
        fruitTimer = 0;
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

    ifstream f(string("high_score.txt").c_str());
    if (!f.good()) highScore = 0;

    txtRecord->setString("high score\n" + to_string(highScore));

    if (!dialog) {
        pacman->update(dt);

        for (auto snack: snacks)
            if (snack) snack->update(dt);

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
    snacksCount = 0;

    heartTexture = new sf::Texture;
    heartTexture->loadFromFile("../res/sprites/heart.png");
    heartTexture->setSmooth(true);

    sf::Sprite heartSprite(*heartTexture);

    auto *icBackTexture = new sf::Texture;
    icBackTexture->loadFromFile("../res/icons/ic_back.png");
    btnBackIc.setPosition({30, (btnBack->getGlobalBounds().top + btnBack->getGlobalBounds().height) / 2});
    btnBackIc.setTexture(*icBackTexture);

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            Pellet *snack = nullptr;
            sf::Vector2f position = sf::Vector2f{j * Dimensions::wallSize.x, i * Dimensions::wallSize.x};
            switch (board[i][j]) {
                case GameObject::ObjectType::HEART:
                    if (level == 1) {
                        heartSprite.setPosition(position);
                        hearts.push_back(heartSprite);
                    }
                    break;
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
            }
        }
    }
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
    unsigned lives = hearts.size();
    cout << lives << endl;
    if (lives > 1) {
        delete pacman;
        pacman = new Pacman(pacmanPosition, this);
        score -= 20;
        hearts.pop_back();
    } else {
        getApplicationContext().pushForm(new GameForm(getApplicationContext()));
        getApplicationContext().resetGame();
    }
}
