#include <iostream>
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
using namespace std;

DWORD getPID(const wstring& pName)
{
	DWORD pID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pEntry;
		pEntry.dwSize = sizeof(pEntry);
		if (Process32First(hSnap, &pEntry))
		{
			do
			{
				if (!pName.compare(pEntry.szExeFile))
				{
					
					pID = pEntry.th32ProcessID;
					break;
				}
				
			} while (Process32Next(hSnap, &pEntry));
		}
	}
		CloseHandle(hSnap);
		return pID;
}

int main()
{
	const char* dllPath = "D:\\BC-training\\Dll1\\x64\\Debug";
	const wstring pName = L"cmd.exe";
	DWORD pID = 0;
	while (!pID)
	{
		
		pID = getPID(pName);
		std::cout << pID;
		Sleep(30);
	}
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pID);
	if (hProc && hProc != INVALID_HANDLE_VALUE)
	{
		void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc,0,0);
		std::cout << "done";
		if (hThread)
		{
			CloseHandle(hThread);
		}
	}
	if (hProc)
	{
		CloseHandle(hProc);
	}
	return 0;
}