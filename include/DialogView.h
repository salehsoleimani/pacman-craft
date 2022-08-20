#ifndef PACMAN_DIALOGVIEW_H
#define PACMAN_DIALOGVIEW_H

#include "ButtonView.h"
#include "TextView.h"
#include <functional>
#include <sstream>

//inherits a rectangleshape as it's transparent background
class DialogView : public sf::RectangleShape {
public:
    DialogView();

    ~DialogView() override;

    void render(sf::RenderTarget *target);

    void pollEvents(const sf::Event &, const sf::Window *);

    //2 overloads for creating dialog
    //creating single button(cta) dialog
    DialogView &create(string, string, string, const function<void()> &);

    //a dialog with secondary button
    DialogView &create(string, string, string, string, const function<void()> &,
                       const function<void()> &);

    void show();

    void hide();

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