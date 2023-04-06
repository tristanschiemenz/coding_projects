#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

const int n = 100;

void draw(std::vector<int>& v, SDL_Renderer* renderer, unsigned int red,unsigned int blue){
    int index = 0;
    for(int i = 0;i<v.size();i++){
        if(i == red){
            SDL_SetRenderDrawColor(renderer,255,0,0,255);
        }else if (i == blue){
            SDL_SetRenderDrawColor(renderer,0,0,255,255);
        }else{
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
        
        SDL_RenderDrawLine(renderer,i,n,i,n-v[i]);
    }
}

int main(int argc, char *argv[]){

    std::vector<int> v(n);

    // Fill the vector with unique numbers
    for (int i = 0; i < n; ++i) {
        v[i] = i + 1;
    }

    // Seed the random number generator
    std::mt19937 rng(std::time(nullptr));

    // Shuffle the vector
    std::shuffle(v.begin(), v.end(), rng);

    //Window and Renderer
    const int scaling=6;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(n*scaling,n*scaling,0,&window,&renderer);
    SDL_RenderSetScale(renderer,scaling,scaling);
    //sorting

    for(int i= 1; i< v.size();i++){
        for(int j = 0; j<v.size();j++){
            if(v[i] < v[j]){
                std::swap(v[i],v[j]);
            }
            //clear screen
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
            SDL_RenderClear(renderer);
            //Draw
            draw(v,renderer,i,j);
            //Show
            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }
    }
    SDL_Delay(1);
    for(int i = 0; i<v.size(); i++){
        std::cout << v[i] << " ";
    }

}