// main_menu.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <functional>

class MainMenu {
public:
    MainMenu(SDL_Renderer *renderer, TTF_Font *font);
    void render();
    void handleEvent(const SDL_Event &event);
    void addButton(int x, int y, const std::string &text, std::function<void()> onClick);

private:
    struct Button {
        SDL_Rect rect;
        std::string text;
        std::function<void()> onClick;
    };

    SDL_Renderer *renderer;
    TTF_Font *font;
    std::vector<Button> buttons;
    
};