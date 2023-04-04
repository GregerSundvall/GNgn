#include "Vector2.h"

#include <iostream>

#include "math.h"


Vector2::Vector2(double const x, double const y) {
	this->x = x;
	this->y = y;
}

void Vector2::Add(const Vector2& other) {
	x += other.x;
	y += other.y;
}

void Vector2::Subtract(const Vector2& other) {
	x -= other.x;
	y -= other.y;
}

void Vector2::Scale(const double scalar) {
	x *= scalar;
	y *= scalar;
}

Vector2 Vector2::Rotated(const double angle) const {
	Vector2 result;
	result.x = x * cos(angle) - y * sin(angle);
	result.y = x * sin(angle) + y * cos(angle);
	return result;
}

double Vector2::Magnitude() const {
	return sqrt(x * x + y * y);
}

double Vector2::MagnitudeSquared() const {
	return x * x + y * y;
}

Vector2& Vector2::Normalize() {
	float length = Magnitude();
	if (length != 0.0) {
		x /= length;
		y /= length;
	}
	return *this;
}

Vector2 Vector2::UnitVector() const {
	Vector2 result = Vector2(0, 0);
	float length = Magnitude();
	if (length != 0.0) {
		result.x = x / length;
		result.y = y / length;
	}
	return result;
}

Vector2 Vector2::Normal() const { return Vector2(y, -x).Normalize(); }

double Vector2::Dot(const Vector2& other) const { return (x * other.x) + (y * other.y); }

double Vector2::Cross(const Vector2& other) const { return (x * other.y) - (y * other.x); }

Vector2& Vector2::operator = (const Vector2& other) { x = other.x; y = other.y; return *this; }

bool Vector2::operator==(const Vector2& other) const { return x == other.x && y == other.y; }

bool Vector2::operator!=(const Vector2& other) const { return !(*this == other); }

Vector2 Vector2::operator+(const Vector2& other) const { Vector2 result; result.x = x + other.x;	result.y = y + other.y; return result; }

Vector2 Vector2::operator-(const Vector2& other) const {Vector2 result; result.x = x - other.x;	result.y = y - other.y; return result; }

Vector2 Vector2::operator*(const double scalar) const { Vector2 result; result.x = x * scalar; result.y = y * scalar; return result; }

Vector2 Vector2::operator/(const double divisor) const {Vector2 result; result.x = x / divisor; result.y = y / divisor; return result; }

Vector2 Vector2::operator-() { Vector2 result; result.x = x * -1; result.y = y * -1; return result; }

Vector2& Vector2::operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }

Vector2& Vector2::operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }

Vector2& Vector2::operator*=(const double scalar) { x *= scalar; y *= scalar;	return *this; }

Vector2& Vector2::operator/=(const double divisor) { x /= divisor; y /= divisor; return *this; }






