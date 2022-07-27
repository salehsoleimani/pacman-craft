#ifndef PACMAN_DIALOGVIEW_H
#define PACMAN_DIALOGVIEW_H

#include "ButtonView.h"
#include "TextView.h"
#include <functional>
#include <sstream>

class DialogView : public sf::RectangleShape {
public:
    DialogView(string, string, string, const sf::Vector2u &, const function<void()> &);

    DialogView(string, string, string, string, const sf::Vector2u &, const function<void()> &);

    void render(sf::RenderTarget *target);

    void pollEvents(const sf::Event &, const sf::Window *);

private:
    void initDialog();

    void initTexts(string, string);

    string justifyText(const string &text);

    sf::Vector2u size;
    ButtonView *ctaBtn;
    TextView *titleTV;
    TextView *txtTV;
    sf::RectangleShape dialogBox;
    sf::RectangleShape line;
};

#endif