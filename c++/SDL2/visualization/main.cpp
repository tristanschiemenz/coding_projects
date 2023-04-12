#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

#include "main_menu.h"
#include "SortingAlgs.h"

const int n = 100;

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
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;

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
    bool drawing = true;
    SortingAlgs sorting(drawing,n,6,renderer,window);
    MainMenu mainMenu(renderer, font);

    mainMenu.addButton(500, 500, "Test", [&sorting, &v]() {
    sorting.bubble_sort(v, 1); // Sort the vector in place
    });


    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else {
                mainMenu.handleEvent(e);
            }
        }

        mainMenu.render();
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();



    // std::shuffle(v.begin(), v.end(), rng);
    //     //bubble
    // sorting.bubble_sort(v,2);

    // std::shuffle(v.begin(), v.end(), rng);
    // //Selction
    // sorting.selection_sort(v,2);

    // std::shuffle(v.begin(), v.end(), rng);
    // //insert
    // sorting.insertion_sort(v,2);

    // std::shuffle(v.begin(), v.end(), rng);
    // //shell
    // sorting.shell_sort(v,n,5);
    
    // std::shuffle(v.begin(), v.end(), rng);
    // //heap
    // sorting.heap_sort(v,n,10);

    // std::shuffle(v.begin(), v.end(), rng);
    // //radix
    // sorting.radix_sort(v,n,10);
    
    // std::shuffle(v.begin(), v.end(), rng);
    // //merge
    // sorting.merge_sort(v,0,n-1,10);

    // std::shuffle(v.begin(), v.end(), rng);
    // //quick
    // sorting.quick_sort(v,0,n-1,10);

    // std::shuffle(v.begin(), v.end(), rng);
    // //couning
    // sorting.counting_sort(v,10);

    // sorting.print_array(v);
    
    return 0;
}