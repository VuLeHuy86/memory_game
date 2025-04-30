#ifndef CARD_H
#define CARD_H

#include <SDL.h>
#include <iostream>

using namespace std;

struct Card {
    private:
        int width = 150;
        int height = 150;

        SDL_Texture* frontTexture;
        SDL_Texture* backTexture;

        bool isCheck = false;
        bool isMatched = false;

        int id;

        SDL_Rect re;

    public:
        int getWidth() const;
        int getHeight() const;

        SDL_Texture* getFront() const;
        SDL_Texture* getBack() const;

        void setFront(SDL_Texture* temp);
        void setBack(SDL_Texture* temp);

        bool getCheck() const;
        void setCheck(bool value);

        bool getMatched() const;
        void setMatched(bool value);

        int getId() const;
        void setId(int x);

        SDL_Rect getRect() const;
        void setRect(const SDL_Rect &temp);
};


#endif // CARD_H














