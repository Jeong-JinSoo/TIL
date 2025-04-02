// Input Assembler 단계의 예제 코드
// IA 단계에서는 버텍스 데이터를 정의하고 이를 바탕으로 기하 프리미티브를 생성하는 설정 작업을 합니다.
#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

// 이하 코드는 윈도우 프로시저, 초기화, 렌더링 루프 등의 설정을 포함할 수 있음

int main() {
    // ... DirectX 디바이스 및 스왑 체인 생성 코드 ...

    // 버텍스 데이터 정의
    struct Vertex
    {
        float x, y, z;
    };

    // 정점 x, y, z 의 위치 설정
    Vertex vertices[] =
    {
        { -1.0f, -1.0f, 0.0f }, // 왼쪽 아래
        { 1.0f, -1.0f, 0.0f },  // 오른쪽 아래
        { 0.0f, 1.0f, 0.0f }    // 위
    };

    // 버텍스 버퍼 생성
    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT; // gpu 읽기/쓰기허용 cpu 접근 불가
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexBufferData = {};
    vertexBufferData.pSysMem = vertices;

    ID3D11Buffer* vertexBuffer;
    device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);

    // Input Assembler 설정
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    context->IASetInputLayout(inputLayout);
    /*
    인풋 레이아웃을 설정합니다.
    쉐이더에게 어떤 종류의 버텍스 데이터가 사용되는지 알려줍니다.
    */

    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    /*
    사용할 버텍스 버퍼를 지정하고, 각 버텍스의 크기와 오프셋을 설정합니다.
    */

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    /*
    기하 프리미티브의 종류를 설정합니다.
    예제는 삼각형을 사용하므로 삼각형을 그리는 방식에 대하여 정해져 있습니다.
    */

    // ... 렌더링 루프 및 Clean-up ...

    return 0;
}