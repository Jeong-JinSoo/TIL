// Vertex Shader �ܰ��� ���� �ڵ�
/*
Vertex Shader �ܰ�� ���������� ����Ǹ�, �� ���ؽ��� ��ġ�� �Ӽ��� ��ȯ�ϰų� ����Ͽ� ����� ���� �� �ֽ��ϴ�.
�Ʒ��� ������ �ܼ��� �Է���ġ�� �״�� ��ȯ�Ͽ����� �����δ� ���ؽ��� ��ȯ, ���� ���, �ؽ�ó ���ε� �پ��� ������ �̷�����ϴ�.

���θ޸�
���� �����ӿ�ũ���� GameObjec / Member / Shader Ŭ������
hlsl ���̴� ������ �ҷ��ͼ� ����ǵ��� ���谡 �Ǿ��� �ִ�.
*/

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ���� �ڵ�� ������ ���ν���, �ʱ�ȭ, ������ ���� ���� ������ ������ �� ����

int main()
{
    // ... DirectX ����̽� �� ���� ü�� ���� �ڵ� ...

    // Vertex Shader �ڵ� ����
    /*
    ���ڿ��� Vertex Shader �ڵ带 ���� �մϴ�.
    ���� ������ �ܼ��� �Է����� ���� ��ġ�� �״�� ��ȯ �ϴ� �ڵ��Դϴ�.
    */
    const char* vsCode = R"(
        float4 main(float4 position : POSITION) : SV_POSITION {
            return position;
        }
    )";

    // Vertex Shader ������ �� ����
    /*
    D3DColpile �Լ��� ����Ͽ� Vertex Shader �ڵ带 �������մϴ�.
    ID3D11VertexShader �������̽��� �����մϴ�.
    */
    ID3D11VertexShader* vertexShader;
    D3DCompile(vsCode, strlen(vsCode), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vertexShader, nullptr);

    // Vertex Shader ����
    /*
    VSSetShaer �Լ��� ����Ͽ� ������ Vertex Shader�� �����մϴ�.
    �̷��� �Ѵٸ� �ش� Vertex Shader�� �׷��Ƚ� ������������ Vertex Shader �ܰ迡�� ����˴ϴ�.
    */
    context->VSSetShader(vertexShader, nullptr, 0);

    // ... ������ ���� �� Clean-up ...

    return 0;
}