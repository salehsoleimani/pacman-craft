#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Values.h"
#include "Animator.h"
#include "GameForm.h"

class Pacman : public GameObject {
public:
    enum class Directions {
        INIT, UP, DOWN, LEFT, RIGHT
    };

    explicit Pacman(sf::Vector2f, GameForm *context);

    ~Pacman();

    void pollEvents(sf::Event &event);

    void update(sf::Time dt) override;

    void render(sf::RenderTarget *target) override;

private:
    GameForm *context;

    Animator *animator;

    Directions direction;

    sf::Vector2f nextMove;

    sf::Vector2f lastMove;

    sf::Sprite pacman;

    float speed = 3;

    void updateRelativePosition();

    bool checkCollision(float x, float y);

    void eat(Food* food);
};


#endif //PACMAN_PACMAN_H
