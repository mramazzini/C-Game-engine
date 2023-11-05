#include "Vector2D.h"
#include <cmath>
Vector2D::Vector2D()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const Vector2D &v)
{
    this->x = v.x;
    this->y = v.y;
}

Vector2D &Vector2D::Add(const Vector2D &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
};
Vector2D &Vector2D::Subtract(const Vector2D &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
};
Vector2D &Vector2D::Multiply(const Vector2D &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
};
Vector2D &Vector2D::Divide(const Vector2D &vec)
{
    this->x /= vec.x;
    this->y /= vec.y;
    return *this;
};

Vector2D &operator+(Vector2D &v1, const Vector2D &v2)
{
    return v1.Add(v2);
};
Vector2D &operator-(Vector2D &v1, const Vector2D &v2)
{
    return v1.Subtract(v2);
};
Vector2D &operator*(Vector2D &v1, const Vector2D &v2)
{
    return v1.Multiply(v2);
};
Vector2D &operator/(Vector2D &v1, const Vector2D &v2)
{
    return v1.Divide(v2);
};

Vector2D &Vector2D::operator+=(const Vector2D &v)
{
    return this->Add(v);
};
Vector2D &Vector2D::operator-=(const Vector2D &v)
{
    return this->Subtract(v);
};
Vector2D &Vector2D::operator*=(const Vector2D &v)
{
    return this->Multiply(v);
};
Vector2D &Vector2D::operator/=(const Vector2D &v)
{
    return this->Divide(v);
};

Vector2D &Vector2D::operator*(const int &i)
{
    this->x *= i;
    this->x *= y;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vector2D &v)
{
    os << "(" << v.x << "," << v.y << ")";
    return os;
}

Vector2D &Vector2D::Zero()
{
    this->x = 0;
    this->y = 0;
    return *this;
}
Vector2D &Vector2D::normalize()
{
    float magnitude = std::sqrt(this->x * this->x + this->y * this->y);
    if (magnitude != 0)
    {
        this->x /= magnitude;
        this->y /= magnitude;
    }
    return *this;
}