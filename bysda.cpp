#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

int main()
{
    // CreateFileMapping to generate unique key
    HANDLE hMapFile;
    LPCSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        1024,                    // maximum object size (low-order DWORD)
        "shmfile");              // name of the mapping object

    // MapViewOfFile to attach to shared memory
    pBuf = (LPCSTR) MapViewOfFile(
        hMapFile,          // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        1024);

    cout << "Write Data : ";
    gets((char*)pBuf);

    printf("Data written in memory: %s\n", pBuf);

    // UnmapViewOfFile to detach from shared memory
    UnmapViewOfFile(pBuf);

    // CloseHandle to close the file mapping object
    CloseHandle(hMapFile);

    return 0;
}
