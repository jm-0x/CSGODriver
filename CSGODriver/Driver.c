#include <ntddk.h>
#include <wdf.h>

#define IOCTL_TEST_CODE CTL_CODE(FILE_DEVICE_UNKNOWN, 0Xdeadbeef, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)

UNICODE_STRING DeviceName = RTL_CONSTANT_STRING(L"\\Device\\CSGODriver"), SymbolicLink = RTL_CONSTANT_STRING(L"\\DosDevices\\CSGODriver");

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, PUNICODE_STRING pRegistryPath)
{
	NTSTATUS status = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOCTLControl;
	DriverObject->MajorFunction[IRP_MJ_CREATE] = IOCTLCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = IOCTLClose;

	status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DriverObject->DeviceObject);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("Could not create device %wZ", DeviceName);
	}
	else
	{
		DbgPrint("Device %wZ created", DeviceName);
	}

	status = IoCreateSymbolicLink(&DeviceName, &SymbolicLink);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("Could not create symbolic link %wZ", SymbolicLink);
	}
	else
	{
		DbgPrint("Symbolic link %wZ created", SymbolicLink);
	}

	DbgPrint("Driver Loaded\n");
	return status;
}

NTSTATUS DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	DbgPrintExt(0, 0, "Driver Unloaded\n");
	PDEVICE_OBJECT object;

	return STATUS_SUCCESS;
}

NTSTATUS IOCTLControl(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	NTSTATUS Status = 0;
	PIO_STACK_LOCATION StackLocation = IoGetCurrentIrpStackLocation(IRP);
	ULONG ControlCode = StackLocation->Parameters.DeviceIoControl.IoControlCode;
	if (ControlCode = IOCTL_TEST_CODE)
	{
		DbgPrint("TEST_CODE recived");
		Status = STATUS_SUCCESS;
	}
	else
	{
		Status = STATUS_INVALID_PARAMETER;
	}
	IRP->IoStatus.Status = Status;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return Status;

}

NTSTATUS IOCTLCreate(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;

}

NTSTATUS IOCTLClose(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}