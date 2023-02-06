#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

bool if_val_inside(string key,map<string,int> m){
    
    map<string,int>::iterator itr=m.find(key);
    if(itr != m.end()){
        return true;
    }else{
        return false;
    }
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int query_size;
    cin >> query_size;
    map<string,int> MyMap;
    for(int i = 0;i<query_size;i++){
        int query;
        cin >> query;
        if(query == 1){
            string key;
            int mark;
            cin >> key >> mark;
            MyMap[key] += mark;
        }else if(query == 2){
            string key;
            cin >> key;
            MyMap.erase(key);
        }else if(query == 3){
            string key;
            cin >> key;
            if(if_val_inside(key, MyMap)){
                cout << MyMap[key] << "\n";
            }else{
                cout << "0\n";
            }
        }
    }
    return 0;
}
