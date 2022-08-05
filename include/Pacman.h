#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Values.h"
#include "Animator.h"
#include "GameForm.h"

class Pacman : public GameObject {
public:
    explicit Pacman(sf::Vector2f, GameForm *);

    ~Pacman();

    void pollEvents(sf::Event &);

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

private:
    //using game context and it's properties
    GameForm *context;
    //animator used for pacman sprite
    Animator *animator;
    Directions direction;
    sf::Vector2i nextMove;
    sf::Vector2i lastMove;
    sf::Sprite pacman;
    float speed = 4;
    bool isFirst = true;
    bool isDead = false;

    void updateRelativePosition();

    bool checkCollision(float x, float y);
};


#endif //PACMAN_PACMAN_H
