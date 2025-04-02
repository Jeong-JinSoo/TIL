// Resterization 단계의 예제 코드
/*
레스터화 단계는 점, 선, 삼각형등 기하 프리미티브를 실제 픽셀로 변환합니다.
정점의 위치와 속성을 픽셀 위치에 매핑하고, 쉐이더 처리 후의 결과를 실제 화면에 표시하도록
2D 형태의 이미지로 변환합니다.

개인메모 2DFrameWork / GameObject / State / RasterState 클래스 참고
*/

#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

// 이하 코드는 윈도우 프로시저, 초기화, 렌더링 루프 등의 설정을 포함할 수 있음

int main() {
    // ... DirectX 디바이스 및 스왑 체인 생성 코드 ...

    // ... 버텍스 쉐이더 및 픽셀 쉐이더 설정 ...
    /*
    이전 단계에서 설정한 VS & PS를 이용하여 처리를 수행합니다.
    */

    // 레스터화 단계 설정
    context->RSSetState(nullptr); // 일반적으로 기본 상태로 사용
    /*
    RSSetState 함수를 사용하여 레스터화 상태를 설정합니다.
    일반적으로 기본상태를 사용하며, 본 예제는 nullptr 을 전달합니다.
    */

    // ... 렌더링 루프 및 Clean-up ...

    return 0;
}