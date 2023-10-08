#include "framework.h"
#include "pch.h"
#include "StringReplacer.h"

#define MAX_READ 128

int fMatchCheck(wchar_t* mainstr, int mainstrLen, wchar_t* checkstr, int checkstrLen) {
    BOOL fmcret = TRUE;
    int x, y;

    for (x = 0; x < mainstrLen; x++) {
        fmcret = TRUE;

        for (y = 0; y < checkstrLen; y++) {
            if (checkstr[y] != mainstr[x + y]) {
                fmcret = FALSE;
                break;
            }
        }

        if (fmcret)
            return x + checkstrLen;
    }
    return -1;
}

void changeTextInProcces(wchar_t* lpOrig, int origSize, wchar_t* lpReplacement) {
    MessageBox(0, L"Started replacing", L"DLL", MB_OK);

    HANDLE hProc = GetCurrentProcess();
    MEMORY_BASIC_INFORMATION mbi;
    SYSTEM_INFO msi;
    ZeroMemory(&mbi, sizeof(mbi));
    GetSystemInfo(&msi);

    SIZE_T dwRead = 0;

    wchar_t* lpData = (wchar_t*)GlobalAlloc(GMEM_FIXED, MAX_READ);

    for (LPBYTE lpAddress = (LPBYTE)msi.lpMinimumApplicationAddress; lpAddress <= (LPBYTE)msi.lpMaximumApplicationAddress; lpAddress += mbi.RegionSize) {
        if (VirtualQuery(lpAddress, &mbi, sizeof(mbi))) {

            if ((mbi.Protect & PAGE_READWRITE) || (mbi.Protect & PAGE_WRITECOPY)) {
                for (LPBYTE tempLpAddress = lpAddress; tempLpAddress < (lpAddress + mbi.RegionSize); tempLpAddress += (MAX_READ - origSize * sizeof(wchar_t))) {
                    if (ReadProcessMemory(hProc,
                        (LPCVOID)tempLpAddress,
                        lpData,
                        MAX_READ, &
                        dwRead) == TRUE) {

                        LPBYTE sometemp = tempLpAddress;
                        if (fMatchCheck(lpData, dwRead / sizeof(wchar_t), lpOrig, origSize) != -1) {

                            wchar_t tempChar = lpOrig[0];
                            wchar_t cmpChar = sometemp[0];
                            while ((sometemp < (tempLpAddress + dwRead)) && (cmpChar != tempChar)) {
                                sometemp++;
                                cmpChar = sometemp[0];
                            }
                            if ((LPCVOID)sometemp == lpOrig) {
                                continue;
                            }

                            int test = WriteProcessMemory(hProc,
                                (LPVOID)sometemp,
                                lpReplacement,
                                origSize * sizeof(wchar_t), &
                                dwRead);
                            test = dwRead;
                        }
                    }
                }
            }
        }
    }

    if (lpData)
        GlobalFree(lpData);

    MessageBox(0, L"Replaced", L"DLL", MB_OK);
}