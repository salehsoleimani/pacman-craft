#ifndef PACMAN_ANIMATOR_H
#define PACMAN_ANIMATOR_H

#include "Application.h"
#include "Animation.h"

using namespace std;

class Animator {
public:
    explicit Animator(sf::Sprite &);

    ~Animator();

    void
    add(string id, sf::Time interval, string textureName, sf::Vector2i offset, unsigned framesCount, bool loop = true);

    void update(sf::Time);

    void setAnimation(string id);

private:
    sf::Sprite &sprite;

    sf::Texture *texture;

    sf::Time progress;

    vector<Animation *> animations;

    Animation *currentAnimation;
};

#endif //PACMAN_ANIMATOR_H
