#include "Food.h"

#include <iostream>

Food::Food(sf::Vector2f position, FoodType foodType) : GameObject(position), foodType(foodType) {
    if (foodType == FoodType::NORMAL)
        food.setRadius(3.0f);
    else
        food.setRadius(7.0f);

    food.setOrigin(food.getGlobalBounds().width / 2, food.getGlobalBounds().height / 2);
    food.setPosition({position.x + Dimensions::wallSize.x / 2, position.y + Dimensions::wallSize.y / 2});
    food.setFillColor(sf::Color::White);
}

void Food::render(sf::RenderTarget *target) {
    target->draw(food);
}

Food::~Food() {

}

void Food::update(sf::Time dt) {
    if (foodType == FoodType::POWER) {
        progress += dt;
        if (progress >= blinkAnimation) {
            progress = sf::Time::Zero;
            if (food.getFillColor() == sf::Color::Transparent)
                food.setFillColor(sf::Color::White);
            else
                food.setFillColor(sf::Color::Transparent);
            progress = sf::Time::Zero;
        }
    }
}
