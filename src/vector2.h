#pragma once

class Vector2
{
public:
    float x;
    float y;

    Vector2(float x, float y) : x(x), y(y) {}
    Vector2() : x(0), y(0) {}
    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 operator*(const Vector2 &other) const
    {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2 operator/(const Vector2 &other) const
    {
        return Vector2(x / other.x, y / other.y);
    }
    Vector2 operator*(float scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 operator/(float scalar) const
    {
        return Vector2(x / scalar, y / scalar);
    }
    Vector2 &operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2 &operator-=(const Vector2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2 &operator*=(const Vector2 &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vector2 &operator/=(const Vector2 &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }
    Vector2 &operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2 &operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    bool operator==(const Vector2 &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator!=(const Vector2 &other) const
    {
        return x != other.x || y != other.y;
    }
    void truncate(float max)
    {
        x = x > max ? max : x;
        y = y > max ? max : y;
    }
};