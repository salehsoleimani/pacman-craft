#ifndef PACMAN_OPTIONSFORM_H
#define PACMAN_OPTIONSFORM_H

#include "Application.h"
#include "Form.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"

class OptionsForm : public Form {
public:
    OptionsForm();

    ~OptionsForm();

private:
    MenuView *menuView;

    sf::Texture logoSrc;
    sf::RectangleShape *logoIV;

    void pollEvents() override;

    void update() override;

    void render() override;

    void initTexts();

    void initMenuView();

    void initImages();
};


#endif //PACMAN_OPTIONSFORM_H
