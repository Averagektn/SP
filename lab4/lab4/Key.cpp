#include "Key.h"

Key::Key(HKEY hKey, LPCWSTR lpSubKey)
{
	DWORD keyDisposition;

	subKey = lpSubKey;
	LSTATUS status = RegCreateKeyEx(hKey, lpSubKey, NULL, NULL, NULL,
		KEY_READ | KEY_WRITE, NULL, &key, &keyDisposition);

	if (status == ERROR_SUCCESS)
	{
		if (keyDisposition == REG_OPENED_EXISTING_KEY)
		{
			std::cout << "Opened existing key. No changes" << std::endl;
		}
		if (keyDisposition == REG_CREATED_NEW_KEY)
		{
			std::cout << "Created new key" << std::endl;
		}
	}
	else
	{
		key = NULL;
		std::cout << "Error. Key was not created" << std::endl;
	}
}

HKEY Key::GetKey()
{
	return key;
}

HKEY Key::Open(HKEY hKey, LPCWSTR lpSubKey)
{
	HKEY res;

	if (RegOpenKeyEx(hKey, lpSubKey, NULL, KEY_READ, &res) == ERROR_SUCCESS)
	{
		return res;
	}

	return NULL;
}

bool Key::Find(HKEY hKey, LPCWSTR lpSubKey)
{
	HKEY res;

	if (RegOpenKeyEx(hKey, lpSubKey, NULL, KEY_READ, &res) == ERROR_SUCCESS)
	{
		RegCloseKey(res);
		std::cout << "Found it: " << (int)res << std::endl;

		return true;
	}

	return false;
}


bool Key::ReadFlags(LPCWSTR lpValueName)
{
	BYTE buffer[256];
	// Must contain initial buffer size
	DWORD bufLength = 256;
	DWORD type = 0;

	// Changes buffer size to real, initializaes buffer and type
	if (RegQueryValueEx(key, lpValueName, NULL, &type, buffer, &bufLength) == ERROR_SUCCESS)
	{
		PrintType(type);
		for (int i = 0; i < bufLength; i++)
		{
			std::cout << (int)buffer[i] << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		return false;
	}

	return true;
}

bool Key::AddValue(LPCWSTR valueName, DWORD type, const BYTE* data, DWORD size)
{
	return RegSetValueEx(key, valueName, NULL, type, data, size) == ERROR_SUCCESS;
}

bool Key::Save()
{
	if (RegFlushKey(key) == ERROR_SUCCESS) {
		std::cout << "Key saved" << std::endl;
		return true;
	}
	else {
		std::cout << "Saving error" << std::endl;
		return false;
	}
}

void Key::PrintType(DWORD type)
{
	int typesSize = 11;
	DWORD types[]
	{
		REG_BINARY, REG_DWORD, REG_DWORD_LITTLE_ENDIAN, REG_DWORD_BIG_ENDIAN, 
		REG_EXPAND_SZ, REG_LINK, REG_MULTI_SZ, REG_NONE, REG_QWORD, REG_QWORD_LITTLE_ENDIAN, REG_SZ
	};
	std::string messages[]
	{
		"Binary data in any form",
		"A 32-bit number",
		"A 32-bit number in little-endian format",// == DWORD
		"A 32-bit number in big-endian format",
		"A null-terminated string that contains unexpanded references to environment variables",
		"A null-terminated Unicode string that contains the target path of a symbolic link that was created by calling the RegCreateKeyEx function with REG_OPTION_CREATE_LINK",
		"A sequence of null-terminated strings, terminated by an empty string",
		"No defined value type",
		"A 64-bit number",
		"A 64-bit number in little-endian format", // == QWORD
		"A null-terminated string. It's either a Unicode or an ANSI string, depending on whether you use the Unicode or ANSI functions"
	};

	for (int i = 0; i < typesSize; i++)
	{
		if ((type ^ types[i]) == 0)
		{
			std::cout << messages[i] << std::endl;
		}
	}
	
}
