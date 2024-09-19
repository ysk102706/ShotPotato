#include "Camera.h"

Camera::Camera() : Camera(70.0f, 1280.0f, 800.0f, 0.1f, 1000.0f) {

}

Camera::Camera(float fov, float width, float height, float zNear, float zFar) : fov(fov), width(width), height(height), zNear(zNear), zFar(zFar), position(0.0f, 0.0f, -5.0f), look(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), right(1.0f, 0.0f, 0.0f), forward(0.0f, 0.0f, 1.0f) {
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

Camera::Camera(Camera& other) : Camera(other.fov, other.width, other.height, other.zNear, other.zFar) {

}

void Camera::MoveForward(float vel) {
	position += forward * vel;
}

void Camera::MoveRight(float vel) {
	position += right * vel;
}

void Camera::MoveUp(float vel) {
	position += up * vel;
}

void Camera::Yaw(float angle) {
	yaw += angle;
}

void Camera::Pitch(float angle) {
	pitch += angle;
}

bool Camera::CreateBuffer(ID3D11Device* device) {
	D3D11_BUFFER_DESC cameraBufferDesc;
	ZeroMemory(&cameraBufferDesc, sizeof(cameraBufferDesc));
	cameraBufferDesc.ByteWidth = sizeof(Matrix4) * 2;
	cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cameraBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	cameraBufferDesc.CPUAccessFlags = 0;
	cameraBufferDesc.MiscFlags = 0;

	Matrix4 cameraMatrix = projectionMatrix * viewMatrix;

	D3D11_SUBRESOURCE_DATA cameraBufferData;
	ZeroMemory(&cameraBufferData, sizeof(cameraBufferData));
	cameraBufferData.pSysMem = &cameraMatrix;

	HRESULT result = device->CreateBuffer(
		&cameraBufferDesc,
		&cameraBufferData,
		cameraBuffer.GetAddressOf()
	);

	if (FAILED(result)) {
		MessageBox(nullptr, L"카메라 버퍼 생성 실패", L"오류", 0);
		return false;
	}

	return true;
}

void Camera::BindBuffer(ID3D11DeviceContext* deviceContext) {
	Matrix4 cameraMatrix = projectionMatrix * viewMatrix;

	deviceContext->UpdateSubresource(cameraBuffer.Get(), NULL, nullptr, &cameraMatrix, 0, 0);
	deviceContext->VSSetConstantBuffers(1, 1, cameraBuffer.GetAddressOf());
}

void Camera::SetAspectRatio(float width, float height) {
	this->width = width;
	this->height = height;
}

void Camera::SetPosition(float x, float y, float z) {
	this->position = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetPosition(Vector3 pos) {
	this->position = pos;
	UpdateViewMatrix();
}

void Camera::UpdateCamera() {
	Matrix4 rotationMatrix = Matrix4::Rotation(pitch, yaw, 0.0f);

	right = rotationMatrix * Vector3::right;
	up = rotationMatrix * Vector3::up;
	forward = rotationMatrix * Vector3::forward;

	// UpdateViewMatrix()에서 ViewLookAt()을 사용하는 경우
	//look = (rotationMatrix * Vector3::forward).Normalize();
	//look = position + look;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
	viewMatrix = Matrix4::ViewEuler(position, pitch, yaw);
}

void Camera::UpdateProjectionMatrix() {
	projectionMatrix = Matrix4::ProjectionPerspective(fov, width, height, zNear, zFar);
}