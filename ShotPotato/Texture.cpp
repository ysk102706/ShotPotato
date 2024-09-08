#include "Texture.h"

bool Texture::LoadTextureFromFile(ID3D11Device* device) {
	textureResource = ResourceLoader::LoadTextureFromFile(device, filename);

	return textureResource != nullptr;
}