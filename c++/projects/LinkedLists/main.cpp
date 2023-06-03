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
    void push(int value){
        LinkedList_data_int* to_append = new LinkedList_data_int;
        to_append->poiItem = new int;
        *(to_append->poiItem) = value;

        to_append->poiNext = head.poiNext;

        
        head.poiNext = to_append;
    }
    void pop(){
        delete head.poiNext->poiItem;
        head.poiNext->poiItem = nullptr;
        LinkedList_data_int* next_pointer = head.poiNext->poiNext;
        delete head.poiNext;
        head.poiNext = next_pointer;

    }

    //adding at the end
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
        
        LinkedList_data_int* current = head.poiNext;

        //go to the one with nullpointer(last one)
        while(current->poiNext != nullptr){
            current = current->poiNext;
        }
        //Changing pointer address to new last one
        current->poiNext = to_append;
        //Memory Managment
        current = nullptr;
    }
    //removing the last item
    void remove(){
        
        LinkedList_data_int* before_current = &head;
        LinkedList_data_int* current = head.poiNext;
        while(current->poiNext != nullptr){
            before_current = current;
            current = current->poiNext;
        }

        delete current->poiItem;
        current->poiItem = nullptr;
        delete current;
        before_current->poiNext = nullptr;
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
    list.push(100);
    list.append(100);
    list.pop();
    list.remove();
    while(true){
        list.push(100);
        list.pop();
    }
    
    size = list.size();
    std::cout << size;
    
    std::cout << size;


}