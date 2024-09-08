#include "TransformBuffer.h"

TransformBuffer::TransformBuffer() {
	memset(&matrix, 0, sizeof(matrix));
}

bool TransformBuffer::Create(ID3D11Device* device) {
	D3D11_BUFFER_DESC transformBufferDesc;
	ZeroMemory(&transformBufferDesc, sizeof(transformBufferDesc));
	transformBufferDesc.ByteWidth = sizeof(Matrix4);
	transformBufferDesc.CPUAccessFlags = 0;
	transformBufferDesc.MiscFlags = 0;
	transformBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	transformBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	matrix = Matrix4::Identity();

	D3D11_SUBRESOURCE_DATA transformBufferData;
	ZeroMemory(&transformBufferData, sizeof(transformBufferData));
	transformBufferData.pSysMem = &matrix;

	HRESULT result = device->CreateBuffer(
		&transformBufferDesc,
		&transformBufferData,
		constantBuffer.GetAddressOf()
	);

	if (FAILED(result)) {
		MessageBox(nullptr, L"상수 버퍼 생성 실패", L"오류", 0);
		return false;
	}

	return true;
}

void TransformBuffer::Bind(ID3D11DeviceContext* deviceContext) {
	deviceContext->UpdateSubresource(constantBuffer.Get(), 0, NULL, &matrix, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
}