#pragma once

#include<sdl/SDL.h>
#include<sdl/SDl_image.h>

class RenderWindow{
    public:
        RenderWindow(const char* p_title,int p_w, int p_h);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};