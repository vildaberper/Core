#pragma once

#include "SFML\System\Vector2.hpp"

#include <string>
#include <vector>

#include "System\Math.h"

class Vector{

private:

	float x;
	float y;

public:

	Vector(const float& x, const float& y);
	Vector(const std::vector<float>& v);
	Vector(const sf::Vector2f& v);
	Vector();
	~Vector();

	std::vector<float> Vector::toVector() const;
	sf::Vector2f Vector::toVector2f() const;

	float length() const;
	float angle() const;
	Vector normalize() const;
	float distanceTo(const Vector& v) const;
	std::string toString(const std::string& separator = ",") const;

	void operator=(const std::vector<float>& v);
	void operator=(const sf::Vector2f& v);

	void operator()(const float& x, const float& y);

	float& operator[](const unsigned char& i);

	bool operator==(const Vector& v) const;
	bool operator==(const std::vector<float>& v) const;
	bool operator==(const sf::Vector2f& v) const;

	Vector operator*(const float& f) const;
	void operator*=(const float& f);

	Vector operator/(const float& f) const;
	void operator/=(const float& f);

	Vector operator+(const Vector& v) const;
	void operator+=(const Vector& v);

	Vector operator-(const Vector& v) const;
	void operator-=(const Vector& v);

};
