#pragma once
#include "Vertex.h"
#include <wrl.h>
#include <d3d11.h>

using Microsoft::WRL::ComPtr;

class Mesh {
public:
	Mesh();
	
	bool InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	int vertexCount;
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11InputLayout> inputLayout;
};