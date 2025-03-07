COM
COM은 무엇인가? Component Object Model의 약자.Com은 매우 진보된 객체를 만드는 방법으로 사실 레고와 매우 흡사하다.
(?) 레고는 더 진보된 모양을 만들기 위해 서로 붙일 수 있다.모두 서로 호환되고, 작동하기 위해선 서로 붙이기만 하면
된다.조각을 바꾸고 싶다면 한 조각의 플러그를 뽑고 다른 조각을 끼우기만 하면 된다.

COM도 마찬가지. COM객체는 실제로 함수를 호출하고 특정 목적을 달성 할 수 있는 C++ 클래스, 혹은 클래스 그룹이다.
어떤 클래스도 작동하기 위해 다른 클래스가 필요 하지 않으며, 함께 작업을 수행하기 위해 실제로 함께 작동할 필요는 없다.
나머지 프로그램을 변경하지 않고도 원하는 대로 플러그인 하거나 분리할 수 있다.

DirectX는 실제로 일련의 COM객체이고, 그중 하나가 Direct3D이다.Direct3D는 다른 COM객체가 내부에 있는 COM객체이다.
궁극적으로 소프트웨어, 하드웨어, 또는 무언가를 활용하여 2D 및 3D그래픽을 실행하는데 필요한 모든 것을 포함한다.

device->CreateRenderTargetView()
device->Release()

Direct3D 클래스에서 CreateRenderTargetVeiw() 및 Release()함수에 엑세스 하기 위해 간접 맴버 엑세스 연산자를 사용한
다.이것이 실제로 어떻게 적용되는지 살펴 본다.

COM의 역할은 모든 복잡성을 숨기는 것 이지만, COM에 대해 알아야 할 네가지 사항이 있다.

1. COM객체는 인터페이스에 의해 제어되는 클래스 또는 클래스 집합이다.인터페이스는 COM객체를 제어하는 함수 집합이다.위
의 예에서 "device"는 COM객체이고 함수는 이를 제어한다.

2. 각 유형의 COM 객체에는 고유한 ID가 있다.예를 들어 Direct3D혹은 DIrectSound객체 모두 다른 고유한 ID를 가진다.때
때로 코드에서 이 ID를 사용해야 한다.

3. COM객체를 사용한 후에는 항상 Release() 함수를 호출해야 한다.이렇게 하면 객체에게 메모리를 해제하고 스레드를 닫으
라고 알린다.

4. COM객체는 일반적으로 'ID3D10Device'와 같이 'I'로 시작하므로 식별하기 쉽다.


Direct3D 헤더
실제 Direct3D 코드로 넘어가기 전에 헤더 파일, 라이브러리 파일, 그리고 다른 것들에 대해 이야기 해본다.
이것들을 살펴보고 무엇인지 알아볼 것이다.

-------------------------------------------------------------------------------------------

// 기본 Windows 헤더 파일  과 Direct3D 헤더 파일을
포함합니다 . #include <windows.h>
#include <windowsx.h> 
#include <d3d11.h> 
#include <d3dx11.h> 
#include <d3dx10.h> 

// Direct3D 라이브러리 파일을 포함합니다. 
#pragma comment (lib, "d3d11.lib") 
#pragma comment (lib, "d3dx11.lib") 
#pragma comment (lib, "d3dx10.lib") 

// 전역 선언 
IDXGISwapChain* swapchain; // 스왑 체인 인터페이스에 대한 포인터 
ID3D11Device* dev; // Direct3D 장치 인터페이스에 대한 포인터 
ID3D11DeviceContext* devcon; // Direct3D 장치 컨텍스트에 대한 포인터 

// 함수 프로토타입 
void InitD3D(HWND hWnd); // Direct3D를 설정하고 초기화합니다. 
void CleanD3D(void); // Direct3D를 닫고 메모리를 해제합니다

. // WindowProc 함수 프로토타입 
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

------------------------------------------------------------------------------------------ -

#include <d3d11.h>
#include <d3dx11.h>

여기에는 Direct3D 11헤더 파일이 포함된다.이러한 파일은 Direct3D 11라이브러리에 포함되어 있다.dxd11.h 파일에는 Dire
ct3D에 대한 확장이 포함되어 있는데, 그래픽 라이브러리에는 필요하지 않지만 게임이나 다른 그래픽 프로그램을 작성 할 때
 매우 유용할 수 있다.

	*모든 컴파일러가 이러한 파일을 자동으로 찾는 것은 아니다.어떤 경우에는 DirectX SDK의 모든 폴더에서 찾도록
	프로젝트를 설정해야 한다.

#include <d3dx10.h>
Direct3D 11은 실제로 Direct3D 10의 확장이다.그러므로 Direct3D 10에서 많은 메크로, 함수, 클래스를 차용했다.
이 헤더를 사용하면 프로그램에서 이를 사용 할 수 있다.

#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx10.lib")

여기에는 Direct3D 11 라이브러리 파일이 포함된다. #pragma comment 지시문은 프로젝트의 개체 파일에 특정 정보를 넣는다.
첫번째 매개변수인 lib를 사용하여 프로젝트에 라이브러리 파일을 추가한다는 것을 선언한다.그리고 d3d11.lib, d3dx11.lib
및 d3dx10.lib 파일을 지정한다.

ID3D11Device* dev
이 변수는 Device에 대한 포인터이다.DIrect3D에서 Device는 비디오 어댑터의 virtual representation(가상표현?) 되도록
의도된 객체이다.이 코드의 줄의 의미는 ID3D11Device라는 COM객체를 생성한다는 것이다.COM이 객체를 만들면 우리는 이 
포인터를 사용하여 간접적으로만 접근할 것이다.

ID3D11DeviceContext* devcon
DeviceContext는 Device와 비슷하지만 GPU와 렌더링 파이프라인을 관리하는 역할을 한다. (device는 주로 비디오 메모리를
처리한다.) 이 객체는 그래픽스를 렌더링하고 렌더링 방법을 결정하는데에 사용한다.

IDXGISwapChain* swapchain
이 변수는 스왑체인에 대한 포인터이다.이 객체는 Direct3D에 속하지 않지만 실제로 Direct3D를 기반으로 하는 DXGI의 일부
이다.

Direct3D 실행

Direc3D를 실제로 코딩하는 첫 번째 단계는 위에서 세 COM 객체를 생성하고 초기화 하는 것 이다. 이는 단일 함수와 그래픽
장치 정보를 포함하는 구조체를 사용하여 수행된다. 여기서 이 함수를 살펴본 다음 해당 부분을 살펴본다.

-------------------------------------------------------------------------------------------

// 이 함수는 Direct3D를 초기화하고 사용할 수 있도록 준비합니다. 
void InitD3D(HWND hWnd)
{
    // 스왑 체인에 대한 정보를 보관할 구조체를 만듭니다 
    . DXGI_SWAP_CHAIN_DESC scd;

    // 사용할 구조체를 지웁니다. 
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // 스왑 체인 설명을 채웁니다. struct 
    scd.BufferCount = 1; // 백 버퍼 하나 
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 32비트 색상 사용 
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 스왑 체인 사용 방법 
    scd.OutputWindow = hWnd; // 사용할 창 
    scd.SampleDesc.Count = 4; // 멀티 샘플 수 
    scd.Windowed = TRUE; // 창 모드/전체 화면 모드 

    // scd 구조체 
    D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL, NULL,
        NULL,
        NULL
        ,
        D3D11_SDK_VERSION,
        &scd,
        &swapchain,
        &dev,
        NULL, &devcon)
        //에 있는 정보를 사용하여 장치, 장치 컨텍스트 및 스왑 체인을 생성

-------------------------------------------------------------------------------------------

DXGI_SWAP_CHAIN_DESC를 설정한다.
    초보 및 고급 게임 프로그래밍에는 처음부터 특정 정보를 DIrect3D에 입력해야 하는 특정 요소가 있다. 이러한 요소는
    많지만 여기서는 몇가지만 살펴본다.

    지금으로서는 DXGI_SWAP_CHAIN_DESC는 멤버가 스왑체인에 대한 설명을 포함하는 구조체이다. 필요한 멤버를 살펴보고,
    튜토리얼 전반에 걸쳐 새로운 멤버가 나오면 다룰 것이다.

ZeroMeMory(&scd, DXGI_SWAP_CHAIN_DESC의 크기)
    ZeroMemory()를 사용하여 scd 구조체 전체를 NULL로 빠르게 초기화한다. 이렇게 하면 구조체의 모든 멤버를 살펴보고
    개별적으로 초기화 할 필요가 없다.

scd.BufferCount = 1
    이 멤버는 스왑 체인에서 사용 할 백버퍼의 수를 포함한다. 백버터와 프런트 버퍼를 하나만 사용할 것이므로 이 값을 1
    로 설정한다. 더 많이 사용 할 수 있지만(디퍼드 렌더링), 아마 1이면 우리가 하는 모든 일에 충분하다.

scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM
    다음 멤버는 색상 형식을 설정하는 데 사용한다. 전면 및 후면 버퍼에서 각 픽셀은 색상별로 저장된다. 이 값은 해당 데
    이터가 어떤 형식으로 저장되는지 결정한다.

    여기서는 Fomat을 DXGI_FORMAT_R8G8B8A8_UNORMd으로 설정한다. 이것은 형식을 나타내는 코드화 된 플래그이다. 여기에
    서 형식에 대해 자세히 알아볼 수 있지만 지금은 변경할 필요가 없다.

scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT
    이 이름들은 점점 더 길어지고 있다. 이 멤버는 우리가 스왑 체인을 어떻게 사용 할 것 인지 알려준다. 이 표는 이에 대
    해 일반적으로 사용되는 두 가지 값이 있다. 많은 플래그 값과 마찬가지로 이러한 플래그는 OR로 함께 사용 할 수 있다.

scd.OutputWindow = hWnd
    이 값은 Direct3D가 그려야 하는 창의 핸들을 설정한다. 우리는 항상 사용해 온 hWnd를 그대로 사용할 것이다.

scd.SampleDesc.Count = 1
    이 멤버는 Direct3D에 멀티샘플 안티앨리어싱(MASS) 렌더링을 수행하는 방법을 알려주는데 사용된다. 기본적으로 안디앨
    리어싱은 각 픽셀을 주변 픽셀과 약간 혼합하려 모양의 가장자리를 매끄럽게 렌더링한다.

    이 값은 Direct3D에 안티앨리어싱에 얼마나 많은 세부 정보를 넣어야 하는지 알려준다. 숫자가 높을 수록 좋다.
        Direct3D 11 비디오 카드는 여기에서 최대 4개를 지원하도록 보장하지만, 최소 값은 1이다.

scd.Windowed = TRUE
    지금 처럼 창에서 Direct3D를 실행하면 이 값은 True로 설정된다. 그렇지 않으면 전체 화면 모드의 경우 FALSE로 설정
    된다.

        참고 : 전체 화면으로 전환하기 전에 해야 할 다은 변경 사항이 있다. 이 값 하나만 변경해도 불행히도 애플리케이
        션이 제대로 전체화면으로 전환되지 않는다.

D3D11CreateDeviceAndSwapChain()
    이것은 큰 기능이지만, 실제로는 매우 간단하다.대부분의 매개변수는 여러분이 쓰는 모든 게임에서 동일하게 유지된다.

    이 함수가 하는 일은 장치, 장치 컨텍스트, 스왑체인 COM 객체를 만드는 것이다.일단 객체를 만들면 실제 렌더링을 수
    행하는데 사용 할 수 있다.

    먼저, 함수의 프로토타입을 살펴보겠습니다.

-------------------------------------------------------------------------------------------

		HRESULT D3D11CreateDeviceAndSwapChain(
			IDXGIAdapter * pAdapter,
			D3D_DRIVER_TYPE DriverType,
			HMODULE Software,
			UINT Flags,
			D3D_FEATURE_LEVEL * pFeatureLevels,
			UINT FeatureLevels,
			UINT SDKVersion,
			DXGI_SWAP_CHAIN_DESC * pSwapChainDesc,
			IDXGISwapChain * *ppSwapChain,
			ID3D11Device * *ppDevice,
			D3D_FEATURE_LEVEL * pFeatureLevel,
			ID3D11DeviceContext * *ppDeviceContext);
-------------------------------------------------------------------------------------------

이제 이 함수의 매개변수로 들어가 보자.

IDXGIAdapter *pAdapter,
    이는 Direct3D가 어떤 그래픽 어댑터를 사용해야 하는지를 나타내는 값이다. 그래픽 어댑터는 일반적으로 GPU와 비디오
    메모리, 디지털-아날로그 변환기 등을 말한다.

    여기서는 DXGI가 처리하도록 하고 넘어간다.(대부분의 경우 하나이기 때문이다.) DXGI에 결정해야 한다는 것을 알리기
    위해 이 매개변수에 NULL을 사용하여 기본 어댑터를 나타낸다.

D3D_DRIVE_TYPE DriverType
    이 매개변수는 Direct3D가 렌더링에 하드웨어를 사용해야 하는지 소프트웨어를 사용해야 하는지를 결정하는데 사용된다.
    이를 결정하는 데 사용 할 수 있는 여러 플래그가 있다.

	D3D_DRIVER_TYPE_HARDWARE	가장 무난한 선택이다. 이것은 렌더링을 위해 고급 GPU 하드웨어를 사용한다.

	D3D_DRIVER_TYPE_REFERENCE	모든 사람이 Direct3D 11을 실행할 수 있는 하드웨어를 가지고 있는 것이 아니므로,
                                그런 사람이 Ditct3D 11기능을 실행하고 싶다면 이 플래그를 사용해야 한다. 느리지만
                                적어도 실행된다.

	D3D_DRIVER_TYPE_SOFTWARE	선택적으로 소프트웨어 기반 렌더링 엔진을 직접 빌드 할 수 있다. 이는 보통 매우느리
                                다.

	D3D_DRIVER_TYPE_WARP	WARP 이전 direct3D 기능을 실행하는 고성능 소프트웨어 엔진이다.

	D3D_DRIVER_TYPE_NULL	렌더링을 하지 않는 경우 사용 가능. Direct3D렌더링 외 프로그램 동작을 위해 GPU의 성능
                            에 엑세스 하는 상황에 사용된다.

HMODULE Software
    이 매개변수는 지금 다루지 않는다. D3D_DRIVER_TYPE_SOFTWARE 플래그와 함께 사용되어 소프트웨어 코드를 설정한다.

UNIT Flags
    플래그. 어렵지 않다. 여기에는 Direct3D가 실행되는 방식을 변경 할 수 있는 몇가지 플래그 값이 있다. 이러한 플래그
    는 서로 OR로 함께 사용 할 수 있다. 다행히도 이러한 플래그 중 어느것도 필요하지 않다. 플래그는 여기 표에 나열되어
    있다.

    D3D11_CREATE_DEVICE_SINGLETHREADED  멀티스레드 렌더링은 기본적으로 활성되어 있다. 허용하지 않고 싶을 때 사용하
                                        는 플래그이다.

    D3D11_CREATE_DEVICE_DEBUG           디버깅을 활성화한다. DIrectX제어판에서도 애플리케이션의 디버깅을 활성화 해
                                        야 할 수 있다. 디버그 메시지는 컴파일러의 출력창에 표시된다.

    D3D11_CREATE_DEVICE_SWITCH_TO_REF   디버킹을 위해 런타임 중에 하드웨어 모드에서 참조 전환 모드로 전환 하는 것이
                                        편리 할 수 있다. 이를 통해 프로그램에서 그렇게 할 수 있다.
                                        
    D3D11_CREATE_DEVICE_BGRA_SUPPORT    이를 통해 Direct2D는 Direct3D와 함께 작업 할 수 있다. Direct2D는 2D 이미
                                        지만 렌더링 하는 별도의 그래픽 라이브러리이다.

D3D_FEATURE_LEVEL *pFeatureLevles
    Direct3D의 각 주요 버전에는 필요한 일련의 비디오 카드 기능이 있다. 하드웨어가 요구 사항을 충족하는 버전을 알고
    있다면 하드웨어의 기능을 더 쉽게 이해 할 수 있다. (고객이 다른 비디오 카드를 가지고 있다는 점을 감안할 때)

    이 매개변수를 사용하면 기능 수준 목록을 만들 수 있다. 이 목록은 Direct3D에 프로그램에서 어떤 기능을 사용할지 알
    려준다.

UINT FeatureLevels
    이 매개변수는 목록에 있는 기능 레벨의 수를 나타낸다.

UINT SDKVersion
    이 매개변수는 항상 D3D11_SDK_VERSION과 동일하다. 왜 그럴까? 다른 기계와의 호환성에서 중요하다. 각 기계는 일
    반적으로 DirectX의 다양한 마이너 버전을 갖는다. 이는 사용자의 DIrectX에 게임을 개발한 버전을 알려준다. 그러
    면 사용자의 DirectX는 뒤돌아보고 그 이후로 발생한 변경 사항을 구련하지 않고도 프로그램을 제대로 실행할 수 있
    다.

DXGI_SWAP_CHAIN_DESC *pSWapChainDesc
    이것은 스왑 체인 구조체에 대한 포인터이다. 우리는 이것을 '& scd'로 채운다.

IDXGISwapChain **psWapChainDesc
    이것은 스왑체인 객체에 대한 포인터를 가리킨다. 이 함수는 우리를 위해 객체를 생성하고 객체의 주소는 이 포인터에 
    저장된다.

ID3D11Device **ppDevice
    이것은 장치 객체에 대한 포인터를 가리키는 포인터이다. 우리는 포인터를 dev로 정의 했으므로 이 매개변수에 &dev를
    넣는다.

D3D_FEATURE_LEVEL* pFeatureLevel
    FeatureLevel에 대한 추가정보. 이것은 FeatureLevel변수에 대한 포인터이다. 함수가 완료되면 변수는 발견된 가장 높
    은 기능 수준의 플래그로 채워진다. 이를 통해 프로그래머는 사용 할 수 있는 하드웨어를 알 수 있다. 이것을 NULL로 설
    정한다.

ID3D11DeviceContext** ppDeviceContext
    이것의 장치 컨텍스트 개체에 대한 포인터를 가리키는 포인터이다. 이 포인터를 'devcon'으로 정의 했으므로 이 매개변수
    에 '&devcon'을 넣는다. 그러면 DeviceContext개체의 주소로 채워진다.

    변수 설정을 완료하면 다음과 같이 입력할 수 있다.
-------------------------------------------------------------------------------------------

D3D11CreateDeviceAndSwapChain(NULL,
                              D3D_DRIVER_TYPE_HARDWARE,
                              NULL,
                              NULL,
                              NULL,
                              NULL,
                              D3D11_SDK_VERSION,
                              &scd,
                              &swapchain,
                              &dev,
                              NULL,
                              &devcon);

-------------------------------------------------------------------------------------------

Driect3D 닫기
    Direct3D가 생성 될 때 마다 닫아야 한다. 이는 매우 간단하다.

    여기에는 세 가지 명령만 있다.

	// 이것은 Direct3D와 COM을 정리하는 함수입니다 
	void CleanD3D()
{
	// 모든 기존 COM 객체를 닫고 해제합니다 
	swapchain->Release();
	dev->Release();
	devcon->Release();
}

여기서 우리가 만든 세 인터페이스, dev, devcon, swapchain 각각에서 Release() 함수를 호출한다. 매개변수도 없고 특별
한 것도 없다. 그냥 모든 것을 정리한다.

기본적으로 COM객체를 생성했지만 닫지 않으면 프로그램 자체가 닫힌 후에도 다음 재부팅까지 컴퓨터의 백그라운드에서 계속
실행된다. 이건 좋지 않은 일이다. 득히 게임의 리소스가 많은 경우 더 나쁘다. COM 객체를 해제하면 모든 것이 풀리고
Windows가 메모리를 다시 가져올 수 있다.