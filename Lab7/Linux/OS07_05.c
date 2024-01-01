#include <stdio.h>
#include <time.h>

int main()
{
    time_t timestamp;
    timestamp = time(&timestamp);

    struct tm *lt;
    lt = localtime(&timestamp);

    printf("%d.%d.%d %d:%d:%d\n", lt->tm_mday, lt->tm_mon + 1, lt->tm_year, lt->tm_hour, lt->tm_min, lt->tm_sec);

    return 0;
}