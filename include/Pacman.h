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

    sf::Vector2f nextMove;

    sf::Vector2f lastMove;

    sf::Sprite pacman;

    float speed = 3;

    void updateRelativePosition();

    bool checkCollision(float x, float y);

    void eat(Pellet* food);
};


#endif //PACMAN_PACMAN_H
