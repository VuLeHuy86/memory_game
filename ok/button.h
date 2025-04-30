#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>

struct Button{
    private:
        int width = 220;
        int height = 60;

        bool clicked = false;

        SDL_Rect re;
        SDL_Texture* texture = nullptr;

    public:
        int getWidth() const;
        int getHeight() const;

        bool getClicked() const;
        void setClicked(bool value);

        SDL_Rect getRect() const;
        void setRect(const SDL_Rect &temp);

        SDL_Texture* getTexture() const;
        void setTexture(SDL_Texture* temp);
};

#endif // BUTTON_H












