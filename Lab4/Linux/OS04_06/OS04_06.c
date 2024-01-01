#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("OS04_06 started\n");
    
    for (int i = 0; i < 1000; i++) {
        printf("%d : %d\n", i, getpid());
        sleep(1);
    }

    printf("OS04_06 completed the work\n");

    return 0;
}