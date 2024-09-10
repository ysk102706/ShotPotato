#pragma once
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class VertexBuffer {
public:
	bool Init(ID3D11Device* device, void* data, int count, int elementByteWidth);
	void Bind(ID3D11DeviceContext* deviceContext);

	int Count() { return count; }
	unsigned int ElementByteWidth() { return elementByteWidth; }

private:
	int count;
	unsigned int elementByteWidth;
	ComPtr<ID3D11Buffer> buffer;
};