#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "Application.h"
#include "Animator.h"

class Pacman : public GameObject {
public:
    enum class Directions {
        INIT, UP, DOWN, LEFT, RIGHT
    };

    explicit Pacman(sf::Vector2f, Form *context);

    ~Pacman();

    void pollEvents(sf::Event &event);

    void update(sf::Time dt) override;

    void render(sf::RenderTarget *target) override;

private:
    Form *context;

    Animator *animator;

    sf::Vector2f relativePosition;

    Directions direction;

    sf::Vector2f nextMove;

    sf::Vector2f lastMove;

    sf::Sprite pacman;

    float speed = 3;

    void updateRelativePosition();

    bool checkCollision(float x, float y);

    void eat();
};


#endif //PACMAN_PACMAN_H
