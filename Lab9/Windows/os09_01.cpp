#include <stdio.h>
#include <Windows.h>
#include <clocale>

BOOL printFIleInfo(LPWSTR FileName)
{
    HANDLE hFile = CreateFileW(FileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    DWORD bytes = NULL;
    char buf[1024];

    ZeroMemory(buf, sizeof(buf));
    
    LPBY_HANDLE_FILE_INFORMATION fileInfo = new BY_HANDLE_FILE_INFORMATION();
    LPSYSTEMTIME creationTime = new SYSTEMTIME();
    LPSYSTEMTIME updatingTime = new SYSTEMTIME();
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    DWORD fileType = NULL;
    fileType = GetFileType(hFile);
    
    if (!GetFileInformationByHandle(hFile, fileInfo))
    {
        CloseHandle(hFile);
        return false;
    }

    if (fileType == NULL)
    {
        CloseHandle(hFile);
        return false;   
    }

    if (!GetFileSizeEx(hFile, fileSize))
    {
        CloseHandle(hFile);
        return false;
    }
    
    printf("File name: %ls\n", FileName);

    if (
        FileTimeToSystemTime(&fileInfo->ftCreationTime, creationTime) &&
        FileTimeToSystemTime(&fileInfo->ftLastWriteTime, updatingTime)
    ) {
        printf("Creation time: %u.%u.%u %u:%u:%u \n", creationTime->wDay, creationTime->wMonth, creationTime->wDay, creationTime->wHour, creationTime->wMinute, creationTime->wSecond);
        printf("Last write time: %u.%u.%u %u:%u:%u \n", updatingTime->wDay, updatingTime->wMonth, updatingTime->wDay, updatingTime->wHour, updatingTime->wMinute, updatingTime->wSecond);
    }

    printf("File type: ");
    switch (fileType)
    {
        case FILE_TYPE_CHAR:
            printf("%s\n", "TYPE_CHAR");
            break;
        case FILE_TYPE_DISK:
            printf("%s\n", "TYPE_DISK");
            break;
        case FILE_TYPE_PIPE:
            printf("%s\n", "TYPE_PIPE");
            break;
        case FILE_TYPE_REMOTE:
            printf("%s\n", "TYPE_REMOTE");
            break;
        case FILE_TYPE_UNKNOWN:
            printf("%s\n", "TYPE_UNKNOWN");
            break;
        default:
            printf("%s\n", "ERROR");
            break;
    }

    printf("File size: %lld\n", fileSize->QuadPart);

    CloseHandle(hFile);

    return true;
}

BOOL printFileText(LPWSTR FileName)
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
    printf("\nFile content:\n");
    printf("%s\n", buf);

    CloseHandle(hFile);

    return true;
}

int main()
{
    setlocale(LC_ALL, ".UTF8");
    printFIleInfo(L"os09_01.txt");
    printFileText(L"os09_01.txt");
    return 0;
}