#include <iostream>
#include <Windows.h>
#define IOCTL_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_GET_PID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
typedef struct _KERNEL_MEMORY_REQUEST
{
	ULONG PID;
	ULONG Address;
	ULONG Value;
	ULONG Size;
} KERNEL_MEMORY_REQUEST, * PKERNEL_MEMORY_REQUEST;

template<typename T>
T ReadMemory(HANDLE handle, ULONG PID, ULONG address, SIZE_T size)
{
	if (handle == INVALID_HANDLE_VALUE) { return false; }

	KERNEL_MEMORY_REQUEST request;
	request.PID = PID;
	request.Address = address;
	request.Size = size;

	if (DeviceIoControl(handle, IOCTL_READ_REQUEST, &request, sizeof(request), &request, sizeof(request), 0, 0))
	{
		return (T)request.Value;
	}
	else
	{
		return (T)false;
	}
}

bool WriteMemory(HANDLE handle, ULONG PID, ULONG address,ULONG value, SIZE_T size)
{
	if (handle == INVALID_HANDLE_VALUE) { return false; }

	DWORD bytes;

	KERNEL_MEMORY_REQUEST request;
	request.PID = PID;
	request.Address = address;
	request.Value = value;
	request.Size = size;

	if (DeviceIoControl(handle, IOCTL_WRITE_REQUEST, &request, sizeof(request), 0, 0, &bytes, NULL))
	{
		return true;
	}
	else
	{
		return false;
	}
}


int main()
{
	HANDLE handle = CreateFileA("\\\\.\\CSGODriver", GENERIC_READ | GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (handle == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Unable to open device... " << GetLastError() << std::endl;
	}
	else
	{


	}
}