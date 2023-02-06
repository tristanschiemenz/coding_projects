#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int query_size;
    cin >> query_size;
    set<long>MySet;
    for(int i = 0;i<query_size;i++){
        long query;
        long val;
        cin >> query >> val;
        
        if(query == 1){    
            MySet.insert(val);
        }else if(query == 2){
            MySet.erase(val);
        }else if(query == 3){
            set<long>::iterator itr = MySet.find(val);
            if(itr != MySet.end()){
                cout << "Yes\n";
            }else {
                cout << "No\n";
            }
        }
        
    }
    return 0;
}



