#include <stdio.h>
#include <Windows.h>
#include <clocale>

bool printFileText(LPWSTR FileName)
{
    HANDLE hFile = CreateFileW(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        return false;
    }

    PLARGE_INTEGER fileSize = new LARGE_INTEGER();

    if (!GetFileSizeEx(hFile, fileSize))
    {
        CloseHandle(hFile);
        return false;
    }

    char* buf = new char[fileSize->QuadPart];

    if (!ReadFile(hFile, buf, fileSize->QuadPart, NULL, NULL))
    {
        CloseHandle(hFile);
        return false;
    }

    buf[fileSize->QuadPart] = '\0';
    printf("File content:\n");
    printf("%s\n", buf);

    CloseHandle(hFile);

    return true;
}

bool insRowFileText(LPWSTR FileName, LPWSTR Str, int Row)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int bufPosition = 0;

    HANDLE hFile = CreateFileW(FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        return false;
    }

    if (!GetFileSizeEx(hFile, fileSize))
    {
        CloseHandle(hFile);
        return false;
    }

    char* buf = new char[fileSize->QuadPart + 1];
    char* bufAfterIns = new char[fileSize->QuadPart + wcslen(Str) + 1];
    
    DWORD n = NULL;

    if (!ReadFile(hFile, buf, fileSize->QuadPart, &n, NULL))
    {
        CloseHandle(hFile);
        return false;
    }

    if (Row < -1)
    {
        CloseHandle(hFile);
        return false;
    }
    
    switch (Row)
    {
        case -1:
            for (int i = 0; i < n; i++)
            {
                bufAfterIns[bufPosition] = buf[i];
                bufPosition++;
            }

            n += wcslen(Str) + 1;
            bufAfterIns[bufPosition] = '\n';
            bufPosition++;

            for (int i = bufPosition, j = 0; i < n; i++, j++)
            {
                bufAfterIns[bufPosition] = Str[j];
                bufPosition++;
            }
            bufAfterIns[bufPosition] = '\0';
            break;
        case 0:
            for (int i = 0; i < wcslen(Str); i++)
            {
                bufAfterIns[bufPosition] = Str[i];
                bufPosition++;
            }

            n += wcslen(Str) + 1;
            bufAfterIns[bufPosition] = '\n';
            bufPosition++;

            for (int i = bufPosition, j = 0; i < n; i++, j++)
            {
                bufAfterIns[bufPosition] = buf[j];
                bufPosition++;
            }
            bufAfterIns[bufPosition] = '\0';
            break;
        default:
            int rowCount = 0;
            for (int i = 0; i < n; i++)
            {
                if (buf[i] == '\n')
                {
                    rowCount++;
                }
            }
            int plusRows = rowCount < Row ? Row - rowCount - 1 : 0;
            plusRows = plusRows < 0 ? 1 : plusRows;
            bufAfterIns = new char[strlen(buf) + wcslen(Str) + plusRows + 2];

            if (plusRows >= 1)
            {
                for (int i = 0; i < n; i++)
                {
                    bufAfterIns[bufPosition] = buf[i];
                    bufPosition++;
                }
                for (int i = 0; i < plusRows; i++)
                {
                    bufAfterIns[bufPosition] = '\n';
                    bufPosition++;
                }

                n += wcslen(Str) + 1 + plusRows;

                for (int i = bufPosition, j = 0; i < n; i++, j++)
                {
                    bufAfterIns[i] = Str[j];
                    bufPosition++;
                }
            }
            else 
            {
                bool rowFound = false;
                int currentRow = 1;

                for (int i = 0; i < n; i++)
                {
                    if (currentRow == Row && rowFound == false)
                    {
                        rowFound = true;
                        int j = 0;
                        while (j < wcslen(Str))
                        {
                            bufAfterIns[bufPosition] = Str[j];
                            bufPosition++;
                            j++;
                        }

                        if ((buf[i] == '\n' && buf[i + 1] == '\n') || (buf[i] == '\n' && buf[i + 1] != '\n'))
                        {
                            continue;
                        }
                        
                        if (buf[i] != '\n' && buf[i + 1] != '\n') {
                            bufAfterIns[bufPosition] = '\n';
                            bufPosition++;
                        }
                    } 

                    if (buf[i] == '\n')
                    {
                        currentRow++;
                    }

                    bufAfterIns[bufPosition] = buf[i];
                    bufPosition++;
                }
            }
            break;
    }


    CloseHandle(hFile);

    hFile = CreateFileW(FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        return false;
    }

    if (WriteFile(hFile, bufAfterIns, strlen(bufAfterIns), NULL, NULL) == FALSE)
    {
        CloseHandle(hFile);
        return false;
    }

    if (SetEndOfFile(hFile) == FALSE)
    {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);

    return true;
}

int main()
{
    setlocale(LC_ALL, ".UTF8");

    LPWSTR fileName = (LPWSTR)L"os09_01.txt";

    printFileText(fileName);
    insRowFileText(fileName, (LPWSTR)L"new row 0", 0);
    insRowFileText(fileName, (LPWSTR)L"new row -1", -1);
    insRowFileText(fileName, (LPWSTR)L"new row 15", 15);
    printFileText(fileName);

    return 0;
}