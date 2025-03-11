#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_LENGTH 1024
void QueryImagePath(HKEY hKey, LPCSTR subKey) {
	HKEY hSubKey;
	CHAR imagePath[MAX_VALUE_LENGTH] = { 0 };
	DWORD bufferSize = sizeof(imagePath);
	DWORD type;
	if (RegOpenKeyEx(hKey, subKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
		if (RegQueryValueEx(hSubKey, "ImagePath", NULL, &type, (LPBYTE)imagePath, &bufferSize)== ERROR_SUCCESS) {
			printf("Subkey: %s\nImagePath: %s\n\n", subKey, imagePath);
		}
		RegCloseKey(hSubKey);
	}
}
int main() {
	HKEY hKey;
	CHAR subKeyName[MAX_KEY_LENGTH];
	DWORD index = 0;
	DWORD subKeySize;
	FILETIME ftLastWriteTime;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		while (1) {
			subKeySize = MAX_KEY_LENGTH;
			if (RegEnumKeyEx(hKey, index, subKeyName, &subKeySize, NULL, NULL, NULL,&ftLastWriteTime) != ERROR_SUCCESS) {
				break;
			}
			char fullSubKey[MAX_KEY_LENGTH + 50];
			snprintf(fullSubKey, sizeof(fullSubKey), "SYSTEM\\CurrentControlSet\\Services\\%s",
				subKeyName);
			QueryImagePath(HKEY_LOCAL_MACHINE, fullSubKey);
			index++;
		}
		RegCloseKey(hKey);
	}
	else {
		printf("Eroare la deschiderea registry-ului!\n");
	}
	return 0;
}