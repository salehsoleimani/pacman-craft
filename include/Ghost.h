#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Values.h"
#include "Animator.h"
#include "GameForm.h"

class Ghost : public GameObject {
public:
    enum class GhostType {
        INIT, INKY, BLINKY, PINKY, CLYDE
    };
    enum class GhostState {
        INIT, CHASE, SCATTER, FRIGHTENED, DEAD
    };
    //switching to random routs/directions we need next tile and next direction as a struct
    struct Direction {
        Directions direction;
        sf::Vector2f tile;
    };

    Ghost(sf::Vector2f, GameForm *,bool useTheDoor = true);

    ~Ghost() override;

    void pollEvents(sf::Event &);

    void render(sf::RenderTarget *) override;

    void update(sf::Time) override;

    //switching states between ghosts from outside
    void changeState(GhostState state);

    const GhostState &getGhostState() const;

    //if pacman or other views intersects with ghost
    bool isColided(const sf::Rect<float> &rect) const;

    const sf::Vector2f &getInitialPosition() const;

    void setPosition(const sf::Vector2f &pos, bool isPacmanDead = false);

    void setDirection(Directions direction);

    const GhostType &getGhost() const;

protected:
    //using game context and it's properties
    GameForm *context = nullptr;
    //animator used for ghost sprite
    Animator *animator = nullptr;
    Directions direction = Directions::INIT;
    Directions lastDirection;
    GhostState ghostState = GhostState::INIT;
    //randomly choose a route between possibleRoutes
    vector<Direction> possibleRoutes;

    //setting target tile for chase and scatter mode
    sf::Vector2f targetScatter;
    sf::Vector2f targetChase;

    GhostType ghostType = GhostType::INIT;

    sf::Sprite ghost;
private:
    void configSpeed();

    void updateRelativePosition();

    bool isInTile();

    void checkPossibleRoutes();

    void reverseGhost();

    void configTimer();

    bool useTheDoor;

    sf::Time frightenedDuration;
    sf::Vector2f nextMove;
    sf::Vector2f nextTile;
    sf::Vector2f lastTile;
    sf::Vector2f targetTile;
    sf::Vector2f initialPosition;
    float maxSpeed = 3;
    float speed;
    float ghostSpeed;
    float frightenedSpeed;
    static int deadGhosts;
    //position ghosts exits the door
    sf::Vector2f doorPosition = {Dimensions::wallSize.x * 9, Dimensions::wallSize.y * 11};

    unsigned stateIndex;
    array<float, 7> stateTimer;
    float frightenedTimer = 0;
    float scatterTimer = 0;
    float chaseTimer = 0;
    GhostState lastState = GhostState::INIT;
};

#endif //PACMAN_GHOST_H
