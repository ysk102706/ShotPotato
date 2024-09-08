#pragma once
#include "Mesh.h"
#include "VertexUV.h"
#include "Vector3.h"

class MeshUV : public Mesh {
public:
	MeshUV();

	bool InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer) override;
	
private:
	void BindBuffers(ID3D11DeviceContext* deviceContext) override;
};