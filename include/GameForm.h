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
#include "DialogView.h"
#include "Fruit.h"

using namespace std;

class Pacman;

class Ghost;

class GameForm : public Form {
public:
    GameForm(Application &);

    ~GameForm();

     list<Snack *> &getSnacks() ;

     list<Ghost *> &getGhosts() ;

    void raiseScore(int);

    void lose();

private:
    unsigned level = 1;

    unsigned fruitsCount = 0;

    bool isFruitVisible = false;

    float fruitTimer = 0;

    unsigned score = 0;

    unsigned eatenSnacks = 0;

    unsigned highScore = 0;

    sf::Vector2f pacmanPosition;

    list<Snack *> snacks;

    list<Ghost *> ghosts;

//    vector<Fruit *> fruits;

    vector<sf::Sprite> hearts;

    Pacman *pacman;

    TextView *txtScore;
    TextView *txtRecord;
    TextView *btnBack;

    sf::Sprite btnBackIc;

    sf::Texture *heartTexture;

    DialogView *dialog = nullptr;

    void pollEvents(sf::Event &, sf::RenderWindow *) override;

    void update(sf::RenderWindow *, const sf::Time &) override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    void initSprites();

};

#endif //PACMAN_GAMEFORM_H
