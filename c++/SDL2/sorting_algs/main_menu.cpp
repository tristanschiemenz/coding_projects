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
    if (TextBox.isSelected) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for selected
        }else {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White for not selected
        }
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
    int x, y;
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "Mouse Down";
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
        for(int i = 0; i < TextBoxs.size(); i++) {
            if (x >= TextBoxs[i].rect.x && x <= TextBoxs[i].rect.x + TextBoxs[i].rect.w &&
                y >= TextBoxs[i].rect.y && y <= TextBoxs[i].rect.y + TextBoxs[i].rect.h) {
            selTextBox = i;
            TextBoxs[i].isSelected = true;  // Mark the current textbox as selected
        } else {
            TextBoxs[i].isSelected = false;  // Mark other textboxes as not selected
        }
        std::cout << TextBoxs[i].text << std::endl;
    }
    }
    if (selTextBox != -1) {
        // For text input
        if (event.type == SDL_TEXTINPUT) {
            TextBoxs[selTextBox].text += event.text.text; 

            // Optional: Update the texture of the TextBox here, if needed
            updateTextBoxTexture(selTextBox);
        }
        // For backspace
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE) {
            if (!TextBoxs[selTextBox].text.empty()) {
                TextBoxs[selTextBox].text.pop_back();

                // Optional: Update the texture of the TextBox here, if needed
                updateTextBoxTexture(selTextBox);
            }
        }
    }
    
}

void MainMenu::addButton(int x, int y, const std::string &text, std::function<void()> onClick) {
    int w, h;
    TTF_SizeText(font, text.c_str(), &w, &h);
    buttons.push_back({ { x, y, w, h }, text, onClick });
}

// Function to add a TextBox and return its index
int MainMenu::addTextBox(int x, int y, const std::string initialText) {
    int w, h;
    TTF_SizeText(font, initialText.c_str(), &w, &h);
    TextBox textBox = { { x, y, w, h }, initialText, nullptr, false };  // False because it's not selected initially
    TextBoxs.push_back(textBox);
    return TextBoxs.size() - 1; // Return the index of the added textbox
}

// Function to get text from a TextBox by index
std::string MainMenu::getTextFromTextBox(int index) {
    if (index >= 0 && index < TextBoxs.size()) {
        return TextBoxs[index].text;
    }
    return ""; // Return an empty string if index is out of range
}

void MainMenu::updateTextBoxTexture(int index) {
    if (index < 0 || index >= TextBoxs.size()) return; // Invalid index check

    // Destroy the old texture
    if (TextBoxs[index].textTexture) {
        SDL_DestroyTexture(TextBoxs[index].textTexture);
        TextBoxs[index].textTexture = nullptr;
    }

    // Create a new texture from the updated text
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, TextBoxs[index].text.c_str(), { 0, 0, 0 });
    TextBoxs[index].textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Free the surface now that we're done with it
    SDL_FreeSurface(textSurface);
}
