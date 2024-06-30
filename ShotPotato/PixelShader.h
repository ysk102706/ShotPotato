#pragma once
#include "Shader.h"
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class PixelShader : public Shader {
public:
	PixelShader(std::wstring filename);

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext) override;

private:
	ComPtr<ID3D11PixelShader> ps;
};