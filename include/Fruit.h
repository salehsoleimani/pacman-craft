#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H

#include "Snack.h"

class Fruit : public Snack {
public:
    enum class FruitType {
        APPLE,
        STRAWBERRY,
        CHERRY,
        PEACH,
        GRAPES,
        BANANA
    };

    explicit Fruit(sf::Vector2f, FruitType);

    ~Fruit();

    void eat() override;

    unsigned getPpt() const override;

private:
    FruitType fruitType;
    sf::Sprite fruit;
    sf::Texture *fruitTexture;
};


#endif //PACMAN_FRUIT_H
