#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define MAX 100

int main()
{
    pid_t pid;
    int fd[2];

    char s1[MAX] = "Hello pipe", s2[MAX];

    pipe(fd);

    // When we use fork in any process, file descriptors remain open across child process and also parent process. Calling fork after creating a pipe, then the parent and child can communicate via the pipe.
    pid = fork();

    if (pid == 0)
    {
        printf("Child Process\n");
        close(fd[1]);
        read(fd[0], s2, MAX);
        close(fd[0]);
        printf("s2 = %s\n", s2);
    }
    else
    {
        close(fd[0]);
        write(fd[1], s1, strlen(s1) + 1);
        close(fd[1]);
    }
}