#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define MAX 100

int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main()
{
    pid_t pid;
    int fd[2];

    pipe(fd);

    pid = fork();

    if (pid == 0)
    {
        printf("Child Process\n");
        close(fd[1]);
        read(fd[0], &n2, sizeof(int));
        close(fd[0]);
        printf("n2 = %d\n", n2);
    }
    else
    {
        close(fd[0]);
        write(fd[1], &n1, sizeof(int));
        close(fd[1]);
    }
}