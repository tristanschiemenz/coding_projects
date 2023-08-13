#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>

#include "main_menu.h"
#include "SortingAlgs.h"


const int n = 600;//10 bis 600 über 600 error wegen negativ scalings

const int MaxStringSize = 11;

std::mt19937 rng(std::time(nullptr));
std::string fill_string(std::string input){
    while(input.size() < MaxStringSize){
        input = input + " ";
    }
    return input;
}
void initializeAndShuffleVector(std::vector<int>& vec, int size, std::mt19937& rng) {
    vec.resize(size);

    // Fill the vector with unique numbers
    for (int i = 0; i < size; ++i) {
        vec[i] = i + 1;
    }

    // Shuffle the vector
    std::shuffle(vec.begin(), vec.end(), rng);
}
void adjustVectorSize(std::vector<int>& v, MainMenu& mainMenu, const int& HOWMUCH, std::mt19937& rng) {
    int newSize = std::stoi(mainMenu.getTextFromTextBox(HOWMUCH));
    if (newSize >= 1 && newSize <= 600) {
        initializeAndShuffleVector(v, newSize, rng);
    } // else: Consider providing an error message for out-of-bounds values.
}



int main(int argc, char *argv[]){

    std::vector<int> v(n);

    // Fill the vector with unique numbers
    initializeAndShuffleVector(v, n, rng);
    // Shuffle the vector
    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;
    
    //Menu
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        std::cerr << "Error initializing SDL or SDL_ttf: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Font *font = TTF_OpenFont("./Font.ttf", 24);

    if (!window || !renderer || !font) {
        std::cerr << "Error creating window, renderer, or font: " << SDL_GetError() << std::endl;
        return 1;
    }


    MainMenu mainMenu(renderer, font);
    bool drawing = true;
    float scaling = 600 / n;

    int DELAY = mainMenu.addTextBox(0,1,fill_string("Delay"));
    int HOWMUCH = mainMenu.addTextBox(0,30,fill_string("Size:1-600"));

    //Buttons
    // Bubble Sort
    mainMenu.addButton(25,200, fill_string("Bubble"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.bubble_sort(v, localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Insertion Sort
    mainMenu.addButton(175, 200, fill_string("Insert"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.insertion_sort(v,localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Selection Sort
    mainMenu.addButton(325, 200, fill_string("Select"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.selection_sort(v,localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Shell Sort
    mainMenu.addButton(25, 300, fill_string("Shell"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.shell_sort(v, v.size(), localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Heap Sort
    mainMenu.addButton(175, 300, fill_string("Heap"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.heap_sort(v, v.size(), localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Radix Sort
    mainMenu.addButton(325, 300, fill_string("Radix"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.radix_sort(v, v.size(), localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Merge Sort
    mainMenu.addButton(25, 400, fill_string("Merge"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.merge_sort(v, 0, v.size(), localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Quick Sort
    mainMenu.addButton(175, 400, fill_string("Quick"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.quick_sort(v, 0, v.size(), localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });

    // Counting Sort
    mainMenu.addButton(325, 400, fill_string("Counting"), [&]() {
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
        float localScaling = 600.0f / v.size();
        SortingAlgs localSorting(drawing, v.size(), localScaling, renderer, window);
        int localdelay = std::stoi(mainMenu.getTextFromTextBox(DELAY));
        localSorting.counting_sort(v, localdelay);
        localSorting.make_green(v);
        adjustVectorSize(v, mainMenu, HOWMUCH, rng);
    });


    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_CLOSE) {;
                        running = false;
                    }
                    break;
                default:
                    mainMenu.handleEvent(e);
                    break;
        }
    }

    mainMenu.render();
    SDL_Delay(10);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    
    return 0;
}

