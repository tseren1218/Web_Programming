#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define BUF_SIZE 256
#define SHARED_MEM_NAME TEXT("MySharedMem")

int _tmain(int argc, _TCHAR* argv[]) 
{
    HANDLE hMapFile;
    LPCTSTR pBuf;gcc
    TCHAR szMsg[BUF_SIZE];

    if (argc < 2) {
        _tprintf(TEXT("Usage: %s <message>\n"), argv[0]);
        return 1;
    }

    // Create a named shared memory object
    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, SHARED_MEM_NAME);
    if (hMapFile == NULL) {
        _tprintf(TEXT("Could not create file mapping object (%d)\n"), GetLastError());
        return 1;
    }

    // Map the shared memory object into the process's address space
    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
    if (pBuf == NULL) {
        _tprintf(TEXT("Could not map view of file (%d)\n"), GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }/

    // Write data to the shared memory
    _stprintf_s((LPTSTR)pBuf, BUF_SIZE, TEXT("%s"), argv[1]);

    _tprintf(TEXT("Press <ENTER> to read from shared memory..."));
    getchar();

    // Read data from the shared memory
    _stprintf_s(szMsg, BUF_SIZE, TEXT("%s"), (LPTSTR)pBuf);
    _tprintf(TEXT("Received: %s\n"), szMsg);

    // Unmap the shared memory from the process's address space
    UnmapViewOfFile(pBuf);

    // Close the shared memory object
    CloseHandle(hMapFile);

    return 0;
}


/*
cd C:\Users\DELL\Documents\GitHub\Web_Programming

shared_mem.exe

*/