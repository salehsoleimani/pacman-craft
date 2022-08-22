#ifndef PACMAN_CUSTOMMAPFORM_H
#define PACMAN_CUSTOMMAPFORM_H

#include "Form.h"
#include "Application.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"
#include "GameForm.h"
#include "OptionsForm.h"
#include "DialogView.h"
#include "BlankTile.h"

class CustomMapForm : public Form {
public:
    CustomMapForm(Application &);

    ~CustomMapForm();

private:
    sf::Keyboard::Key lastEnteredKey;

    vector<BlankTile *> blanks;

    TextView *txtGuide;

    ButtonView *btnPlay;

    void pollEvents(sf::Event &, sf::RenderWindow *) override;

    void update(sf::RenderWindow *, const sf::Time &) override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    void initButtons();
};

#endif //PACMAN_CUSTOMMAPFORM_H
