# include <iostream>
# include <vector>
# include <math.h>
# define SMALL 1e-5f

# include "Vector.hpp"
# include "Boid.hpp"
# include "Simulator.hpp"


Vector::Vector() : a(0.f), b(0.f) {}
Vector::Vector(float x, float y) : a(x), b(y) {}
Vector::Vector(const Vector& other) {
	this->a = other.a;
	this->b = other.b;
}
Vector::~Vector() {} // std::cout << "Destructor Vector" << std::endl; }

// Fonctions pour les opérations vectorielles (addition, soustraction, normalisation, etc.)
Vector Vector::operator+(const Vector& other) const {
	return Vector(this->a + other.a, this->b + other.b);
}
Vector Vector::operator-(const Vector& other) const {
	return Vector(this->a - other.a, this->b - other.b);
}
Vector Vector::operator*(float scalar) const {
	return Vector(this->a * scalar, this->b * scalar);
}
Vector Vector::normalized() const {
	float mag = magnitude();
	return Vector(this->a / mag, this->b / mag);
}
float Vector::magnitude() const {
	float offset{ SMALL };
	return sqrtf(powf(this->a,2) + powf(this->b,2) + offset);
}

float Vector::getX() const { float x = this->a;  return x; }
float Vector::getY() const { float y = this->b;  return y; }