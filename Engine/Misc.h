#pragma once

class Vector2 {
public:
    double x;
    double y;

    Vector2();
    Vector2(double x, double y);
    ~Vector2() = default;

    void Add(const Vector2& other);
    void Subtract(const Vector2& other);
    void Scale(const double scalar);
    Vector2 Rotated(const double angle) const;

    double Magnitude() const;
    double MagnitudeSquared() const;

    Vector2& Normalize();
    Vector2 UnitVector() const;
    Vector2 Normal() const;

    double Dot(const Vector2& other) const;
    double Cross(const Vector2& other) const;

    Vector2& operator = (const Vector2& other);
    bool operator == (const Vector2& other) const;
    bool operator != (const Vector2& other) const;
    Vector2 operator + (const Vector2& other) const;
    Vector2 operator - (const Vector2& other) const;
    Vector2 operator * (const double scalar) const;
    Vector2 operator / (const double divisor) const;
    Vector2 operator - ();

    Vector2& operator += (const Vector2& other);
    Vector2& operator -= (const Vector2& other);
    Vector2& operator *= (const double scalar);
    Vector2& operator /= (const double divisor);
    
    
};

    