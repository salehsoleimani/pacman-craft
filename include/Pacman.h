#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Values.h"
#include "Animator.h"
#include "GameForm.h"

class Pacman : public GameObject {
public:
    Pacman(sf::Vector2f, GameForm *);

    ~Pacman() override;

    void pollEvents(sf::Event &);

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;


    const sf::Vector2f &getPosition() const;

    const Directions &getDirection() const;


private:
    //using game context and it's properties
    GameForm *context;
    //animator used for pacman sprite
    Animator *animator;
    Directions direction;
    sf::Vector2i nextMove;
    sf::Vector2i lastMove;
    sf::Sprite pacman;
    float maxSpeed = 4;
    float speed;
    bool isDead = false;

    void updateRelativePosition();

    bool checkCollision(float x, float y);

    void configSpeed();
};


#endif //PACMAN_PACMAN_H
