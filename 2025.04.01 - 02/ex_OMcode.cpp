// Output Merger 단계의 예제 코드
/*
Output Merger 단계에서는 픽셀의 최종 색상, 깊이, 스텐실(Stencil) 값을 기반으로 렌더 타겟에 픽셀을 렌더링 합니다.
또한 블렌딩, 깊이 테스트, 스텐실 테스트 등의 작업을 수행하여 최종적으로 보여지는 영상을 결정합니다.
이 단계는 화면에 렌더링 결과를 표시하고 색상, 깊이정보를 기반으로 다양한 후처리 작업을 수행하여 최종 출력을 만들어내는 중요한 과정입니다.
*/

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// 이하 코드는 윈도우 프로시저, 초기화, 렌더링 루프 등의 설정을 포함할 수 있음

int main() {
    // ... DirectX 디바이스 및 스왑 체인 생성 코드 ...

    // ... 버텍스 쉐이더 및 픽셀 쉐이더 설정 ...
    /*
    이전 단계에서 설정한 버텍스 쉐이더 픽셀 쉐이더를 이용하여 처리 수행을 합니다.
    */

    // Output Merger 설정
    /*
    OMSetRenderTargets 함수를 사용하여 렌더 타겟(프레임 버퍼)를 설정합니다.
    첫번째 매개변수는 렌더 타겟의 갯수를 나타냅니다.
    두번째 매개변수는 렌더 타겟 뷰의 배열을 전달합니다.
    이 단계에서는 보통 프레임 버퍼에 픽셀을 렌더하기 위해 사용합니다.
    */
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);

    // ... 렌더링 루프 및 Clean-up ...

    return 0;
}