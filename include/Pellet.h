#ifndef PACMAN_PELLET_H
#define PACMAN_PELLET_H

#include "Snack.h"

class Pellet : public Snack {
public:
    //for blinking power pellets
    enum class PelletState {
        NORMAL, BLINK
    };

    Pellet(sf::Vector2f, SnackType);

    ~Pellet() override;

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

    void eat() override;

    //we use this method from base class in other classes
    unsigned getPpt() const override;

private:
    //blink each 400 milliseconds
    sf::Time progress, blinkAnimation = sf::milliseconds(400.0f);

//    PelletType foodType = PelletType::INIT;

    PelletState foodState = PelletState::NORMAL;

    //we use a circle for each pellet
    sf::CircleShape food;

};


#endif //PACMAN_PELLET_H
