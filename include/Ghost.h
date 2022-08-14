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
    //switching to random routs/directions we need next tile and next direction as a struct
    struct Direction {
        Directions direction;
        sf::Vector2f tile;
    };

    Ghost(sf::Vector2f, GameForm *);

    ~Ghost() override;

    void pollEvents(sf::Event &);

    void render(sf::RenderTarget *) override;

    void update(sf::Time);

    //switching states between ghosts from outside
    void changeState(GhostState state);

    const GhostState &getGhostState() const;

    //if pacman or other views intersects with ghost
    bool isColided(const sf::Rect<float> &rect) const;

    const sf::Vector2f &getInitialPosition() const;

    void setPosition(const sf::Vector2f &pos);

protected:
    //using game context and it's properties
    GameForm *context = nullptr;
    //animator used for ghost sprite
    Animator *animator = nullptr;
    Directions direction = Directions::INIT;
    GhostState ghostState = GhostState::CHASE;
    //we randomly choose a route between possibleRoutes
    vector<Direction> possibleRoutes;
    sf::Time frightenedDuration;
    sf::Vector2f nextMove;
    sf::Vector2f nextTile;
    sf::Vector2f lastTile;
    sf::Vector2f initialPosition;
    sf::Sprite ghost;
    bool isDead = false;
    float speed = 3;
    float frightenedTimer = 0;
    static int deadGhosts;

    void updateRelativePosition();

    bool isInTile();

    void checkPossibleRoutes();

};


#endif //PACMAN_GHOST_H
