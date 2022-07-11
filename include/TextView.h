#ifndef PACMAN_TEXTVIEW_H
#define PACMAN_TEXTVIEW_H

#include "View.h"

using namespace std;

class TextView : public View {
public:
    ~TextView();

    TextView(string,sf::Vector2f);

    void update(sf::RenderTarget *) override;

    void setFontSize(int);

private:
    sf::Text *txtView;
    sf::Font font;
    sf::Color textColor = sf::Color::White;
};


#endif //PACMAN_TEXTVIEW_H
