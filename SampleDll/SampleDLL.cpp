#include "pch.h"
#define EXPORTING_DLL
#include "SampleDLL.h"

// 내보낸 함수
extern "C" __declspec(dllexport) void HelloWorld()
{
	MessageBox(NULL, TEXT("Hello World"), TEXT("In a DLL"), MB_OK);
}
