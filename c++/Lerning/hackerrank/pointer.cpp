#include <stdio.h>
#include <iostream>
#include <climits>
#include <cstdlib>



void update(int *a,int *b) {
    // Complete this function
    int a_strich = *a + *b;
    int b_strich = std::abs(*a-*b);
    *a = a_strich;
    *b = b_strich;
}
int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
