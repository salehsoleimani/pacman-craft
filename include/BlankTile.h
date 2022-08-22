#ifndef PACMAN_BLANKTILE_H
#define PACMAN_BLANKTILE_H

#include "GameObject.h"

class BlankTile : public GameObject {
public:
    explicit BlankTile(sf::Vector2f);

    ~BlankTile() override;

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

    void setObjectType(const ObjectType &objectType);

    const sf::Rect<float> &getGlobalBounds() const;

private:
    sf::RectangleShape *wall;
    sf::Sprite tileSprite;
    sf::Texture *texture;
    ObjectType objectType = GameObject::ObjectType::INIT;
};


#endif //PACMAN_BLANKTILE_H