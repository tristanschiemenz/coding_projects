#include <iostream>


int add_numbers(int how_many_to_add){
    if (how_many_to_add == 1){
        return 1;
    }
    return how_many_to_add + add_numbers(how_many_to_add-1);
}

int main(){
    int sum = add_numbers(10000);
    std::cout << sum;
    return 0;
}