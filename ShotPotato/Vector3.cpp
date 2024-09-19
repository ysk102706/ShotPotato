#include "Vector3.h"

const Vector3 Vector3::zero(0, 0, 0);
const Vector3 Vector3::one(1, 1, 1);
const Vector3 Vector3::forward(0, 0, 1);
const Vector3 Vector3::up(0, 1, 0);
const Vector3 Vector3::right(1, 0, 0);

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vector3::Length() {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::Dot(const Vector3& oth) {
	return (x * oth.x) + (y * oth.y) + (z * oth.z);
}

Vector3 Vector3::Normalize() {
	float len = Length();
	return *this / len;
}

Vector3 Vector3::Cross(const Vector3& oth) {
	float _x = y * oth.z - z * oth.y;
	float _y = z * oth.x - x * oth.z;
	float _z = x * oth.y - y * oth.x;
	return Vector3(_x, _y, _z);
}

Vector3& Vector3::operator=(const Vector3& oth) {
	x = oth.x;
	y = oth.y;
	z = oth.z;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& oth) {
	return Vector3(x + oth.x, y + oth.y, z + oth.z);
}

Vector3& Vector3::operator+=(const Vector3& oth) {
	x += oth.x;
	y += oth.y;
	z += oth.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& oth) {
	return Vector3(x - oth.x, y - oth.y, z - oth.z);
}

Vector3& Vector3::operator-=(const Vector3& oth) {
	x -= oth.x;
	y -= oth.y;
	z -= oth.z;
	return *this;
}

Vector3 Vector3::operator*(const float& oth) {
	return Vector3(x * oth, y * oth, z * oth);
}

Vector3& Vector3::operator*=(const float& oth) {
	x *= oth;
	y *= oth;
	z *= oth;
	return *this;
}

Vector3 Vector3::operator/(const float& oth) {
	return Vector3(x / oth, y / oth, z / oth);
}

Vector3& Vector3::operator/=(const float& oth) {
	x /= oth;
	y /= oth;
	z /= oth;
	return *this;
}