#pragma once
#include "Shader.h"
#include <wrl.h>
#include "Texture.h"
#include <vector>

using Microsoft::WRL::ComPtr;

class PixelShader : public Shader {
public:
	PixelShader();
	PixelShader(std::wstring filename);

	bool Compile(ID3D11Device* device) override;
	bool Create(ID3D11Device* device) override;
	void Bind(ID3D11DeviceContext* deviceContext) override;

	bool CreateSamplerState(ID3D11Device* device);
	void BindSamplerState(ID3D11DeviceContext* deviceContext);

	bool LoadTexture(ID3D11Device* device, std::wstring filename);
	void BindTexture(ID3D11DeviceContext* deviceContext);

	ID3D11PixelShader* GetPixelShader() { return ps.Get(); }

private:
	ComPtr<ID3D11PixelShader> ps;

	std::vector<Texture> textures;
	ComPtr<ID3D11SamplerState> samplerState;
};