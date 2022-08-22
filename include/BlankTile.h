#ifndef PACMAN_BLANKTILE_H
#define PACMAN_BLANKTILE_H

#include "GameObject.h"

class BlankTile : public GameObject {
public:
    explicit BlankTile(sf::Vector2f);

    ~BlankTile() override;

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

    void setObjectType(ObjectType objectType);

    const sf::Rect<float> &getGlobalBounds() const;

    ObjectType getObjectType();

    ObjectType objectType = GameObject::ObjectType::BLANK;
private:
    sf::RectangleShape *wall;
    sf::Sprite tileSprite;
    sf::Texture *texture;
};


#endif //PACMAN_BLANKTILE_H