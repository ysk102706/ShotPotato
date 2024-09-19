#include "Mesh.h"

Mesh::Mesh() : vertexBuffer(), indexBuffer(), inputLayout(), transform(), position(Vector3::zero), rotation(Vector3::zero), scale(Vector3::one) {

}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext) {
	BindBuffers(deviceContext);
	DrawBuffers(deviceContext);
}

void Mesh::BindBuffers(ID3D11DeviceContext* deviceContext) {
	vertexBuffer.Bind(deviceContext);
	indexBuffer.Bind(deviceContext);
	inputLayout.Bind(deviceContext);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	transform.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext) {
	deviceContext->DrawIndexed(indexBuffer.Count(), 0, 0);
}

void Mesh::UpdateBuffers(ID3D11DeviceContext* deivceContext) {
	transform.matrix = Matrix4::Translation(position) * Matrix4::Rotation(rotation) * Matrix4::Scale(scale);
}

void Mesh::SetPosition(float x, float y, float z) {
	position = Vector3(x, y, z);
}

void Mesh::SetPosition(Vector3 position) {
	this->position = position;
}

void Mesh::SetRotation(float x, float y, float z) {
	rotation = Vector3(x, y, z);
}

void Mesh::SetRotation(Vector3 rotation) {
	this->rotation = rotation;
}

void Mesh::SetScale(float x, float y, float z) {
	scale = Vector3(x, y, z);
}

void Mesh::SetScale(Vector3 scale) {
	this->scale = scale;
}