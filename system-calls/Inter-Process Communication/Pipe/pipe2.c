#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main()
{
    int fd[2], buffer[2];

    if (pipe(fd) == -1)
    {
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        int n;
        printf("Enter a number to calculate factorial -> ");
        scanf("%d", &n);

        buffer[0] = n, buffer[1] = factorial(n);

        close(fd[0]);
        write(fd[1], buffer, sizeof(buffer));

        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));

        printf("Factorial of %d = %d\n", buffer[0], buffer[1]);

        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {
            printf("Child Process executed successfully.\n");
        }
    }
}