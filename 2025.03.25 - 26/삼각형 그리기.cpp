�ﰢ�� �׸���

�̹����� ȭ�鿡 �ﰢ���� �׸��� ���� ����. �Ϸ��� ������ ����� �ϵ��� ȭ�鿡 �׸����� �Ͽ� �� �ﰢ���� ������
��.

���⿡�� ���� �ڵ尡 �ʿ��ϴ�. �ﰢ���� �������ϴ� ���� ��üȭ������ ��ȯ�ϴ� �� ��ŭ �����ٰ� ���������� �ʰ�����,
�ᱹ���� Ȯ���� �ǹ̰� �ְ�, ��� �����ϸ鼭 ���� �� ������ ���̴�. �ٷ� ������

�ﰢ���� �������Ϸ��� �������� �۾��� �ʿ��ϴ�. �� ������ ������ ������ ���� ���λ������� ������.

1. ���� GPU�� ������Ʈ���� �������ϴ� ����� �˷��ش�.
2. ��°, �ﰢ���� �� ������ �����.
3. ��°, �� ������ ���� �޸𸮿� �����Ѵ�.
4. ��°, GPU�� �� ������ �д� ����� �˷��ش�.
5. �ټ�°, ���������� �ﰢ���� �������Ѵ�.

�� �ܰ�� ������ �������� ����� �ʴ�. �ϳ��ϳ� �ܰ������� ��Ƴ����ٸ� �ݹ� ���� �� �ִ�.

���̴� ���
	ù ��° �ܰ��� GPU�� �ﰢ���� �������ϴ� ����� �˷��ִ� �ͺ��� ���캻��.
	
	������ ���μ����� ������ ���������ο� ���� ����ȴ�. ���� 1�� ����Ѵٸ� ������ ������������ �������� �̹����� 
	�����ϴ� �Ϸ��� �ܰ��� ���� ����ؾ� �Ѵ�. �������� ������������ ������ �ؾ� ���� �ڵ����� ���� ���Ѵ�. ����
	���α׷��� �ؾ� �ϸ�, ���̴��� ���� ���α׷��ֵȴ�.

	���̴��� ���̴��� ���̵带 �������� �ʱ� ������ ������ ������ �ִ� ����̴�. ���̴��� ������ ������������ �� ��
	�踦 �����ϴ� �̴� ���α׷��̴�.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/1.png
	���̴��� ������������ ���α׷��� �Ѵ�.

	�������� ������ ���̴��� ������, ������ ������ �ϴ� ���� ������ ����ȴ�. ���� ���, ���� ���̴��� �������� ��
	������ ���� �ѹ��� ����Ǵ� ���α׷��̰�, �ȼ����̴��� �׷��� �� �ȼ��� ���� ����Ǵ� ���α׷��̴�.

	���� �������� ���̴� ���α׷��ֿ� ���� �˾ƺ���. ������ �ﰢ���� �������Ϸ��� �ϸ�, �׷��� ���ؼ��� Ư�� ���̴���
	GPU�� �ε��ؾ� �Ѵ�.

	���̴��� �ε��Ϸ��� �� �ܰ谡 �ʿ��ϴ�. �ؾ� �� ���� ������ ����.

	1. .shader���Ͽ��� �� ���̴��� �ε��ϰ� �������Ѵ�.
	2. �� ���̴��� ��� ���̴� ��ü�� ĸ��ȭ �Ѵ�.
	3. �� ���̴��� ��� Ȱ�� ���̴��� �����Ѵ�.

	�� �ܰ���� ��� �ſ� �����ϴ�. ������ ���캸��.

	1. .shader ���Ͽ��� �ΰ��� ���̴��� �ε��ϰ� �������Ѵ�.
		�� ù��° �κп����� �ΰ��� ���̴��� �������Ѵ�. �̴� ���� ���̴��� �ȼ� ���̴���, �������� �ʿ��� �ΰ��� ��
		�̴� �̴�.

		���̴��� �ε��ϰ� ������ �Ϸ��� D3DX11CompileFromFile()�̶�� �Լ��� ����Ѵ�. �� �Լ��� ���� ���� �Ű���
		���� ������ ������, ����Ե� ���� ������ 0���� �����ϰ� ���߿� ������ �� �ִ�.

		����, �� �Լ��� ������Ÿ���� ���캻��.

		HRESULT D3DX11CompileFromFile(
			LPCTSTR pSrcFile, // D3D10_SHADER_MACRO �ڵ带 �����ϴ� ���� 
			*pDefines, // ��� 
			LPD3D10INCLUDE pInclude, // ��� 
			LPCSTR pFunctionName, // ���̴��� ���� �Լ� �̸� 
			LPCSTR pProfile, // ���̴� ������ 
			UINT Flags1, // ��� 
			UINT Flags2, // ��� 
			ID3DX11ThreadPump* pPump, // ��� 
			ID3D10Blob** ppShader, // �����ϵ� ���̴��� �����ϴ� blob 
			ID3D10Blob** ppErrorMsgs, // ��� 
			HRESULT* pHResult); // ���

		��� �谳������ ���캸������ "���"�̶�� ǥ�õ� �Ű������� �����Ѵ�.

		LPCTSTR pSrcFile,
			�� ù��° �Ű������� �����ϵ��� ���� ���̴� �ڵ带 �����ϴ� ������ �̸��̴�. �츮���Դ� 
			L"shader.shader" �� �ɰ��̴�. ���̴��� �Ϲ������� .shader Ȯ���ڸ� ���� ���Ͽ� ��������� ���ϴ� �ٸ�
			Ȯ���ڸ� ����� ���� �ִ�.

		LPCSTR pFunctionName,
			�� �Ű������� ���̴��� �̸��̴�. �ڵ忡�� �� ���̴��� Ư�� �Լ��� �����ϸ�, �̴� �ش� ���̴��� �̸�����
			���ֵȴ�. �� �������� ���� ���̴��� Vshader �� PShader��� �Ѵ�.

		LPCSTR pProfile,
			���̴� ���������� �����Ϸ����� �츮�� �������ϴ� ���̴��� ������ ������ �� ������ �˷��ִ� �ڵ��̴�. ��
			��� ������ ���� ����ȴ�.

			vs_4_0

			���⼭ "V"�� ������ �ǹ̶��, "s"�� ���̴��� �ǹ��ϰ�, "_4_0"�� HLSL���� 4.0�� �ǹ��Ѵ�. "V"�� �ȼ� ��
			�̴��� "p"�� �ٲ� �� �ִ�.

			�� �Լ��� ó�� ȣ�� �� ���� "vs_4_0"�� ����ϰ� �� ��° ȣ���� ���� "ps_4_0"�� ����Ѵ�.

		ID3D10Blob **ppShader,

			�� �Ű������� blol ��ü�� ���� �������̴�. �� blob ��ü�� ���̴��� ������ �� �ڵ�� ä������.

			blob ��ü�� ������ ���۸� �����ϴ� ����� ���� COM��ü�̴�. GetBufferPointer() �� GetBufferSize() ��
			���� ����Ͽ� �������� ������ �� �� �ִ�. �Ʒ����� �̿� ���� ���� ���캻��.

		���� �ڵ�� �ۼ��� �Լ��� ���캸��. �ſ� �����ϴ�.

		ID3D10Blob* VS, * PS;
		D3DX11CompileFromFile(L"���̴�.���̴�", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"���̴�.���̴�", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		�̰� ��Ȯ�� ���� ���� �ϴ°ɱ�? ���� ���̴��� ���, "shaders.shader"�� ������ �ε��ϰ�, "VShader" �Լ��� 
		ã��, ���� 4.0 ���� ���̴��� �������ϰ�, ������ �� ����� blob VS�� �����Ѵ�.

		�� �ڵ�� Ŀ�� ���̹Ƿ� InitPipeline() �̶�� �� �Լ��� �־��.

		void InitPipeline()
		{
			// �� ���̴��� �ε��ϰ� �������մϴ�. 
			ID3D10Blob* VS, * PS;
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);
		}

		�׷���, ������ �� �ڵ�� ������ �� �� �ִ��� �˾ƺ���.

	2. �� ���̴��� ��� Ȱ�� ���̴��� �����Ѵ�.

		�� �ܰ�� �����ϴ�. ������ ����.

		void InitPipeline()
		{
			// �� ���̴��� �ε��ϰ� �������մϴ� 
			ID3D10Blob* VS, * PS;
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

			// �� ���̴��� ���̴� ��ü�� ĸ��ȭ�մϴ� 
			dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
			dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

			// ���̴� ��ü�� �����մϴ� 
			devcon->VSSetShader(pVS, 0, 0);
			devcon->PSSetShader(pPS, 0, 0);
		}

		�̷��� �Լ��� ��� ù��° �Ű������� ������ ���̴��� �ּ��̰�, �ٸ� �ΰ�ü�� ��� �ܰ��̸� ���߿� �ٷ��.

		pVS�� pPS�� ��� COM��ü�̹Ƿ� �ݵ�� �����ؾ� �Ѵ�.

		void CleanD3D(void)
		{
			swapchain->SetFullscreenState(FALSE, NULL); // â ���� ��ȯ 

			// ��� ���� COM ��ü�� �ݰ� ���� 
			pVS->Release();
			pPS->Release();
			swapchain->Release();
			backbuffer->Release();
			dev->Release();
			devcon->Release();
		}

		������ڸ�, �� �Լ��� �������� ���� GPU�� �غ��Ѵ�. ������ �������� �̹����� ��ȯ�ϴ� �� �ʿ��� ��� ��ħ��
		�־�����. ���� ��� �� ������ �ȴ�.

���� ����
	ù��° ���뿡��, ������ ���Ǹ� �ٷ�� �ִ�. ������ 3D �������� ��Ȯ�� ���� ��ġ�� �Ӽ��̴�. ��ġ�� �ܼ��� ������
	��ǥ�� ��Ÿ���� �� ���� ���� ������ �����ȴ�. ������ �Ӽ��� ���� ���� ����Ͽ� ���ǵȴ�.

	Direct3D�� �Է� ���̾ƿ� �̶�� �ϴ� ���� ����Ѵ�. �Է� ���̾ƿ��� ������ ��ġ�� �Ӽ��� �����ϴ� �������� ����
	�ƿ��̴�. �ʿ信 ���� �����ϰ� ������ �� �ִ� ������ �����̴�. �̰��� ��Ȯ�� ��� �۵��ϴ��� ���캻��.

	������ ����ü�� ���������, ����ü���� 3D �̹����� ����� �� �ʿ��� �����Ͱ� ����ִ�. �̹����� ǥ���Ϸ��� ���
	������ GPU�� ������ ���� Direct3D�� �����͸� �� ���ۿ� ������ �ϵ��� ����Ѵ�. ������ ������ �ʿ��� ��� ������
	�� ������ �Ѵٸ� ���? �̷����� �Ͼ��.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/2.png
	��� ������ �����͸� �����ϴ� Vertex ����

	����, ���⼭ ������ �������� �ٷ� �� �� ���� �� �� ������, �� ���� ��� �� �� ���� �ʿ��ϴٰ� �����Ѵ�. ������
	���� �ϸ� GPU�� ���� �� ���� ���� �� �ִ�.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/3.png
	�������� ���� ������ �� ������ ����ȴ�.

	�Է� ���̾ƿ��� ����� �� �̷� ���� �߻��Ѵ�. � ������ ������� �����ϰ�, �� ������ ������ �� ������ ���̿� ��
	���� ������ ���� �� �ִ�.

	���� ����
		�����ϰ� �����غ���. �ϳ��� ������ �����.

		struct VERTEX
		{
			FLOAT X, Y, Z; // ��ġ 
			D3DXCOLOR Color; // ���� 
		};

		���ôٽ���, ��ġ�� ��Ÿ���� ������ float�� ������ ��Ÿ���� �ϳ��� float�� �ִ�.
		���� �� ����ü�� ����Ͽ� ���� ������ ����� ����. ������ ���� �� �� �ִ�.

		VERTEX OurVertex = {0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)};

		����, ������ ���� ���� �迭�� ���� �� �� �ִ�.

			VERTEX OurVertices[] =
		{
			{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
			{0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
			{-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
		};

		�� ��� �ﰢ���� ���������, �� �ﰢ���� �� ȭ�鿡 �׷����� ���� �� �� �ִ�.

	���� ���� ����
		C++���� ���� ���� ����� �����͸� �����ؾ� �Ѵ�. ���� �޸𸮿� ���� �� �� �ֵ��� DirectX3D�� �ý��� �޸�
		�� ���� �޸� ��ο� ���۸� ������ �� �ִ� Ư�� COM ��ü�� �����Ѵ�.

		���۴� �ý��� �޸𸮿� ���� �޸𸮿� ��� �����ұ�? ó������ �̷��� ������ �����Ͱ� �ý��� �޸𸮿� ����
		�ȴ�. ���������� ���۰� �ʿ��� ��, Direct3D�� �ڵ����� ���� �޸𸮿� �����Ѵ�. ���� ī���� �޸𸮰� ����
		������ Direct3D�� ��� ������ �ʾҰų� "���� �켱����"�� ���ֵǴ� ���۸� �����Ϸ� ���ο� ���ҽ��� ���� ��
		���� �����Ѵ�.

		http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/4.png
		�ʿ��� �� ���� �޸��� ���� ����

		�� Direct3D�� �츮�� ����ؼ� �� �۾��� �ؾ� �ұ�? ���� �޸𸮿� ������ �ϴ� ����� ���� ī��� �ü��
		������ ���� �ٸ��� ������ ȥ�ڼ� �� �۾��� �ϴ� ���� �ſ� ��ƴ�. Direct3D�� �츮�� ����ؼ� �� �۾��� ����
		�� �ִ� ���� �ſ�ſ� ���ϴ�.

		�� COM ��ü�� ID3D11Buffer��� �Ѵ�. �̸� �����Ϸ��� CreateBuffer()�Լ��� ����Ѵ�. �ڵ�� ������ ����.

		ID3D11Buffer* pVBuffer; // ���� 

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC; // CPU�� GPU�� �׼����ϴ� ���� �׼��� 
		bd.ByteWidth = sizeof(VERTEX) * 3; // ũ��� VERTEX ����ü * 3 
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ���۷� ��� 
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU�� ���ۿ� �� �� �ֵ��� ��� 

		dev->CreateBuffer(&bd, NULL, &pVBuffer); // ���� ����

		�� ������ ������ �ǹ��ϴ��� �˾ƺ���.

		D3D11_BUFFER_DESC bd;
			�̴� ������ �Ӽ��� ��� �ִ� ����ü�̴�.

		ZeroMemory(&bd, sizeof(bd));
			���� Direct3D ����ü�� ����������, �̸� �ʱ�ȭ�Ϸ��� 0���� �����ؾ� �Ѵ�.

		bd.Usage
			���۴� ������ �� ȿ�������� �����ȴ�. �̸� �ùٸ��� �����Ϸ��� Direct3D�� ���ۿ� �׼��� �Ϸ��� �����
			�˾ƾ� �Ѵ�.

			�� ǥ�� ���⿡�� ��� �� �� �ִ� �پ��� �÷��׸� �����ش�. �� Ʃ�丮�󿡼��� ���� ����� ����� ���̴�.

		Flag					CPU Access		GPU Access
		D3D11_USAGE_DEFAULT		None			Read / Write
		DXD11_USAGE_IMMUTABLE	None			Read Only
		DXD11_USAGE_DYNAMIC		Write Only		Read Only
		DXD11_USAGE_STAGING		Read / Write	Read / Write

		bd.ByteWidth
			�� ������ ������ ������ ũ�Ⱑ ���Եȴ�. �̴� �츮�� ���⿡ �������� ���� �迭�� ���� ũ���̴�. �� ����
			������ sizeof(VERTEX) * 3�� ����Ͽ� �̸� ��´�.

		bd.BindFlags
			�� ���� Direct3D�� � ������ ���۸� ���� ������ �˷��ش�. ���� �� �ִ� ������ ������ ���������� ����
			��, ����� ���� ������ ���� �����̴�. �̸� ���� D3D11_BIND_VERTEX_BUFFER �÷��׸� ����ϸ� �ȴ�.

			�ٸ� �÷��״� �� ���������� �� �� ����̹Ƿ� ���⼭ ������ �ٷ��� �ʴ´�.

		bd.CPUAccessFlags
			�� ����� Direct3D�� CPU�� ������ �ϴ� ����� �˷������ν� ��� �÷��׿� ���� ������ �߰��մϴ�. ���⼭
			������ �÷��״� D3D11_CPU_ACCESS_WRITE�� D3D11_CPU_ACCESS_READ�̸�, ǥ 2.1�� ��ġ�ϵ��ϸ� ����� ��
			�ִ�.

			�ý��� �޸𸮿��� ���۷� �����͸� �����Ϸ��� �ϹǷ� D3D11_CPU_ACCESS_WRITE�� ����Ѵ�.

		dev->CreateBuffer(&bd, NULL, &pVBuffer);
			���۸� ����� �Լ��̴�. ù ��° �Ű������� ���� ����ü�� �ּ��̴�. �� ��° �Ű� ������ ���� �� Ư�� ����
			�ͷ� ���۸� �ʱ�ȭ�ϴ� �� ����� �� ������ ���⼭�� NULL�� �����ߴ�. ����° �Ű������� ������ ��ü �ּ�
			�̴�. ���⼭ pVBuffer�� ���� ���ۿ� ���� �����͸� �ǹ��Ѵ�.

	���� ���� ä���
		���� �ﰢ���� ������ � �ְ�, ������ ���� ���� ���۵� �ִ�. ���� �ؾ� �� ���� ������ ���ۿ� �����ϴ� �� ��
		�̴�.

		�׷��� Direct3D�� ��׶��忡�� ���ۿ� �Բ� �۾� �� �� �����Ƿ� CPU�� ���� ���ۿ� �׼��� �� �� ����. ���ۿ�
		�������Ϸ��� ���۸� �����ؾ� �Ѵ�. ��, Direct3D�� ���ۿ� ����Ǵ� ��� �۾��� �Ϸ��� ���� ���۰� ���� ���� ��
		�� ���� GPU�� ���ۿ� �Բ� �۾��ϴ� ���� �����Ѵ�.

		���� ���� ���۸� ä����� ������ �����Ѵ�.

		1. ���� ���۸� �����Ѵ�. (�׷��� ������ ��ġ�� ��´�.)
		2. �����͸� ���ۿ� �����Ѵ�.(memcpy()�� ����Ѵ�.)
		3. ������ ������ �����Ѵ�.

		�ڵ忡���� ������ ����.

		D3D11_MAPPED_SUBRESOURCE ms;
		devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // ���� ���� 
		memcpy(ms.pData, OurVertices, sizeof(OurVertices)); // ������ ���� 
		devcon->Unmap(pVBuffer, NULL); // ���� ���� ����

		D3D11_MAPPED_SUBRESOURCE ms;
			�̰��� �츮�� ���۸� �����ϸ� ���ۿ� ���� ������ ä���� ����ü�̴�. �� �������� ������ ��ġ�� ���� ����
			�Ͱ� ���ԵǸ�, "ms.pData"�� ����Ͽ� �� �����Ϳ� ������ �� �� �ִ�.

		devcon->Map()
			���� ���� ���۸� �����Ͽ� ���� �� �� �ְ� ���ش�. �Ű������� �� ����.
			ù ��°�� ������ ��ü�� �ּ��̴�. ���� �����ʹ� pVBuffer��� �Ҹ��Ƿ� �װ��� ����Ѵ�.
			�� ��°�� ����̴�. ���߿� �ٷ��. ������ NULL�� �����صд�.
			�� ��° �Ű������� ���εǴ� ���� ���ۿ� ���� CPU�׼����� ������ �� �ִ� �÷��� ��Ʈ�̴�.
			D3D11_MAP_WRITE_DUSCARD�� ����Ϸ��� ������ �ٸ� �÷��״� �� ǥ���� ã�� �� �ִ�.


		Flag	Description
		D3D11_MAP_READ					���۴� CPU������ ���� �� �ִ�.
		DXD11_MAP_WRITE					���۴� CPU������ �� �� �ִ�.
		DXD11_MAP_READ_WRITE			���۴� CPU�� ���� �а� �� �� �ִ�.
		DXD11_MAP_WRITE_DISCARD			������ ���� ������ ��������, ���ο� ���۰� ���⸦ ���� ������.
		DXD11_MAP_WRITE_NO_OVERWRITE	GPU�� ��ǰ�� ����ϴ� ���ȿ��� ���ۿ� �� ���� �����͸� �߰��� �� �ִ� ��
										�� �÷���.�׷��� GPU�� ����ϴ� ��ǰ���� �۾��ؼ��� �ȵȴ�.

		�� ��° �Ű� ������ �� �ٸ� �÷����̴�. NULL�Ǵ� D3D11_MAP_FLAG_DO_NOT_WAIT�� �� �ִ�. �� �÷��״� GPU��
		������ ���۷� �۾� ���̴��� ���α׷��� ��� �����ϵ��� �����Ѵ�.

		������ �Ű� ������ D3D11_MAPPED_SUBRESOURCE ����ü�� �ּ��̴�. �Լ��� ���⼭ ������ ����ü�� ä���� �ʿ���
		������ �����Ѵ�.

		memcpy()
			��������, �츮�� ǥ�� memcpy()�� �����Ѵ�. �츮�� ms.pData�� ��������, OurVertices(Ȥ�� �ٸ�����)��
			�ҽ���, sizeof(OurVertices)�� ũ��� ����Ѵ�.

		devcon->Unmap()
			���������� ���۸� ����Ѵ�. �̷��� �ϸ� GPU�� ���ۿ� �ٽ� ������ �� �� �ְ� CPU�� �ٽ� ���ܵȴ�. ù��°
			�Ű������� ����(pVBuffer)�̰� �� ��° �Ű������� ���(NULL)�̴�.

�� ���ǿ����� ���� ���ο� �ڵ带 �ٷ��. ��� ���� �������ϰ� �� �����ϰ� ����� ���� �� ��� �ڵ带 inGraphics()��
�� ������ �Լ��� �־���. ��ü �Լ��� ������ ����.

struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; }; // ������ �����ϴ� ����ü 
			ID3D11Buffer* pVBuffer; // ���� ���� 

			void InitGraphics()
			{
				// VERTEX�� ����Ͽ� �ﰢ�� ���� struct 
				VERTEX OurVertices[] =
				{
					{0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)},
					{0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f)},
					{-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f)}
				};


				// ���� ���� 
				D3D11_BUFFER_DESC ���� bd;
				ZeroMemory(&bd, sizeof(bd));

				bd.Usage = D3D11_USAGE_DYNAMIC; // CPU�� GPU�� �����ϴ� ���� �׼��� 
				bd.ByteWidth = sizeof(VERTEX) * 3; // ũ��� VERTEX ����ü * 3 
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ���۷� ��� 
				bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU�� ���ۿ� �� �� �ֵ��� ��� 

				dev->CreateBuffer(&bd, NULL, &pVBuffer); // ���� ���� 


				// ������ ���ۿ� ���� 
				D3D11_MAPPED_SUBRESOURCE ms;
				devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // ���� ���� 
				memcpy(ms.pData, OurVertices, sizeof(OurVertices)); // ������ ���� 
				devcon->Unmap(pVBuffer, NULL); // ���� ���� ���� 
			}

�̰��� 3D ���α׷����� �ٽ� �κ��̸�, �츮�� �װ��� ����ϰ� �����ϸ鼭 �� ���� ������ ���̴�. �� �������� �� ������
�� �� ���� ���캸�� ������ �����ߴ��� Ȯ���ϴ� ���� ����.

�Է� ���̾ƿ� Ȯ��

	���ݱ��� �� �������� �츮��

	A) ������������ ������ ���� ���̴��� �ε��ϰ� �����ϰ�,
	B) ������ ����Ͽ� ����� ����� GPU���� ����� �� �ֵ��� �غ��ߴ�.

	�츮�� ������ �츮 ������ ���� ����ü�� �־��� ��, GPU�� ��� ������ ���� �� �ִ��� �ñ��� ���̴�. �츮�� ��ġ
	�� ���󺸴� ���� �־��ٴ� ���� ��� �� �� ������? �츮�� �ٸ� ���� �ǹ����� �ʾҴٴ� ���� ��� �� �� ������?

	������ �Է� ���̾ƿ�(input layout)�̴�.

	�ռ� ����ߵ���, ������ �ӵ��� �����ϱ� ���� �� ������ � ������ �������� ���� �� �� �ִ�. �Է� ���̾ƿ��� ��
	�� ����ü�� ���̾ƿ��� �����ϴ� ��ü��, GPU�� �����͸� �����ϰ� ȿ�������� ������ �� �ֵ��� �Ѵ�.

	ID3D11InputLayout ��ü�� VERTEX ����ü�� ���̾ƿ��� �����Ѵ�. �� ��ü�� �����Ϸ��� CreateInputLayout()�Լ���
	ȣ���Ѵ�.

	���⿡�� �ΰ��� �κ��� �ִ�. ù°, ������ �� ��Ҹ� �����ؾ� �Ѵ�. ��°, �Է� ���̾ƿ� ��ü�� ������ �Ѵ�.

�Է� ��� �����
	���� ���̾ƿ��� �ϳ� �̻��� �Է� ��ҷ� �����ȴ�. �Է� ��Ҵ� ��ġ�� ����� ���� ������ �� �Ӽ��̴�. �� ��Ҵ�
	D3D11_INPUT_ELEMENT_DESC ����ü�� ���ǵȴ�. �� ����ü�� ���� ���� �Ӽ��� �����Ѵ�. ���� �Ӽ��� ���� ������ ��
	���Ϸ��� �̷��� ����ü�� �迭�� �ֱ⸸ �ϸ� �ȴ�.

	D3D11_INPUT_ELEMENT_DESCied[] =
	{
		{"��ġ", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, ����_�����ʹ� D3D11_�Է�_��, 0},
		{"����", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, ����_�����ʹ� D3D11_�Է�_��, 0},
	};

	�� ����ü���� 7���� ���� �ִ�.

	ù ��° ���� semantic �̶�� �Ѵ�.semantic�� GPU�� ���� ������ ���Ǵ��� �˷��ִ� �������̴�. �� ǥ�� �� ����
	semantic���� �����ְ� ������, ��� �����ϸ鼭 �� ���� ���� �ٷ� �����̴�.

	Semantic		Values
	POSITION		float, float, float - or -D3DXVECTOR3
	POSITIONT		float, float, float - or -D3DXVECTOR3
	COLOR			float, float, float, float - or -D3DXVECTOR4 - or -D3DXCOLOR
	PSIZE			float

	�� ��° ���� Semantic Index�̴�. �ΰ��� ������ ���� ������ �ִٸ� �Ѵ� COLOR�ǹ� ü�踦 ����Ѵ�. ȥ���� ���ϱ�
	���� ���⼭�� �� �Ӽ��� �ٸ� ���ڸ� �����Ѵ�.

	�� ��° ���� �������� �����̴�. ���� �ǹ̷п��� ���� ���� �������̴�.(4������ ���� ���) �߿��� ���� ������ ����
	���� ����ϴ� �Ͱ� ��ġ�Ѵٴ� ���̴�.

	�� ��° ���� �Է� �����̶�� �Ѵ�. �̰��� ����̸� ���߿� �ٷ� ���̴�. ������ 0�̾�� �Ѵ�.

	�ټ� ��° ���� ����ü���� ��Ұ� �� ����Ʈ���� ��Ÿ����. �̸� �������̶�� �Ѵ�. ���ôٽ���, ��ġ�� ������ 0�̰�
	������ ������ 12�̴�. ��, ��ġ�� ����ü���� 0����Ʈ ���� �����ϰ� ������ ����ü���� 12����Ʈ���� �����Ѵ�. ���,
	D3D11_APPEND_ALIGNED_ELEMENT �� �Է��ϸ� �˾Ƽ� ó���� ������, ������ �����ϴٸ� ��ƴ�.

	���� ��° ���� ��Ұ� ���Ǵ� ���̴�. ���⿡�� �� ���� ������ �÷��װ� ������, �츮�� ���� �ִ� ���� 
	D3D11_INPUT_PER_VERTEX_DATA �̴�. �ٸ� �÷��״� ���߿� �ٸ���.

	������ ���� D3D11_INPUT_PER_VERTEX_DATA �÷��׿� �Բ� ������ �����Ƿ� 0���� �����Ѵ�.

Input Layout ��ü ����
	�̰� �츮�� �׸��� �׸��� �����ϱ� �� ������ �����̴�.

	���⼭ CreateInputLayout()�� ȣ���Ͽ� ���� ������ ��Ÿ���� ��ü�� �����. �����ϱ� ���� �Լ��� ������Ÿ���� ��
	�캻��.

	HRESULT CreateInputLayout( 
		D3D11_INPUT_ELEMENT_DESC *pInputElementDescs, 
		UINT NumElements, 
		void *pShaderBytecodeWithInputSignature, 
		SIZE_T BytecodeLength,
		ID3D11InputLayout **pInputLayout);

	�̰��� �Ѻ��⿡ �׷��� ������ �����δ� Direct3D���� ���� ���� ��� �� �ϳ��̴�.

	D3D11_INPUT_ELEMENT_DESC *pInputElementDescs
		�� ù ��° �Ű������� ��� ���� �迭�� ���Ե� �������̴�. ���⿡ &ied�� �ִ´�.

	Unit NumElements,
		�� �ڸ��� �� �Ű������� �迭�� ��� ���̴�. �츮�� ��쿣 2�̴�.

	void* pShdaerBytecodeWithINputSignature,
		�̰��� ������������ ù ��° ���̴�, �� ���� ���̴��� ���� �������̴�. ��, ���⿡ 'VS->GetBufferPointer()'
		�� �־��ٴ� ���̴�.

	SIZE_T BytecodeLength,
		�̰��� ���̴� ������ �����̴�. ���⿡ 'VS->GetBufferSize()'�� ������ �ȴ�.
	
	ID3D11InputLayout **pInputLayout,
		�̰��� �Է� ���̾ƿ� ��ü�� ���� �������̴�. 'pLayout'ó�� �����ϰ� ȣ���ص� �������Ƿ� ���⿡ '&pLayout'
		�� �ִ´�.

	������ �Լ��� �ۼ��� ����� ������ ����.

	ID3D11InputLayout* pLayout; // ���� 

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"��ġ", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_VERTEX_DATA��_�Է�_��, 0},
		{"����", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_VERTEX_DATA��_�Է�_��, 0},
	};

	dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);

	����, �� �Լ��� �����Ϸ��� VSFile�� VSSize�� �������ؾ� �ϹǷ� �� �ڵ带 InitPipeline()�Լ� ���ο� �ٷ� ������
	��.

	void InitPipeline()
	{
		// �� ���̴��� �ε��ϰ� �������մϴ� 
		.ID3D10Blob* VS, * PS;
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// �� ���̴��� ���̴� ��ü�� ĸ��ȭ�մϴ� 
		.dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// ���̴� ��ü�� �����մϴ�. 
		devcon->VSSetShader(pVS, 0, 0);
		devcon->PSSetShader(pPS, 0, 0);

		// �Է� ���̾ƿ� ��ü�� �����մϴ� 
		. D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	}

	����ϱ� ���� ���������� �Ѱ��� �����ڸ�, �Է� ���̾ƿ��� ����� ���� �����Ǳ� �� ������ �ƹ� �ϵ� �Ͼ�� �ʴ�
	��. �Է� ���̾ƿ��� �����Ϸ��� IASetInputLayout() �Լ��� ȣ���Ѵ�. ������ �Ű������� �Է� ���̾ƿ� ��ü�̴�.

	void InitPipeline()
	{
		// �� ���̴��� �ε��ϰ� �������մϴ� 
		.ID3D10Blob* VS, * PS;
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
		D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

		// �� ���̴��� ���̴� ��ü�� ĸ��ȭ�մϴ� 
		.dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
		dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

		// ���̴� ��ü�� �����մϴ� 
		.devcon->VSSetShader(pVS, 0, 0);
		devcon->PSSetShader(pPS, 0, 0);

		// �Է� ���̾ƿ� ��ü�� �����մϴ� 
		.D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
		devcon->IASetInputLayout(pLayout);
	}

	���� ������ ������ �׷�����.

Primitive �׸���
	�������� ���� ȣ���ؾ� �ϴ� ������ �Լ��� �������� �ִ�.

	ù ��°�� � ���� ���۸� ����� ������ �����Ѵ�. �� ��°�� � ������ �⺻���� ����� ������ �����Ѵ�.(��: ��
	���� ���, ���ν�Ʈ�� ��) �� ��°�� ������ ����� �׸���.

	IASetVertexBuffers()
		�̷��� �Լ� �� ù ��°�� IASetVertexBuffers()�̴�. �̰��� ������ �� �� � ������ �о�� �ϴ��� GPU�� �˷�
		�ش�. �� ���� ���� �Ű������� �����Ƿ� ������Ÿ���� ���캸��.

		void IASetVertexBuffers(UINT StartSlot,
                        UINT NumBuffers,
                        ID3D11Buffer **ppVertexBuffers,
                        UINT *pStrides,
                        UINT *pOffsets);

		ù ��° �Ű������� ����̹Ƿ� ������ 0���� �����Ѵ�.

		�� ��° �Ű������� �츮�� �����ϴ� ������ ���� �˷��ش�. ���۰� �ϳ��ۿ� �����Ƿ� &pVBuffer�� ä�� �� �ִ�.

		�� ��° �Ű������� �� ���� ������ ���� ���� ũ�⸦ �˷��ִ� UINT �迭�� ����Ų��. �� �Ű������� ä��� ����
		UINT�� ����� "sizeof(VERTEX)"�� ä��� �ش� UINT�� �ּҸ� ���⿡ �ִ´�.

		�ټ� ��° �Ű������� �������� �����ؾ� �ϴ� ���� ������ ����Ʈ ���� �˷��ִ� UINT �迭�̴�. ������ 0�̴�. �̸�
		���� 0�� UINT�� �����ϰ� ���⿡ �ּҸ� �ִ´�.

		�Ű������� ���� ä��� ���� ������ ����.

		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		devcon->IASetVertexBuffers(0, 1, &pBuffer, &stride, &offset);

	IASetPrimitvieTopology()
		�� �� ��° �Լ��� DIrect3D�� � ������ �⺻�� ���Ǵ��� �˷��ش�. �̴� ���� 3���� �ٷ������ ���� �ڵ�
		�� ������ ����.

		Flag										Description
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST			Shows a series of points, one for each vertex.
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST			Shows a series of separated lines.
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP			Shows a series of connected lines.
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST		Shows a series of separated triangles.
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP		Shows a series of connected triangles.

		�� �Լ��� ������ �Ű������� �̷��� �÷��� �� �ϳ��̴�. ������ ���� �ۼ��ȴ�.

		devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DRAW()
		���� DIrect3D�� � ������ �⺻���� ����������, � ���� ���ۿ��� �о���� �˷������Ƿ�, ���� ���ۿ� ����
		�� �׸����� �����Ѵ�.

		�� �Լ��� ���� ������ �⺻���� �� ���۷� �׸���.������Ÿ���� ������ ����.

		void Draw(UINT VertexCount,			// �׷��� ������ ��
				  UINT StartVetexLocation);	// �׷��� ù ��° ����

		�̷��� �Ű������� ���ۿ��� � ������ �׸��� �����Ѵ�. �� ��° �Ű������� �׷��� �� ������ ù ��° ������
		�˷��ִ� �����̰�, ù��° �Ű������� �׷��� �� ������ ���̴�.

		������ �Լ��� ������ ����.

		devcon->Draw(3, 0); // ���� 0���� �����Ͽ� 3���� ������ �׸��ϴ�.

		���� ������ render_frame() �Լ� ��ü�� ���캻��.

		// ���� �������� �������ϴ� �� ���Ǵ� �Լ� 
		void RenderFrame(void)
		{
			// �� ���۸� ���� �Ķ������� ����ϴ� 
			devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

			// ǥ���� ���� ���۸� �����մϴ� 
			UINT stride = sizeof(VERTEX);
			UINT offset = 0;
			devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

			// ����� �⺻ ������ �����մϴ� 
			devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// ���� ���۸� �� ���ۿ� �׸��ϴ� 
			devcon->Draw(3, 0);

			// �� ���ۿ� ����Ʈ ���۸� ��ȯ�մϴ� 
			swapchain->Present(0, 0);
		}

		���� ���۸� �����ϰ� ���̴��� �ε��ϴ� �Ϳ� ���ϸ� �׸� �׸���� ���� ������ �����ϴ�.

�ϼ��� ���α׷�
	�� ���α׷��� �����ϰ� �����ϱ� ���� ���̴� ���� ��ü�� �ʿ��ϴ�. "Shaders.shader"��� �ϸ�, ������ �Ʒ� "Show
	Shaders" ��� ���� ������ ã�� �� �ִ�. �� ���������� ���̴� �ڵ带 �ݵ�� ������ �ʿ�� ����. ���� Ʃ�丮�󿡼�
	�ڼ��� �ٷ��.

	�� ������ ������Ʈ ���� ��ü�� �����ؾ� �Ѵ�. �ַ�� Ž���⿡�� '��� ���� ǥ��'�� ���� �� �� ����. ������ ����
	���Ѵ�.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/5.png
	�ַ�� Ž������ ���̴� ����

	���� DirectX �ڵ带 ���캻��.
	//���� ��� �� main.cpp, Shader.shader ���� ����

	����ؼ� ������Ʈ �ϰ� � ����� �������� ���캻��. �̰��� �����ϸ� ȭ�鿡 ������ ���� ǥ�õȴ�.

	http://www.directxtutorial.com/Lessons/11/B1-D3DGettingStarted/5/6.png
	������ �� �ﰢ��