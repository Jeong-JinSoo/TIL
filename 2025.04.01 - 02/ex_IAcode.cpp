// Input Assembler �ܰ��� ���� �ڵ�
// IA �ܰ迡���� ���ؽ� �����͸� �����ϰ� �̸� �������� ���� ������Ƽ�긦 �����ϴ� ���� �۾��� �մϴ�.
#include <Windows.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

// ���� �ڵ�� ������ ���ν���, �ʱ�ȭ, ������ ���� ���� ������ ������ �� ����

int main() {
    // ... DirectX ����̽� �� ���� ü�� ���� �ڵ� ...

    // ���ؽ� ������ ����
    struct Vertex
    {
        float x, y, z;
    };

    // ���� x, y, z �� ��ġ ����
    Vertex vertices[] =
    {
        { -1.0f, -1.0f, 0.0f }, // ���� �Ʒ�
        { 1.0f, -1.0f, 0.0f },  // ������ �Ʒ�
        { 0.0f, 1.0f, 0.0f }    // ��
    };

    // ���ؽ� ���� ����
    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT; // gpu �б�/������� cpu ���� �Ұ�
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexBufferData = {};
    vertexBufferData.pSysMem = vertices;

    ID3D11Buffer* vertexBuffer;
    device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);

    // Input Assembler ����
    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    context->IASetInputLayout(inputLayout);
    /*
    ��ǲ ���̾ƿ��� �����մϴ�.
    ���̴����� � ������ ���ؽ� �����Ͱ� ���Ǵ��� �˷��ݴϴ�.
    */

    context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    /*
    ����� ���ؽ� ���۸� �����ϰ�, �� ���ؽ��� ũ��� �������� �����մϴ�.
    */

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    /*
    ���� ������Ƽ���� ������ �����մϴ�.
    ������ �ﰢ���� ����ϹǷ� �ﰢ���� �׸��� ��Ŀ� ���Ͽ� ������ �ֽ��ϴ�.
    */

    // ... ������ ���� �� Clean-up ...

    return 0;
}