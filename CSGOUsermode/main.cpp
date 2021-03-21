#include <iostream>
#include <Windows.h>
#define IOCTL_TEST_CODE CTL_CODE(FILE_DEVICE_UNKNOWN, 0Xdeadbeef, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

int main()
{
	HANDLE device = CreateFileA("\\\\.\\CSGODriver", GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (device == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Unable to open device... " << GetLastError() << std::endl;
	}
	else
	{
		DeviceIoControl(device, IOCTL_TEST_CODE, 0, 0, 0, 0, 0, 0);
		CloseHandle(device);
	}
}