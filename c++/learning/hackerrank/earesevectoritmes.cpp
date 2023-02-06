#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int vector_size;
    cin >> vector_size;
    vector<int> MyVector;
    //creating vector
    for(int i = 0;i<vector_size;i++){
        int temp;
        cin >> temp;
        MyVector.push_back(temp);
    }
    //erease one item
    int one_eraeser;
    cin >> one_eraeser;
    MyVector.erase(MyVector.begin() + one_eraeser-1);
    
    int start;
    int end;
    cin >> start >> end;
    MyVector.erase(MyVector.begin()+start-1 , MyVector.begin() + end-1);
    
    cout << MyVector.size() << endl;
    for(int i = 0;i<MyVector.size();i++){
        cout << to_string(MyVector[i]) + " ";
    }
    
    return 0;
}