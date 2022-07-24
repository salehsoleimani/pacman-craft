#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "Application.h"
#include "Animator.h"

class Pacman {
public:
    enum class Directions {
        INIT, UP, DOWN, LEFT, RIGHT
    };

    explicit Pacman(float row, float col, const array<array<char, 19>, 26> &board);

    ~Pacman();

    void pollEvents(sf::Event &event);

    void update(const sf::Time &dt);

    void render(sf::RenderTarget *target);

private:
    Animator *animator;

// we need this to check collisions
    array<array<char, 19>, 26> board;

    sf::Vector2f relativePosition;

    void updateRelativePosition();

    Directions direction;

    sf::Vector2f nextMove;
    sf::Vector2f lastMove;

    sf::Sprite pacman;

    float speed = 3;

    bool checkCollision(float x, float y);
};


#endif //PACMAN_PACMAN_H
