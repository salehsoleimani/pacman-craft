#include <iostream>
#include "Application.h"
#include "GameForm.h"

int main() {
    //initialize application and first state
    Application app;
    app.pushForm(new GameForm(app));
    app.run();

    return 0;
}