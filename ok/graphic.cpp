#include "graphic.h"
#include <SDL_image.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

bool init(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        return false;
    }

    window = SDL_CreateWindow("Memory game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) return false;

    return true;
}

SDL_Texture* LoadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path);
    if (tempSurface == nullptr) {
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

void render(SDL_Renderer* renderer, const vector<Card> &cards) {
    for (const Card &card : cards) {
        SDL_Rect rect = card.getRect();
        if (card.getCheck() || card.getMatched()) {
            SDL_RenderCopy(renderer, card.getFront(), nullptr, &rect);
        } else {
            SDL_RenderCopy(renderer, card.getBack(), nullptr, &rect);
        }
    }
}

void close(SDL_Window* window, SDL_Renderer *renderer, SDL_Texture* backTexture) {
    SDL_DestroyTexture(backTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void setupMenuButtons (Button& playButton, Button& introButton, Button& backButton, SDL_Texture* &menuBackground, SDL_Texture* &textHelp, SDL_Renderer* renderer) {
    menuBackground = LoadTexture("assets/hehe.png", renderer);

    SDL_Rect playRect = {700, 200, 220, 60};
    playButton.setRect(playRect);
    playButton.setTexture(LoadTexture("assets/play.png", renderer));

    SDL_Rect introRect = {700, 300, 220, 60};
    introButton.setRect(introRect);
    introButton.setTexture(LoadTexture("assets/intro.png", renderer));

    SDL_Rect backRect = {20, 630, 220, 60};
    backButton.setRect(backRect);
    backButton.setTexture(LoadTexture("assets/quaylai.png", renderer));

    textHelp = LoadTexture("assets/help.png", renderer);
}

void renderButton(SDL_Renderer* renderer, const Button& temp) {
    SDL_Rect rect = temp.getRect();
    SDL_RenderCopy(renderer, temp.getTexture(), nullptr, &rect);
}
















