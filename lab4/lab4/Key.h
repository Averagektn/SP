#pragma once
#include <Windows.h>
#include <iostream>

class Key
{
public:
	Key(HKEY hKey, LPCWSTR lpSubKey);

	bool ReadFlags(LPCWSTR lpValueName);
	bool AddValue(LPCWSTR valueName, DWORD type, const BYTE* data, DWORD size);
	bool Save();
	HKEY GetKey();

	static HKEY Open(HKEY hKey, LPCWSTR lpSubKey);
	static bool Find(HKEY hKey, LPCWSTR lpSubKey);
private:
	HKEY key;
	LPCWSTR subKey;
	void PrintType(DWORD type);
};

