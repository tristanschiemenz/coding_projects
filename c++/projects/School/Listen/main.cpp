#include<iostream>

template <typename T>
struct doubleLinkedNode {
    doubleLinkedNode* pre = nullptr;
    doubleLinkedNode* next = nullptr;
    T data;
};

template<typename T>
class Liste {
public:
    doubleLinkedNode<T>* head;
    doubleLinkedNode<T>* tail;
    int count;
    Liste() {
        count = 0;
        head = nullptr;
        tail = nullptr;
    }
    void push(T toAdd) {
        count++;
        doubleLinkedNode<T>* newNode = new doubleLinkedNode<T>;
        newNode->data = toAdd;
        newNode->next = head;
        newNode->pre = nullptr;
        if (tail == nullptr) {
            tail = newNode;
        }
        if (newNode->next != nullptr) {
            newNode->next->pre = newNode;
        }
        head = newNode;
    }
    T pop() {
        if (head == nullptr) {
            std::cerr << "Pop error: List is empty";
            exit(1);
        }
        T toReturn = head->data;
        doubleLinkedNode<T>* toPop = head;
        head = head->next;
        if (head != nullptr) {
            head->pre = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete toPop;
        count--;
        return toReturn;
    }
    void append(T toAdd) {
        count++;
        doubleLinkedNode<T>* newNode = new doubleLinkedNode<T>;
        newNode->data = toAdd;
        newNode->pre = tail;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        }
        if (newNode->pre != nullptr) {
            newNode->pre->next = newNode;
        }
        tail = newNode;

    }
    T remove() {
        if (tail == nullptr) {
            std::cerr << "Remove error: List is empty";
            exit(1);
        }
        T toReturn = tail->data;
        doubleLinkedNode<T>* toRem = tail;
        tail = tail->pre;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete toRem;
        count--;
        return toReturn;
    }
    int size() {
        return count;
    }


};

template<typename T>
class ordertListe: public Liste<T>{
public:
    ordertListe() : Liste<T>(){}
    void einfügenAn(int index, T data) {
    if (index < 0 || index > this->count) {
        std::cerr << "Invalider Index";
        exit(1);
        
    }

    doubleLinkedNode<T>* newNode = new doubleLinkedNode<T>;
    newNode->data = data;

    if (index == 0) {
        // am Kopf
        newNode->next = this->head;
        if (this->head != nullptr) {
            this->head->pre = newNode;
        }
        this->head = newNode;
        if (this->tail == nullptr) {
            this->tail = newNode;
        }
    } else {
        // Irgendwo oder am Ende
        doubleLinkedNode<T>* current = this->head;
        for (int i = 0; i < index - 1 && current != nullptr; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->pre = current;
        if (current->next != nullptr) {
            current->next->pre = newNode;
        } else {
            // Tail hinzufügen
            this->tail = newNode;
        }
        current->next = newNode;
    }

    this->count++;
}
    T entfernenAn(int index) {
    if (this->head == nullptr || index < 0 || index >= this->count) {
        std::cerr << "Invalider Index";
        exit(1);
    }

    doubleLinkedNode<T>* toRemove = this->head;
    for (int i = 0; i < index; ++i) {
        toRemove = toRemove->next;
    }

    T toReturn = toRemove->data;

    if (toRemove->pre != nullptr) {
        toRemove->pre->next = toRemove->next;
    } else {
        // Head Entfernen
        this->head = toRemove->next;
    }

    if (toRemove->next != nullptr) {
        toRemove->next->pre = toRemove->pre;
    } else {
        // Tail entfernen
        this->tail = toRemove->pre;
    }

    delete toRemove;
    this->count--;
    return toReturn;
}
};

int main()
{
    ordertListe<int> Liste;

    Liste.push(5);
    Liste.append(10);
    Liste.append(15);
    Liste.append(20);

    Liste.einfügenAn(1, 7);
    Liste.einfügenAn(3, 17);
    std::cout << Liste.pop() << " ";
    std::cout << Liste.pop() << " ";
    std::cout << Liste.pop() << " ";
    std::cout << Liste.pop() << " ";
    std::cout << Liste.pop() << " ";
    std::cout << Liste.pop() << " ";
    


    return 0;
}




