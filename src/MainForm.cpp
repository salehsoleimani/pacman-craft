#include "MainForm.h"


MainForm::MainForm() {
    this->mapFileName = "../res/map_menu.txt";

    initTexts();
    initMenuView();
    initImages();
    initGrid();
}

MainForm::~MainForm() {
    delete menuView;
    delete logoIV;
    delete txtCredits;
    for (auto wall: walls) delete wall;
}

Form *MainForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    if (menuView->getSelectedItemIndex() == 1) {
                        context->pushForm(optionsForm);
//                        context->changeForm(this->context.)
                    }
                    break;
                case sf::Keyboard::Down:
                    menuView->selectItem(menuView->getSelectedItemIndex() + 1);
                    break;
                case sf::Keyboard::Up:
                    menuView->selectItem(menuView->getSelectedItemIndex() - 1);
                    break;
            }

    }
    return nullptr;
}

void MainForm::update() {
//    pollEvents();
}

void MainForm::render(sf::RenderWindow *window) {
    menuView->render(window);
    txtCredits->render(window);
    for (Wall *wall: walls) wall->render(window);
    window->draw(*logoIV);
}

void MainForm::initTexts() {
    txtCredits = new TextView("made with <3 by saleh", {155, 629});
    txtCredits->setCharacterSize(Font::smallFontSize);
    txtCredits->setFillColor(Colors::colorCyan);
}

void MainForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(Config::videoMode.width / 2.f, 355));
    menuView->pushItem("play", [&] {
//        window->close();
//        GameForm("../res/map.txt").display();
    });
    menuView->pushItem("options", [&] {
//        OptionsForm().display();
//        window->close();
    });
    menuView->pushItem("quit", [&] {});
}

void MainForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(Config::videoMode.width / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}

void MainForm::initGrid() {
    File file(mapFileName);
    file.open(ios::in);
    string line;
    for (int i = 0; i < 26; ++i) {
        line = file.getline();
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            board[i][j] = line[j];
        }
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            if (board[i][j] == 'W')
                walls.push_back(new Wall({j * Dimensions::wallSize.x,
                                          i * Dimensions::wallSize.y}));
        }
        cout << endl;
    }
}
