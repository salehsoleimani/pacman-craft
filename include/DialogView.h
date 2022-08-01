#ifndef PACMAN_DIALOGVIEW_H
#define PACMAN_DIALOGVIEW_H

#include "ButtonView.h"
#include "TextView.h"
#include <functional>
#include <sstream>

class DialogView : public sf::RectangleShape {
public:
    DialogView();

//    DialogView();

    ~DialogView();

    void render(sf::RenderTarget *target);

    void pollEvents(const sf::Event &, const sf::Window *);

    DialogView &create(string, string, string, const function<void()> &);

    DialogView &create(string, string, string, string, const function<void()> &,
                       const function<void()> &);

    bool show();

    bool hide();

    bool isVisible() const;

private:
    void initDialog();

    void initTexts(string, string);

    bool visible = false;
    sf::Vector2u size;
    ButtonView *ctaBtn = nullptr;
    ButtonView *secondaryBtn = nullptr;
    TextView *titleTV = nullptr;
    TextView *txtTV = nullptr;
    sf::RectangleShape dialogBox;
    sf::RectangleShape line;
};

#endif