#include <stdio.h>

// Define a global variable with external linkage
int externalVariable = 14;

// Define a function with external linkage
void externalFunction()
{
    printf("External Function Called! externalVariable = %d\n", externalVariable);
}
