#ifndef PACMAN_TEXTVIEW_H
#define PACMAN_TEXTVIEW_H

#include "View.h"

using namespace std;

class TextView {
public:
    TextView(string, sf::Vector2f);

    ~TextView();

    void setFontSize(int);

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *);

private:
    sf::Vector2f position;

    sf::Text *txtView;
    sf::Font font;
    sf::Color textColor = sf::Color::White;
};


#endif //PACMAN_TEXTVIEW_H
