#include "game.h"
#include "logic1.h"
#include "graphic.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* background = nullptr;
int count = 0;

Button playButton, introButton, backButton;
SDL_Texture* menuBackground = nullptr;
SDL_Texture* textHelp = nullptr;

GameState state = MENU;

void gamePlay(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* background) {
// Tạo các thẻ (cards)
    vector<Card> cards = createShuffledCards(renderer);

    // Tính toán vị trí các thẻ
    calculateCardPositions(cards);

    // Tải texture của background
    background = LoadTexture("assets/background.png", renderer);
    if (background == nullptr) {
        close(window, renderer, background);
        return ;
    }

    bool quit = false;
    SDL_Event e;

    // Vòng lặp game
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);  // Lấy tọa độ chuột
                handleMouseClick(cards, mouseX, mouseY, count); // Xử lý sự kiện click chuột
            }
        }

        handleCardFlipBack(cards);

        // Render các đối tượng lên màn hình
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, nullptr, nullptr); // Render background
        render(renderer, cards);  // Render các thẻ
        SDL_RenderPresent(renderer);  // Cập nhật màn hình

        SDL_Delay(16);  // Giới hạn FPS ~60

        if (checkWin(cards)) {
            SDL_Delay(2000); // Hiển thị thông báo chiến thắng trong 2 giây
            quit = true;  // Thoát game sau khi chiến thắng
        }
    }
    // Dọn dẹp tài nguyên
    close(window, renderer, background);
}

void mainloop(SDL_Renderer* renderer, SDL_Window* window, SDL_Texture* background, GameState state) {
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (state == MENU && e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Rect pRect = playButton.getRect();
                SDL_Rect iRect = introButton.getRect();

                if (mouseX >= pRect.x && mouseX <= pRect.x + pRect.w &&
                    mouseY >= pRect.y && mouseY <= pRect.y + pRect.h) {
                    state = PLAYING;
                } else if (mouseX >= iRect.x && mouseX <= iRect.x + iRect.w &&
                    mouseY >= iRect.y && mouseY <= iRect.y + iRect.h) {
                    state = HELP;
                }
            }

            if (state == HELP && e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                SDL_Rect bRect = backButton.getRect();

                if (mouseX >= bRect.x && mouseX <= bRect.x + bRect.w &&
                mouseY >= bRect.y && mouseY <= bRect.y + bRect.h) {
                    state = MENU;
                }
            }
        }

        SDL_RenderClear(renderer);

        if (state == MENU) {
            SDL_RenderCopy(renderer, menuBackground, nullptr, nullptr);
            renderButton(renderer, playButton);
            renderButton(renderer, introButton);
        } else if (state == HELP) {
            SDL_RenderCopy(renderer, textHelp, nullptr, nullptr);
            renderButton(renderer, backButton);

        } else if (state == PLAYING) {
            gamePlay(renderer, window, background);
            quit = true;
             // Sau khi chơi xong quay lại menu
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
