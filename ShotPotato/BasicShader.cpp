#include "BasicShader.h"

VertexShader BasicShader::vs = VertexShader(L"BasicVS.hlsl");
PixelShader BasicShader::ps = PixelShader(L"BasicPS.hlsl");

bool BasicShader::Compile(ID3D11Device* device) {
	if (!vs.Compile(device)) return false;
	if (!ps.Compile(device)) return false;
	return true;
}

bool BasicShader::Create(ID3D11Device* device) {
	if (!vs.Create(device)) return false;
	if (!ps.Create(device)) return false;
	return true;
}

void BasicShader::Bind(ID3D11DeviceContext* deviceContext) {
	vs.Bind(deviceContext);
	ps.Bind(deviceContext);
}

ID3DBlob* BasicShader::ShaderBuffer() {
	return vs.ShaderBuffer();
}