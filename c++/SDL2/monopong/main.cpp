#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RADIUS = 200;
const int THICKNESS = 4;


void DrawQuarterCircle(SDL_Renderer* renderer, int x, int y, int radius, double startAngle, int thick, std::vector<std::pair<int,int>> * positions) {
    double endAngle = startAngle + 2 * M_PI / 7;
    for(int i = 0; i<thick; i++){
        for (double theta = startAngle; theta < endAngle; theta += 0.01) {
            int xPos = x + radius * cos(theta);
            int yPos = y + radius * sin(theta);
            positions->push_back(std::pair<int,int>(xPos, yPos));
            SDL_RenderDrawPoint(renderer, xPos, yPos);
        }
        radius++;
    }
}
void DrawBall(SDL_Renderer* renderer, int * x ,int * y, int xaccel, int yaccel){
    SDL_Rect rect;
    rect.x = *x;
    rect.y = *y;
    rect.w = THICKNESS*2;
    rect.h = THICKNESS*2;
    SDL_RenderDrawRect(renderer, &rect);
    *x += xaccel;
    *y += yaccel;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("MonoPong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    double startAngle = 0.0;
    SDL_Event e;
    bool quit = false;
    int xBall = SCREEN_WIDTH/2;
    int yBall = SCREEN_HEIGHT/2;
    int xac = 1;
    int yac = -1;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_LEFT:
                        startAngle += 0.05; // Erhöht den Winkel um 0.01 Radian
                        break;
                    case SDLK_RIGHT:
                        startAngle -= 0.05; // Verringert den Winkel um 0.01 Radian
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

        std::vector<std::pair<int,int>> circlePos;

        DrawQuarterCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RADIUS, startAngle,THICKNESS,&circlePos);

        DrawBall(renderer,&xBall,&yBall, xac, yac);

        SDL_RenderPresent(renderer);

        circlePos.clear();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
