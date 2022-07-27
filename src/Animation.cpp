#include "Animation.h"

Animation::Animation(string id, sf::Time interval, string texturePath, bool loop) : id(id), texturePath(texturePath),
                                                                                    interval(interval), loop(loop) {}

//adding animation frames clip-content as IntRect objects
void Animation::addFrames(sf::Vector2i offset, unsigned framesCount) {
    this->framesCount = framesCount;
    for (int i = 0; i < framesCount; ++i) {
        frames.push_back(sf::IntRect(offset.x, offset.y, Dimensions::wallSize.x, Dimensions::wallSize.y));
        offset.x += Dimensions::wallSize.x;
    }
}

string Animation::getId() const {
    return id;
}

sf::Time Animation::getInterval() const {
    return interval;
}

const vector<sf::IntRect> &Animation::getFrames() const {
    return frames;
}

string Animation::getTexturePath() const {
    return texturePath;
}

bool Animation::isLoop() const {
    return loop;
}

unsigned int Animation::getFramesCount() const {
    return framesCount;
}