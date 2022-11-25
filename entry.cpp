#include <iostream>
#include <Windows.h>
#include <thread>

using namespace std;

int main()
{
    SetConsoleTitleA("Auto Login");

    HKEY key{};
    const uint8_t admin_logon{ 1 };

    cout << "This program will allow you to skip Windows login at startup.\nContinue? (Y/N): ";
    if (cin.get() != 'y')
        return EXIT_FAILURE;

    for (int i = 5; i > 0; i--, this_thread::sleep_for(chrono::seconds(1)))
        cout << "Process is starting in " << i << " seconds...\n";

    system("cls");

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &key) != ERROR_SUCCESS || RegSetValueExA(key, "ForceUnlockLogon", false, REG_DWORD, &admin_logon, 1) != ERROR_SUCCESS)
        cout << "Failed to set key.";
    else
        cout << "Process completed successfully";

    RegCloseKey(key);

    cin.get();
	return EXIT_SUCCESS;
}
