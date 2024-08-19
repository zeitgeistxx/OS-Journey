#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(1);
    }
    else if (child_pid == 0)
    {
        printf("Child Process\n");
        sleep(5);
    }
    else
    {
        printf("Parent Process\n");
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {
            printf("Parent process: Child exited with status %d\n", WEXITSTATUS(status));
        }
    }
}