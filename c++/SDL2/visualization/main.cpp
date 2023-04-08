#include <SDL2/SDL.h>
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
            SDL_CreateWindowAndRenderer(n*scaling,n*scaling,0,&window,&renderer);
            SDL_RenderSetScale(renderer,scaling,scaling);
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
                    SDL_Delay(delay);
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
                SDL_Delay(delay);
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
                    SDL_Delay(delay);

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
                    SDL_Delay(delay);
                }
            }
        }
    }
    void insertion_sort(std::vector<int> &v,int delay){
        int key, j;
        for(int i = 1; i < v.size(); i++){
            key = v[i];
            j = i-1;
            while (j >= 0 && v[j] > key){
                v[j+1] = v[j];
                j--;
                if(Sdrawing){
                    draw(v,i,j);
                    SDL_Delay(delay);
                }
            }
            v[j+1] = key;
            if(Sdrawing){
                    draw(v,i,j);
                    SDL_Delay(delay);
            }
            
        }
    }
    void selection_sort(std::vector<int> &v, int delay){
        int minimumIndex;
        for(int i = 0; i < v.size(); i++){
            minimumIndex = i;
            for(int j = i; j < v.size();j++){
                if(v[minimumIndex] > v[j]){
                    minimumIndex = j;
                }
                if(Sdrawing){
                    draw(v,minimumIndex,j);
                    SDL_Delay(delay);
                }
            }
            std::swap(v[i],v[minimumIndex]);
        }
    }
    void merge_sort(std::vector<int> &array, int const begin, int const end,int delay){  
        if (begin >= end)
            return; // Returns recursively
    
        auto mid = begin + (end - begin) / 2;
        merge_sort(array, begin, mid,delay);
        if(Sdrawing){
            draw(array,mid,begin);
            SDL_Delay(delay);
        }
        merge_sort(array, mid + 1, end,delay);
        if(Sdrawing){
            draw(array,mid,end);
            SDL_Delay(delay);
        }
        merge(array, begin, mid, end,delay);
        if(Sdrawing){
            draw(array,mid,mid);
            SDL_Delay(delay);
        }
    }
    private:
    void draw(std::vector<int> &v, unsigned int red,unsigned int blue){
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
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
        SDL_RenderPresent(renderer);
    }
    void merge(std::vector<int> &array, int const left, int const mid, int const right,int delay)
    {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne
        = 0, // Initial index of first sub-array
        indexOfSubArrayTwo
        = 0; // Initial index of second sub-array
    int indexOfMergedArray
        = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
        if(Sdrawing){
            draw(array,indexOfSubArrayOne,indexOfSubArrayTwo);
            SDL_Delay(delay);
        }
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
    }
    bool Sdrawing;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;


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
    bool drawing = true;
    SortingAlgs sorting(drawing,6);
    sorting.bubble_sort(v,1);

    std::shuffle(v.begin(), v.end(), rng);

    sorting.selection_sort(v,1);

    std::shuffle(v.begin(), v.end(), rng);

    sorting.merge_sort(v,0,n-1,0);

    std::shuffle(v.begin(), v.end(), rng);

    sorting.insertion_sort(v,1);

    std::shuffle(v.begin(), v.end(), rng);

    sorting.counting_sort(v,10);

    sorting.print_array(v);
    
    //Returning
    return 0;
}