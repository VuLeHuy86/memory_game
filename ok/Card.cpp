#include "Card.h"

using namespace std;

// struct Card
int Card::getWidth() const {
    return width;
}

int Card::getHeight() const {
    return height;
}

SDL_Texture* Card::getFront() const {
    return frontTexture;
}

SDL_Texture* Card::getBack() const {
    return backTexture;
}

void Card::setFront(SDL_Texture* temp) {
    frontTexture = temp;
}

void Card::setBack(SDL_Texture* temp) {
    backTexture = temp;
}

bool Card::getCheck() const {
    return isCheck;
}

bool Card::getMatched() const {
    return isMatched;
}

void Card::setCheck(bool value) {
    isCheck = value;
}

void Card::setMatched(bool value) {
    isMatched = value;
}

int Card::getId() const {
    return id;
}

void Card::setId(int x) {
    id = x;
}

SDL_Rect Card::getRect() const {
    return re;
}

void Card::setRect(const SDL_Rect &temp) {
    re = temp;
}














