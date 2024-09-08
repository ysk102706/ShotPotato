#include "MeshUV.h"

MeshUV::MeshUV()
{
}

bool MeshUV::InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer)
{
	VertexUV vertices[] =
	{
		VertexUV(Vector3(0.0f, 0.5f, 0.0f), Vector2(0.0f, 1.0f)),
		VertexUV(Vector3(0.5f, -0.5f, 0.0f), Vector2(0.0f, 0.0f)),
		VertexUV(Vector3(-0.5f, -0.5f, 0.0f), Vector2(1.0f, 0.0f))
	};

	// 정점의 개수
	vertexCount = ARRAYSIZE(vertices);

	// 정범 버퍼 만들기
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = sizeof(vertices); // 얼마만큼 읽을지
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 정점 데이터 버퍼로 씀
	vertexBufferDesc.CPUAccessFlags = 0; // CPU가 GPU에 접근할 수 있게 할지. 0은 접근 못하게 함
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// 데이터 담기
	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;

	// 정점 버퍼 생성
	HRESULT result = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		vertexBuffer.GetAddressOf()
	);

	if (FAILED(result)) return false;

	// 정점에 대한 명세 만들기 (입력 레이아웃)
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // 앞에 position이 float값 3개라서 12바이트니까 12
	};

	// 입력 레이아웃 설정
	result = device->CreateInputLayout(
		layout,
		ARRAYSIZE(layout),
		vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(),
		inputLayout.GetAddressOf()
	);

	if (FAILED(result)) return false;

	if (!transform.Create(device)) return false;

	return true;

}

void MeshUV::BindBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride = sizeof(VertexUV); // 한번에 몇 개씩 읽을지
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 선을 그릴 때는 LineList.

	transform.Bind(deviceContext);
}
