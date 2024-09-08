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

	// ������ ����
	vertexCount = ARRAYSIZE(vertices);

	// ���� ���� �����
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.ByteWidth = sizeof(vertices); // �󸶸�ŭ ������
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ���� ������ ���۷� ��
	vertexBufferDesc.CPUAccessFlags = 0; // CPU�� GPU�� ������ �� �ְ� ����. 0�� ���� ���ϰ� ��
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	// ������ ���
	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;

	// ���� ���� ����
	HRESULT result = device->CreateBuffer(
		&vertexBufferDesc,
		&vertexBufferData,
		vertexBuffer.GetAddressOf()
	);

	if (FAILED(result)) return false;

	// ������ ���� �� ����� (�Է� ���̾ƿ�)
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0} // �տ� position�� float�� 3���� 12����Ʈ�ϱ� 12
	};

	// �Է� ���̾ƿ� ����
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
	unsigned int stride = sizeof(VertexUV); // �ѹ��� �� ���� ������
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // ���� �׸� ���� LineList.

	transform.Bind(deviceContext);
}
