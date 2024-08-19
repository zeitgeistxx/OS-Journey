#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t child_pid = fork();

    // Negative: Child process creation failed
    // Zero: Return to newly created Child Process
    // Positive: Return to parent process, with process ID of child process

    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(1);
    }
    else if (child_pid == 0)
    {
        printf("Child --> PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent --> PID = %d,Parent PID = %d\n", getpid(), getppid());
        printf("New Child = %d\n", child_pid);
    }
}