#ifndef PACMAN_GAMEFORM_H
#define PACMAN_GAMEFORM_H

#include "Application.h"
#include "Form.h"
#include "File.h"
#include <array>

using namespace std;

class GameForm : public Form {
public:
    GameForm(string);
private:
    array<array<char, 19>, 22> board;

    void pollEvents()
    override;

    void update()
    override;

    void render()
    override;
};

#endif //PACMAN_GAMEFORM_H