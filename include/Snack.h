#ifndef PACMAN_SNACK_H
#define PACMAN_SNACK_H

#include "GameObject.h"
#include "Values.h"
#include "Animator.h"

class Snack : public GameObject {
public:
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

protected:
    bool eaten;
};


#endif //PACMAN_SCACK_H
