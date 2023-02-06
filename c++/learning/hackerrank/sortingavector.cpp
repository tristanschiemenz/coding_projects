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
    vector<int> MyVector;
    cin >> vector_size;
    for(int n = 0;n<vector_size;n++){
        int temp;
        cin >> temp;
        MyVector.push_back(temp);
    }
    sort(MyVector.begin(),MyVector.end());
    for(int n = 0;n<vector_size;n++){
        cout << to_string(MyVector[n]) + " ";
    }
    return 0;
}