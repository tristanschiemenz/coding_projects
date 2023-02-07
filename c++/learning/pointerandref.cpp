#include <iostream>
#include <vector>
#include <cmath>
#include <string>




int sumup(int *eins, int zwei){
    *eins += zwei;
}
int main(){

    int zahl = 10;
    std::string str = "Hello";
    std::cout << zahl << std::endl;
    std::cout << str << std::endl;

    int &refzahl = zahl; //referenz aber leitet refzahl zu zahl um
    std::cout << refzahl << std::endl;
    int* ptrzahl = &zahl;
    int eins;
    int zwei;
    int drei;
    std::cout << &eins << " " << &zwei << " " << &drei << std::endl; 
    std::cout << ptrzahl << " ";
    *ptrzahl += 27;
    std::cout << ptrzahl << " \n";
    std::cout << *ptrzahl << std::endl;

    int &test = *ptrzahl;
    zahl += 1;
    std::cout << test << std::endl;

    int haupt = 10;
    int dazu = 15;
    sumup(&haupt,dazu);
    std::cout << haupt << std::endl;
    

    return 0;
}
