#include <iostream>
int main() {
    int result;
    __asm__(
   "movl $10, %%eax;"
"movl $8, %%ebx;"
"imull %%ebx, %%eax;"
"movl $100, %%eax;"
"movl %eax, %%ebx;"
"sub %%ebx, %%eax;"
        : "=a" (result)
    );
    std::cout << result;
    return 0;
}
