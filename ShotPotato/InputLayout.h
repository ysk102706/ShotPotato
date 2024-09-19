#pragma once
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class InputLayout {
public:
	bool Init(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* layout, int count, ID3DBlob* vsBuffer);
	void Bind(ID3D11DeviceContext* deviceContext);

private:
	ComPtr<ID3D11InputLayout> inputLayout;
};