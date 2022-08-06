#ifndef PACMAN_TEXTVIEW_H
#define PACMAN_TEXTVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

// a simple textview with app font and textsize
class TextView : public sf::Text {
public:
    TextView(string, sf::Vector2f);

    void update(sf::RenderTarget *);

    virtual void render(sf::RenderTarget *);

    //set text origin to center for placing in center of window for example
    void setCenterHorizontal(bool);

private:
    sf::Font font;
};


#endif //PACMAN_TEXTVIEW_H
