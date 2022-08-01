#ifndef PACMAN_GAMEFORM_H
#define PACMAN_GAMEFORM_H

#include <algorithm>
#include <array>
#include <list>
#include "Wall.h"
#include "TextView.h"
#include "MainForm.h"
#include "Form.h"
#include "File.h"
#include "ButtonView.h"
#include "Fruit.h"

using namespace std;

class Pacman;

class Ghost;

class GameForm : public Form {
public:
    GameForm(Application &);

    ~GameForm();

    list<Snack *> &getSnacks();

    list<Ghost *> &getGhosts();

    void raiseScore(int);

    void lose();

    unsigned getLevel() const;

private:

    void pollEvents(sf::Event &, sf::RenderWindow *) override;

    void update(sf::RenderWindow *, const sf::Time &) override;

    void render(sf::RenderWindow *) override;

    void initGame();

    void initSprites();

    void resetBoard();

    void readRecord();

    void storeRecord();

    float fruitTimer = 0;
    unsigned level = 1;
    unsigned long int score;
    unsigned fruitsCount;
    unsigned eatenSnacks;
    unsigned snacksCount;
    unsigned long int highScore;
    bool isFruitVisible = false;
    sf::Vector2f pacmanPosition;
    list<Snack *> snacks;
    list<Ghost *> ghosts;
    vector<sf::Sprite> hearts;
    Pacman *pacman;
    TextView *txtScore;
    TextView *txtRecord;
    TextView *btnBack;
    sf::Sprite btnBackIc;
    sf::Texture *heartTexture;
};

#endif //PACMAN_GAMEFORM_H
