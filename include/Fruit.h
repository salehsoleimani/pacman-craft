#ifndef PACMAN_FRUIT_H
#define PACMAN_FRUIT_H

#include "Snack.h"

class Fruit : public Snack {
public:
    //we need this to access eaten fruit type later
    enum class FruitType {
        APPLE,
        STRAWBERRY,
        CHERRY,
        PEACH,
        GRAPES,
        BANANA,
        INIT
    };

    Fruit(sf::Vector2f, FruitType);

    ~Fruit() override;

    void eat() override;

    //returns each fruit points
    unsigned getPpt() const override;

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

private:
    FruitType fruitType = FruitType::INIT;
    sf::Sprite fruit;
    sf::Texture *fruitTexture;
};


#endif //PACMAN_FRUIT_H
