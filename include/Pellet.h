#ifndef PACMAN_PELLET_H
#define PACMAN_PELLET_H

#include "Snack.h"

class Pellet : public Snack {
public:
    enum class PelletType {
        NORMAL, POWER
    };

    enum class PelletState {
        NORMAL, BLINK
    };

    explicit Pellet(sf::Vector2f, PelletType);

    ~Pellet() override;

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

    void eat() override;

    unsigned getPpt() const override;

private:
    sf::Time progress, blinkAnimation = sf::milliseconds(400.0f);

    PelletType foodType;

    PelletState foodState = PelletState::NORMAL;

    sf::CircleShape food;

};


#endif //PACMAN_PELLET_H
