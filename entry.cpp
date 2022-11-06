#include <iostream>
#include <Windows.h>
#include <thread>

int main()
{
    HKEY key{};
    const std::uint8_t admin_logon{ 1 };

    std::printf("This program will allow you to skip Windows login at startup.\nWould you like to continue?\nY/N: ");
    if (std::cin.get() != 'y')
        return EXIT_FAILURE;

    for (int i = 5; i > 0; i--, std::this_thread::sleep_for(std::chrono::seconds(1)))
        std::printf("Process is starting in %d seconds...\n", i);

    system("cls");

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &key) != ERROR_SUCCESS || RegSetValueExA(key, "ForceUnlockLogon", false, REG_DWORD, &admin_logon, 1) != ERROR_SUCCESS)
    {
        std::printf("Failed to set key.\n");
        RegCloseKey(key);
    }
    std::printf("Process completed successfully.\n");
    RegCloseKey(key);
    
    std::cin.get();
    return EXIT_SUCCESS;
}
