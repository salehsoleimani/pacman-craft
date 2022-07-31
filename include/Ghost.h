#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Values.h"
#include "Animator.h"
#include "GameForm.h"

class Ghost : public GameObject {
public:
    enum class GhostState {
        CHASE, SCATTER, FRIGHTENED, DEAD
    };

    explicit Ghost(sf::Vector2f, GameForm *);

    virtual ~Ghost();

    void pollEvents(sf::Event &);

    void render(sf::RenderTarget *) override;

    void update(sf::Time);

    void changeState(GhostState state);

    const GhostState &getGhostState() const;

    void die();

protected:
    //using game context and it's properties
    GameForm *context = nullptr;
    //animator used for ghost sprite
    Animator *animator = nullptr;
    Directions direction;
    sf::Sprite ghost;
    float speed = 3;
    GhostState ghostState;
    float frightenedTimer = 0;

    static int deadGhosts;

    void updateRelativePosition();
};


#endif //PACMAN_GHOST_H
