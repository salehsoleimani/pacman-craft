#include "Pellet.h"

Pellet::Pellet(sf::Vector2f position, SnackType snackType) : Snack(position) {
    this->snackType = snackType;

    if (snackType == SnackType::PELLET)
        food.setRadius(3.0f);
    else
        food.setRadius(7.0f);

    food.setOrigin(food.getGlobalBounds().width / 2, food.getGlobalBounds().height / 2);
    food.setPosition({position.x + Dimensions::wallSize.x / 2, position.y + Dimensions::wallSize.y / 2});
    food.setFillColor(Colors::colorDot);

    eaten = false;
}

Pellet::~Pellet() = default;

void Pellet::render(sf::RenderTarget *target) {
    target->draw(food);
}

void Pellet::update(sf::Time dt) {
    //blinking power state
    if (snackType == SnackType::POWER && !isEaten()) {
        progress += dt;
        if (progress >= blinkAnimation) {
            progress = sf::Time::Zero;
            if (foodState == PelletState::BLINK) {
                food.setFillColor(Colors::colorDot);
                foodState = PelletState::NORMAL;
            } else {
                food.setFillColor(sf::Color::Transparent);
                foodState = PelletState::BLINK;
            }
            progress = sf::Time::Zero;
        }
    }
}

void Pellet::eat() {
    //amount of pause before eating pellet
    if (snackType == SnackType::PELLET)
        sf::sleep(sf::seconds(1 / Config::windowFrameRate));
    else
        sf::sleep(sf::seconds(3 / Config::windowFrameRate));

    eaten = true;
    food.setFillColor(sf::Color::Transparent);
}

//enhance this later
unsigned Pellet::getPpt() const {
    switch (snackType) {
        case SnackType::PELLET:
            return 20;
        case SnackType::POWER:
            return 50;
        default:
            return 0;
    }
}