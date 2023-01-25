#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int i;
    for(i=0;i<= 500000;i++){
        cout << sqrt(i*6/4%3+1+6/6)<< endl;
        cout << i << endl;
    }    
}