#include <iostream>
int main() {
    int result;
    __asm__(
   "movl $9, %%eax;"
"movl $10, %%ebx;"
"imull %%ebx, %%eax;"
"movl %%eax, %%eax;"
"movl $9, %%ebx;"
"xorl %%edx, %%edx;"
"idivl %%eax;"
"movl $2, %%eax;"
"movl $2, %%ebx;"
"addl %%ebx, %%eax;"
"movl $8, %%eax;"
"movl %%eax, %%ebx;"
"sub %%ebx, %%eax;"
"movl %%eax, %%eax;"
"movl %%eax, %%ebx;"
"addl %%ebx, %%eax;"
        : "=a" (result)
    );
    std::cout << result;
    return 0;
}
