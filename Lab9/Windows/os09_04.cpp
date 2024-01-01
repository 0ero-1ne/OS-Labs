#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctime>
#include <Windows.h>

#define DIR_PATH  L"C:/Univer/OS/Lab9/Windows/"

int rows = 0;

bool printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    LPWSTR path = (LPWSTR)DIR_PATH;

    HANDLE notif = FindFirstChangeNotificationW(path, false, FILE_NOTIFY_CHANGE_LAST_WRITE);
    
    clock_t t1 = clock();
    clock_t t2 = clock();
    
    DWORD dwWaitStatus;

    printf("Start watching:\n");

    while (true)
    {
        dwWaitStatus = WaitForSingleObject(notif, mlsec);
        switch (dwWaitStatus)
        {
        case WAIT_OBJECT_0:
        {
            if (FindNextChangeNotification(notif) == FALSE)
            {
                break;
            }
            else
            {
                int position = 0;
                int rowCount = 0;
                
                HANDLE hFile = CreateFileW(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                
                while (hFile == INVALID_HANDLE_VALUE)
                {
                    hFile = CreateFileW(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                }

                if (GetFileSizeEx(hFile, fileSize) == FALSE)
                {
                    CloseHandle(hFile);
                    return false;
                }

                char* buf = new char[(fileSize->QuadPart + 1) * sizeof(char)];
                ZeroMemory(buf, (fileSize->QuadPart + 1) * sizeof(char));
                DWORD n = NULL;

                if (ReadFile(hFile, buf, fileSize->QuadPart, &n, NULL) == FALSE)
                {
                    CloseHandle(hFile);
                    return false;
                }

                while (buf[position++] != '\0')
                {
                    if (buf[position] == '\n')
                    {
                        rowCount++;
                    }
                }

                rowCount = rowCount == 0 ? 0 : rowCount + 1;

                if (rows != rowCount)
                {
                    printf("Rows: %d\n", rowCount);
                    rows = rowCount;
                }
                CloseHandle(hFile);
            }
        }
        }
        t2 = clock();
        if (t2 - t1 > mlsec)
        {
            break;
        }
        
    }

    CloseHandle(notif);
    printf("Ended watch");

    return true;
}

int main()
{
    LPWSTR fileName = (LPWSTR)L"os09_01.txt";

    printWatchRowFileTxt(fileName, 30000);

    return 0;
}