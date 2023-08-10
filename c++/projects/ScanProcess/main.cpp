#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>



void EnumerateProcesses() {
    // Take a snapshot of all processes in the system.
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to take a snapshot of processes." << std::endl;
        return;
    }

    // Set the size of the structure before using it.
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process, and exit if unsuccessful.
    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Failed to get the first process." << std::endl;
        CloseHandle(hProcessSnap);
        return;
    }

    // Now walk the snapshot of processes and display information about each one.
    do {
        std::wcout << L"Process Name: " << pe32.szExeFile << L", PID: " << pe32.th32ProcessID << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

int main()
{
    EnumerateProcesses();
    return 0;
}

