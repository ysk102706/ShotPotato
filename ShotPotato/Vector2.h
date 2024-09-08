#pragma once
#include <math.h>

class Vector2 {
public:
	float x, y;

	Vector2();
	Vector2(float x, float y);

	float Length();
	float Dot(const Vector2 oth);
	Vector2 Normalize();

	Vector2& operator=(const Vector2& oth);

	Vector2 operator+(const Vector2& oth);
	Vector2& operator+=(const Vector2& oth);

	Vector2 operator-(const Vector2& oth);
	Vector2& operator-=(const Vector2& oth);

	Vector2 operator*(const float& oth);
	Vector2& operator*=(const float& oth);

	Vector2 operator/(const float& oth);
	Vector2& operator/=(const float& oth);

};