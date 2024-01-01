#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <iomanip>

int main()
{
    while (true)
    {
        std::cout << "Tasklist\n\n";
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

        PROCESSENTRY32 peProcessEntry;
        peProcessEntry.dwSize = sizeof(PROCESSENTRY32);

        try
        {
            if (!Process32First(snap, &peProcessEntry))
			    throw "Process32First";
            do
            {
                std::cout << std::setw(50) << std::left << peProcessEntry.szExeFile << peProcessEntry.th32ProcessID << "\n";
            } while (Process32Next(snap, &peProcessEntry));
            
        }
        catch (char* message)
        {
            std::cout << "Error: " << message << std::endl;
        }

        Sleep(3000);
        system("cls");
    }

    return 0;
}