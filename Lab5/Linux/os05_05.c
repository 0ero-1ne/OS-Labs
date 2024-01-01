#include <stdio.h>
#include <unistd.h>

int main()
{
    for (int i = 0; i < 1000; i++)
    {
        printf("%d - %d - %d\n", getpid(), i, nice(0));
        sleep(1);
    }

    return 0;
}