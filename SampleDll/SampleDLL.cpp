#include "pch.h"
#define EXPORTING_DLL
#include "SampleDLL.h"

// ������ �Լ�
extern "C" __declspec(dllexport) void HelloWorld()
{
	MessageBox(NULL, TEXT("Hello World"), TEXT("In a DLL"), MB_OK);
}
