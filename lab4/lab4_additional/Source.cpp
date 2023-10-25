#include <Windows.h>
#include <iostream>

#define REG_NOTIFY_CHAGES REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_ATTRIBUTES | REG_NOTIFY_CHANGE_LAST_SET | REG_NOTIFY_CHANGE_SECURITY

bool MonitorRegistryChanges(HKEY hKey) 
{
    HKEY hMonitorKey;
    bool isMonitoring = true;

    if (RegOpenKeyEx(hKey, NULL, 0, KEY_NOTIFY, &hMonitorKey) == ERROR_SUCCESS)
    {
        std::cout << "Register change detection started..." << std::endl;

        while (isMonitoring)
        {
            if (RegNotifyChangeKeyValue(hMonitorKey, TRUE, REG_NOTIFY_CHAGES, NULL, FALSE) == ERROR_SUCCESS)
            {
                std::cout << "Key's change detected" << std::endl;
            }
            else
            {
                std::cout << "Error during key monitoring" << std::endl;
                isMonitoring = false;
            }
        }

        RegCloseKey(hMonitorKey);
        return true;
    }
    else
    {
        std::cout << "Open register key error" << std::endl;
        return false;
    }
}

int main()
{
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"lab4\\NewKey", 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) 
    {
        MonitorRegistryChanges(hKey);
        RegCloseKey(hKey);
    }
    else
    {
        std::cout << "Open register key error" << std::endl;
    }

    return 0;
}
