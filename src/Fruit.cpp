#include "Fruit.h"

Fruit::Fruit(sf::Vector2f position, FruitType fruitType) : Snack(position), fruitType(fruitType) {
    string texturePath = Path::fruit;

    switch (fruitType) {
        case FruitType::APPLE:
            texturePath += "apple.png";
            break;
        case FruitType::STRAWBERRY:
            texturePath += "strawberry.png";
            break;
        case FruitType::CHERRY:
            texturePath += "cherry.png";
            break;
        case FruitType::PEACH:
            texturePath += "peach.png";
            break;
        case FruitType::GRAPES:
            texturePath += "grapes.png";
            break;
        case FruitType::BANANA:
            texturePath += "banana.png";
            break;
    }

    fruitTexture = new sf::Texture;
    fruitTexture->loadFromFile(texturePath);
    fruitTexture->setSmooth(true);
    fruit.setTexture(*fruitTexture);
}


Fruit::~Fruit() {
    delete fruitTexture;
}

void Fruit::eat() {
    eaten = true;
    fruit.setColor(sf::Color::Transparent);
}

unsigned Fruit::getPpt() const {
    switch (fruitType) {
        case FruitType::APPLE:
            return 100;
        case FruitType::STRAWBERRY:
            return 300;
        case FruitType::CHERRY:
            return 500;
        case FruitType::PEACH:
            return 700;
        case FruitType::GRAPES:
            return 1000;
        case FruitType::BANANA:
            return 2000;
    }
}