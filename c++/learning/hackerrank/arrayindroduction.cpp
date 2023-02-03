#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int len_arr;
    scanf("%d\n",&len_arr);
    int input_arr[len_arr];
    
    for(int i = 0; i < len_arr;i++){
        cin >> input_arr[i];
    }
    
    for(int i = len_arr;i>0;i--){
        cout << input_arr[i-1] << " ";
    }
       
    return 0;
}
