// main_menu.cpp
#include "main_menu.h"
#include <iostream>


MainMenu::MainMenu(SDL_Renderer *renderer, TTF_Font *font) : renderer(renderer), font(font), titleTexture(nullptr) {
    //TODO
    //RENder and window vreater
    selTextBox = -1;
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
    for (auto &TextBox : TextBoxs) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &TextBox.rect);

        if (TextBox.textTexture == nullptr) {
            SDL_Surface *textSurface = TTF_RenderText_Solid(font, TextBox.text.c_str(), { 0, 0, 0 });
            TextBox.textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_FreeSurface(textSurface);
        }
        SDL_RenderCopy(renderer, TextBox.textTexture, nullptr, &TextBox.rect);
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
                y >= button.rect.y && y <= button.rect.y + button.rect.h) 
            {
                button.onClick();
            }
        }
        for(int i = 0; i < TextBoxs.size(); i++){
            if (x >= TextBoxs[i].rect.x && x <= TextBoxs[i].rect.x + TextBoxs[i].rect.w &&
                y >= TextBoxs[i].rect.y && y <= TextBoxs[i].rect.y + TextBoxs[i].rect.h) 
            {
                selTextBox = i;
            }
        }
    }
    if(selTextBox != -1){
        if(event.type == SDL_TEXTINPUT){
            TextBoxs[selTextBox].text = TextBoxs[selTextBox].text + event.text.text; 
        }else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && TextBoxs[selTextBox].text.length() >0){
            TextBoxs[selTextBox].text.pop_back();
        }
    }
    
}

void MainMenu::addButton(int x, int y, const std::string &text, std::function<void()> onClick) {
    int w, h;
    TTF_SizeText(font, text.c_str(), &w, &h);
    buttons.push_back({ { x, y, w, h }, text, onClick });
}
//Return & of  created TextBox
