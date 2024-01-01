#include <iostream>
#include <process.h>
#include <windows.h>

int main()
{
    for (int i = 0; i < 125; i++)
    {
        std::cout << "OS03_02_2: " << i << " - " << _getpid() << std::endl;
        Sleep(1000);
    }

    return 0;
}