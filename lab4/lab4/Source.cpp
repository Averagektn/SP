#include <Windows.h>
#include <iostream>
#include "Key.h"

int main()
{
	Key key(HKEY_CURRENT_USER, L"lab4\\NewKey");
	const BYTE data[]{ 89, 22, 11, 12, 13, 14, 15, 16 };
	int dataSize = 8;

	key.AddValue(L"Value5", REG_QWORD, data, dataSize);
	key.Save();
	key.ReadFlags(L"Value5");

	RegCloseKey(key.GetKey());
	key.Find(HKEY_CURRENT_USER, L"lab4\\NewKey");

	return 0;
}
