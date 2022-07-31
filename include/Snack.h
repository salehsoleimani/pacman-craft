#ifndef PACMAN_SNACK_H
#define PACMAN_SNACK_H

#include "GameObject.h"
#include "Values.h"
#include "Animator.h"

class Snack : public GameObject {
public:
    enum class SnackType {
        PELLET,
        POWER,
        FRUIT
    };

    explicit Snack(sf::Vector2f position) : GameObject(position) {}

    virtual ~Snack() = default;

    virtual void eat() = 0;

    virtual unsigned getPpt() const = 0;

    bool isEaten() const {
        return eaten;
    }

    void setEaten(bool eaten) {
        this->eaten = eaten;
    }

    const SnackType &getSnackType() const {
        return snackType;
    }

protected:
    bool eaten;
    SnackType snackType;
};


#endif //PACMAN_SCACK_H
