#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        sleep(5);
        printf("Child --> PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent --> PID = %d, Child PID = %d\n", getpid(), pid);
        exit(0); // Parent process exits immediately, leaving the child as an orphan
    }
}
