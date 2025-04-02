// Pixel Shader �ܰ��� �ڵ� ����

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ���� �ڵ�� ������ ���ν���, �ʱ�ȭ, ������ ���� ���� ������ ������ �� ����

int main() {
    // ... DirectX ����̽� �� ���� ü�� ���� �ڵ� ...

    // ... ���ؽ� ���̴� ���� ...
    /*
    ���� �ܰ迡�� ������ ���ؽ� ���̴��� �̿��Ͽ� ���ؽ� ó���� �����մϴ�.
    */

    // Pixel Shader �ڵ� ����
    /*
    psCode ���ڿ��� PixelShader �ڵ带 �����մϴ�.
    �� ������ �ܼ��� ���������� ����ϴ� �ڵ带 ����մϴ�.
    */
    const char* psCode = R"(
        float4 main() : SV_TARGET {
            return float4(1.0, 0.0, 0.0, 1.0); // ���������� ���
        }
    )";

    // Pixel Shader ������ �� ����
    /*
    D3DCompile �Լ��� ����Ͽ� PixelShader �ڵ带 �������ϰ�
    ID3D11PixelShader �������̽��� �����մϴ�.
    ���θ޸� - ���� ������� �����ӿ�ũ�� ���̴� Ŭ�������� ������ �ҷ��� ������
    */
    ID3D11PixelShader* pixelShader;
    D3DCompile(psCode, strlen(psCode), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &pixelShader, nullptr);

    // Pixel Shader ����
    /*
    PSSetShader �Լ��� ����Ͽ� ������ PixelShader�� �����մϴ�.
    �̷����ϸ� �ش� PixelShader�� �׷��Ƚ� ������������ PixelShader �ܰԿ��� ����˴ϴ�.
    */
    context->PSSetShader(pixelShader, nullptr, 0);

    // ... ������ ���� �� Clean-up ...

    return 0;
}