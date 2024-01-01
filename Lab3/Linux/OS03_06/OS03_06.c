#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t child_process = fork();

    if (child_process == 0) {
        system("./../OS03_05/OS03_05_1");
    }
    else if (child_process > 0) {
        printf("OS03_06 started\n");
        for (int i = 0; i < 100; i++)
        {
            printf("OS03_06: %d - %d\n", i, getpid());
            sleep(1);
        }

        printf("OS03_06 complete the work\n");
    }
    else {
        perror("Create fork failed");
        return -1;
    }

    return 0;    
}
