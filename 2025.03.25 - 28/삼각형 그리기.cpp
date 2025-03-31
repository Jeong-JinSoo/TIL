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

		bd.CPUAccessFlags
			이 멤버는 Direct3D에 CPU에 엑세스 하는 방법을 알려줌으로써 사용 플래그에 대한 설명을 추가합니다. 여기서
			유일한 플래그는 D3D11_CPU_ACCESS_WRITE와 D3D11_CPU_ACCESS_READ이며, 표 2.1과 일치하도록만 사용할 수
			있다.

			시스템 메모리에서 버퍼로 데이터를 복사하려고 하므로 D3D11_CPU_ACCESS_WRITE를 사용한다.

		dev->CreateBuffer(&bd, NULL, &pVBuffer);
			버퍼를 만드는 함수이다. 첫 번째 매개변수는 설명 구조체의 주소이다. 두 번째 매개 변수는 생성 시 특정 데이
			터로 버퍼를 초기화하는 데 사용할 수 있지만 여기서는 NULL로 설정했다. 세번째 매개변수는 버퍼의 객체 주소
			이다. 여기서 pVBuffer는 정점 버퍼에 대한 포인터를 의미한다.

	정점 버퍼 채우기
		이제 삼각형의 정점이 몇개 있고, 정점을 넣을 정점 버퍼도 있다. 이제 해야 할 일은 정점을 버퍼에 복사하는 것 뿐
		이다.

		그러나 Direct3D는 백그라운드에서 버퍼와 함께 작업 할 수 있으므로 CPU가 직접 버퍼에 액세스 할 수 없다. 버퍼에
		엑세스하려면 버퍼를 메핑해야 한다. 즉, Direct3D는 버퍼에 수행되는 모든 작업을 완료한 다음 버퍼가 매핑 해제 될
		때 까지 GPU가 버퍼와 함께 작업하는 것을 차단한다.

		따라서 정점 버퍼를 채우려면 다음을 수행한다.

		1. 정점 버퍼를 매핑한다. (그러면 버퍼의 위치를 얻는다.)
		2. 데이터를 버퍼에 복사한다.(memcpy()를 사용한다.)
		3. 버퍼의 매핑을 해제한다.

		코드에서는 다음과 같다.

		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // 버퍼 매핑 
		memcpy(ms.pData, OurVertices, sizeof(OurVertices)); // 데이터 복사 
		devcon->Unmap(pVBuffer, NULL); // 버퍼 매핑 해제

		D3D11_MAPPED_SUBRESOURCE ms;
			이것은 우리가 버퍼를 매핑하면 버퍼에 대한 정보로 채워질 구조체이다. 이 정보에는 버퍼의 위치에 대한 포인
			터가 포함되며, "ms.pData"를 사용하여 이 포인터에 엑세스 할 수 있다.

		devcon->Map()
			다음 줄은 버퍼를 매핑하여 접근 할 수 있게 해준다. 매개변수는 꽤 쉽다.
			첫 번째는 버퍼의 객체의 주소이다. 버퍼 포인터는 pVBuffer라고 불리므로 그것을 사용한다.
			두 번째는 고급이다. 나중에 다룬다. 지금은 NULL로 설정해둔다.
			세 번째 매개변수는 매핑되는 동안 버퍼에 대한 CPU액세스를 제어할 수 있는 플래그 세트이다.
			D3D11_MAP_WRITE_DUSCARD를 사용하려고 하지만 다른 플래그는 이 표에서 찾을 수 있다.


		Flag	Description
		D3D11_MAP_READ					버퍼는 CPU에서만 읽을 수 있다.
		DXD11_MAP_WRITE					버퍼는 CPU에서만 쓸 수 있다.
		DXD11_MAP_READ_WRITE			버퍼는 CPU에 의해 읽고 쓸 수 있다.
		DXD11_MAP_WRITE_DISCARD			버퍼의 이전 내용은 지워지고, 새로운 버퍼가 쓰기를 위해 열린다.
		DXD11_MAP_WRITE_NO_OVERWRITE	GPU가 부품을 사용하는 동안에도 버퍼에 더 많은 데이터를 추가할 수 있는 고
										급 플래그.그러나 GPU가 사용하는 부품으로 작업해서는 안된다.

		네 번째 매개 변수는 또 다른 플래그이다. NULL또는 D3D11_MAP_FLAG_DO_NOT_WAIT일 수 있다. 이 플래그는 GPU가
		여전히 버퍼로 작업 중이더라도 프로그램을 계속 진행하도록 강제한다.

		마지막 매개 변수는 D3D11_MAPPED_SUBRESOURCE 구조체의 주소이다. 함수는 여기서 지정한 구조체를 채워서 필요한
		정보를 제공한다.

		memcpy()
			다음으로, 우리는 표전 memcpy()를 수행한다. 우리는 ms.pData를 목적지로, OurVertices(혹은 다른무언가)를
			소스로, sizeof(OurVertices)를 크기로 사용한다.

		devcon->Unmap()
			마지막으로 버퍼를 언맵한다. 이렇게 하면 GPU가 버퍼에 다시 엑세스 할 수 있고 CPU가 다시 차단된다. 첫번째
			매개변수는 버퍼(pVBuffer)이고 두 번째 매개변수는 고급(NULL)이다.

이 섹션에서는 많은 새로운 코드를 다룬다. 모든 것을 마무리하고 더 간단하게 만들기 위해 이 모든 코드를 inGraphics()라
는 별도의 함수에 넣었다. 전체 함수는 다음과 같다.

struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; }; // 정점을 정의하는 구조체 
			ID3D11Buffer* pVBuffer; // 정점 버퍼 

			void InitGraphics()
			{
				// VERTEX를 사용하여 삼각형 생성 struct 
				VERTEX OurVertices[] =
				{
					{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
					{0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
					{-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
				};


				// 정점 버퍼 
				D3D11_BUFFER_DESC 생성 bd;
				ZeroMemory(&bd, sizeof(bd));

				bd.Usage = D3D11_USAGE_DYNAMIC; // CPU와 GPU가 접근하는 쓰기 액세스 
				bd.ByteWidth = sizeof(VERTEX) * 3; // 크기는 VERTEX 구조체 * 3 
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 정점 버퍼로 사용 
				bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU가 버퍼에 쓸 수 있도록 허용 

				dev->CreateBuffer(&bd, NULL, &pVBuffer); // 버퍼 생성 


				// 정점을 버퍼에 복사 
				D3D11_MAPPED_SUBRESOURCE ms;
				devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // 버퍼 매핑 
				memcpy(ms.pData, OurVertices, sizeof(OurVertices)); // 데이터 복사 
				devcon->Unmap(pVBuffer, NULL); // 버퍼 매핑 해제 
			}

이것은 3D 프로그래밍의 핵심 부분이며, 우리는 그것을 사용하고 진행하면서 꽤 많이 수정할 것이다. 이 시점에서 이 섹션을
두 번 정도 살펴보고 정말로 이해했는지 확인하는 것이 좋다.

입력 레이아웃 확인

	지금까지 이 수업에서 우리는

	A) 파이프라인을 제어학 위해 셰이더를 로드하고 설정하고,
	B) 정점을 사용하여 모양을 만들고 GPU에서 사용할 수 있도록 준비했다.

	우리가 정점을 우리 스스로 만든 구조체에 넣었을 때, GPU가 어떻게 정점을 읽을 수 있는지 궁금할 것이다. 우리가 위치
	를 색상보다 먼저 넣었다는 것을 어떻게 할 수 있을까? 우리가 다른 것을 의미하지 않았다는 것을 어떻게 알 수 있을까?

	정답은 입력 레이아웃(input layout)이다.

	앞서 언급했듯이, 렌더링 속도를 개선하기 위해 각 정점에 어떤 정보를 저장할지 선택 할 수 있다. 입력 레이아웃은 정
	점 구조체의 레이아웃을 포함하는 객체로, GPU가 데이터를 적절하고 효율적으로 구성할 수 있도록 한다.

	ID3D11InputLayout 객체는 VERTEX 구조체의 레이아웃을 저장한다. 이 객체를 생성하려면 CreateInputLayout()함수를
	호출한다.

	여기에는 두가지 부분이 있다. 첫째, 정점의 각 요소를 정의해야 한다. 둘째, 입력 레이아웃 객체를 만들어야 한다.

입력 요소 만들기
	정점 레이아웃은 하나 이상의 입력 요소로 구성된다. 입력 요소는 위치나 색상과 같은 정점의 한 속성이다. 각 요소는
	D3D11_INPUT_ELEMENT_DESC 구조체로 정의된다. 이 구조체는 단일 정점 속성을 설명한다. 여러 속성을 가진 정점을 생
	성하려면 이러한 구조체를 배열에 넣기만 하면 된다.

	D3D11_INPUT_ELEMENT_DESCied[] =
	{
		{"위치", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, 정점_데이터당 D3D11_입력_값, 0},
		{"색상", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, 정점_데이터당 D3D11_입력_값, 0},
	};

	이 구조체에는 7개의 값이 있다.

	첫 번째 값은 semantic 이라고 한다.semantic은 GPU에 값이 무엇에 사용되는지 알려주는 문제열이다. 이 표는 몇 가지
	semantic값을 보여주고 있으며, 계속 진행하면서 더 많은 값을 다룰 예정이다.

	Semantic		Values
	POSITION		float, float, float - or -D3DXVECTOR3
	POSITIONT		float, float, float - or -D3DXVECTOR3
	COLOR			float, float, float, float - or -D3DXVECTOR4 - or -D3DXCOLOR
	PSIZE			float

	두 번째 값은 Semantic Index이다. 두가지 색상을 가진 정점이 있다면 둘다 COLOR의미 체계를 사용한다. 혼란을 피하기
	위해 여기서는 각 속성에 다른 숫자를 지정한다.

	세 번째 값은 데이터의 형식이다. 많은 의미론에서 값의 수는 임의적이다.(4개보다 작은 경우) 중요한 것은 형식이 정점
	에서 사용하는 것과 일치한다는 것이다.

	네 번째 값은 입력 슬롯이라고 한다. 이것은 고급이며 나중에 다룰 것이다. 지금은 0이어야 한다.

	다섯 번째 값은 구조체에서 요소가 몇 바이트인지 나타낸다. 이를 오프셋이라고 한다. 보시다시피, 위치는 오프셋 0이고
	색상은 오프셋 12이다. 즉, 위치는 구조체에서 0바이트 에서 시작하고 색상은 구조체에서 12바이트에서 시작한다. 사실,
	D3D11_APPEND_ALIGNED_ELEMENT 를 입력하면 알아서 처리해 주지만, 공간이 부족하다면 어렵다.

	여섯 번째 값은 요소가 사용되는 것이다. 여기에는 두 가지 가능한 플래그가 있지만, 우리가 관심 있는 것은 
	D3D11_INPUT_PER_VERTEX_DATA 이다. 다른 플래그는 나중에 다른다.

	마지막 값은 D3D11_INPUT_PER_VERTEX_DATA 플래그와 함께 사용되지 않으므로 0으로 설정한다.

Input Layout 객체 생성
	이게 우리가 그림을 그리기 시작하기 전 마지막 과정이다.

	여기서 CreateInputLayout()를 호출하여 정점 형식을 나타내는 객체를 만든다. 논의하기 전에 함수의 프로토타입을 살
	펴본다.

	HRESULT CreateInputLayout( 
		D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, 
		UINT NumElements, 
		void *pShaderBytecodeWithInputSignature, 
		SIZE_T BytecodeLength,
		ID3D11InputLayout **pInputLayout);

	이것은 겉보기에 그렇지 않지만 실제로는 Direct3D에서 가장 쉬운 기능 중 하나이다.

	D3D11_INPUT_ELEMENT_DESC *pInputElementDescs
		이 첫 번째 매개변수는 요소 설명 배열에 포함된 포인터이다. 여기에 &ied를 넣는다.

	Unit NumElements,
		꽤 자명한 이 매개변수는 배열의 요소 수이다. 우리의 경우엔 2이다.

	void* pShdaerBytecodeWithINputSignature,
		이것은 파이프라인의 첫 번째 셰이더, 즉 정점 셰이더에 대한 포인터이다. 즉, 여기에 'VS->GetBufferPointer()'
		를 넣었다는 뜻이다.

	SIZE_T BytecodeLength,
		이것은 셰이더 파일의 길이이다. 여기에 'VS->GetBufferSize()'를 넣으면 된다.
	
	ID3D11InputLayout **pInputLayout,
		이것은 입력 레이아웃 객체에 대한 포인터이다. 'pLayout'처럼 간단하게 호출해도 괜찮으므로 여기에 '&pLayout'
		을 넣는다.

	실제로 함수를 작성한 모습은 다음과 같다.

	ID3D11InputLayout* pLayout; // 전역 

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"위치", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_VERTEX_DATA당_입력_값, 0},
		{"색상", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_VERTEX_DATA당_입력_값, 0},
	};

	dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);

	물론, 이 함수를 실행하려면 VSFile과 VSSize에 엑세스해야 하므로 이 코드를 InitPipeline()함수 내부에 바로 삽입한
	다.

	void InitPipeline()
	{
		// 두 셰이더를 로드하고 컴파일합니다 
		.ID3D10Blob* VS, * PS;
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// 두 셰이더를 셰이더 객체로 캡슐화합니다 
		.dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// 셰이더 객체를 설정합니다. 
		devcon->VSSetShader(pVS, 0, 0);
		devcon->PSSetShader(pPS, 0, 0);

		// 입력 레이아웃 객체를 생성합니다 
		. D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	}

	계속하기 전에 마지막으로 한가지 말하자면, 입력 레이아웃을 만드는 것은 설정되기 전 까지는 아무 일도 일어나지 않는
	다. 입력 레이아웃을 설정하려면 IASetInputLayout() 함수를 호출한다. 유일한 매개변수는 입력 레이아웃 객체이다.

	void InitPipeline()
	{
		// 두 셰이더를 로드하고 컴파일합니다 
		.ID3D10Blob* VS, * PS;
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// 두 셰이더를 셰이더 객체로 캡슐화합니다 
		.dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// 셰이더 객체를 설정합니다 
		.devcon->VSSetShader(pVS, 0, 0);
		devcon->PSSetShader(pPS, 0, 0);

		// 입력 레이아웃 객체를 생성합니다 
		.D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		devcon->IASetInputLayout(pLayout);
	}

	이제 실제로 뭔가를 그려보자.

Primitive 그리기
	렌더링을 위해 호출해야 하는 간단한 함수는 세가지가 있다.

	첫 번째는 어떤 정점 버퍼를 사용할 것인지 설정한다. 두 번째는 어떤 유형의 기본형을 사용할 것인지 설정한다.(예: 삼
	각형 목록, 라인스트립 등) 세 번째는 실제로 모양을 그린다.

	IASetVertexBuffers()
		이러한 함수 중 첫 번째는 IASetVertexBuffers()이다. 이것은 렌더링 할 때 어떤 정점을 읽어야 하는지 GPU에 알려
		준다. 몇 가지 쉬운 매개변수가 있으므로 프로토타입을 살펴보자.

		void IASetVertexBuffers(UINT StartSlot,
                        UINT NumBuffers,
                        ID3D11Buffer **ppVertexBuffers,
                        UINT *pStrides,
                        UINT *pOffsets);

		첫 번째 매개변수는 고급이므로 지금은 0으로 설정한다.

		두 번째 매개변수는 우리가 설정하는 버퍼의 수를 알려준다. 버퍼가 하나밖에 없으므로 &pVBuffer로 채울 수 있다.

		네 번째 매개변수는 각 정점 버퍼의 단일 정점 크기를 알려주는 UINT 배열을 가리킨다. 이 매개변수를 채우기 위해
		UINT를 만들고 "sizeof(VERTEX)"로 채우고 해당 UINT의 주소를 여기에 넣는다.

		다섯 번째 매개변수는 렌더링을 시작해야 하는 정점 버퍼의 바이트 수를 알려주는 UINT 배열이다. 보통은 0이다. 이를
		위해 0의 UINT를 생성하고 여기에 주소를 넣는다.

		매개변수를 전부 채우고 나면 다음과 같다.

		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		devcon->IASetVertexBuffers(0, 1, &pBuffer, &stride, &offset);

	IASetPrimitvieTopology()
		이 두 번째 함수는 DIrect3D에 어떤 유형의 기본이 사용되는지 알려준다. 이는 레슨 3에서 다루었지만 사용된 코드
		는 다음과 같다.

		Flag										Description
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST			Shows a series of points, one for each vertex.
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST			Shows a series of separated lines.
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP			Shows a series of connected lines.
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST		Shows a series of separated triangles.
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP		Shows a series of connected triangles.

		이 함수의 유일한 매개변수는 이러한 플래그 중 하나이다. 다음과 같이 작성된다.

		devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DRAW()
		이제 DIrect3D에 어떤 종류의 기본형을 렌더링할지, 어떤 정점 버퍼에서 읽어올지 알려줬으므로, 정점 버퍼에 내용
		을 그리도록 지시한다.

		이 함수는 정점 버퍼의 기본형을 백 버퍼로 그린다.프로토타입은 다음과 같다.

		void Draw(UINT VertexCount,			// 그려질 정점의 수
				  UINT StartVetexLocation);	// 그려질 첫 번째 정점

		이러한 매개변수는 버퍼에서 어떤 정점을 그릴지 제어한다. 두 번째 매개변수는 그려야 할 버퍼의 첫 번째 정점을
		알려주는 숫자이고, 첫번째 매개변수는 그려야 할 정점의 수이다.

		실제로 함수는 다음과 같다.

		devcon->Draw(3, 0); // 정점 0부터 시작하여 3개의 정점을 그립니다.

		이제 수정한 render_frame() 함수 전체를 살펴본다.

		// 단일 프레임을 렌더링하는 데 사용되는 함수 
		void RenderFrame(void)
		{
			// 백 버퍼를 진한 파란색으로 지웁니다 
			devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

			// 표시할 정점 버퍼를 선택합니다 
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

			// 사용할 기본 유형을 선택합니다 
			devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// 정점 버퍼를 백 버퍼에 그립니다 
			devcon->Draw(3, 0);

			// 백 버퍼와 프런트 버퍼를 전환합니다 
			swapchain->Present(0, 0);
		}

		정점 버퍼를 구축하고 셰이더를 로딩하는 것에 비하면 그림 그리기는 놀라울 정도로 간단하다.

완성된 프로그램
	이 프로그램을 빌드하고 실행하기 전에 셰이더 파일 자체가 필요하다. "Shaders.shader"라고 하며, 내용은 아래 "Show
	Shaders" 라고 적힌 곳에서 찾을 수 있다. 이 시점에서는 셰이더 코드를 반드시 이해할 필요는 없다. 다음 튜토리얼에서
	자세히 다룬다.

	이 파일은 프로젝트 폴더 자체에 저장해야 한다. 솔루션 탐색기에서 '모든 파일 표시'를 실행 할 수 없다. 다음과 같아
	야한다.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/5.png
	솔루션 탐색기의 셰이더 파일

	최종 DirectX 코드를 살펴본다.
	//동일 경로 내 main.cpp, Shader.shader 파일 참고

	계속해서 업데이트 하고 어떤 결과가 나오는지 살펴본다. 이것을 실행하면 화면에 다음과 같이 표시된다.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/6.png
	렌더링 된 삼각형