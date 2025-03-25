삼각형 그리기

이번에는 화면에 삼각형을 그리는 법을 배운다. 일련의 정점을 만들고 하드웨어가 화면에 그리도록 하여 이 삼각형을 구축한
다.

여기에는 많은 코드가 필요하다. 삼각형을 렌더링하는 것이 전체화면으로 전환하는 것 만큼 빠르다고 주장하지는 않겠지만,
결국에는 확실히 의미가 있고, 계속 진행하면서 일이 더 쉬워질 것이다. 바로 들어가보자

삼각형을 렌더링하려면 여러가지 작업이 필요하다. 이 레슨은 길지만 다음과 같은 세부사항으로 나뉜다.

1. 먼저 GPU에 지오메트리를 레더링하는 방법을 알려준다.
2. 둘째, 삼각형의 세 정점을 만든다.
3. 셋째, 이 정점을 비디오 메모리에 저장한다.
4. 넷째, GPU에 이 정점을 읽는 방법을 알려준다.
5. 다섯째, 마지막으로 삼각형을 렌더링한다.

이 단계들 각각은 생각보다 어렵지 않다. 하나하나 단계적으로 밟아나간다면 금방 끝낼 수 있다.

섀이더 사용
	첫 번째 단계인 GPU에 삼각형을 렌더링하는 방법을 알려주는 것부터 살펴본다.
	
	렌더링 프로세스는 렝더링 파이프라인에 의해 제어된다. 레슨 1을 기억한다면 렌더링 파이프라인은 렌더링된 이미지를 
	생성하는 일련의 단계라는 것을 기억해야 한다. 불행히도 파이프라인은 무엇을 해야 할지 자동으로 알지 못한다. 먼저
	프로그래밍 해야 하며, 셰이더에 의해 프로그래밍된다.

	셰이더는 셰이더가 셰이드를 제공하지 않기 때문에 오해의 소지가 있는 용어이다. 셰이더는 실제로 파이프라인의 한 단
	계를 제어하는 미니 프로그램이다.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/1.png
	셰이더는 파이프라인을 프로그래밍 한다.

	여러가지 유형의 셰이더가 있으며, 각각은 렌더링 하는 동안 여러번 실행된다. 예를 들어, 정점 셰이더는 렌더링된 각
	정점에 대해 한번씩 실행되는 프로그램이고, 픽셀셰이더는 그려진 각 픽셀에 대해 실행되는 프로그램이다.

	다음 수업에서 셰이더 프로그래밍에 대해 알아본다. 지금은 삼각형을 렝더링하려고 하며, 그러기 위해서는 특정 셰이더를
	GPU에 로드해야 한다.

	셰이더를 로딩하려면 몇 단계가 필요하다. 해야 할 일은 다음과 같다.

	1. .shader파일에서 두 셰이더를 로드하고 컴파일한다.
	2. 두 셰이더를 모두 셰이더 객체로 캡슐화 한다.
	3. 두 셰이더를 모두 활성 셰이더로 설정한다.

	이 단계들은 모두 매우 간단하다. 빠르게 살펴보자.

	1. .shader 파일에서 두개의 셰이더를 로드하고 컴파일한다.
		이 첫번째 부분에서는 두개의 셰이더를 컴파일한다. 이는 정점 셰이더와 픽셀 셰이더로, 렌더링에 필요한 두개의 셰
		이더 이다.

		셰이더를 로드하고 컴파일 하려면 D3DX11CompileFromFile()이라는 함수를 사용한다. 이 함수는 많은 수의 매개변
		수를 가지고 있으며, 놀랍게도 그중 상당수는 0으로 설정하고 나중에 무시할 수 있다.

		먼저, 이 함수의 프로토타입을 살펴본다.

		HRESULT D3DX11CompileFromFile(
			LPCTSTR pSrcFile, // D3D10_SHADER_MACRO 코드를 포함하는 파일 
			*pDefines, // 고급 
			LPD3D10INCLUDE pInclude, // 고급 
			LPCSTR pFunctionName, // 셰이더의 시작 함수 이름 
			LPCSTR pProfile, // 셰이더 프로필 
			UINT Flags1, // 고급 
			UINT Flags2, // 고급 
			ID3DX11ThreadPump* pPump, // 고급 
			ID3D10Blob** ppShader, // 컴파일된 셰이더를 포함하는 blob 
			ID3D10Blob** ppErrorMsgs, // 고급 
			HRESULT* pHResult); // 고급

		모든 배개변수를 살펴보겠지만 "고급"이라고 표시된 매개변수는 무시한다.

		LPCTSTR pSrcFile,
			이 첫번째 매개변수는 컴파일되지 않은 셰이더 코드를 포함하는 파일의 이름이다. 우리에게는 
			L"shader.shader" 가 될것이다. 셰이더는 일반적으로 .shader 확장자를 가진 파일에 저장되지만 원하는 다른
			확장자를 사용할 수도 있다.

		LPCSTR pFunctionName,
			이 매개변수는 셰이더의 이름이다. 코드에서 각 셰이더는 특정 함수로 시작하며, 이는 해당 셰이더의 이름으로
			간주된다. 이 레슨에서 예제 셰이더는 Vshader 및 PShader라고 한다.

		LPCSTR pProfile,
			셰이더 프로파일은 컴파일러에게 우리가 컴파일하는 셰이더의 유형과 컴파일 할 버전을 알려주는 코드이다. 코
			드는 다음과 같이 포멧된다.

			vs_4_0

			여기서 "V"는 정점을 의미라고, "s"는 셰이더를 의미하고, "_4_0"은 HLSL버전 4.0을 의미한다. "V"를 픽셀 셰
			이더의 "p"로 바꿀 수 있다.

			이 함수를 처음 호출 할 떄는 "vs_4_0"을 사용하고 두 번째 호출할 때는 "ps_4_0"을 사용한다.

		ID3D10Blob **ppShader,

			이 매개변수는 blol 객체에 대한 포인터이다. 이 blob 객체는 셰이더의 컴파일 된 코드로 채워진다.

			blob 객체는 데이터 버퍼를 저장하는 깔끔한 작은 COM객체이다. GetBufferPointer() 및 GetBufferSize() 함
			수를 사용하여 콘텐츠에 엑세스 할 수 있다. 아래에서 이에 대한 예를 살펴본다.

		실제 코드로 작성된 함수를 살펴보자. 매우 간단하다.

		ID3D10Blob* VS, * PS;
		D3DX11CompileFromFile(L"셰이더.셰이더", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"셰이더.셰이더", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		이건 정확히 무슨 일을 하는걸까? 정점 셰이더의 경우, "shaders.shader"의 내용을 로드하고, "VShader" 함수를 
		찾고, 버전 4.0 정점 셰이더로 컴파일하고, 컴파일 된 결과를 blob VS에 저장한다.

		이 코드는 커질 것이므로 InitPipeline() 이라는 새 함수에 넣어본다.

		void InitPipeline()
		{
			// 두 셰이더를 로드하고 컴파일합니다. 
			ID3D10Blob* VS, * PS;
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);
		}

		그러면, 컴파일 된 코드로 무엇을 할 수 있는지 알아본다.

	2. 두 셰이더를 모두 활성 셰이더로 설정한다.

		이 단계는 간단하다. 다음과 같다.

		void InitPipeline()
		{
			// 두 셰이더를 로드하고 컴파일합니다 
			ID3D10Blob* VS, * PS;
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

			// 두 셰이더를 셰이더 객체로 캡슐화합니다 
			dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
			dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

			// 셰이더 객체를 설정합니다 
			devcon->VSSetShader(pVS, 0, 0);
			devcon->PSSetShader(pPS, 0, 0);
		}

		이러한 함수의 경우 첫번째 매개변수는 설정할 셰이더의 주소이고, 다른 두객체는 고급 단계이며 나중에 다룬다.

		pVS와 pPS는 모두 COM객체이므로 반드시 해제해야 한다.

		void CleanD3D(void)
		{
			swapchain->SetFullscreenState(FALSE, NULL); // 창 모드로 전환 

			// 모든 기존 COM 객체를 닫고 해제 
			pVS->Release();
			pPS->Release();
			swapchain->Release();
			backbuffer->Release();
			dev->Release();
			devcon->Release();
		}

		요약하자면, 이 함수는 렌더링을 위해 GPU를 준비한다. 정점을 렌더링된 이미지로 변환하는 데 필요한 모든 지침이
		주어졌다. 이제 몇개만 더 있으면 된다.

정점 버퍼
	첫번째 내용에서, 정점의 정의를 다루고 있다. 정점은 3D 공간에서 정확한 점의 위치와 속성이다. 위치는 단순히 정점의
	좌표를 나타내는 세 개의 숫자 값으로 구성된다. 정점의 속성도 숫자 값을 사용하여 정의된다.

	Direct3D는 입력 레이아웃 이라고 하는 것을 사용한다. 입력 레이아웃은 정점의 위치와 속성을 포함하는 데이터의 레이
	아웃이다. 필요에 따라 수정하고 설정할 수 있는 데이터 형식이다. 이것이 정확히 어떻게 작동하는지 살펴본다.

	정점은 구조체로 만들어지며, 구조체에는 3D 이미지를 만드는 데 필요한 데이터가 들어있다. 이미지를 표시하려면 모든
	정보를 GPU에 복사한 다음 Direct3D에 데이터를 백 버퍼에 렌더링 하도록 명령한다. 하지만 정점에 필요한 모든 데이터
	를 보내야 한다면 어떨까? 이런일이 일어난다.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/2.png
	모든 가능한 데이터를 포함하는 Vertex 형식

	물론, 여기서 문제가 무엇인지 바로 알 수 없을 수 도 있지만, 이 정보 블록 중 두 개만 필요하다고 가정한다. 다음과
	같이 하면 GPU로 월씬 더 빨리 보낼 수 있다.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/3.png
	선택적인 정점 형식이 더 빠르게 진행된다.

	입력 레이아웃을 사용할 때 이런 일이 발생한다. 어떤 정보를 사용할지 선택하고, 그 정보만 보내면 각 프레임 사이에 더
	많은 정점을 보낼 수 있다.

	정점 생성
		간단하게 시작해보자. 하나의 정점을 만든다.

		struct VERTEX
		{
			FLOAT X, Y, Z; // 위치 
			D3DXCOLOR Color; // 색상 
		};

		보시다시피, 위치를 나타내는 세개의 float와 색상을 나타내는 하나의 float가 있다.
		이제 이 구조체를 사용하여 실제 정점을 만들어 본다. 다음과 같이 할 수 있다.

		VERTEX OurVertex = {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)};

		물론, 다음과 같이 정점 배열을 만들 수 도 있다.

			VERTEX OurVertices[] =
		{
			{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
			{0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
			{-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
		};

		그 결과 삼각형이 만들어지고, 이 삼각형이 곧 화면에 그려지는 것을 볼 수 있다.

	정점 버퍼 생성
		C++에서 구조 제를 만들면 데이터를 저장해야 한다. 비디오 메모리에 전급 할 수 있도록 DirectX3D는 시스템 메모리
		와 비디오 메모리 모두에 버퍼를 유지할 수 있는 특정 COM 객체를 제공한다.

		버퍼는 시스템 메모리와 비디오 메모리에 어떻게 존재할까? 처음에는 이러한 버퍼의 데이터가 시스템 메모리에 저장
		된다. 렌더링에서 버퍼가 필요할 때, Direct3D가 자동으로 비디오 메모리에 복사한다. 비디오 카드의 메모리가 부족
		해지면 Direct3D는 잠시 사용되지 않았거나 "낮은 우선순위"로 간주되는 버퍼를 삭제하려 새로운 리소스를 위한 공
		간을 마련한다.

		http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/4.png
		필요할 때 비디오 메모리의 정점 버퍼

		왜 Direct3D가 우리를 대신해서 이 작업을 해야 할까? 비디오 메모리에 엑세스 하는 방법은 비디오 카드와 운영체제
		버전에 따라 다르기 때문에 혼자서 이 작업을 하는 것은 매우 어렵다. Direct3D가 우리를 대신해서 이 작업을 관리
		해 주는 것은 매우매우 편리하다.

		이 COM 객체는 ID3D11Buffer라고 한다. 이를 생성하려면 CreateBuffer()함수를 사용한다. 코드는 다음과 같다.

		ID3D11Buffer* pVBuffer; // 전역 

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC; // CPU와 GPU가 액세스하는 쓰기 액세스 
		bd.ByteWidth = sizeof(VERTEX) * 3; // 크기는 VERTEX 구조체 * 3 
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 정점 버퍼로 사용 
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU가 버퍼에 쓸 수 있도록 허용 

		dev->CreateBuffer(&bd, NULL, &pVBuffer); // 버퍼 생성

		이 모든것이 무엇을 의미하는지 알아보자.

		D3D11_BUFFER_DESC bd;
			이는 버퍼의 속성을 담고 있는 구조체이다.

		ZeroMemory(&bd, sizeof(bd));
			많은 Direct3D 구조체와 마찬가지로, 이를 초기화하려면 0으로 설정해야 한다.

		bd.Usage
			버퍼는 가능한 한 효율적으로 설정된다. 이를 올바르게 수행하려면 Direct3D가 버퍼에 액세스 하려는 방법을
			알아야 한다.

			이 표는 여기에서 사용 할 수 있는 다양한 플래그를 보여준다. 이 튜토리얼에서는 동적 사용을 사용할 것이다.

		Flag					CPU Access		GPU Access
		D3D11_USAGE_DEFAULT		None			Read / Write
		DXD11_USAGE_IMMUTABLE	None			Read Only
		DXD11_USAGE_DYNAMIC		Write Only		Read Only
		DXD11_USAGE_STAGING		Read / Write	Read / Write

		bd.ByteWidth
			이 값에는 생성될 버퍼의 크기가 포함된다. 이는 우리가 여기에 넣으려는 정점 배열과 같은 크기이다. 이 수업
			에서는 sizeof(VERTEX) * 3을 계산하여 이를 얻는다.

		bd.BindFlags
			이 값은 Direct3D에 어떤 종류의 버퍼를 만들 것인지 알려준다. 만들 수 있는 버퍼의 종류는 여러가지가 있지
			만, 만들고 싶은 종류는 정점 버퍼이다. 이를 위해 D3D11_BIND_VERTEX_BUFFER 플래그를 사용하면 된다.

			다른 플래그는 이 수업에서는 좀 더 고급이므로 여기서 당장은 다루지 않는다.