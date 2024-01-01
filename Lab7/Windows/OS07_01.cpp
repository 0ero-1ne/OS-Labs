#include <ctime>
#include <stdio.h>

int main()
{
    time_t timestamp;
    timestamp = time(&timestamp);

    tm lt;
    localtime_s(&lt, &timestamp);

    printf("%d.%d.%d %d:%d:%d", lt.tm_mday, lt.tm_mon + 1, lt.tm_year, lt.tm_hour, lt.tm_min, lt.tm_sec);

    return 0;
}