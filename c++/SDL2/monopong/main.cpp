#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <math.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RADIUS = 200;

void DrawQuarterCircle(SDL_Renderer* renderer, int x, int y, int radius, double startAngle) {
    double endAngle = startAngle + M_PI / 2;
    for (double theta = startAngle; theta < endAngle; theta += 0.01) {
        int xPos = x + radius * cos(theta);
        int yPos = y + radius * sin(theta);
        SDL_RenderDrawPoint(renderer, xPos, yPos);
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("MonoPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    double startAngle = 0.0;
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_LEFT:
                        startAngle += 0.1; // Erhöht den Winkel um 0.01 Radian
                        break;
                    case SDLK_RIGHT:
                        startAngle -= 0.1; // Verringert den Winkel um 0.01 Radian
                        break;
                }
            }
        }

        startAngle = fmod(startAngle, 2 * M_PI);
        if (startAngle < 0) {
            startAngle += 2 * M_PI;
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        DrawQuarterCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RADIUS, startAngle);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
