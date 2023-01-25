#include<sdl/SDL.h>
#include<sdl/SDL_image.h>
#include<iostream>


#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title,int p_w,int p_h)
:window(NULL),renderer(NULL)
{
    window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h, SDL_WINDOW_SHOWN);

    if (window == NULL){
        std::cout<<"WINDOW faild to init. ERROR: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
}

