#ifndef PACMAN_MAINFORM_H
#define PACMAN_MAINFORM_H

#include "Application.h"
#include "Form.h"
#include "TextView.h"
#include "Wall.h"

class MainForm : public Form {
public:
    MainForm();

    ~MainForm();

private:
    TextView *btnPlay;
    TextView *btnOptions;
    TextView *btnQuit;
    TextView *txtCredits;


    void pollEvents() override;

    void update() override;

    void render() override;

    void initTexts();

    void initWalls();

};


#endif //PACMAN_MAINFORM_H
