#pragma once
#include "Mesh.h"
#include <string>
#include "VertexUV.h"
#include <vector>
#include "ResourceLoader.h"

class ModelUV : public Mesh {
public:
	ModelUV();

	bool InitBuffers(ID3D11Device* deivce, ID3DBlob* vsBuffer) override;
	bool InitBuffers(ID3D11Device* deivce, ID3DBlob* vsBuffer, std::string modelFileName);

private:
	void BindBuffers(ID3D11DeviceContext* deviceContext) override;
};