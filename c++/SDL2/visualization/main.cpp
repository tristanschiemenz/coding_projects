// #include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>

const int n = 100;


class SortingAlgs{
    public:
    SortingAlgs(bool &drawing, int scaling){
        Sdrawing = drawing;

        if(Sdrawing){
            // SDL_CreateWindowAndRenderer(n*scaling,n*scaling,0,&window,&renderer);
            // SDL_RenderSetScale(renderer,scaling,scaling);
        }
    }
    void print_array(std::vector<int> &v){
        for(int i = 0; i<v.size(); i++){
            std::cout << v[i] << " ";
        }
    }
    void bubble_sort(std::vector<int>& v, int delay){
        for(int i= 1; i< v.size();i++){
            for(int j = 0; j<v.size();j++){
                if(v[i] < v[j]){
                    std::swap(v[i],v[j]);
                }
                if(Sdrawing){
                    //Draw
                    draw(v,i,j);
                    //Show
                    // SDL_Delay(delay);
                }
            }
        }
    }
    void counting_sort(std::vector<int> &v,int delay){
        //finding the heighes value
        int indexHeighest = 0;
        int heighest = v[indexHeighest]; 
        for(int i = 1; i < v.size(); i++){
            if(v[i] > heighest){
                heighest = v[i];
                indexHeighest = i;
            }
            if(Sdrawing){
                draw(v,indexHeighest,i);
                // SDL_Delay(delay)
            }
        }
        
        int counts[heighest+1];
            // Initialize the count for each element in array to 0
        for (int i = 0; i <= heighest+1; ++i) {
            counts[i] = 0;
        }
        //Counting
        for(int i=0;i<v.size();i++){
            counts[v[i]]++;
            if(Sdrawing){
                    //Draw
                    draw(v,i,i);
                    //Delay
                    // SDL_Delay(delay);

            }
        }
        //Writing the new results
        int position = 0;
        for(int i = 0;i < heighest + 1;i++){
            for(int j = 0; j < counts[i]; j++){
                v[position] = i;
                position++;
                if(Sdrawing){
                    draw(v,i,i);
                    // SDL_Delay(delay);
                }
            }
        }
    }
    void insertion_sort(std::vector<int> &v){}
    private:
    void draw(std::vector<int> &v, unsigned int red,unsigned int blue){
        // SDL_SetRenderDrawColor(renderer,0,0,0,255);
        // SDL_RenderClear(renderer);
        for(int i = 0;i<v.size();i++){
            if(i == red){
                // SDL_SetRenderDrawColor(renderer,255,0,0,255);
            }else if (i == blue){
                // SDL_SetRenderDrawColor(renderer,0,0,255,255);
            }else{
                // SDL_SetRenderDrawColor(renderer,255,255,255,255);
            }
            
            // SDL_RenderDrawLine(renderer,i,n,i,n-v[i]);
        }
        // SDL_RenderPresent(renderer);
}
    bool Sdrawing;
    // SDL_Window* window = nullptr;
    // SDL_Renderer* renderer = nullptr;


};

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
    bool drawing = false;
    SortingAlgs sorting(drawing,6);
    // sorting.bubble_sort(v,1);

    // std::shuffle(v.begin(), v.end(), rng);

    sorting.counting_sort(v,0);
    sorting.print_array(v);
    
    //Returning
    return 0;
}