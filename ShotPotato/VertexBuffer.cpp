#include "VertexBuffer.h"

bool VertexBuffer::Init(ID3D11Device* device, void* data, int count, int elementByteWidth) {
	this->count = count;
	this->elementByteWidth = elementByteWidth;

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = this->elementByteWidth * this->count;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = data;

	HRESULT result = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		buffer.GetAddressOf()
	);

	if (FAILED(result)) {
		MessageBox(nullptr, L"버텍스 버퍼 생성 실패", L"오류", 0);
		return false;
	}

	return true;
}

void VertexBuffer::Bind(ID3D11DeviceContext* deviceContext) {
	unsigned int stride = elementByteWidth;
	unsigned int offset = 0;

	// 정점 버퍼 배열을 입력 어셈블러 단계에서 바인딩
	deviceContext->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);
}