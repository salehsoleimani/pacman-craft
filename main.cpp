#include <iostream>
#include "Application.h"
#include "MainForm.h"

int main() {
//    MainForm mainForm;
//    mainForm.display();

//    GameForm gameForm("../res/map.txt");
//    gameForm.display();

    Application app;
    app.pushForm(new MainForm(&app));
    app.run();

    return 0;
}