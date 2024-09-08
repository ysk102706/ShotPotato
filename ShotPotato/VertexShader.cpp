#include "VertexShader.h"

VertexShader::VertexShader() {

}

VertexShader::VertexShader(std::wstring filename) : Shader(filename, "VS", "vs_5_0"), vs(0) {

}

bool VertexShader::Compile(ID3D11Device* device) {
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
		MessageBox(nullptr, L"정점 셰이더 컴파일 실패", L"오류", 0);
		return false;
	}

	return true;
}

bool VertexShader::Create(ID3D11Device* device) {
	HRESULT ret = device->CreateVertexShader(
		shaderBuffer.Get()->GetBufferPointer(),
		shaderBuffer.Get()->GetBufferSize(),
		nullptr,
		vs.GetAddressOf()
	);

	if (FAILED(ret)) {
		MessageBox(nullptr, L"정점 셰이더 생성 실패", L"오류", 0);
		return false;
	}

	return true;
}

void VertexShader::Bind(ID3D11DeviceContext* deviceContext) {
	deviceContext->VSSetShader(vs.Get(), NULL, NULL);
}