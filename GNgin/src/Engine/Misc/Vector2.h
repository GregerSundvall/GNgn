#pragma once
struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	~Vector2() = default;

	void Add(const Vector2& other);
	void Subtract(const Vector2& other);
	void Scale(const float scalar);
	Vector2 GetRotatedBy(const float angle) const;

	float Magnitude();


};

