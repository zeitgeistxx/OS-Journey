#include <stdio.h>
#include <time.h>

int main()
{
    printf("Program running...\n");

    time_t start_time, current_time;

    time(&start_time);

    do
    {
        time(&current_time);
    } while (difftime(current_time, start_time) < 10.0);

    printf("Program executed for 10sec\n");
}