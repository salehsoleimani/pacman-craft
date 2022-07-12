#include "Form.h"

Form::Form(string mapFileName) {
    this->mapFileName = mapFileName;
    window = nullptr;
    initWindow();
    initGrid();
}

Form::~Form() {
    if (window != nullptr) delete window;
}

void Form::initWindow() {
    Application &app = Application::getInstance();

    window = new sf::RenderWindow(app.videoMode, app.appName, app.style);
    window->setFramerateLimit(app.windowFrameRate);
}

bool Form::isRunning() const {
    return window->isOpen();
}

void Form::display() {
    while (isRunning()) {
        update();
        window->clear(Application::colorBlue);
        render();

        for (Wall *wall: walls) wall->render(window);

        window->display();
    }
}

void Form::initGrid() {
    File file(mapFileName);
    file.open(ios::in);
    string line;
    for (int i = 0; i < 26; ++i) {
        line = file.getline();
        for (int j = 0; j < Application::WALL_COL; ++j) {
            board[i][j] = line[j];
        }
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Application::WALL_COL; ++j) {
            if (board[i][j] == 'W')
                walls.push_back(new Wall(sf::Vector2f(j * Application::wallSize.x,
                                                      i * Application::wallSize.y)));
        }
        cout << endl;
    }
}