#include <ntddk.h>
#include <wdf.h>
#include "memory.h"


NTSTATUS KernelReadMemory(PEPROCESS process, PVOID source, PVOID target, SIZE_T size)
{
	PSIZE_T bytes;
	if (NT_SUCCESS(MmCopyVritualMemory(process, source, PsGetCurrentProcess(), target, size, KernelMode, &bytes)))
	{
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ACCESS_DENIED;
	}
}

NTSTATUS KernelWriteMemory(PEPROCESS process, PVOID source, PVOID target, SIZE_T size)
{
	PSIZE_T bytes;
	if (NT_SUCCESS(MmCopyVritualMemory(PsGetCurrentProcess(), source, process, target, size, KernelMode, &bytes)))
	{
		return STATUS_SUCCESS;
	}
	else
	{
		return STATUS_ACCESS_DENIED;
	}
}