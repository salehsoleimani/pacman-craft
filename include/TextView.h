#ifndef PACMAN_TEXTVIEW_H
#define PACMAN_TEXTVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class TextView : public sf::Text {
public:
    TextView(string, sf::Vector2f);

    TextView();

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *);

    void setCenterHorizontal(bool);

private:
    sf::Font font;
};


#endif //PACMAN_TEXTVIEW_H
