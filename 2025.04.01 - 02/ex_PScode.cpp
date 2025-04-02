// Pixel Shader 단계의 코드 예제

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// 이하 코드는 윈도우 프로시저, 초기화, 렌더링 루프 등의 설정을 포함할 수 있음

int main() {
    // ... DirectX 디바이스 및 스왑 체인 생성 코드 ...

    // ... 버텍스 쉐이더 설정 ...
    /*
    이전 단계에서 설정한 버텍스 쉐이더를 이용하여 버텍스 처리를 수행합니다.
    */

    // Pixel Shader 코드 정의
    /*
    psCode 문자열에 PixelShader 코드를 정의합니다.
    본 예제는 단순히 빨간색으로 출력하는 코드를 사용합니다.
    */
    const char* psCode = R"(
        float4 main() : SV_TARGET {
            return float4(1.0, 0.0, 0.0, 1.0); // 빨간색으로 출력
        }
    )";

    // Pixel Shader 컴파일 및 생성
    /*
    D3DCompile 함수를 사용하여 PixelShader 코드를 컴파일하고
    ID3D11PixelShader 인터페이스를 생성합니다.
    개인메모 - 현재 사용중인 프레임워크는 쉐이더 클래스에서 파일을 불러와 컴파일
    */
    ID3D11PixelShader* pixelShader;
    D3DCompile(psCode, strlen(psCode), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &pixelShader, nullptr);

    // Pixel Shader 설정
    /*
    PSSetShader 함수를 사용하여 생성한 PixelShader를 설정합니다.
    이렇게하면 해당 PixelShader가 그래픽스 파이프라인의 PixelShader 단게에서 실행됩니다.
    */
    context->PSSetShader(pixelShader, nullptr, 0);

    // ... 렌더링 루프 및 Clean-up ...

    return 0;
}