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
    void quick_sort(std::vector<int> &arr, int start, int end, int delay){
        // base case
        if (start >= end)
            return;
    
        // partitioning the array
        int p = partition(arr, start, end,delay);
        if(Sdrawing){
            draw(arr,start,end);
            SDL_Delay(delay);
        }
        // Sorting the left part
        quick_sort(arr, start, p - 1,delay);
        quick_sort(arr, p + 1, end,delay);
    }
    void shell_sort(std::vector<int> &arr, int size,int delay){
        // Start with a big gap, then reduce the gap
        for (int gap = size/2; gap > 0; gap /= 2)
        {
            // Do a gapped insertion sort for this gap size.
            // The first gap elements a[0..gap-1] are already in gapped order
            // keep adding one more element until the entire array is
            // gap sorted 
            for (int i = gap; i < size; i += 1)
            {
                // add a[i] to the elements that have been gap sorted
                // save a[i] in temp and make a hole at position i
                int temp = arr[i];
    
                // shift earlier gap-sorted elements up until the correct 
                // location for a[i] is found
                int j;            
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                    if(Sdrawing){
                        draw(arr,j,i);
                        SDL_Delay(delay);
                }
                
                //  put temp (the original a[i]) in its correct location
                arr[j] = temp;
                if(Sdrawing){
                    draw(arr,gap,i);
                    SDL_Delay(delay);
                }
            }
        }
    }
    void heap_sort(std::vector<int> &arr, int N,int delay){
        // Build heap (rearrange array)
        for (int i = N / 2 - 1; i >= 0; i--){
            heapify(arr, N, i,delay);
            if(Sdrawing){
                draw(arr,i,N);
                SDL_Delay(delay);
            }
        }
        // One by one extract an element
        // from heap
        for (int i = N - 1; i > 0; i--) {
    
            // Move current root to end
            std::swap(arr[0], arr[i]);
            if(Sdrawing){
                draw(arr,i,i);
                SDL_Delay(delay);
            }
            // call max heapify on the reduced heap
            heapify(arr, i, 0,delay);
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
    void merge(std::vector<int> &array, int const left, int const mid, int const right,int delay){
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
                draw(array,indexOfMergedArray,indexOfSubArrayOne);
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
            if(Sdrawing){
                draw(array,indexOfMergedArray,indexOfSubArrayOne);
                SDL_Delay(delay);
            }
        }
        // Copy the remaining elements of
        // right[], if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
            if(Sdrawing){
                draw(array,indexOfMergedArray,indexOfSubArrayTwo);
                SDL_Delay(delay);
            }
        }
        delete[] leftArray;
        delete[] rightArray;
    }
    int partition(std::vector<int> &arr, int start, int end,int delay){
    
        int pivot = arr[start];
    
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] <= pivot){
                count++;
            }
            if(Sdrawing){
                draw(arr,pivot,i);
                SDL_Delay(delay);
            }
        }
    
        // Giving pivot element its correct position
        int pivotIndex = start + count;
        std::swap(arr[pivotIndex], arr[start]);
    
        // Sorting left and right parts of the pivot element
        int i = start, j = end;
    
        while (i < pivotIndex && j > pivotIndex) {
            if(Sdrawing){
                draw(arr,i,j);
                SDL_Delay(delay);
            }
            while (arr[i] <= pivot) {
                i++;
            }

            while (arr[j] > pivot) {
                j--;
            }
    
            if (i < pivotIndex && j > pivotIndex) {
                std::swap(arr[i++], arr[j--]);
            }
        }
    
        return pivotIndex;
    }
    void heapify(std::vector<int> &arr, int N, int i,int delay){
    
        // Initialize largest as root
        int largest = i;
    
        // left = 2*i + 1
        int l = 2 * i + 1;
    
        // right = 2*i + 2
        int r = 2 * i + 2;
    
        // If left child is larger than root
        if (l < N && arr[l] > arr[largest]){
            largest = l;
        }
        // If right child is larger than largest
        // so far
        if (r < N && arr[r] > arr[largest]){
            largest = r;
        }
        if(Sdrawing){
            draw(arr,i,largest);
            SDL_Delay(delay);

        }
        
        // If largest is not root
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            if(Sdrawing){
                draw(arr,i,largest);
                SDL_Delay(delay);
            }
            // Recursively heapify the affected
            // sub-tree
            heapify(arr, N, largest,delay);
        }
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

    bool drawing = true;
    SortingAlgs sorting(drawing,6);
    
    std::shuffle(v.begin(), v.end(),rng);
    sorting.heap_sort(v,n,10);

    // std::shuffle(v.begin(), v.end(), rng);
    //     //bubble
    // sorting.bubble_sort(v,1);

    // std::shuffle(v.begin(), v.end(), rng);
    // //Selction
    // sorting.selection_sort(v,1);

    // std::shuffle(v.begin(), v.end(), rng);
    // //insert
    // sorting.insertion_sort(v,1);

    // std::shuffle(v.begin(), v.end(), rng);
    // //shell
    // sorting.shell_sort(v,n,5);
    
    // std::shuffle(v.begin(), v.end(), rng);
    // //merge
    // sorting.merge_sort(v,0,n-1,10);

    // std::shuffle(v.begin(), v.end(), rng);
    // //quick
    // sorting.quick_sort(v,0,n-1,10);

    // std::shuffle(v.begin(), v.end(), rng);
    // //couning
    // sorting.counting_sort(v,10);

    sorting.print_array(v);
    
    return 0;
}