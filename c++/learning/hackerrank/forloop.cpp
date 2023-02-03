#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    // Complete the code.
    
    char number_name[10][10] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
    int number_name_len = *(&number_name + 1) - number_name;
    int start,end;
    scanf("%d\n%d",&start,&end);
    for(int i=start;i<=end;i++){
        if(i<=9){
            cout << number_name[i]<<endl;
        }else{
            if(i%2==0){
                cout << "even"<< endl;
            }else{
                cout << "odd" << endl;
            }
        }
    }
    return 0;
}
