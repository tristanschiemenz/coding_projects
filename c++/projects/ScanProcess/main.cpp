#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <cstring>


const int BUFFER_SIZE = 0x10000;  // 64KB, larger buffer size

struct MemoryEntry {
    LPVOID address;
    std::vector<BYTE> valueBytes; // can store values of varying byte lengths
};

std::vector<MemoryEntry> AdressesValues;
std::mutex vecMutex;  // For thread-safety when accessing AdressesValues


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



void accessMemoryRegion(HANDLE processHandle, LPVOID startAddress, LPVOID endAddress) {
    MEMORY_BASIC_INFORMATION memInfo;
    LPVOID currentAddress = startAddress;

    while(currentAddress < endAddress && VirtualQueryEx(processHandle, currentAddress, &memInfo, sizeof(memInfo))) {
        if (memInfo.State == MEM_COMMIT && (memInfo.Protect & PAGE_READWRITE) && !(memInfo.Protect & PAGE_GUARD)) {
            BYTE buffer[BUFFER_SIZE];
            SIZE_T bytesRead;

            if (ReadProcessMemory(processHandle, currentAddress, buffer, sizeof(buffer), &bytesRead)) {
                std::lock_guard<std::mutex> lock(vecMutex);
                for (SIZE_T i = 0; i < bytesRead; i++) {
                    MemoryEntry entry;
                    entry.address = (LPVOID)((uintptr_t)currentAddress + i);
                    entry.valueBytes.push_back(buffer[i]);  // Assuming buffer holds BYTE value
                    AdressesValues.push_back(entry);
                }
            }
        }
        currentAddress = (LPVOID)((uintptr_t)currentAddress + memInfo.RegionSize);
    }
}
void accessMemory(HANDLE processHandle) {
    const int NUM_THREADS = 4; // Adjust as per the system
    LPVOID maxAddress = (LPVOID)0x7FFFFFFFFFFFFFFF;
    uintptr_t chunkSize = (uintptr_t)maxAddress / NUM_THREADS;
    
    std::vector<std::thread> threads;

    for(int i = 0; i < NUM_THREADS; i++) {
        LPVOID startAddress = (LPVOID)(i * chunkSize);
        LPVOID endAddress = (LPVOID)((i+1) * chunkSize);

        threads.push_back(std::thread(accessMemoryRegion, processHandle, startAddress, endAddress));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

template <typename T>
std::vector<BYTE> toBytes(T value) {
    std::vector<BYTE> result(sizeof(T));
    memcpy(result.data(), &value, sizeof(T));
    return result;
}

template <typename T>
void searchSteps(std::vector<MemoryEntry> searchList) {
    std::cout << "\n What Data you are searching for?";
    T selData;
    std::cin >> selData;

    std::vector<BYTE> searchBytes = toBytes(selData);

    std::vector<MemoryEntry> FoundList;

    for (int i = 0; i < searchList.size(); i++) {
        if (memcmp(searchList[i].valueBytes.data(), searchBytes.data(), searchBytes.size()) == 0) {
            std::cout << i << ". (+)  at  " << searchList[i].address << std::endl;
            FoundList.push_back(searchList[i]);
        }
    }

    std::cout << "1: Next Searching --- 2: Edit Value --- 3.New Scan\n";
    int ModeChoice;
    std::cin >> ModeChoice;
    switch (ModeChoice) {
    case 1:
        searchSteps<T>(FoundList);
        break;
    case 2:
        //EditValue()
        break;
    case 3:
        break;
    default:
        break;
    }
}

int main()
{
    EnumerateProcesses();
    int selPID;
    std::cout << "\n Select the PID:";
    std::cin >> selPID;
    DWORD dPID = selPID;

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dPID);
    accessMemory(processHandle);

    searchSteps<int>(AdressesValues);


    return 0;
}

