#pragma once

typedef struct _KERNEL_MEMORY_REQUEST 
{
	ULONG PID;
	ULONG Address;
	ULONG Value;
	ULONG Size;
} KERNEL_MEMORY_REQUEST, *PKERNEL_MEMORY_REQUEST;

NTSTATUS KernelReadMemory(PEPROCESS process, PVOID source, PVOID target, SIZE_T size);
NTSTATUS KernelWriteMemory(PEPROCESS process, PVOID source, PVOID target, SIZE_T size);