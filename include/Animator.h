#ifndef PACMAN_ANIMATOR_H
#define PACMAN_ANIMATOR_H

#include "Animation.h"

using namespace std;

//main animation manager. we use this to store and play animations on sprites
class Animator {
public:
    explicit Animator(sf::Sprite &);

    ~Animator();

    void
    add(string id, sf::Time interval, string textureName, sf::Vector2i offset, unsigned framesCount, bool loop = true);

    void update(sf::Time);

    //changes current running animation to the given id
    void setAnimation(string id);

    bool isFinished() const;
private:
    bool finished = false;
    //store a reference to the sprite to set it's texture
    sf::Sprite &sprite;
    sf::Texture *texture;
    //current animation progress
    sf::Time progress;
    //used for adding multiple animations for a specific sprite
    vector<Animation *> animations;
    Animation *currentAnimation;
};

#endif //PACMAN_ANIMATOR_H
