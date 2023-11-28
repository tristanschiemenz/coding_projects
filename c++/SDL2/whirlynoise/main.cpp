#include <SDL2/SDL.h>
#include <cstdlib> 
#include <cmath> 
#include <vector>
#include <algorithm>

const int WIDTH = 500;
const int HEIGHT = 500;
const int WINDOWWIDTH = 1000;
const int WINDOWHEIGHT = 1000;
const int DIM = 250;

struct cor{
    int x;
    int y;
    int z;
};

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    const int diameter = (radius * 2);

    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y) {
        // Each of these lines draws a pair of points at opposite ends of a diameter.
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    return;
}

std::vector<cor> createRandomPoints(int n){
    std::vector<cor> outputList;
    for(int i = 0; i < n; ++i){
        cor newItem;
        newItem.x = rand() % WIDTH;
        newItem.y = rand() % HEIGHT;
        newItem.z = rand() % DIM;
        outputList.push_back(newItem);
    }
    return outputList;
}

std::vector<int> calcAllDistances(std::vector<cor> pointList, int x, int y, int z){
    std::vector<int> distList;
    for(int i = 0; i < pointList.size(); ++i){
        distList.push_back(sqrt(pow(pointList[i].x - x, 2) + pow(pointList[i].y - y, 2) + pow(pointList[i].z - z, 2)));
    }
    return distList;
}
void drawColorOnDist(SDL_Renderer* renderer, std::vector<int> distList, int x, int y, int z, int n) {
    double color = 0;
    for (int i = 0; i < n; ++i) {
        color += distList[i];
    }
    // Normalize or clamp the color value
    color = color * 2;
    SDL_SetRenderDrawColor(renderer, color, color, color, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Noise", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetScale(renderer,WINDOWWIDTH/WIDTH, WINDOWHEIGHT/HEIGHT);
    //generate random Points
    std::vector<cor> randomPoints = createRandomPoints(75);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    //Draw Circle
    for(int i = 0; i < randomPoints.size(); ++i){
        drawCircle(renderer, randomPoints[i].x, randomPoints[i].y, 2);
    }
    //calc distanc
    int z = 0;
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear with black
        SDL_RenderClear(renderer);

        // z = (z + 1) % DIM; // Increment and wrap-around z
        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                std::vector<int> distList = calcAllDistances(randomPoints, x, y, z);
                std::sort(distList.begin(), distList.end());
                drawColorOnDist(renderer, distList, x, y, z, 1);
                // SDL_RenderPresent(renderer); // Update screen
            }
        }

        SDL_RenderPresent(renderer); // Update screen

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    return 0;
}