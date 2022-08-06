#ifndef PACMAN_OPTIONSFORM_H
#define PACMAN_OPTIONSFORM_H

#include "Form.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"
#include "MainForm.h"
#include "DialogView.h"

class OptionsForm : public Form {
public:
    OptionsForm(Application &);

    ~OptionsForm();

private:
    MenuView *menuView;
    sf::Texture logoSrc;
    sf::RectangleShape *logoIV;

    void pollEvents(sf::Event &, sf::RenderWindow *) override;

    void update(sf::RenderWindow *, const sf::Time &) override;

    void render(sf::RenderWindow *) override;

    void initMenuView();

    void initImages();
};


#endif //PACMAN_OPTIONSFORM_H
