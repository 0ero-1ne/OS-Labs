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

bool delRowFileTxt(LPWSTR FileName, DWORD Row)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    int rowCount = 1;
    int position = 0;
    int bufPosition = 0;
    bool rowFound = false;

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
    char* bufAfterDel = new char[fileSize->QuadPart + 1];
    
    DWORD n = NULL;

    if (!ReadFile(hFile, buf, fileSize->QuadPart, &n, NULL))
    {
        CloseHandle(hFile);
        return false;
    }

    buf[n] = '\0';

    for (int i = 0; i < n; i++)
    {
        if (rowCount == Row)
        {
            rowFound = true;
            if (buf[i] != '\n' && buf[i] != '\0')
            {
                continue;
            }
        }

        if (buf[i] == '\n')
        {
            rowCount++;
            if (rowFound && (rowCount - 1 == Row))
            {
                continue;
            }
        }

        bufAfterDel[bufPosition] = buf[i];
        bufPosition++;
    }

    if (bufAfterDel[bufPosition - 1] == '\n')
    {
        bufAfterDel[bufPosition - 1] = '\0';
    }

    if (rowFound == false)
    {
        CloseHandle(hFile);
        return false;
    }

    CloseHandle(hFile);

    hFile = CreateFileW(FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hFile);
        return false;
    }

    if (WriteFile(hFile, bufAfterDel, strlen(bufAfterDel), NULL, NULL) == FALSE)
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

    delRowFileTxt(fileName, 15);

    printFileText(fileName);

    return 0;
}