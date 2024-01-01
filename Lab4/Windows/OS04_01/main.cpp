#include <iostream>
#include <thread>
#include <process.h>
#include <Windows.h>

int main()
{
    DWORD process_id = GetCurrentProcessId();
    DWORD thread_id = GetCurrentThreadId();

    std::cout << "i\tPID\tTID\n";
    std::cout << "-----\t-----\t-----\n";

    for (int i = 0; i < 1000; i++)
    {
        std::cout << i << "\t" << process_id << "\t" << thread_id << std::endl;
        Sleep(1000);
    }

	return 0;
}