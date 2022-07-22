#include "Pacman.h"

Pacman::Pacman(float row, float col, const array<array<char, 19>, 26> &board) : board(board) {
    auto *texture = new sf::Texture;
    texture->loadFromFile("../res/sprites/pacman.png");
    texture->setSmooth(true);
    pacman.setPosition({row * Dimensions::wallSize.x, col * Dimensions::wallSize.y});
    pacman.setSize(Dimensions::wallSize);
    pacman.setTexture(texture);
    relativePosition = {row, col};
}

Pacman::~Pacman() {

}

void Pacman::pollEvents(sf::Event &event) {

    if (event.type == sf::Event::KeyPressed)
        switch (event.key.code) {
            case sf::Keyboard::Down:
                direction = Directions::DOWN;
                break;
            case sf::Keyboard::Up:
                direction = Directions::UP;
                break;
            case sf::Keyboard::Left:
                direction = Directions::LEFT;
                break;
            case sf::Keyboard::Right:
                direction = Directions::RIGHT;
                break;
            default:
                direction = Directions::INIT;
                break;
        }
}

void Pacman::update() {

    sf::Vector2f currentPosition = pacman.getPosition();

    //a vector to hold next move coordinates
    nextMove = {0, 0};

    switch (direction) {
        case Directions::DOWN:
            nextMove.y += speed;
            break;
        case Directions::UP:
            nextMove.y -= speed;
            break;
        case Directions::LEFT:
            nextMove.x -= speed;
            break;
        case Directions::RIGHT:
            nextMove.x += speed;
            break;
        case Directions::INIT:
            nextMove = {0, 0};
            break;
    }

    pacman.move(nextMove);

    updateRelativePosition();

    //walking through gates
    if (Dimensions::wallSize.x * Dimensions::WALL_COL <= pacman.getPosition().x)
        pacman.setPosition(-Dimensions::wallSize.x, pacman.getPosition().y);
    else if (pacman.getPosition().x <= -Dimensions::wallSize.x)
        pacman.setPosition(Config::videoMode.width, pacman.getPosition().y);
    else if (pacman.getPosition().x < 1/2* Dimensions::wallSize.x  ||
             (pacman.getPosition().x >= Dimensions::wallSize.x * (Dimensions::WALL_COL - 1)))
        return;
    else {
        if (checkCollision(relativePosition.x, relativePosition.y)) {
            pacman.setPosition(currentPosition);

            currentPosition = pacman.getPosition();

            updateRelativePosition();

            if (lastMove != nextMove && !checkCollision(relativePosition.x, relativePosition.y))
                pacman.move(lastMove);

            updateRelativePosition();

            if (checkCollision(relativePosition.x, relativePosition.y))
                pacman.setPosition(currentPosition);

        } else
            lastMove = nextMove;
    }

}

bool Pacman::checkCollision(float x, float y) {
    if (board[ceil(y)][ceil(x)] == 'W' || board[ceil(y)][floor(x)] == 'W' || board[floor(y)][ceil(x)] == 'W' ||
        board[floor(y)][floor(x)] == 'W')
        return true;
    return false;
}

void Pacman::updateRelativePosition() {
    relativePosition = {pacman.getPosition().x / Dimensions::wallSize.x,
                        pacman.getPosition().y / Dimensions::wallSize.x};
}

void Pacman::render(sf::RenderTarget *target) {
    target->draw(pacman);
}
