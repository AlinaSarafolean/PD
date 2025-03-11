#include <windows.h>
#include <iostream>
#include <string>
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_LENGTH 1024
void QueryImagePath(HKEY hKey, const std::string& subKey) {
	HKEY hSubKey;
	char imagePath[MAX_VALUE_LENGTH];
	DWORD bufferSize = sizeof(imagePath);
	DWORD type;

	if (RegOpenKeyExA(hKey, subKey.c_str(), 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
	
		if (RegQueryValueExA(hSubKey, "ImagePath", NULL, &type,
			reinterpret_cast<LPBYTE>(imagePath), &bufferSize) == ERROR_SUCCESS) {
			std::cout << "Subkey: " << subKey << "\nImagePath: " << imagePath << "\n\n";
		}
		RegCloseKey(hSubKey);
	}
}
int main() {
	HKEY hKey;
	char subKeyName[MAX_KEY_LENGTH];
	DWORD index = 0;
	DWORD subKeySize;
	FILETIME ftLastWriteTime;
	
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services", 0,
		KEY_READ, &hKey) == ERROR_SUCCESS) {
	
		while (true) {
			subKeySize = MAX_KEY_LENGTH;
			if (RegEnumKeyExA(hKey, index, subKeyName, &subKeySize, NULL, NULL, NULL,
				&ftLastWriteTime) != ERROR_SUCCESS) {
				break; 
			}
			
			std::string fullSubKey = "SYSTEM\\CurrentControlSet\\Services\\" +
				std::string(subKeyName);
			QueryImagePath(HKEY_LOCAL_MACHINE, fullSubKey);
			index++;
		}
		RegCloseKey(hKey);
	}
	else {
		std::cerr << "Eroare la deschiderea registry-ului!" << std::endl;
	}
	return 0;
}