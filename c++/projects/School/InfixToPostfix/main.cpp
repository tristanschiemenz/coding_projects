#include <iostream>
#include <string>
#include <cctype>
#include <functional>
#include <fstream>

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
        } else if (std::isalnum(ch)) { //Überprüfung für Zahlen/Buchstaben
            PostfixTerm.push_back(ch);
        } else { //Rechenzeichen
            if (!PostfixTerm.empty() && PostfixTerm.back() != ' ') {
                PostfixTerm.push_back(' ');
            }
            if (ch == ')') {
                while (!operatorenStapel.isEmpty() && operatorenStapel.top() != '(') {
                    PostfixTerm.push_back(operatorenStapel.pop());
                    PostfixTerm.push_back(' ');
                }
                operatorenStapel.pop(); //( entfernen
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

std::pair<std::string, std::string> PostfixToAssembler(std::string postFixTerm) {
    Stapel<std::string> zahlStapel;
    std::string readableAssemblyCode;
    std::string inlineAssemblyCode;

    for (size_t i = 0; i < postFixTerm.size(); ++i) {
        if (postFixTerm[i] == ' ') {
            // Skip
        } else if (isalnum(postFixTerm[i])) {
            std::string Snumber;
            while (i < postFixTerm.size() && isalnum(postFixTerm[i])) {
                Snumber.push_back(postFixTerm[i]);
                i++;
            }
            zahlStapel.push(Snumber);
        } else {
            std::string op2 = zahlStapel.pop();
            std::string op1 = zahlStapel.pop();
            if (!isdigit(op2[0])) { // Check if op2 is a number
                readableAssemblyCode += "mov eax, " + op2 + "\n";
                inlineAssemblyCode += "\"movl %" + op2 + ", %%eax;\"\n";
            } else {
                readableAssemblyCode += "mov eax, " + op2 + "\n";
                inlineAssemblyCode += "\"movl $" + op2 + ", %%eax;\"\n";
            }
            if (!isdigit(op1[0])) { // Check if op1 is a number
                readableAssemblyCode += "mov ebx, " + op1 + "\n";
                inlineAssemblyCode += "\"movl %" + op1 + ", %%ebx;\"\n";
            } else {
                readableAssemblyCode += "mov ebx, " + op1 + "\n";
                inlineAssemblyCode += "\"movl $" + op1 + ", %%ebx;\"\n";
            }

            
            switch (postFixTerm[i]) {
                case '+':
                    readableAssemblyCode += "add eax, ebx\n";
                    inlineAssemblyCode += "\"addl %%ebx, %%eax;\"\n";
                    break;
                case '-':
                    readableAssemblyCode += "sub eax, ebx\n";
                    inlineAssemblyCode += "\"sub %%ebx, %%eax;\"\n";
                    break;
                case '*':
                    readableAssemblyCode += "mul ebx\n";
                    inlineAssemblyCode += "\"imull %%ebx, %%eax;\"\n";
                    break;
                case '/':
                    readableAssemblyCode += "div ebx\n";
                    inlineAssemblyCode += "\"xorl %%edx, %%edx;\"\n"; // Clear EDX before division
                    inlineAssemblyCode += "\"idivl %%eax;\"\n";
                    break;
            }
            zahlStapel.push("eax");
        }
    }

    return {readableAssemblyCode, inlineAssemblyCode};
}

int runAssembly(std::string& AssemblyString){
    std::string cppCode = 
        "#include <iostream>\n"
        "int main() {\n"
        "    int result;\n"
        "    __asm__(\n"
        "   " + AssemblyString + ""
        "        : \"=a\" (result)\n"
        "    );\n"
        "    std::cout << result;\n"
        "    return 0;\n"
        "}\n";
    std::ofstream out("generated_assembly_code.cpp");
    out << cppCode;
    out.close();

    if(std::system("g++ -o generated_assembly_code generated_assembly_code.cpp") != 0){
        std::cerr << "Assembly Compile failed.";
        exit(1);
    }
    if (std::system(".\\generated_assembly_code > output.txt") != 0) {
        std::cerr << "Execution of the assembly code failed.\n";
        return -1;
    }

    std::ifstream inFile("output.txt");
    std::string strResult;
    if (!std::getline(inFile, strResult)) {
        std::cerr << "Failed to read the output.\n";
        return -1;
    }
    inFile.close();

     // Convert the string to an integer
    int result = std::stoi(strResult);

    return result;

}
int main()
{
    std::string assemcode = PostfixToAssembler(InfixToPostfix("8*10-100")).second;
    std::cout << runAssembly(assemcode);
    return 0;
}



