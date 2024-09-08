#include "TextureMappingShader.h"

bool TextureMappingShader::Init(ID3D11Device* device, std::wstring textureFileName) {
	vs = VertexShader(L"TextureMappingVS.hlsl");
	ps = PixelShader(L"TextureMappingPS.hlsl");

	if (!Compile(device, textureFileName)) return false;
	if (!Create(device)) return false;

	return true;
}

bool TextureMappingShader::Compile(ID3D11Device* device, std::wstring textureFileName) {
	if (!vs.Compile(device)) return false;
	if (!ps.Compile(device)) return false;

	if (!ps.LoadTexture(device, textureFileName)) return false;

	return true;
}

bool TextureMappingShader::Create(ID3D11Device* device) {
	if (!vs.Create(device)) return false;
	if (!ps.Create(device)) return false;

	if (!ps.CreateSamplerState(device)) return false;

	return true;
}

void TextureMappingShader::Bind(ID3D11DeviceContext* deviceContext) {
	vs.Bind(deviceContext);
	ps.Bind(deviceContext);
	ps.BindTexture(deviceContext);
	ps.BindSamplerState(deviceContext);
}

ID3DBlob* TextureMappingShader::ShaderBuffer() {
	return vs.ShaderBuffer();
}