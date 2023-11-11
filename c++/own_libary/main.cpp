#include <iostream>
#include <string>

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
    T peak() {
        return head.next->data;
    }
    bool isEmpty(){
        SingelLinkedNode<T> * nextNode;
        if(head.next == nullptr){
            return true;
        }
        return false;
    }

private:
    SingelLinkedNode<T> head;
};

template<typename T>
class Schlange {
    public:
    Schlange() : size(0) {
        head.next = nullptr;
        lastElem = &head;
    }
    void Enqueue(T inputData){
        SingelLinkedNode<T> * newNode = new SingelLinkedNode<T>;
        newNode->data = inputData;
        newNode->next = nullptr;
        lastElem->next = newNode;
        lastElem = newNode;
        size++;
    }
    T Dequeue(){
        if (!head.next) {
            std::cerr << "Stack underflow! Versuch ein Element aus einer leeren Schlange zu nehmen!" << std::endl;
            exit(1);
        }
        T NodeData = head.next->data;
        SingelLinkedNode<T> * NodeAfterDelete = head.next->next;
        delete head.next;
        head.next = NodeAfterDelete;
        size--;
        return NodeData;
    }
    T peak() {
        if (!head.next) {
            std::cerr << "Schlange ist leer!" << std::endl;
            exit(1);
        }
        return head.next->data;
    }
    void ForEach(std::function<void(T&)> action) {
        for (SingelLinkedNode<T>* current = head.next; current != nullptr; current = current->next) {
            action(current->data);
        }
    }
    unsigned int Size() const {
        return size;
    }

    private:
    SingelLinkedNode<T> head;
    SingelLinkedNode<T> * lastElem;
    unsigned int size;
};
class TermTransformer(){
    public:
    TermTransformer(std::string input){
        toTransform = input;
    }
    void changeTerm(std::string input){
        toTransform = input;
    }
    std::string InfixToPostfix(){
        //add In to Po with toTransform and store it into latestTransform
        Schlange<int> numbers;
        Stapel<std::string> operators;
        std::string curNumber;
        for(int i = 0; i < toTransform.size(); i++){
            if(toTransform[i] >= 0 && toTransform[i] <= 9){
                curNumber = curNumber + toTransform[i];
            }
            else if(toTransform[i] == "+" || toTransform[i] == "-" || toTransform[i] == "*" || toTransform[i] == "/"){
                numbers.Enqueue(std::stoi(curNumber));
                if()

            }
            
        }
    }
    std::string PostfixToAssem(){
        
    }
    private:
    std::string latestTransform;
    std::string toTransform;
}


int main(){
    
    Stapel<int> stack;



    return 0;
}