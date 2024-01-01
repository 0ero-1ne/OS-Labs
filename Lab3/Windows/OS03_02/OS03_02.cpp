#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <process.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION piOne;
    PROCESS_INFORMATION piTwo;

    BOOL bProcess;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&piOne, sizeof(piOne));
    ZeroMemory(&piTwo, sizeof(piTwo));

    bProcess = CreateProcess(
        "OS03_02_1.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &piOne
    );

    if (bProcess == FALSE)
    {
        std::cout << "Create process failed -> " << GetLastError() << std::endl;
        return -1;
    }
    std::cout << "Process OS03_02_1 created\n";

    bProcess = CreateProcess(
        "OS03_02_2.exe",
        NULL,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &piTwo
    );

    if (bProcess == FALSE)
    {
        std::cout << "Create process failed -> " << GetLastError() << std::endl;
        return -1;
    }
    std::cout << "Process OS03_02_2 created\n";

    for (int i = 0; i < 100; i++)
    {
        std::cout << "OS03_02: " << i << " - " << _getpid() << std::endl;
        Sleep(1000);
    }

    WaitForSingleObject(piOne.hProcess, INFINITE);
    WaitForSingleObject(piTwo.hProcess, INFINITE);
    CloseHandle(piOne.hProcess);
    CloseHandle(piOne.hThread);
    CloseHandle(piTwo.hProcess);
    CloseHandle(piTwo.hThread);
    std::cout << "Process OS03_02_1 ended\n";
    std::cout << "Process OS03_02_2 ended\n";

    return 0;
}