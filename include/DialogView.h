#ifndef PACMAN_DIALOGVIEW_H
#define PACMAN_DIALOGVIEW_H

#include "ButtonView.h"
#include "TextView.h"
#include <functional>
#include <sstream>

class DialogView : public sf::RectangleShape {
public:
    DialogView(const string& dialogTitle,const string& dialogTxt,const string& cta,const sf::Vector2u &size,const function<void()>& onClick);

//    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *target);

    void initDialog();

    void pollEvents(const sf::Event &, const sf::Window *);

private:
    string justifyText(const string &text);

    sf::Vector2u size;
    ButtonView *ctaBtn;
    TextView *titleTV;
    TextView *txtTV;
    sf::RectangleShape dialogBox;
    sf::RectangleShape line;

};

#endif