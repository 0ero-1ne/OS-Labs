#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("OS03_04 started\n");
    for (int i = 0; i < 1000; i++)
    {
        printf("%d - %d\n", i, getpid());
        sleep(1);
    }
    printf("OS03_04 complete the work\n");

    return 0;
}