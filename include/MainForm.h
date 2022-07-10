#ifndef PACMAN_MAINFORM_H
#define PACMAN_MAINFORM_H

#include "Application.h"
#include "Form.h"

class MainForm : public Form {
private:
    void pollEvents() override;

    void update() override;

    void render() override;
};


#endif //PACMAN_MAINFORM_H
