#include "PixelShader.h"

PixelShader::PixelShader() {

}

PixelShader::PixelShader(std::wstring filename) : Shader(filename, "PS", "ps_5_0") {

}

bool PixelShader::Compile(ID3D11Device* device) {
	HRESULT ret = D3DCompileFromFile(
		filename.c_str(),
		NULL,
		NULL,
		entry.c_str(),
		profile.c_str(),
		NULL,
		NULL,
		shaderBuffer.GetAddressOf(),
		NULL
	);

	if (FAILED(ret)) {
		MessageBox(nullptr, L"픽셀 셰이더 컴파일 실패", L"오류", NULL);
		return false;
	}

	return true;
}

bool PixelShader::Create(ID3D11Device* device) {
	HRESULT ret = device->CreatePixelShader(
		shaderBuffer.Get()->GetBufferPointer(),
		shaderBuffer.Get()->GetBufferSize(),
		nullptr,
		ps.GetAddressOf()
	);
	
	if (FAILED(ret)) {
		MessageBox(nullptr, L"픽셀 셰이더 컴파일 실패", L"오류", 0);
		return false;
	}

	return true;
}

void PixelShader::Bind(ID3D11DeviceContext* deviceContext) {
	deviceContext->PSSetShader(ps.Get(), NULL, NULL);
}

bool PixelShader::CreateSamplerState(ID3D11Device* device) {
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT result = device->CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
	if (FAILED(result)) return false;

	return true;
}

void PixelShader::BindSamplerState(ID3D11DeviceContext* deviceContext) {
	deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

bool PixelShader::LoadTexture(ID3D11Device* device, std::wstring filename) {
	Texture texture;
	texture.filename = filename;
	if (!texture.LoadTextureFromFile(device)) return false;
	textures.push_back(texture);

	return true;
}

void PixelShader::BindTexture(ID3D11DeviceContext* deviceContext) {
	for (int i = 0; i < textures.size(); i++) {
		deviceContext->PSSetShaderResources(
			i, 1, textures[i].textureResource.GetAddressOf()
		);
	}
}