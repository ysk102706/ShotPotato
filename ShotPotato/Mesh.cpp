#include "Mesh.h"

Mesh::Mesh() {

}

void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext) {
	BindBuffers(deviceContext);
	DrawBuffers(deviceContext);
}

void Mesh::BindBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	transform.Bind(deviceContext);
}

void Mesh::DrawBuffers(ID3D11DeviceContext* deviceContext) {
	deviceContext->Draw(vertexCount, 0);
}

void Mesh::UpdateBuffers(ID3D11DeviceContext* deivceContext) {
	transform.matrix = Matrix4::Scale(scale) * Matrix4::Rotation(rotation) * Matrix4::Translation(position);
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