#include <windows.h>
#include <setupapi.h>
#include <regstr.h>
#include <stdio.h>
#include <tchar.h>

#pragma comment(lib, "setupapi.lib")

int main() {
    HDEVINFO deviceInfo;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD i;

    deviceInfo = SetupDiGetClassDevs(
        NULL,
        "USB",
        NULL,
        DIGCF_PRESENT | DIGCF_ALLCLASSES);

    if (deviceInfo == INVALID_HANDLE_VALUE) {
        printf("Eroare la obținerea listei de dispozitive.\n");
        return 1;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    for (i = 0; SetupDiEnumDeviceInfo(deviceInfo, i, &deviceInfoData); ++i) {
        TCHAR desc[1024];
        DWORD size = 0;

        if (SetupDiGetDeviceRegistryProperty(
                deviceInfo,
                &deviceInfoData,
                SPDRP_DEVICEDESC,
                NULL,
                (PBYTE)desc,
                sizeof(desc),
                &size)) {
            _tprintf(_T("Dispozitiv USB: %s\n"), desc);
        }
    }

    SetupDiDestroyDeviceInfoList(deviceInfo);
    return 0;
}
