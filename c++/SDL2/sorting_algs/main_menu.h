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
    ~MainMenu();
    void render();
    void handleEvent(const SDL_Event &event);
    void addButton(int x, int y, const std::string &text, std::function<void()> onClick);
    int addTextBox(int x, int y, const std::string initialText = "");
    std::string getTextFromTextBox(int index);
    void updateTextBoxTexture(int index);

private:
    struct Button {
        SDL_Rect rect;
        std::string text;
        std::function<void()> onClick;
        SDL_Texture *textTexture;
    };
    struct TextBox {
        SDL_Rect rect;
        std::string text;
        SDL_Texture *textTexture = nullptr;
        bool isSelected;
    };
    SDL_Rect titleRect;
    SDL_Texture *titleTexture;
    SDL_Renderer *renderer;
    TTF_Font *font;
    std::vector<Button> buttons;
    std::vector<TextBox> TextBoxs;
    int selTextBox;
};