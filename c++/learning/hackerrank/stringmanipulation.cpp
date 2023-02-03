#include <iostream>
#include <string>
using namespace std;

int main() {
	// Complete the program
    string in1;
    string in2;
    cin >> in1 >> in2;
    
    printf("%ld %ld\n",in1.size(),in2.size());
    
    string addet = in1 + in2;
    cout << addet << endl;
    
    //swap the first letters
    char temp;
    temp = in1[0];
    in1[0] = in2[0];
    in2[0] = temp;
    
    //swaping the last
    temp = in1[in1.size()];
    in1[in1.size()] = in2[in2.size()];
    in2[in2.size()] = temp;
    cout << in1 << " " << in2;
    
    return 0;
}