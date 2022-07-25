#ifndef PACMAN_ANIMATION_H
#define PACMAN_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Values.h"

using namespace std;

class Animation {
public:
    Animation(string id, sf::Time interval, string texturePath, bool loop);

    void addFrames(sf::Vector2i offset, unsigned framesCount);

    string getId() const;

    sf::Time getInterval() const;

    const vector<sf::IntRect> &getFrames() const;

    string getTexturePath() const;

    bool isLoop() const;

    unsigned int getFramesCount() const;

private:
    unsigned framesCount;

    string id;

    sf::Time interval;

    vector<sf::IntRect> frames;

    string texturePath;

    bool loop;
};


#endif //PACMAN_ANIMATION_H
