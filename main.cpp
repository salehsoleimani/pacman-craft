#include <iostream>
#include "Application.h"
#include "GameForm.h"

int main() {
    Application app;
    app.pushForm(new GameForm());
    app.run();

    return 0;
}