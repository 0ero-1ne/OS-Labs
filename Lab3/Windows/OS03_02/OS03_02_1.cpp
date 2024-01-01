#include <iostream>
#include <process.h>
#include <windows.h>

int main()
{
    for (int i = 0; i < 50; i++)
    {
        std::cout << "OS03_02_1: " << i << " - " << _getpid() << std::endl;
        Sleep(1000);
    }

    return 0;
}