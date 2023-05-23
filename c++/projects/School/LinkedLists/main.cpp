#include <iostream>

struct LinkedList_data_int{
    int*  poiItem;
    LinkedList_data_int* poiNext;
};

class LinkedList{
    public:
    LinkedList(){
        head.poiItem = nullptr;
        head.poiNext = nullptr;
    };
    void append(int value){
        //Creating new struct
        LinkedList_data_int* to_append = new LinkedList_data_int;
        //Value assignement
        to_append->poiItem = new int;
        *(to_append->poiItem) = value;
        //pointer to nullpoint
        to_append->poiNext = nullptr;
        
        //first Item
        if(LinkedList::size() == 0){
            head.poiNext = to_append;
            return;
        }
        
        LinkedList_data_int* current = &head;

        //go to the one with nullpointer(last one)
        while(current->poiNext != nullptr){
            current = current->poiNext;
        }
        //Changing pointer address to new last one
        current->poiNext = to_append;
        //Memory Managment
        current = nullptr;
    }
    int size(){
        LinkedList_data_int* current = &head;
        int count = 0;

        while(current->poiNext != nullptr){
            current = current->poiNext;
            count++;
        }

        //MEMORY
        current = nullptr;
        return count;

    }
    private:
    LinkedList_data_int head;
};

int main(){
    LinkedList list;
    int size = list.size();

    std::cout << size << "\n"; 
    list.append(5);
    list.append(5);
    size = list.size();
    std::cout << size;


}