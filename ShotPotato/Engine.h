#pragma once
#include "Window.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include "MeshUV.h"
#include "BasicShader.h"
#include "TextureMappingShader.h"

using Microsoft::WRL::ComPtr;

class Engine {
public:
	Engine(HINSTANCE hInstance, int widht, int height, std::wstring title);

	bool Init();
	int Run();

private:
	void Update();
	void Draw();

	bool InitScene();
	bool InitDirect3D();

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RenderTargetView> renderTargetView;
	D3D11_VIEWPORT viewport;

	TextureMappingShader textureShader;

	MeshUV meshUV;
};