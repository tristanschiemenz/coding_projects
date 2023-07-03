#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <chrono>


int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int RADIUS = 200;
const int THICKNESS = 3;


void DrawHourCircle(SDL_Renderer* renderer, int x, int y, int radius, double startAngle, int thick) {
    double endAngle = startAngle + 2 * M_PI / 12;
    for(int i = 0; i<thick; i++){
        for (double theta = startAngle; theta < endAngle; theta += 0.01) {
            int xPos = x + radius * cos(theta);
            int yPos = y + radius * sin(theta);
            SDL_RenderDrawPoint(renderer, xPos, yPos);
        }
        radius++;
    }
}
void DrawMinuteCircle(SDL_Renderer* renderer, int x, int y, int radius, double startAngle, int thick) {
    radius = radius * 0.9;
    double endAngle = startAngle + 2 * M_PI / 60;
    for(int i = 0; i<thick; i++){
        for (double theta = startAngle; theta < endAngle; theta += 0.01) {
            int xPos = x + radius * cos(theta);
            int yPos = y + radius * sin(theta);
            SDL_RenderDrawPoint(renderer, xPos, yPos);
        }
        radius++;
    }
}
void DrawSecCircle(SDL_Renderer* renderer, int x, int y, int radius, double startAngle, int thick) {
    radius = radius * 0.8;
    double endAngle = startAngle + 2 * M_PI / 3600;
    for(int i = 0; i<thick; i++){
        for (double theta = startAngle; theta < endAngle; theta += 0.01) {
            int xPos = x + radius * cos(theta);
            int yPos = y + radius * sin(theta);
            SDL_RenderDrawPoint(renderer, xPos, yPos);
        }
        radius++;
    }
}


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Clock", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    double startAngle = 0.0;
    SDL_Event e;
    bool quit = false;
    int xBall = SCREEN_WIDTH/2;
    int yBall = SCREEN_HEIGHT/2;
    int xac = 1;
    int yac = -1;


    while (!quit) {
        SDL_GetWindowSize(window,&SCREEN_WIDTH,&SCREEN_HEIGHT);
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_LEFT:
                        startAngle += 0.01; // Erhöht den Winkel um 0.01 Radian
                        break;
                    case SDLK_RIGHT:
                        startAngle -= 0.01; // Verringert den Winkel um 0.01 Radian
                        break;
                }
            }
        }

        startAngle = fmod(startAngle, 2 * M_PI);



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        if(SCREEN_WIDTH <= SCREEN_HEIGHT){
            RADIUS = SCREEN_WIDTH * 0.40;
        }else{RADIUS = SCREEN_HEIGHT * 0.40;}

        // Get current time as a time_point object
        auto now = std::chrono::system_clock::now();

        // Count time since epoch in milliseconds
        auto duration = now.time_since_epoch();
        double milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

        // Calculate precise angles
        double secondAngle = fmod(milliseconds / 1000, 60) / 60.0 * 2 * M_PI;
        double minuteAngle = fmod(milliseconds / 60000, 60) / 60.0 * 2 * M_PI;
        double hourAngle = fmod(milliseconds / 3600000, 12) / 12.0 * 2 * M_PI;

        // Correct for the fact that 0 angle points to the right in a typical graphical coordinate system
        secondAngle -= M_PI / 2;
        minuteAngle -= M_PI / 2;
        hourAngle -= M_PI / 2;

        DrawHourCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RADIUS, hourAngle,THICKNESS);
        DrawMinuteCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RADIUS, minuteAngle,THICKNESS);
        DrawSecCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RADIUS, secondAngle,THICKNESS);



        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
