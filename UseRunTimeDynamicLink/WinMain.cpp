#include <windows.h>

typedef VOID(*DLLPROC)();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hinstDLL; // DLL �ڵ�
	DLLPROC HelloWorld; // �Լ� ������
	BOOL fFreeDLL;

	// DLL �ε�
	hinstDLL = LoadLibrary(TEXT("SampleDll.dll"));
	//hinstDLL = LoadLibrary(TEXT(".\\..\\SampleDll\\x64\\Debug\\SampleDll.dll"));

	if (hinstDLL != NULL)
	{
		// �Լ� �ּ� ��������
		HelloWorld = (DLLPROC)GetProcAddress(hinstDLL, "HelloWorld");
		if (HelloWorld != NULL)
		{
			// �Լ� ȣ��
			(HelloWorld)();
		}

		// DLL ����
		fFreeDLL = FreeLibrary(hinstDLL);
	}
	else
	{
		MessageBox(NULL, TEXT("DLL Load Failed!"), TEXT("Error"), MB_OK);
	}

	return 0;
}