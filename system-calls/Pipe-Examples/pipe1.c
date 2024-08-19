#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define MAX 100

int main()
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }

    char s1[MAX] = "HELLO FROM PARENT", s2[MAX];

    // When we use fork in any process, file descriptors remain open across child process and also parent process. Calling fork after creating a pipe, then the parent and child can communicate via the pipe.
    pid_t pid = fork();

    /* fd[1] is for writing to pipe
     * fd[0] is for reading from pipe
     */

    if (pid < 0)
    {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        close(fd[1]);
        read(fd[0], s2, sizeof(s2));
        close(fd[0]);
        printf("Child --> %s\n", s2);
    }
    else
    {
        close(fd[0]);
        write(fd[1], s1, strlen(s1) + 1);
        close(fd[1]);
    }
}