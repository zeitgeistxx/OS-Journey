#include <stdio.h>

#ifndef ARG1
#define ARG1 10
#endif

#ifndef ARG2
#define ARG2 20
#endif

int main() {
    int a = ARG1;
    int b = ARG2;
    int sum = a + b;

    printf("Sum of %d and %d is %d\n", a, b, sum);
    return 0;
}

// gcc -DARG1=30 -DARG2=40 -o myprogram test.c
