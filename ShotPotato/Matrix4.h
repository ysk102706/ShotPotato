#pragma once
#include "Vector3.h"
#include "Math.h"

class Matrix4 {
public:
	Matrix4();

	static Matrix4 Identity();

	static Matrix4 Translation(Vector3 pos);
	static Matrix4 Translation(float x, float y, float z);
	static Matrix4 InverseTranslation(Vector3 pos);
	static Matrix4 InverseTranslation(float x, float y, float z);

	static Matrix4 Rotation(Vector3 rot);
	static Matrix4 Rotation(float x, float y, float z);
	static Matrix4 InverseRotation(Vector3 rot);
	static Matrix4 InverseRotation(float x, float y, float z);
	static Matrix4 RotationX(float angle);
	static Matrix4 RotationY(float angle);
	static Matrix4 RotationZ(float angle);

	static Matrix4 Scale(Vector3 scale);
	static Matrix4 Scale(float x, float y, float z);

	static Matrix4 ViewLookAt(Vector3 pos, Vector3 target, Vector3 up);
	static Matrix4 ViewEuler(Vector3 pos, float pitch, float yaw);

	static Matrix4 ProjectionPerspective(float fov, float width, float height, float near, float far);
	static Matrix4 ProjectionOrthographic(float width, float height, float near, float far);

	static Matrix4 Transpose(const Matrix4& target);

	float& Get(int row, int col);

	void Mul(Matrix4& ret, Matrix4 oth, int row, int col);

	Matrix4& operator=(const Matrix4 oth);
	Matrix4 operator*(const Matrix4 oth);
	Matrix4 operator*=(const Matrix4 oth);

	Vector3 operator*(const Vector3 oth);

private:
	float elements[16];
};