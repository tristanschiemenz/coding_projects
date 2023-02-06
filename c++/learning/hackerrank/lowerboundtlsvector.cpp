#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


long in_list(long query, vector<long> vec){
    for(long i = 0;i<vec.size();i++){
        if (query == vec[i]){
            return i;
        }
    }
    return -1;
}
long next_bigger_item(long NumNotIn, vector<long> vec){
    for(long i= 0;i<vec.size();i++){
        if(NumNotIn < vec[i]){
            return i;
        }
    }
    return -1;
}

int main() {
    /* Enter your code here. Read input from STDIN. Prlong output to STDOUT */   
    long vector_size;
    cin >> vector_size;
    vector<long> MyVector;
    //creating vector
    for(long i = 0;i<vector_size;i++){
        long temp;
        cin >> temp;
        MyVector.push_back(temp);
    }
    //geting queris
    long que_size;
    cin >> que_size;
    for(long i = 0;i<que_size;i++){
        
        long query;
        cin >> query;
        
        long index = in_list(query,MyVector); 
        if(index >= 0){
            cout << "Yes " + to_string(index+1) + "\n";//fixing gap between index and postion 
        }else if(next_bigger_item(query, MyVector) >= 0){
            cout << "No " + to_string(next_bigger_item(query,MyVector) + 1) + "\n";
        }
    }
    
    return 0;
}
