// Vertex Shader 단계의 예제 코드
/*
Vertex Shader 단계는 정점단위로 실행되며, 각 버텍스의 위치와 속성을 변환하거나 계산하여 출력을 만들어낼 수 있습니다.
아래의 예제는 단순히 입력위치를 그대로 반환하였지만 실제로는 버텍스의 변환, 빛의 계산, 텍스처 매핑등 다양한 연산이 이루어집니다.

개인메모
현재 프레임워크에서 GameObjec / Member / Shader 클래스는
hlsl 쉐이더 파일을 불러와서 실행되도록 설계가 되어져 있다.
*/

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// 이하 코드는 윈도우 프로시저, 초기화, 렌더링 루프 등의 설정을 포함할 수 있음

int main()
{
    // ... DirectX 디바이스 및 스왑 체인 생성 코드 ...

    // Vertex Shader 코드 정의
    /*
    문자열에 Vertex Shader 코드를 정의 합니다.
    현재 예제는 단순히 입력으로 받은 위치를 그대로 반환 하는 코드입니다.
    */
    const char* vsCode = R"(
        float4 main(float4 position : POSITION) : SV_POSITION {
            return position;
        }
    )";

    // Vertex Shader 컴파일 및 생성
    /*
    D3DColpile 함수를 사용하여 Vertex Shader 코드를 컴파일합니다.
    ID3D11VertexShader 인터페이스를 생성합니다.
    */
    ID3D11VertexShader* vertexShader;
    D3DCompile(vsCode, strlen(vsCode), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vertexShader, nullptr);

    // Vertex Shader 설정
    /*
    VSSetShaer 함수를 사용하여 생성한 Vertex Shader를 설정합니다.
    이렇게 한다면 해당 Vertex Shader가 그래픽스 파이프라인의 Vertex Shader 단계에서 실행됩니다.
    */
    context->VSSetShader(vertexShader, nullptr, 0);

    // ... 렌더링 루프 및 Clean-up ...

    return 0;
}