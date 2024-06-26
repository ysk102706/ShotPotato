#include "Matrix4.h"
#include <string>

Matrix4::Matrix4() {
	memset(elements, 0, sizeof(elements));
}

Matrix4 Matrix4::Identity() {
	Matrix4 ret;
	ret.Get(0, 0) = 1.0f; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = 1.0f; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = 1.0f; ret.Get(2, 3) = 0.0f;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::Translation(Vector3 pos) {
	return Translation(pos.x, pos.y, pos.z);
}

Matrix4 Matrix4::Translation(float x, float y, float z) {
	Matrix4 ret;
	ret.Get(0, 0) = 1.0f; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = x;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = 1.0f; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = y;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = 1.0f; ret.Get(2, 3) = z;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::InverseTranslation(Vector3 pos) {
	return InverseTranslation(pos.x, pos.y, pos.z);
}

Matrix4 Matrix4::InverseTranslation(float x, float y, float z) {
	Matrix4 ret;
	ret.Get(0, 0) = 1.0f; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = -x;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = 1.0f; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = -y;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = 1.0f; ret.Get(2, 3) = -z;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::Rotation(Vector3 rot) {
	return Rotation(rot.x, rot.y, rot.z);
}

Matrix4 Matrix4::Rotation(float x, float y, float z) {
	return RotationY(y) * RotationX(x) * RotationZ(z);
}

Matrix4 Matrix4::InverseRotation(Vector3 rot) {
	return InverseRotation(rot.x, rot.y, rot.z);
}

Matrix4 Matrix4::InverseRotation(float x, float y, float z) {
	return Transpose(RotationZ(z)) * Transpose(RotationX(x)) * Transpose(RotationY(y));
}

Matrix4 Matrix4::RotationX(float angle) {
	Matrix4 ret;
	angle *= Math::Deg2Rad;
	float cos = cosf(angle);
	float sin = sinf(angle);
	ret.Get(0, 0) = 1.0f; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = cos; ret.Get(1, 2) = -sin; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = sin; ret.Get(2, 2) = cos; ret.Get(2, 3) = 0.0f;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::RotationY(float angle) {
	Matrix4 ret;
	angle *= Math::Deg2Rad;
	float cos = cosf(angle);
	float sin = sinf(angle);
	ret.Get(0, 0) = cos; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = sin; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = 1.0f; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = -sin; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = cos; ret.Get(2, 3) = 0.0f;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::RotationZ(float angle) {
	Matrix4 ret;
	angle *= Math::Deg2Rad;
	float cos = cosf(angle);
	float sin = sinf(angle);
	ret.Get(0, 0) = cos; ret.Get(0, 1) = -sin; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = sin; ret.Get(1, 1) = cos; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = 1.0f; ret.Get(2, 3) = 0.0f;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::Scale(Vector3 scale) {
	return Scale(scale.x, scale.y, scale.z);
}

Matrix4 Matrix4::Scale(float x, float y, float z) {
	Matrix4 ret;
	ret.Get(0, 0) = x; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = y; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = z; ret.Get(2, 3) = 0.0f;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::ViewLookAt(Vector3 pos, Vector3 target, Vector3 up) {
	Vector3 f = (target - pos).Normalize();
	Vector3 r = up.Cross(f).Normalize();
	Vector3 u = f.Cross(r).Normalize();

	Matrix4 ret;
	ret.Get(0, 0) = r.x; ret.Get(0, 1) = r.y; ret.Get(0, 2) = r.z; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = u.x; ret.Get(1, 1) = u.y; ret.Get(1, 2) = u.z; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = f.x; ret.Get(2, 1) = f.y; ret.Get(2, 2) = f.z; ret.Get(2, 3) = 0.0f;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret * InverseTranslation(pos);
}

Matrix4 Matrix4::ViewEuler(Vector3 pos, float pitch, float yaw) {
	return InverseRotation(pitch, yaw, 0.0f) * InverseTranslation(pos);
}

Matrix4 Matrix4::ProjectionPerspective(float fov, float width, float height, float near, float far) {
	float aspectRatio = width / height;
	float H = 1 / tanf(fov / 2.0f);
	float W = H / aspectRatio;
	float A = far / (far - near);
	float B = (-near * far) / (far - near);

	Matrix4 ret;
	ret.Get(0, 0) = W; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = H; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = A; ret.Get(2, 3) = B;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 1.0f; ret.Get(3, 3) = 0.0f;
	return ret;
}

Matrix4 Matrix4::ProjectionOrthographic(float width, float height, float near, float far) {
	float W = 2 / width;
	float H = 2 / height;
	float A = 1 / (far - near);
	float B = -near / (far - near);

	Matrix4 ret;
	ret.Get(0, 0) = W; ret.Get(0, 1) = 0.0f; ret.Get(0, 2) = 0.0f; ret.Get(0, 3) = 0.0f;
	ret.Get(1, 0) = 0.0f; ret.Get(1, 1) = H; ret.Get(1, 2) = 0.0f; ret.Get(1, 3) = 0.0f;
	ret.Get(2, 0) = 0.0f; ret.Get(2, 1) = 0.0f; ret.Get(2, 2) = A; ret.Get(2, 3) = B;
	ret.Get(3, 0) = 0.0f; ret.Get(3, 1) = 0.0f; ret.Get(3, 2) = 0.0f; ret.Get(3, 3) = 1.0f;
	return ret;
}

Matrix4 Matrix4::Transpose(const Matrix4& target) {
	Matrix4 ret = target;

	Math::Swap(ret.Get(0, 1), ret.Get(1, 0));
	Math::Swap(ret.Get(0, 2), ret.Get(2, 0));
	Math::Swap(ret.Get(0, 3), ret.Get(3, 0));

	Math::Swap(ret.Get(1, 2), ret.Get(2, 1));
	Math::Swap(ret.Get(1, 3), ret.Get(3, 1));
	Math::Swap(ret.Get(2, 3), ret.Get(3, 2));

	return ret;
}

float& Matrix4::Get(int row, int col) {
	return elements[(row * 4) + col];
}

Matrix4& Matrix4::operator=(const Matrix4 oth) {
	for (int i = 0; i < 16; i++) {
		elements[i] = oth.elements[i];
	}
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 other) {
	Matrix4 ret;
	for (int i = 0; i < 4; i++) {
		Mul(ret, other, i, 0);
		Mul(ret, other, i, 1);
		Mul(ret, other, i, 2);
		Mul(ret, other, i, 3);
	}
	return ret;
}

void Matrix4::Mul(Matrix4& ret, Matrix4 other, int row, int col) {
	ret.Get(row, col) =
		Get(row, 0) * other.Get(0, col) +
		Get(row, 1) * other.Get(1, col) +
		Get(row, 2) * other.Get(2, col) +
		Get(row, 3) * other.Get(3, col);
}

Matrix4 Matrix4::operator*=(const Matrix4 other) {
	*this = *this * other;
	return *this;
}

Vector3 Matrix4::operator*(const Vector3 other) {
	Vector3 ret;
	ret.x = elements[0] * other.x + elements[1] * other.y + elements[2] * other.z;
	ret.y = elements[4] * other.x + elements[5] * other.y + elements[6] * other.z;
	ret.z = elements[8] * other.x + elements[9] * other.y + elements[10] * other.z;
	return ret;
}