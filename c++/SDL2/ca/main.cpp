#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;
const int PIXELSIZE = 5;
const bool RULE[8] ={0,1,1,0,1,0,1,1};



void drawPixel(Uint32* pixels,int x, int y){
    for (int dy = 0; dy < PIXELSIZE; ++dy) {
        for (int dx = 0; dx < PIXELSIZE; ++dx) {
            int pixelIndex = (y + dy) * SCREEN_WIDTH + (x + dx);
            if (pixelIndex < SCREEN_WIDTH * SCREEN_HEIGHT) {
                pixels[pixelIndex] = 0x000000; // Set the pixel to white
            }
        }
    }
}
std::vector<bool> updateRow(const std::vector<bool>& states){
    int sizeofArray = states.size(); 
    std::vector<bool> updatedRow(sizeofArray);

    updatedRow[0] = states[0];
    updatedRow[sizeofArray - 1] = states[sizeofArray - 1];

    for(int i = 1; i < sizeofArray - 1; i++){
        int number = (states[i - 1] << 2) | (states[i] << 1) | states[i + 1];
        updatedRow[i] = RULE[7 - number];
    }

    return updatedRow;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("CA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Event e;
    bool quit = false;

    Uint32* pixels = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]();
    std::fill_n(pixels, SCREEN_WIDTH * SCREEN_HEIGHT, 0xFFFFFFFF);
    int x = 0;
    int y = 0;

    std::vector<bool> start;
    start.resize(SCREEN_WIDTH/PIXELSIZE);
    std::fill(start.begin(),start.end(),0);
    start[start.size()/2] = 1;

    while (!quit) {
        SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        x--;
                        break;
                    case SDLK_RIGHT:
                        x++;
                        break;
                    case SDLK_UP:
                        y--;
                        break;
                    case SDLK_DOWN:
                        y++;
                        break;
                }
            }
        }

        for(int i = 0; i < start.size(); i++){
            if(start[i]){
                std::cout << i << std::endl;
                drawPixel(pixels,i*PIXELSIZE,y*PIXELSIZE);
            }
        }
    	start = updateRow(start);
        y++;
         if (y * PIXELSIZE >= SCREEN_HEIGHT) {
            // Implement scroll logic: Shift everything up by PIXELSIZE
            memmove(pixels, pixels + SCREEN_WIDTH * PIXELSIZE, (SCREEN_HEIGHT - PIXELSIZE) * SCREEN_WIDTH * sizeof(Uint32));
            // Clear the last PIXELSIZE rows
            memset(pixels + (SCREEN_HEIGHT - PIXELSIZE) * SCREEN_WIDTH, 0, PIXELSIZE * SCREEN_WIDTH * sizeof(Uint32));
            std::fill_n(pixels + (SCREEN_HEIGHT - PIXELSIZE) * SCREEN_WIDTH, PIXELSIZE * SCREEN_WIDTH, 0xFFFFFFFF);
            y--;
        }
        SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}