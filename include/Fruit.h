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

    Fruit(sf::Vector2f, FruitType);

    ~Fruit() override;

    void eat() override;

    unsigned getPpt() const override;

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

private:
    FruitType fruitType;
    sf::Sprite fruit;
    sf::Texture *fruitTexture;
};


#endif //PACMAN_FRUIT_H
