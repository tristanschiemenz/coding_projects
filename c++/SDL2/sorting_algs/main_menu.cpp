// main_menu.cpp
#include "main_menu.h"
#include <iostream>

MainMenu::MainMenu(SDL_Renderer *renderer, TTF_Font *font) : renderer(renderer), font(font), titleTexture(nullptr) {
    //TODO
    //RENder and window vreater
}
MainMenu::~MainMenu() {
    // Destroy textures in the destructor
    if (titleTexture) {
        SDL_DestroyTexture(titleTexture);
    }
    for (auto &button : buttons) {
        if (button.textTexture) {
            SDL_DestroyTexture(button.textTexture);
        }
    }
};


void MainMenu::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (titleTexture == nullptr) {
        SDL_Surface *titleSurface = TTF_RenderText_Solid(font, "Sorting Algorithm Visualization", { 255, 255, 255 });
        titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
        titleRect = { 100, 100, titleSurface->w, titleSurface->h };
        SDL_FreeSurface(titleSurface);
    }
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titleRect);

    for (auto &button : buttons) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &button.rect);

        if (button.textTexture == nullptr) {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, button.text.c_str(), { 0, 0, 0 });
            button.textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
        }
        SDL_RenderCopy(renderer, button.textTexture, nullptr, &button.rect);
    }

    SDL_RenderPresent(renderer);
}


void MainMenu::handleEvent(const SDL_Event &event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "Mouse Down";
        int x, y;
        SDL_GetMouseState(&x, &y);

        for (const auto &button : buttons) {
            if (x >= button.rect.x && x <= button.rect.x + button.rect.w &&
                y >= button.rect.y && y <= button.rect.y + button.rect.h) {
                button.onClick();
            }
        }
    }
}

void MainMenu::addButton(int x, int y, const std::string &text, std::function<void()> onClick) {
    int w, h;
    TTF_SizeText(font, text.c_str(), &w, &h);
    buttons.push_back({ { x, y, w, h }, text, onClick });
}
