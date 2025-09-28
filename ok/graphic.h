#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <vector>
#include "Card.h"
#include "button.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

bool init(SDL_Window* &window, SDL_Renderer* &renderer);// truyền tham chiếu của con trỏ để thay đổi con trỏ

SDL_Texture* LoadTexture(const char* c, SDL_Renderer* renderer);// hàm load texture từ file

void render(SDL_Renderer* renderer, const vector<Card> &cards);// hàm render các thẻ lên mh

void close(SDL_Window* window, SDL_Renderer *renderer, SDL_Texture* backTexture);// dọn dẹp tài nguyên

void setupMenuButtons (Button& playButton, Button& introButton, Button& backButton, SDL_Texture* &menuBackground, SDL_Texture* &textHelp, SDL_Renderer* renderer);// setup cho các nút

void renderButton(SDL_Renderer* renderer, const Button& temp);// render các nút sau khi đã setup

#endif




















