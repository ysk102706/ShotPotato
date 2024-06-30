#pragma once
#include "VertexShader.h"
#include "PixelShader.h"

class BasicShader {
public:
	static bool Compile(ID3D11Device* device);
	static bool Create(ID3D11Device* device);
	static void Bind(ID3D11DeviceContext* deviceContext);

	static ID3DBlob* ShaderBuffer();

private:
	static VertexShader vs;
	static PixelShader ps;
};