#include "Mesh.h"

Mesh::Mesh() : vertexCount(0), vertexBuffer(0), inputLayout(0) {

}

bool Mesh::InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer) {
	Vertex vertices[] = {
		Vertex(0.0f, 0.5f, 0.0f),
		Vertex(0.5f, -0.5f, 0.0f),
		Vertex(-0.5f, -0.5f, 0.0f)
	};

	vertexCount = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;

	HRESULT ret = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		vertexBuffer.GetAddressOf()
	);

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	ret = device->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(),
		inputLayout.GetAddressOf()
	);

	if (FAILED(ret)) {
		MessageBox(nullptr, L"입력 레이아웃 생성 실패", L"오류", 0);
		return false;
	}
}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->Draw(vertexCount, 0);
}