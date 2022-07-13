#ifndef PACMAN_TEXTVIEW_H
#define PACMAN_TEXTVIEW_H

#include "Application.h"

class TextView : public sf::Text {
public:
    TextView(string, sf::Vector2f);

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *);

    void setCenterHorizontal(bool);

private:
    sf::Vector2f position;

    sf::Font font;
};


#endif //PACMAN_TEXTVIEW_H
