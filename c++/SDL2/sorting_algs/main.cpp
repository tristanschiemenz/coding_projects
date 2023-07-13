#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

#include "main_menu.h"
#include "SortingAlgs.h"

const int n = 10;//10 bis 600 über 600 error wegen negativ scalings

int main(int argc, char *argv[]){

    std::vector<int> v(n);

    // Fill the vector with unique numbers
    for (int i = 0; i < n; ++i) {
        v[i] = i + 1;
    }

    // Seed the random number generator
    std::mt19937 rng(std::time(nullptr));
    std::shuffle(v.begin(), v.end(), rng);
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
    SortingAlgs sorting(drawing,n,scaling,renderer,window);

    //Buttons
    //Bubble Sort
    mainMenu.addButton(25,200, "Bubble      ", [&sorting, &v, &rng]() {
    sorting.bubble_sort(v, 1); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Insertion Sort
    mainMenu.addButton(175, 200, "Insert    ", [&sorting, &v, &rng]() {
    sorting.insertion_sort(v,1); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Selction Sort
    mainMenu.addButton(325, 200, "Selection ", [&sorting, &v, &rng]() {
    sorting.selection_sort(v,1); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Shell Sort
    mainMenu.addButton(25, 300, "Shell      ", [&sorting, &v, &rng]() {
    sorting.shell_sort(v,n,5); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Heap Sort
    mainMenu.addButton(175, 300, "Heap      ", [&sorting, &v, &rng]() {
    sorting.heap_sort(v,n,10); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Radix Sort
    mainMenu.addButton(325, 300, "Radix     ", [&sorting, &v, &rng]() {
    sorting.radix_sort(v,n,10); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Merge Sort
    mainMenu.addButton(25, 400, "Merge      ", [&sorting, &v, &rng]() {
    sorting.merge_sort(v,0,n,10); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Quick Sort
    mainMenu.addButton(175, 400, "Quick     ", [&sorting, &v, &rng]() {
    sorting.quick_sort(v,0,n,10); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    //Counting Sort
    mainMenu.addButton(325, 400, "Counting  ", [&sorting, &v, &rng]() {
    sorting.counting_sort(v,10); // Sort the vector in place
    sorting.make_green(v);
    std::shuffle(v.begin(), v.end(), rng);
    });
    


    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mainMenu.handleEvent(e);
                    break;
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_CLOSE) {;
                        running = false;
                    }
                    break;
                default:
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