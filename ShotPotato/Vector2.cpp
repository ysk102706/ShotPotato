#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::Length() {
	return sqrtf(x * x + y * y);
}

float Vector2::Dot(const Vector2 oth) {
	return x * oth.x + y * oth.y;
}

Vector2 Vector2::Normalize() {
	float len = Length();
	return *this / len;
}

Vector2& Vector2::operator=(const Vector2& oth) {
	x = oth.x;
	y = oth.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& oth) {
	return Vector2(x + oth.x, y + oth.y);
}

Vector2& Vector2::operator+=(const Vector2& oth) {
	x += oth.x;
	y += oth.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& oth) {
	return Vector2(x - oth.x, y - oth.y);
}

Vector2& Vector2::operator-=(const Vector2& oth) {
	x -= oth.x;
	y -= oth.y;
	return *this;
}

Vector2 Vector2::operator*(const float& oth) {
	return Vector2(x * oth, y * oth);
}

Vector2& Vector2::operator*=(const float& oth) {
	x *= oth;
	y *= oth;
	return *this;
}

Vector2 Vector2::operator/(const float& oth) {
	return Vector2(x / oth, y / oth);
}

Vector2& Vector2::operator/=(const float& oth) {
	x /= oth;
	y /= oth;
	return *this;
}