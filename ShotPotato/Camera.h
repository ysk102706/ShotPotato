#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include <d3d11.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Camera {
public:
	Camera();
	Camera(float fov, float width, float height, float zNear, float zFar);
	Camera(Camera& other);

	void MoveForward(float vel);
	void MoveRight(float vel);
	void MoveUp(float vel);

	void Yaw(float angle);
	void Pitch(float angle);

	bool CreateBuffer(ID3D11Device* device);
	void BindBuffer(ID3D11DeviceContext* deviceContext);

	float AspectRatio() { return width / height; }
	void SetAspectRatio(float width, float height);

	Matrix4 View() { return viewMatrix; }
	Matrix4 Projection() { return projectionMatrix; }

	Vector3 Position() { return position; }
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 pos);

	void UpdateCamera();

private:
	float fov;
	float width;
	float height;
	float zNear;
	float zFar;

	Matrix4 projectionMatrix;

	float yaw = 0.0f;
	float pitch = 0.0f;

	Vector3 position;

	Vector3 forward;
	Vector3 right;
	Vector3 up;

	Vector3 look;

	Matrix4 viewMatrix;

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	ComPtr<ID3D11Buffer> cameraBuffer;
};