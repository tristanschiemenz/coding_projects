#include <iostream>

template<typename T>
struct doubelLinkedNode
{
    T data; //auto assigning Data
    doubelLinkedNode * next;
    doubelLinkedNode * before;
};

template<typename T>
struct SingelLinkedNode {
    T data;
    SingelLinkedNode* next;
};
//oben Hinzufügen und oben Entfernen
template<typename T>
class Stapel {
public:
    Stapel() {
        head.data = T();  
        head.next = nullptr;
    }

    void push(const T& inputData) {
        SingelLinkedNode<T>* newNode = new SingelLinkedNode<T>;
        newNode->data = inputData;
        newNode->next = head.next;
        head.next = newNode;
    }

    T pop() {
        if (!head.next) {
            std::cerr << "Stack underflow! Trying to pop element from empty Stack" << std::endl;
            exit(1);
        }
        T NodeData = head.next->data;
        SingelLinkedNode<T>* NodeAfterDelete = head.next->next;
        delete head.next;
        head.next = NodeAfterDelete;
        return NodeData;
    }

private:
    SingelLinkedNode<T> head;
};

template<typename T>
class Schlange {
    public:
    Schlange(){
        head.next = nullptr;
        head.data = T();
        lastElem = &head;
    }
    void Enqueue(T inputData){
        SingelLinkedNode<T> * newNode = new SingelLinkedNode<T>;
        newNode->data = inputData;
        newNode->next = nullptr;
        lastElem->next = newNode;
        lastElem = newNode;
    }
    T Dequeue(){
        if (!head.next) {
            std::cerr << "Stack underflow! Trying to pop element from empty Stack" << std::endl;
            exit(1);
        }
        T NodeData = head.next->data;
        SingelLinkedNode<T> * NodeAfterDelete = head.next->next;
        delete head.next;
        head.next = NodeAfterDelete;
        return NodeData;
    }


    private:
    SingelLinkedNode<T> head;
    SingelLinkedNode<T> * lastElem;
};


int main(){
    
    Stapel<int> stack;



    return 0;
}