// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "StringReplacer.h"

wchar_t origin[] = L"orig";
wchar_t dest[] = L"dest";

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    // Perform actions based on the reason for calling.
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        changeTextInProcces(origin, ARRAYSIZE(origin) - 1, dest);
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
