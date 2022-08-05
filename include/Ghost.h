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

    struct Direction {
        Directions direction;
        sf::Vector2f tile;
    };

    explicit Ghost(sf::Vector2f, GameForm *);

    virtual ~Ghost();

    void pollEvents(sf::Event &);

    void render(sf::RenderTarget *) override;

    void update(sf::Time);

    void changeState(GhostState state);

    const GhostState &getGhostState() const;

    void die();

    bool isColided(const sf::Rect<float> &rect) const;

protected:
    //using game context and it's properties
    GameForm *context = nullptr;
    //animator used for ghost sprite
    Animator *animator = nullptr;
    Directions direction;
    Directions lastDirection;
    sf::Sprite ghost;
    float speed = 3;
    GhostState ghostState;
    float frightenedTimer = 0;
    sf::Time frightenedDuration;
    vector<Direction> possibleRoutes;
    sf::Vector2f lastMove;
    sf::Vector2f nextMove;
//    sf::Vector2f lastMove;
    sf::Vector2f nextTile;
    sf::Vector2f lastTile;
    static int deadGhosts;

    void updateRelativePosition();

    bool isInTile();

    void checkPossibleRoutes();

};


#endif //PACMAN_GHOST_H
