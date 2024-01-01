#include <iostream>
#include <process.h>
#include <windows.h>

int main()
{
    for (int i = 0; i < 1000; i++)
    {
        std::cout << i << " - " << _getpid() << std::endl;
        Sleep(1000);
    }

    return 0;
}