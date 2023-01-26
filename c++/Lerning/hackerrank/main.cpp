#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int input_n_q[2];
    scanf("%d %d\n",&input_n_q[0],&input_n_q[1]);
    
    //scan the input lists
    vector<int*> indeces;
    for(int i = 0;i<input_n_q[0];i++){ 
        int len_in;
        scanf("%d ",&len_in);
        int 
        int *p_input = &input_list;
        for(int j = 0;j<len_in; j++){
            int temp;
            scanf("%d ",&temp);
            indeces[i][j] = temp;
        }
        scanf("\n");
    }
    cout << indeces[0][0];
    
       
    return 0;
}