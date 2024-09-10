#include "ResourceLoader.h"
#include <wrl.h>

using Microsoft::WRL::ComPtr;

ID3D11ShaderResourceView* ResourceLoader::LoadTextureFromFile(ID3D11Device* device, std::wstring filename) {
	filename = std::wstring(L"..//res//textures//") + filename;

	DirectX::ScratchImage image;
	HRESULT result = GetScratchImage(filename, &image);

	if (FAILED(result)) return nullptr;

	ComPtr<ID3D11Texture2D> texture;
	result = DirectX::CreateTexture(
		device,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		(ID3D11Resource**)texture.GetAddressOf()
	);

	if (FAILED(result)) return nullptr;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; 
	srvDesc.Texture2D.MostDetailedMip = 0; 
	srvDesc.Texture2D.MipLevels = 1; 

	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);

	srvDesc.Format = textureDesc.Format;

	ID3D11ShaderResourceView* shaderResourceView;
	result = device->CreateShaderResourceView(
		texture.Get(),
		&srvDesc,
		&shaderResourceView
	);

	if (FAILED(result)) return nullptr;

	return shaderResourceView;
}

void ResourceLoader::LoadModel(std::string filename, std::vector<Vertex>* vertices, std::vector<unsigned int>* indices) {
	filename = std::string("..//res//models//") + filename;

	const aiScene* scene = aiImportFile(
		filename.c_str(),
		aiProcess_CalcTangentSpace | 
		aiProcess_Triangulate | 
		aiProcess_JoinIdenticalVertices | 
		aiProcess_ConvertToLeftHanded 
	);

	if (scene != nullptr) {
		for (int i = 0; i < scene->mNumMeshes; i++) {
			const aiMesh* mesh = scene->mMeshes[i];

			for (int i = 0; i < mesh->mNumVertices; i++) {
				Vector3 pos = Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

				Vertex vertex = Vertex(pos.x, pos.y, pos.z);
				vertices->push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				const aiFace& face = mesh->mFaces[i];
				indices->push_back(face.mIndices[0]);
				indices->push_back(face.mIndices[1]);
				indices->push_back(face.mIndices[2]);
			}
		}
	}
	else {
		MessageBox(nullptr, L"모델 로드 실패", L"오류", 0);
		throw std::exception("모델 로드 실패");
	}
}

void ResourceLoader::LoadModel(std::string filename, std::vector<VertexUV>* vertices, std::vector<unsigned int>* indices) {
	filename = std::string("..//res//models//") + filename;

	const aiScene* scene = aiImportFile(
		filename.c_str(),
		aiProcess_CalcTangentSpace | 
		aiProcess_Triangulate | 
		aiProcess_JoinIdenticalVertices | 
		aiProcess_ConvertToLeftHanded 
	);

	if (scene != nullptr) {
		for (int i = 0; i < scene->mNumMeshes; i++) {
			const aiMesh* mesh = scene->mMeshes[i];

			for (int j = 0; j < mesh->mNumVertices; j++) {
				Vector3 pos = Vector3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);

				Vector2 uv = mesh->HasTextureCoords(i) ? Vector2(mesh->mTextureCoords[i][j].x, mesh->mTextureCoords[i][j].y) : Vector2(0.0f, 0.0f);

				VertexUV vertex = VertexUV(pos, uv);
				vertices->push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				const aiFace& face = mesh->mFaces[i];
				indices->push_back(face.mIndices[0]);
				indices->push_back(face.mIndices[1]);
				indices->push_back(face.mIndices[2]);
			}
		}
	}
	else {
		MessageBox(nullptr, L"모델 로드 실패", L"오류", 0);
		throw std::exception("모델 로드 실패");
	}
}

std::wstring ResourceLoader::GetExtension(std::wstring str) {
	size_t sz = str.rfind('.', str.length());
	if (sz != std::wstring::npos) return str.substr(sz + 1, str.length() - sz);
	return std::wstring();
}

HRESULT ResourceLoader::GetScratchImage(std::wstring filename, DirectX::ScratchImage* image) {
	std::wstring extension = GetExtension(filename);

	if (extension._Equal(L"tga") || extension._Equal(L"TGA")) return DirectX::LoadFromTGAFile(filename.c_str(), NULL, *image);
	else if (extension._Equal(L"dds") || extension._Equal(L"DDS")) return DirectX::LoadFromDDSFile(filename.c_str(), DirectX::DDS_FLAGS_NONE, NULL, *image);
	else return DirectX::LoadFromWICFile(filename.c_str(), DirectX::WIC_FLAGS_NONE, NULL, *image);

	return E_NOTIMPL;
}