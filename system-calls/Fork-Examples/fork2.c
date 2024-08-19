#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    int x = 100;
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(1);
    }
    else if (child_pid == 0)
    {
        printf("Child Process\n");
        x = 200;
        printf("x = %d\n", x);
    }
    else
    {
        sleep(1);
        printf("Parent Process\n");
        printf("x = %d\n", x);
    }
}


// Proof of seperate address space.
// Copy-On-Write(COW)