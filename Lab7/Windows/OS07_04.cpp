#include <stdio.h>
#include <ctime>
#include <Windows.h>

#define SECOND 10000000

int main()
{
    HANDLE timer = CreateWaitableTimerA(NULL, FALSE, "TIMER");
    long long startTime = -60 * SECOND;

    LPCSTR filePath = "os07_04_X.exe";
    STARTUPINFO startupInfoFirst;
    STARTUPINFO startupInfoSecond;

    PROCESS_INFORMATION processInfoFirst;
    PROCESS_INFORMATION processInfoSecond;

    ZeroMemory(&startupInfoFirst, sizeof(STARTUPINFO));
    ZeroMemory(&startupInfoSecond, sizeof(STARTUPINFO));

    ZeroMemory(&processInfoFirst, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&processInfoSecond, sizeof(PROCESS_INFORMATION));

    startupInfoFirst.cb = sizeof(STARTUPINFO);
    startupInfoSecond.cb = sizeof(STARTUPINFO);

    if (!SetWaitableTimer(timer, (LARGE_INTEGER*)&startTime, 60000, NULL, NULL, FALSE))
    {
        throw "SetWaitableTimer Error";
    }

    if (!CreateProcessA(filePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfoFirst, &processInfoFirst))
    {
        throw "First process creation error";
    }

    if (!CreateProcessA(filePath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfoSecond, &processInfoSecond))
    {
        throw "First process creation error";
    }

    WaitForSingleObject(processInfoFirst.hProcess, INFINITE);
    WaitForSingleObject(processInfoSecond.hProcess, INFINITE);

    CloseHandle(processInfoFirst.hProcess);
    CloseHandle(processInfoSecond.hProcess);

    CloseHandle(timer);

    return 0;
}