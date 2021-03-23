#include <ntddk.h>
#include <wdf.h>
#include "communication.h"
#include "data.h"
#include "memory.h"


NTSTATUS IOCTLControl(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS status = 0;
	ULONG bytes = 0;

	PIO_STACK_LOCATION StackLocation = IoGetCurrentIrpStackLocation(IRP);
	ULONG ControlCode = StackLocation->Parameters.DeviceIoControl.IoControlCode;
	switch (ControlCode)
	{
	case IOCTL_WRITE_REQUEST: {

		PKERNEL_MEMORY_REQUEST input = (PKERNEL_MEMORY_REQUEST)IRP->AssociatedIrp.SystemBuffer;
		PEPROCESS process;
		if (NT_SUCCESS(PsLookupProcessByProcessId(input->PID, &process)))
		{
			KernelWriteMemory(process, &input->Value, input->Address, input->Size);
		}
		bytes = sizeof(KERNEL_MEMORY_REQUEST);
		status = STATUS_SUCCESS;
	} break;
	case IOCTL_READ_REQUEST: {

		PKERNEL_MEMORY_REQUEST input = (PKERNEL_MEMORY_REQUEST)IRP->AssociatedIrp.SystemBuffer;
		PKERNEL_MEMORY_REQUEST output = (PKERNEL_MEMORY_REQUEST)IRP->AssociatedIrp.SystemBuffer;
		
		PEPROCESS process;
		if (NT_SUCCESS(PsLookupProcessByProcessID(input->PID, &process)))
		{
			KernelReadMemory(process, input->Address, &input->Value, input->Size);
		}

		bytes = sizeof(KERNEL_MEMORY_REQUEST);
		status = STATUS_SUCCESS;
	} break;
	case IOCTL_GET_PID_REQUEST: {
		PULONG buffer = IRP->AssociatedIrp.SystemBuffer;
		*buffer = ProcessID;
		bytes = sizeof(*buffer);
		status = STATUS_SUCCESS;
	} break;
	case IOCTL_GET_MODULE_REQUEST: {
		PULONG buffer = IRP->AssociatedIrp.SystemBuffer;
		*buffer = ClientAddress;
		bytes = sizeof(*buffer);
		status = STATUS_SUCCESS;
	} break;
	default: {
		bytes = 0;
		status = STATUS_INVALID_PARAMETER;
	} break;
	}
	IRP->IoStatus.Status = status;
	IRP->IoStatus.Information = bytes;
	IoCompleteRequest(IRP, IO_NO_INCREMENT);

	return status;

}

NTSTATUS IOCTLCreate(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;

}

NTSTATUS IOCTLClose(PDEVICE_OBJECT DeviceObject, PIRP IRP)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	IRP->IoStatus.Status = STATUS_SUCCESS;
	IRP->IoStatus.Information = 0;

	IoCompleteRequest(IRP, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
