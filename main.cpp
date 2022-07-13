#include <iostream>
#include "MainForm.h"
#include "GameForm.h"

int main() {
    MainForm mainForm;
    mainForm.display();

    GameForm gameForm("../res/map.txt");
    gameForm.display();

    return 0;
}