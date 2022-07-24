#include "Animator.h"

Animator::Animator(sf::Sprite &sprite) : sprite(sprite) {
    currentAnimation = nullptr;
    texture = new sf::Texture;
}

void
Animator::add(string id, sf::Time interval, string textureName, sf::Vector2i offset, unsigned framesCount, bool loop) {
    Animation *animation = new Animation(id, interval, textureName, loop);
    animations.push_back(animation);

    animation->addFrames(offset, framesCount);

    if (!currentAnimation) {
        texture->loadFromFile(animation->getTexturePath());
        texture->setSmooth(true);
        sprite.setTexture(*texture);

        currentAnimation = animation;
        progress = sf::Time::Zero;
    }
}

void Animator::update(sf::Time dt) {
    progress += dt;

    if (currentAnimation) {
        int frame = (int) ((progress.asSeconds() / currentAnimation->getInterval().asSeconds()) *
                           currentAnimation->getFramesCount());

        if (currentAnimation->isLoop())
            frame %= currentAnimation->getFramesCount();
        else if (frame >= currentAnimation->getFramesCount())
            frame = currentAnimation->getFramesCount() - 1;

        sprite.setTextureRect(currentAnimation->getFrames()[frame]);
    }
}

void Animator::setAnimation(string id) {
    for (auto it = animations.begin(); it != animations.end(); ++it)
        if ((*it)->getId() == id) {
            if (*it) {
                texture->loadFromFile((*it)->getTexturePath());
                texture->setSmooth(true);
                sprite.setTexture(*texture);
            }
            currentAnimation = *it;
            progress = sf::Time::Zero;
        }
}

Animator::~Animator() {
    delete texture;
    for (auto animation: animations)
        delete animation;
}
