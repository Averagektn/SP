// DLLInjection.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <iostream>

#define DLL_NAME "C:\Archive\5 semester\SP\lab3\StringReplacer\x64\Debug\StringReplacer.dll"

BOOL InjectSearchProcessingDll(int pid);

int main()
{
	int pid;

	printf("Enter the process id:\n");
	scanf_s("%d", &pid);

	InjectSearchProcessingDll(pid);

	getchar();
	getchar();

	return 0;
}

BOOL InjectSearchProcessingDll(int pid)
{
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	LPVOID funcPointer = (LPVOID)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");

	LPVOID alloc = VirtualAllocEx(process, 0, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!WriteProcessMemory(process, alloc, DLL_NAME, strlen(DLL_NAME), NULL))
	{
		std::cout << "Error: Cannot write to the virtual memory of the process.\n";
		return false;
	}

	HANDLE remoteThread = CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)funcPointer, (LPVOID)alloc, 0, 0);

	std::cout << "Dll was successfully injected.\n";
	WaitForSingleObject(remoteThread, INFINITE);
	CloseHandle(remoteThread);

	return true;
}