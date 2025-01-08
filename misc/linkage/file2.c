#include <stdio.h>

// Declare the global variable and function defined in another file
extern int externalVariable;
extern void externalFunction();

void anotherFunction() {
    printf("Another Function: externalVariable before = %d\n", externalVariable);
    externalVariable += 10;
    externalFunction();
}
