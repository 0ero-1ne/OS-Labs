#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("OS03_05_1 started\n");
    for (int i = 0; i < 50; i++)
    {
        printf("OS03_05_1: %d - %d\n", i, getpid());
        sleep(1);
    }
    printf("OS03_05_1 completed the work\n");

    return 0;
}