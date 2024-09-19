#include "InputLayout.h"

bool InputLayout::Init(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, int count, ID3DBlob* vsBuffer) {
	HRESULT result = device->CreateInputLayout(
		layout,
		count,
		vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(),
		inputLayout.GetAddressOf()
	);

	if (FAILED(result))
	{
		MessageBox(nullptr, L"�Է� ���̾ƿ� ���� ����", L"����", 0);
		return false;
	}

	return true;
}

void InputLayout::Bind(ID3D11DeviceContext* deviceContext) {
	deviceContext->IASetInputLayout(inputLayout.Get());
}