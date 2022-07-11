#include <iostream>
#include "MainForm.h"
#include "GameForm.h"

int main() {
    GameForm gameForm("../res/map.txt");
    gameForm.display();

    return 0;
}