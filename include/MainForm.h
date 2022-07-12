#ifndef PACMAN_MAINFORM_H
#define PACMAN_MAINFORM_H

#include "Application.h"
#include "Form.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"

class MainForm : public Form {
public:
    MainForm();

    ~MainForm();

private:
    MenuView* menuView;
//
//    TextView *btnPlay;
//    TextView *btnOptions;
//    TextView *btnQuit;
    TextView *txtCredits;


    void pollEvents() override;

    void update() override;

    void render() override;

    void initTexts();

    void initWalls();

    void initMenuView();
};


#endif //PACMAN_MAINFORM_H
