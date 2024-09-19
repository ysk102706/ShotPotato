#include "ModelUV.h"

ModelUV::ModelUV()
{
}

bool ModelUV::InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer) {
	return true;
}

bool ModelUV::InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer, std::string modelFileName) {
	std::vector<VertexUV> vertices;
	std::vector<unsigned int> indices;

	ResourceLoader::LoadModel(modelFileName, &vertices, &indices);

	if (!vertexBuffer.Init(device, vertices.data(), vertices.size(), sizeof(VertexUV))) return false;
	if (!indexBuffer.Init(device, indices.data(), indices.size())) return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	if (!inputLayout.Init(device, layout, ARRAYSIZE(layout), vsBuffer)) return false;

	if (!transform.Create(device)) return false;

	return true;
}