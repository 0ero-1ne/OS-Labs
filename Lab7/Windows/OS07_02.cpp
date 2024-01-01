#include <stdio.h>
#include <ctime>

int main()
{
    int counter = 0, is5 = 0, is10 = 0;
    clock_t start = clock();
    
    for (;;)
    {
        counter++;
        if (is5 == 0 && (double)(clock() - start) / CLOCKS_PER_SEC == 5.000)
        {
            printf("5 seconds - %d iterations\n", counter);
            is5 = 1;
        }
        else if (is10 == 0 && (double)(clock() - start) / CLOCKS_PER_SEC == 10.000)
        {
            printf("10 seconds - %d iterations\n", counter);
            is10 = 1;
        }
        else if((double)(clock() - start) / CLOCKS_PER_SEC == 15.000)
        {
            break;
        }
    }

    printf("15 seconds - %d iterations", counter);

    return 0;
}