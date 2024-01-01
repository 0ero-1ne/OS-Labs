#include <iostream>
#include <Windows.h>

int check;

void InCriticalSection()
{
    _asm
    {
        CriticalSection:
            lock bts check, 0;
            jc CriticalSection
    }
}

void OutCriticalSection()
{
    _asm
    {
        _asm lock btr check, 0
    }
}

DWORD WINAPI ChildThread()
{
    InCriticalSection();
    for (short i = 0; i < 100; i++)
    {
        std::cout << "OS06_01_THREAD: " << i << std::endl;
        Sleep(40);
    }
    OutCriticalSection();

    return 0;
}



int main()
{
    DWORD ChildId = NULL;
    HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &ChildId);

    InCriticalSection();

    for (short i = 0; i < 100; i++)
    {
        std::cout << "OS06_01: " << i << std::endl;
        Sleep(40);
    }

    OutCriticalSection();

    WaitForSingleObject(hChild, INFINITE);
    CloseHandle(hChild);

    system("pause");
    return 0;
}