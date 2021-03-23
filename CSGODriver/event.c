#include <ntddk.h>
#include <wdf.h>
#include "event.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE PloadImageNotifyRoutine(PUNICODE_STRING ImageName, HANDLE PID, PIMAGE_INFO ImageInfo)
{
	if (wcsstr(ImageName->Buffer, L"\\csgo\\bin\\client.dll"))
	{
		ClientAddress = ImageInfo->ImageBase;
		ProcessID = PID;
	}
}