//SortingsAlgs.h
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <functional>


class SortingAlgs{
    public:
    SortingAlgs(bool &drawing,int n, int scaling, SDL_Renderer* inrenderer = nullptr,SDL_Window* inwindow = nullptr);
    void print_array(std::vector<int> &v);

    void bubble_sort(std::vector<int>& v, int delay);
    void counting_sort(std::vector<int> &v,int delay);
    void insertion_sort(std::vector<int> &v,int delay);
    void selection_sort(std::vector<int> &v, int delay);
    void merge_sort(std::vector<int> &array, int const begin, int const end,int delay);
    void quick_sort(std::vector<int> &arr, int start, int end, int delay);
    void shell_sort(std::vector<int> &arr, int size,int delay);
    void heap_sort(std::vector<int> &arr, int N,int delay);
    void radix_sort(std::vector<int> &arr, int N,int delay);

    private:
    void draw(std::vector<int> &v, unsigned int red,unsigned int blue);
    void merge(std::vector<int> &array, int const left, int const mid, int const right,int delay);
    int partition(std::vector<int> &arr, int start, int end,int delay);
    void heapify(std::vector<int> &arr, int N, int i,int delay);
    void countSort(std::vector<int> &arr, int N, int exp,int delay);
    int getMax(std::vector<int> &arr, int n,int delay);

    bool Sdrawing;
    SDL_Window* window;
    SDL_Renderer* renderer;


};
