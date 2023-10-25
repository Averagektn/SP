#include <Windows.h>
#include <iostream>
#include "Key.h"

int main()
{
	Key key(HKEY_CURRENT_USER, L"lab4\\NewKey");
	const BYTE data[]{ 1, 2, 3, 4, 5, 6, 7, 8 };
	int dataSize = 8;

	key.AddValue(L"Value3", REG_QWORD, data, dataSize);
	key.Save();
	key.ReadFlags(L"Value3");

	RegCloseKey(key.GetKey());

	return 0;
}
