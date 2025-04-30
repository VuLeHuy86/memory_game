#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "logic1.h"
#include "button.h"
#include <SDL.h>

// các biến toàn cục
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* background;
extern int count;

extern Button playButton, introButton, backButton;
extern SDL_Texture* menuBackground;
extern SDL_Texture* textHelp;

enum GameState {
    MENU,
    PLAYING,
    HELP,
    QUIT
};

extern GameState state;

void gamePlay(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* background);

void mainloop(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* background, GameState state);

#endif // GAME_H
