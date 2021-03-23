#include <ntddk.h>
#include <wdf.h>
#include "communication.h"
#include "data.h"
#include "event.h"

NTSTATUS DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	IoDeleteDevice(pDriverObject->DeviceObject);
	IoDeleteSymbolicLink(&SymbolicLink);
	DbgPrint("Driver Unloaded\n");
	return STATUS_SUCCESS;
}
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	NTSTATUS status = STATUS_SUCCESS;

	PsSetLoadImageNotifyRoutine(PloadImageNotifyRoutine);
	DriverObject->DriverUnload = DriverUnload;

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IOCTLControl;
	DriverObject->MajorFunction[IRP_MJ_CREATE] = IOCTLCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = IOCTLClose;

	status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DriverObject->DeviceObject);
	if (NT_SUCCESS(status))
	{
		DbgPrint("Scuessfully created device %wZ", DeviceName);
	}
	else
	{
		DbgPrint("Could not create device %wZ", DeviceName);
	}

	status = IoCreateSymbolicLink(&DeviceName, &SymbolicLink);
	if (NT_SUCCESS(status))
	{
		DbgPrint("Symbolic link %wZ created", SymbolicLink);
	}
	else
	{
		DbgPrint("Could not create symbolic link %wZ", SymbolicLink);
	}

	DbgPrint("Driver Loaded\n");
	return status;
}





