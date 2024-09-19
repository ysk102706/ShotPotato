#pragma once
#include "Vertex.h"
#include <wrl.h>
#include <d3d11.h>
#include "TransformBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InputLayout.h"

using Microsoft::WRL::ComPtr;

class Mesh {
public:
	Mesh();
	
	virtual bool InitBuffers(ID3D11Device* device, ID3DBlob* vsBuffer) = 0;
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

	virtual void BindBuffers(ID3D11DeviceContext* deviceContext);
	virtual void DrawBuffers(ID3D11DeviceContext* deviceContext);

	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);

	Vector3& Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);

	Vector3& Rotation() { return rotation; }
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rotation);

	Vector3& Scale() { return scale; }
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);

protected:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	InputLayout inputLayout;

	TransformBuffer transform;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};