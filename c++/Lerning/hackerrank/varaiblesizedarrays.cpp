#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
     int nrArrays;
     int nrQueries;
     
     cin >> nrArrays >> nrQueries;
     std::vector<vector<int>> mainArray;;
     
     for (int i = 0; i < nrArrays; i++){
         int subArraySize;
         cin >> subArraySize;
         std::vector<int> subArray;
         for (int i = 0; i < subArraySize; i++){
             int value;
             cin >> value;
             subArray.push_back(value);
         }
         mainArray.push_back(subArray);
     }  
     
     int arrayIndex;
     int subArrayIndex;
     for (int i = 0; i < nrQueries; i++){
         cin >> arrayIndex >> subArrayIndex;
         cout << mainArray[arrayIndex][subArrayIndex] << "\n";
     }
    return 0;
}