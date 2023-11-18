#pragma once
#include <Windows.h>
#include <iostream>

class Key
{
public:
	// Initializes key by head directory name and subdirectory name
	Key(HKEY hKey, LPCWSTR lpSubKey);

	// Reads value of flag
	bool ReadFlags(LPCWSTR lpValueName);

	// Adds another value if it not exists or changes it
	bool AddValue(LPCWSTR valueName, DWORD type, const BYTE* data, DWORD size);

	// Saves key changes
	bool Save();

	// Returs key handler
	HKEY GetKey();

	// Open any key by name
	static HKEY Open(HKEY hKey, LPCWSTR lpSubKey);

	// Find key by name
	static bool Find(HKEY hKey, LPCWSTR lpSubKey);
private:
	// Key value
	HKEY key;

	// Subkey name
	LPCWSTR subKey;

	// Prints type of key
	void PrintType(DWORD type);
};

