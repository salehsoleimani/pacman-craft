#ifndef PACMAN_MAINFORM_H
#define PACMAN_MAINFORM_H

#include "Application.h"
#include "Form.h"
#include "TextView.h"
#include "Wall.h"

class MainForm : public Form {
public:
    ~MainForm();

private:

    TextView *textView;

    void pollEvents() override;

    void update() override;

    void render() override;
};


#endif //PACMAN_MAINFORM_H
