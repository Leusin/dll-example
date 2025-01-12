# 1. DLL이란?

![image](https://github.com/user-attachments/assets/ceb4da94-6aab-47fe-86f0-1d695bb24e79)

**DLL**(Dynamic Link Library)은 Windows에서 구현된 동적 라이브러리 입니다. 다른 플랫폼에서는 Mac의 **dylib**(dynamic library)와 Linux의 **so**(shared object) 파일이 동적 라이브러리로 사용됩니다.

동적 라이브러리는 실행 시간에 프로그램에 로드되며, 여러 프로그램이 동시에 공유할 수 있는 코드와 데이터를 포함합니다. Windows 운영 체제에서는 많은 기능이 DLL로 제공됩니다. 대표적으로 **comdlg32.dll**은 Windows의 팝업 대화 상자를 생성하는 데 사용됩니다.

![image](https://github.com/user-attachments/assets/0f0ddd3b-0ceb-4864-a6f9-6bf21b7b5555)

comdlg32.dll의 기본 경로 C:\Windows\System32

DLL 파일의 파일 확장자는 .dll인 경우가 많지만 다른 파일 확장자를 가질 수 있습니다. 
(예: ActiveX 컨트롤의 경우 .ocx, 레거시(16비트) 장치 드라이버의 경우 .drv)

## 1) DLL의 모듈성

DLL을 사용하면 프로그램을 여러 개별 구성 요소로 모듈화할 수 있습니다. 이를 통해 다음과 같은 이점을 얻을 수 있습니다.

- **디스크 공간 절약**
    
    여려 프로로그램이 동일한 DLL을 공유하기 때문에 디스크 공간 사용량을 줄일 수 있습니다.
    
    즉, 여러 프로세스가 하나의 DLL을 물리 메모리(RAN, SDD, HDD)에 공유하므로 메모리 사용량과 스와핑이 줄어듭니다.
    
- **로드 시간 향상과 메모리 절약**
    
    프로그램 실행 시 필요한 DLL만 로드되므로 초기 로드 시간이 단축되고, 사용하지 않는 DLL은 메모리에 올라가지 않아 불필요한 RAM사용량을 절약할 수 있습니다.
    
- **유지보수와 업데이트**
    
    DLL만 개별적으로 업데이트할 수 있어 프로그램 전체에 영향을 주지 않고 새로운 기능을 추가가 가능합니다.
    
    함수 인수, 함수 호출 규칙(Calling Convention), 반환 값이 변하지 않는 한 응용프로그램을 다시 컴파일할 필요 없습니다.
    
- 언어 간 호환성
    
    호출 규칙(C, Pascal 등)을 따르면 다른 프로그래밍 언어에서도 동일한 DLL 함수를 호출할 수 있습니다.
    

## 2)  DLL 종속성 문제(DLL Hell)

DLL 사용은 편리하지만, 프로그램 입장에서는 DLL의 새 코드가 호환하는지 확인할 방법이 없기 때문에 여러 DLL에 의존할 경우 호환성 문제가 발생할 수 있습니다.

이러한 상황에서는 프로그램 실행이 멈추며 다음과 같은 오류 메시지가 표시될 수 있습니다.

![image](https://github.com/user-attachments/assets/64121e5b-7a21-4546-86c3-51fcb7f2fdbf)
“파일이름.exe - 시스템 오류 core.dll이(가) 없어 코드 실행을 진행할 수 없습니다. 프로그램을 다시 설치하면 이 문제가 해결될 수 있습니다"
(이미지 출처: https://how2open.com/blog/core-dll을-찾을-수-없거나-누락-된-오류를-수정하는-방법/)

이와 같은 문제를 **DLL Hell**이라고 부르며 특히 오래된 Windows 버전에 이러한 문제를 빈번하게 발생했었습니다.

### **DLL 문제의 주요 원인**

- **호환성 문제**
    
    새로운 DLL 버전이 기존 프로그램과 호환되지 않으면 프로그램이 실행되지 않거나 예기치 못한 오류가 발생할 수 있습니다.
    
- **의도하지 않은 변경**
    
    설치 프로그램이 특정 애플리케이션을 위해 DLL을 수정하거나, 기존 DLL을 덮어씌우거나 제거하면 다른 프로그램에서 충돌이 발생할 수 있습니다.
    

예를 들어, 과거 일부 프로그램은 사용자의 의도와 상관없이 DLL을 새로운 버전으로 업그레이드하거나, 이전 버전을 덮어쓰거나, 심지어 삭제하기도 했습니다. 설치 프로그램이 특정 애플리케이션에 최적화된 DLL을 제공하더라도, 이 DLL이 다른 프로그램과 호환되지 않으면 충돌을 일으킬 가능성이 높습니다.

![image](https://github.com/user-attachments/assets/c9d0f177-24d3-443b-80b6-a502ea8b505b)
이미지 출처: https://ko.wikipedia.org/wiki/NSIS

## 3) 최신 Windows 에서 해결책

DLL Hell 문제는 Microsoft가 시스템 표준을 보호하지 않았고 버전 관리를 지원하지 않았으며, 개발자들은 DLL 업데이트로 인해 다른 프로그램에 문제가 생길 가능성을 충분히 고려하지 않기 때문입니다. 

최신 버전의 Windows에서 다음과 같은 해결책으로 Dll Hell 문제를 완화했습니다.

- **Windows 파일 보호**: 운영 체제는 권한 없이 시스템 DLL을 삭제하거나 업데이트하는 것을 차단합니다.
- **전용 DLL(Private DLL)**: 프로그램 설치 경로에 필요한 DLL을 저장하거나 **.local** 파일을 통해 공유 특정 프로그램이 자신만의 독립적인 DLL 버전을 사용할 수 있도록 합니다.
- **동시 버전 허용(Side-by-Side Assembly)**: 동일한 DLL의 여러 버전을 시스템에서 동시 실행할 수 있습니다.


# 2. 구조와 동작 방식

## 1) 유형

응용 프로그램에서 DLL을 로드할 때는 두 가지 연결 방법을 통해 DLL 함수를 호출할 수 있습니다.

### **로드타임 동적 연결(load-time dynamic linking)**

- 필요한 DLL은 프로그램 시작 시 먼저 자동으로 로드됩니다.
- DLL이 없으면 응용프로그램 실행 자체가 불가능하거나 진입점 함수가 TRUE를 반환지 않으면 오류 메시지가 표시됩니다.
- 컴파일 시 .lib(가져오기 라이브러리, import library) 파일이 프로그램에 포함되어 컴파일러가 이를 활용해 코드를 링크합니다. .lib 파일은 DLL의 내부 코드를 포함하지 않고 함수 진입점에 대한 정보를 제공합니다
- DLL 파일에 직접 접근하지 않아도 개발자는 DLL의 함수를 로컬 함수처럼 사용할 수 있습니다.(예: printf, sacnf)

### 런타임 동적 연결(run-time dynamic linking)

- 프로그램 실행 도중 필요할 때 DLL을 로드합니다.
- DLL이 없어도 프로그램 실행이 가능하며, 다른 DLL을 로드하거나 동적 기능 확장이 가능합니다.
- .lib 파일을 사용하지 않는 대신 Windows API 함수 **LoadLibrary** 또는 **LoadLibraryEx** 함수에 매개변수로 DLL 파일의 경로를 지정하여 DLL을 메모리에 로드합니다.
- DLL 함수 호출 시에는 **GetProcAddress**로 함수의 메모리 주소를 가져온 뒤 함수 포인터로 저장하여 호출합니다.
    
    ```c
    HMODULE hDll = LoadLibrary("example.dll"); // 해당 DLL의 핸들(참조 값)이 반환
    typedef int(*MyFunctionType)(int);
    MyFunctionType MyFunction = (MyFunctionType)GetProcAddress(hDll, "FunctionName");
    MyFunction(42);
    FreeLibrary(hDll); // 로드 해제
    ```
    
- DLL의 존재 여부를 실행 시 확인하므로 실행 중에 다른 DLL을 교체하거나 기능을 동적으로 추가할 수 있습니다.

## 2) 메모리 관리

- **가상 주소 공간 공유**
    
    ![image](https://github.com/user-attachments/assets/ca0eb1b0-4bc0-47b4-82f5-59dd1fcaba25)
    
    두 프로세스는 동일한 DLL의 물리적 페이지를 공유 중입니다.
    
    ![image](https://github.com/user-attachments/assets/56bc0e80-f268-472c-bcb0-f76233039446)
    
     Process 1이 쓰기를 시도하면, 새로운 물리적 페이지가 만들어져 독립적으로 사용됩니다.
    
    여러 프로세스가 동일한 DLL을 로드하면, 해당 DLL의 물리적 페이지는 여러 프로세스 간에 공유됩니다. 읽기 작업은 공유되지만, 쓰기 작업은 각 프로세스가 독립적으로 처리합니다(Copy-On-Write, COW).
    
- **참조 카운트**
    
    시스템은 각 DLL을 로드할 때 참조 카운트가 1씩 증가하합니다. 프로세스 종료 또는 (런타임 동적 연결의 경우)FreeLibrary 호출로 DLL을 끝내면 참조 카운트가 1씩 감소하며 참조 카운트가 0이 되면 DLL 이 메모리에서 해제됩니다.
    
- **스레드 컨텍스트**
    
    DLL 함수가 호출되면 호출한 스레드의 컨텍스트에서 실행됩니다. 이것이 의미하는 바는 다음과 같습니다.
    
    - **스택 공유**
        
        DLL 함수는 호출한 스레드의 스택을 사용합니다. 따라서, 호출 스레드가 지역 변수로 저장한 데이터를 DLL 함수가 사용할 수 있습니다.
        
    - **가상 주소 공간 공유**
        
        DLL은 호출 프로세스의 메모리 공간을 공유하므로, 동적으로 할당된 데이터나 파일 핸들을 다른 스레드와 공유할 수 있습니다.
        
    - **핸들 공유**
        
        DLL 함수에서 열린 핸들(파일, 소켓, 메모리 등)은 호출 프로세스의 다른 스레드에서 액세스할 수 있습니다.
        

# 3. DLL 개발

## 1) DLL 진입점

DLL을 만들 때는 필요에 따라 진입점 함수를 지정할 수 있습니다. 이 함수는 DLL이 로드될 때와 해제될 때 자동으로 호출되며, 프로그램의 실행 흐름에서 중요한 초기화 및 정리 작업을 담당합니다.

```c
BOOL APIENTRY DllMain(
    HANDLE hModule,             // DLL 모듈의 핸들
    DWORD ul_reason_for_call,   // 호출 이유
    LPVOID lpReserved           // 예약된 파라미터. 잘 사용되지 않습니다.
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH: // 프로세스가 DLL을 로드할 때
            break;
        case DLL_THREAD_ATTACH:  // 프로세스가 스레드를 생성할 때
            break;
        case DLL_THREAD_DETACH:  // 스레드가 종료될 때
            break;
        case DLL_PROCESS_DETACH: // 프로세스가 DLL을 언로드할 때
            break;
    }
    return TRUE; // 로드 성공
}

```

- **진입점 함수 사용 시기**

- 프로세스가 DLL을 로드할 때 (예: LoadLibrary 함수 호출 시)

- 프로세스가 DLL을 언로드할 때 (예: FreeLibrary 함수 호출 시)

- 스레드가 DLL을 사용하거나 종료할 때

DLL의 진입점 함수는 단순한 초기화 작업만 수행해야 합니다. 복잡한 작업이나 다른 DLL을 호출하는 것은 피해야 합니다. 다른 DLL을 호출하거나 복잡한 연산을 수행하면 DLL의 로드/언로드 과정에서 예기치 않은 문제를 발생시킬 수 있습니다.

## 2) DLL 함수 내보내기

DLL 내부 함수를 내보내려면 두 가지 방법 중 하나를 사용할 수 있습니다:

1. **__declspec(dllexport)** 키워드 사용
2. 모듈 정의 파일(**.def**) 사용

- **__declspec(dllexport) 키워드 사용하는 방법**
    
    일반적으로 **__declspec(dllexport)**문과 **__declspec(dllimport)**문을 구분하기 위해 define 문과 ifdef 문이 포함된 하나의 헤더 파일을 사용합니다.
    
    ```c
    #ifdef EXPORTING_DLL
        __declspec(dllexport) void HelloWorld(); // 내보내려는 함수 선언
    #else
        __declspec(dllimport) void HelloWorld(); // 가져오려는 함수 선언
    #endif
    ```
    
- **모듈 정의 파일(.def)을 사용하는 방법**
    
    이 경우 **__declspec(dllexport)** 키워드 없이도 함수를 내보낼 수 있습니다.
    
    모듈 정의 파일에서 DLL에 대한 LIBRARY 문과 EXPORTS 문을 선언합니다. 
    
    ```c
    // SampleDLL.def
    LIBRARY "sampleDLL"
    EXPORTS HelloWorld
    ```
    

# 4. 예제

## 1) DLL 구현

- **SampleDLL.h**
    
    ```c
    #ifndef INDLL_H
    #define INDLL_H
    
    #ifdef EXPORTING_DLL
    extern "C" __declspec(dllexport) void HelloWorld();
    #else
    extern "C" __declspec(dllimport) void HelloWorld();
    #endif
    
    #endif // INDLL_H
    
    ```
    
- **SampleDLL.cpp**
    
    ```c
    #include "pch.h"
    #define EXPORTING_DLL
    #include "SampleDLL.h"
    
    // 내보낸 함수
    extern "C" __declspec(dllexport) void HelloWorld()
    {
        MessageBox(NULL, TEXT("Hello World"), TEXT("In a DLL"), MB_OK);
    }
    
    ```
    
    C++에서 DLL 내보내기 시에는 **extern "C"**를 사용하여 이름 맹글링을 방지해야 합니다.
    

![image](https://github.com/user-attachments/assets/830c8619-66f6-4261-a613-1d3a804c357c)

dll 프로젝트 속성은 위와 같이 설정한 뒤 빌드합니다.

## 2) 로드타임 동적 연결 사용

1. 프로젝트 설정에서 가져오기 라이브러리 파일(**.h**, **.lib**)의 경로를 설정하기.
    
    ![image](https://github.com/user-attachments/assets/56e7b1c1-37ea-462d-8089-45b17583d7a2)
    
    ![image](https://github.com/user-attachments/assets/5f99c313-5a26-424c-b8a4-54d9390cb781)
    
2. 프로젝트의 설정에서 DLL의 **.lib** 파일을 정적으로 링킹하기.
    
    ![image](https://github.com/user-attachments/assets/f91d71f9-583f-47ea-ac1b-8e8a2435fa5d)
    
    ![image](https://github.com/user-attachments/assets/6bc2591d-97d4-4211-9c19-2971dc45bcd1)
    
    ![image](https://github.com/user-attachments/assets/0b4ba5b7-7b4e-46ed-a76c-491c7619166e)
    
3. 빌드 후 이벤트로 DLL을 실행 파일에 복사 하도록 설정하기.
    
    ![image](https://github.com/user-attachments/assets/0c3abd20-9b43-4d88-8b20-3ac1cebb7614)
    
    ![image](https://github.com/user-attachments/assets/0f85da01-e672-4574-bdf2-3d03af95493c)
    
    xcopy \y \d "[dll 파일의 디렉터리 경로]\SampleDLL.dll" "[실행 파일의 디렉터리 경로]" 
    
- **main.cpp**(콘솔 응용 프로그램, 하위 시스템: 콘솔(/SUBSYSTEM:CONSOLE))
    
    ```c
    #include "SampleDLL.h"
    
    // 정적 링크 방식
    int main()
    {
    	// DLL에서 내보낸 함수 호출
    	HelloWorld();
    	return 0;
    }
    ```
    
- **실행 결과**
    
    ![image](https://github.com/user-attachments/assets/dcc60ff5-c4a5-4997-872d-dd5969851d22)
    
    실행 성공
    
    ![image](https://github.com/user-attachments/assets/db575a7d-ee90-42c1-b7a0-62bd9be0a0ec)
    
    실행 실패
    

## 3) 런타임 동적 연결 사용

- **WinMain.cpp**(Windows 응용 프로그램, 하위 시스템: 창(/SUBSYSTEM:WINDOWS))
    
    ```c
    #include <windows.h>
    
    typedef VOID(*DLLPROC)();
    
    int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
    	HINSTANCE hinstDLL; // DLL 핸들
    	DLLPROC HelloWorld; // 함수 포인터
    	BOOL fFreeDLL;
    
    	// DLL 로드
    	hinstDLL = LoadLibrary(TEXT(".\\..\\SampleDll\\x64\\Debug\\SampleDll.dll"));
    
    	if (hinstDLL != NULL)
    	{
    		// 함수 주소 가져오기
    		HelloWorld = (DLLPROC)GetProcAddress(hinstDLL, "HelloWorld");
    		if (HelloWorld != NULL)
    		{
    			// 함수 호출
    			(HelloWorld)();
    		}
    
    		// DLL 해제 (메모리 누수를 막기 위해 꼭 필요!)
    		fFreeDLL = FreeLibrary(hinstDLL);
    	}
    	else
    	{
    		MessageBox(NULL, TEXT("DLL Load Failed!"), TEXT("Error"), MB_OK);
    	}
    
    	return 0;
    }
    ```
    
    런타임 동적 연결에서 **LoadLibrary**에 DLL 경로를 지정할 때 경로를 명확히 설정해야 합니다. 혹은 빌드 후 이벤트로 실행 결로에 dll파일을 복사하도록할 수도 있습니다.
    
    **LoadLibrary** 와 **GetProcAddress** 호출 실패 시 적절한 에러 메시지를 출력하거나 처리해야 합니다.
    
- **실행 결과**
    
    ![image](https://github.com/user-attachments/assets/3ef08879-d934-4dec-a6d8-dd47c2f164c1)
    
    실행 성공
    
    ![image](https://github.com/user-attachments/assets/3dbdd12e-33f5-4155-bee5-4e858049bf8c)
    
    실행 실패
    

---

# 참고

- [YouTube - What Are DLLs?](https://www.youtube.com/watch?v=4daUujBgQQ8)
- [YouTube - 21장. Dynamic Linking Library](https://www.youtube.com/watch?v=JK6U91t7mgY)
- [Microsoft Learn - DLL이란?](https://learn.microsoft.com/ko-kr/troubleshoot/windows-client/setup-upgrade-and-drivers/dynamic-link-library)
- [Microsoft Learn - 동적 링크 라이브러리](https://learn.microsoft.com/ko-kr/windows/win32/dlls/dynamic-link-libraries)
- [Microsoft Learn - 메모리 보호](https://learn.microsoft.com/ko-kr/windows/win32/memory/memory-protection)
- [Microsoft Learn - 연습: 고유한 동적 링크 라이브러리 만들기 및 사용(C++)](https://learn.microsoft.com/ko-kr/cpp/build/walkthrough-creating-and-using-a-dynamic-link-library-cpp?view=msvc-170)
- [Wikipedia - 동적 링크 라이브러리](https://ko.wikipedia.org/wiki/%EB%8F%99%EC%A0%81_%EB%A7%81%ED%81%AC_%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC)
- [Wikipedia - 사이드 바이 사이트 어셈블리](https://ko.wikipedia.org/wiki/%EC%82%AC%EC%9D%B4%EB%93%9C_%EB%B0%94%EC%9D%B4_%EC%82%AC%EC%9D%B4%EB%93%9C_%EC%96%B4%EC%85%88%EB%B8%94%EB%A6%AC)
- [나무위키 - DLL](https://namu.wiki/w/DLL)
- [NAVER Blog - dll파일 명시적링크하기(LoadLibrary(),GetProcAdress() ,FreeLibrary()](https://blog.naver.com/sorkelf/40133647878)
