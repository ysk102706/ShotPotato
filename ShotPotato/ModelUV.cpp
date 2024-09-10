#include "ModelUV.h"

ModelUV::ModelUV()
{
}

bool ModelUV::InitBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer) {
	return true;
}

bool ModelUV::InitBuffers(ID3D11Device* device, ID3DBlob* vertexShaderBuffer, std::string modelFileName) {
	std::vector<VertexUV> vertices;

	ResourceLoader::LoadModel(modelFileName, &vertices);

	vertexCount = vertices.size();

	D3D11_BUFFER_DESC vsDesc;
	vsDesc.ByteWidth = sizeof(VertexUV) * vertexCount;
	vsDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vsDesc.CPUAccessFlags = 0;
	vsDesc.MiscFlags = 0;
	vsDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices.data(); 

	HRESULT result = device->CreateBuffer(
		&vsDesc,
		&vertexBufferData,
		vertexBuffer.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"정점 버퍼 생성 실패", L"오류", 0);
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	result = device->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		inputLayout.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"입력 레이아웃 생성 실패", L"오류", 0);
		return false;
	}

	if (!transform.Create(device)) return false;

	return true;
}

void ModelUV::BindBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride = sizeof(VertexUV);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	transform.Bind(deviceContext);
}