#ifndef PACMAN_VIEW_H
#define PACMAN_VIEW_H

#include "Application.h"

class View {
public:
    View(sf::Vector2f position);

    ~View();

    void render(sf::RenderTarget *);

    virtual void update(sf::RenderTarget *) = 0;

    sf::Vector2f getPosition() const;

protected:
    //both sprite and shape inherits Drawable class
    sf::Drawable *view;

    sf::Vector2f position;

};


#endif //PACMAN_VIEW_H
