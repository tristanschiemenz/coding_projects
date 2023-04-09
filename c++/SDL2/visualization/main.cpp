#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

#include "main_menu.h"
#include "SortingAlgs.h"

const int n = 100;

int main(int argc, char *argv[]){

    std::vector<int> v(n);

    // Fill the vector with unique numbers
    for (int i = 0; i < n; ++i) {
        v[i] = i + 1;
    }

    // Seed the random number generator
    std::mt19937 rng(std::time(nullptr));

    // Shuffle the vector

    bool drawing = true;
    SortingAlgs sorting(drawing,n,6);
    
    std::shuffle(v.begin(), v.end(), rng);
        //bubble
    sorting.bubble_sort(v,2);

    std::shuffle(v.begin(), v.end(), rng);
    //Selction
    sorting.selection_sort(v,2);

    std::shuffle(v.begin(), v.end(), rng);
    //insert
    sorting.insertion_sort(v,2);

    std::shuffle(v.begin(), v.end(), rng);
    //shell
    sorting.shell_sort(v,n,5);
    
    std::shuffle(v.begin(), v.end(), rng);
    //heap
    sorting.heap_sort(v,n,10);

    std::shuffle(v.begin(), v.end(), rng);
    //radix
    sorting.radix_sort(v,n,10);
    
    std::shuffle(v.begin(), v.end(), rng);
    //merge
    sorting.merge_sort(v,0,n-1,10);

    std::shuffle(v.begin(), v.end(), rng);
    //quick
    sorting.quick_sort(v,0,n-1,10);

    std::shuffle(v.begin(), v.end(), rng);
    //couning
    sorting.counting_sort(v,10);

    sorting.print_array(v);
    
    return 0;
}