#include "button.h"

// struct Button
int Button::getWidth() const {
    return width;
}

int Button::getHeight() const {
    return height;
}

bool Button::getClicked() const {
    return clicked;
}

void Button::setClicked(bool value) {
    clicked = value;
}

SDL_Rect Button::getRect() const {
    return re;
}

void Button::setRect(const SDL_Rect &temp) {
    re = temp;
}

SDL_Texture* Button::getTexture() const {
    return texture;
}

void Button::setTexture(SDL_Texture* temp) {
    texture = temp;
}
















