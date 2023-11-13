#include <iostream>
#include <string>
#include <cctype>
#include <functional>

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
    SingelLinkedNode* nextNode;
};
//oben Hinzufügen und oben Entfernen
template <typename T>
class Stapel {
public:
	Stapel() {
		firstPointer = nullptr;
	}
	void push(T Idata) {
		size++;
		SingelLinkedNode<T>* elem = new SingelLinkedNode<T>;
		elem->data = Idata;
		elem->nextNode = firstPointer;
		firstPointer = elem;
		return;
	}
	T pop() {
		if (isEmpty()) {
			std::cerr << "Stapel ist leer!!";
			exit(1);
		}
		size--;
		SingelLinkedNode<T>* toPop = firstPointer;
		firstPointer = firstPointer->nextNode;
		T data = toPop->data;
		delete toPop;
		return data;

	}
	T top() {
	    if(isEmpty()){
	        std::cerr << "Stapel ist leer!!";
	        exit(1);
	    }
		return firstPointer->data;
	}
	bool isEmpty() {
		if (firstPointer == nullptr) {
			return true;
		}
		return false;
	}
	unsigned int count() const {
		return size;
	}
private:
	SingelLinkedNode<T>* firstPointer;
	unsigned int size;
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
int prioritaet(char Ioperaotr) {
    switch (Ioperaotr) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        case '(': return 0; // Priorität für '('
        default: return -1; // Fallback für ungültige Operatoren
    }
}

std::string InfixToPostfix(std::string InfixTerm) {
    std::string PostfixTerm;
    Stapel<char> operatorenStapel;

    for (char ch : InfixTerm) {
        if(ch == ' '){
            //skip
        } else if (std::isalnum(ch)) { // Überprüfung für Zahlen/Buchstaben
            PostfixTerm.push_back(ch);
        } else { // Rechenzeichen
            if (!PostfixTerm.empty() && PostfixTerm.back() != ' ') {
                PostfixTerm.push_back(' ');
            }
            if (ch == ')') {
                while (!operatorenStapel.isEmpty() && operatorenStapel.top() != '(') {
                    PostfixTerm.push_back(operatorenStapel.pop());
                    PostfixTerm.push_back(' ');
                }
                operatorenStapel.pop(); // '(' entfernen
            } else if(ch == '('){
                operatorenStapel.push('(');
            } else {
                while (!operatorenStapel.isEmpty() && prioritaet(ch) <= prioritaet(operatorenStapel.top())) {
                    PostfixTerm.push_back(operatorenStapel.pop());
                    PostfixTerm.push_back(' ');
                }
                operatorenStapel.push(ch);
            }
        }
    }

    while (!operatorenStapel.isEmpty()) {
        if (PostfixTerm.back() != ' ') {
            PostfixTerm.push_back(' ');
        }
        PostfixTerm.push_back(operatorenStapel.pop());
    }
    return PostfixTerm;
}

int main(){
    
    std::cout << InfixToPostfix("45+ab*5-(4^2-5)");



    return 0;
}