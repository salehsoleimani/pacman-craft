#ifndef PACMAN_FOOD_H
#define PACMAN_FOOD_H

#include "GameObject.h"
#include "Values.h"
#include "Animator.h"

class Food : public GameObject {
public:
    enum class FoodType {
        NORMAL, POWER
    };

    enum class FoodState {
        NORMAL, BLINK, EATEN
    };

    explicit Food(sf::Vector2f, FoodType);

    ~Food();

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

    void ate();

    unsigned getPpt() const;

    bool isEaten() const;
private:
    sf::Time progress, blinkAnimation = sf::milliseconds(400.0f);

    FoodType foodType;

    FoodState foodState = FoodState::NORMAL;

    sf::CircleShape food;

};


#endif //PACMAN_FOOD_H
