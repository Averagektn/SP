// DLLInjection.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <iostream>

#define DLL_NAME "C:\Archive\5 semester\SP\lab3\StringReplacer\x64\Debug\StringReplacer.dll"

BOOL InjectDll(int pid);

int main()
{
	int pid;

	printf("Enter the process id:\n");
	scanf_s("%d", &pid);

	InjectDll(pid);

	getchar();
	getchar();

	return 0;
}

BOOL InjectDll(int pid)
{
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (process == NULL)
	{
		std::cout << "Error: Cannot open the process.\n";
		return false;
	}

	LPVOID funcPointer = (LPVOID)GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");
	if (funcPointer == NULL)
	{
		return false;
	}

	LPVOID alloc = VirtualAllocEx(process, 0, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (alloc == NULL)
	{
		return false;
	}

	if (!WriteProcessMemory(process, alloc, DLL_NAME, strlen(DLL_NAME), NULL))
	{
		return false;
	}

	HANDLE remoteThread = CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)funcPointer, (LPVOID)alloc, 0, 0);
	if (remoteThread == NULL)
	{
		return false;
	}

	std::cout << "Injected\n";

	CloseHandle(remoteThread);


	return true;
}
