#include "PixelShader.h"

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