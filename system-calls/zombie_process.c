#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

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
        printf("Child process: PID = %d\n", getpid());
        exit(0); // Child process exits immediately
    }
    else
    {
        printf("Parent process: PID = %d\n", getpid());
        printf("Child process created: PID = %d\n", pid);

        // Sleep to keep the parent process alive
        sleep(30);
        wait(NULL);
    }
}
