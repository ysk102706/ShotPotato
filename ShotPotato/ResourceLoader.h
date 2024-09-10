#pragma once
#include <DirectXTex/DirectXTex.h>
#include <string>
#include <d3d11.h>
#include <Windows.h>
#include <wrl.h>
#include "Vertex.h"
#include "VertexUV.h"
#include "Vector3.h"
#include "Vector2.h"
#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <vector>

class ResourceLoader {
public:
	static ID3D11ShaderResourceView* LoadTextureFromFile(ID3D11Device* device, std::wstring filename);

	static void LoadModel(std::string filename, std::vector<Vertex>* vertices, std::vector<unsigned int>* indices);
	static void LoadModel(std::string filename, std::vector<VertexUV>* vertices, std::vector<unsigned int>* indices);

	static std::wstring GetExtension(std::wstring str);

private:
	static HRESULT GetScratchImage(std::wstring filename, DirectX::ScratchImage* image);
};