#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // change to the "/" directory
    int nochdir = 0;

    // redirect standard input, output and error to /dev/null
    // this is equivalent to "closing the file descriptors"
    int noclose = 0;

    //  system("sh abc.sh");

    // glibc call to daemonize this process without a double fork
    if (daemon(nochdir, noclose))
    {
        // this block is executed if process cant be daemonised
        perror("daemon");
    }

    // our process is now a daemon!
    // while (1)
    // {

    // }
    sleep(60);

    return 0;
}