#include <windows.h>

typedef VOID(*DLLPROC)();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hinstDLL; // DLL 핸들
	DLLPROC HelloWorld; // 함수 포인터
	BOOL fFreeDLL;

	// DLL 로드
	hinstDLL = LoadLibrary(TEXT("SampleDll.dll"));
	//hinstDLL = LoadLibrary(TEXT(".\\..\\SampleDll\\x64\\Debug\\SampleDll.dll"));

	if (hinstDLL != NULL)
	{
		// 함수 주소 가져오기
		HelloWorld = (DLLPROC)GetProcAddress(hinstDLL, "HelloWorld");
		if (HelloWorld != NULL)
		{
			// 함수 호출
			(HelloWorld)();
		}

		// DLL 해제
		fFreeDLL = FreeLibrary(hinstDLL);
	}
	else
	{
		MessageBox(NULL, TEXT("DLL Load Failed!"), TEXT("Error"), MB_OK);
	}

	return 0;
}