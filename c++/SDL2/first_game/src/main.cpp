
#define SDL_MAIN_HANDLED
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>
#include <iostream>
//mingw32-make -f Makefile
#include "RenderWindow.hpp"

int main(int argc,char* argv[]){
    
    if (SDL_Init(SDL_INIT_VIDEO) > 0){
        std::cout << "HEY .. SDL_Init has failed. Sdl_error: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))){
        std::cout <<"IMG_init has failed. Error: " << SDL_GetError()<< std::endl;
    }

    RenderWindow window("GAME v1.0",1280,720);

    return 0;
}