#pragma once
#include <math.h>

class Vector3 {
public:
	float x, y, z;

	static const Vector3 zero;
	static const Vector3 one;
	static const Vector3 forward;
	static const Vector3 up;
	static const Vector3 right;

	Vector3();
	Vector3(float x, float y, float z);

	float Length();
	float Dot(const Vector3& oth);
	Vector3 Normalize();
	Vector3 Cross(const Vector3& oth);

	Vector3& operator=(const Vector3& oth);

	Vector3 operator+(const Vector3& oth);
	Vector3& operator+=(const Vector3& oth);

	Vector3 operator-(const Vector3& oth);
	Vector3& operator-=(const Vector3& oth);

	Vector3 operator*(const float& oth);
	Vector3& operator*=(const float& oth);

	Vector3 operator/(const float& oth);
	Vector3& operator/=(const float& oth);

};