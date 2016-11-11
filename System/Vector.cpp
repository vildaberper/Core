#include "System\Vector.h"

Vector::Vector(const float& x, const float& y){
	Vector::x = x;
	Vector::y = y;
}

Vector::Vector(const std::vector<float>& fs){
	x = fs.size() > 0 ? fs[0] : 0.0f;
	y = fs.size() > 1 ? fs[1] : 0.0f;
}

Vector::Vector(const sf::Vector2f& fs){
	x = fs.x;
	y = fs.y;
}

Vector::Vector(){
	x = 0;
	y = 0;
}

Vector::~Vector(){

}

std::vector<float> Vector::toVector() const{
	std::vector<float> fs;
	fs.push_back(x);
	fs.push_back(y);
	return fs;
}

sf::Vector2f Vector::toVector2f() const{
	return sf::Vector2f(x, y);
}

float Vector::length() const{
	return distance2D(0, 0, x, y);
}

float Vector::angle() const{
	return angleTo(0, 0, x, y);
}

Vector Vector::normalize() const{
	float l = length();
	return (*this) / (l != 0.0f ? l : 1.0f);
}

float Vector::distanceTo(const Vector& v) const{
	return distance2D(x, y, v.x, v.y);
}

std::string Vector::toString(const std::string& separator) const{
	return std::to_string(x) + separator + std::to_string(y);
}

void Vector::operator=(const std::vector<float>& v){
	x = v.size() > 0 ? v[0] : 0.0f;
	y = v.size() > 1 ? v[1] : 0.0f;
}
void Vector::operator=(const sf::Vector2f& v){
	x = v.x;
	y = v.y;
}

void Vector::operator()(const float& x, const float& y){
	Vector::x = x;
	Vector::y = y;
}

float& Vector::operator[](const unsigned char& i){
	return i == 0 ? x : y;
}

bool Vector::operator==(const Vector& v) const{
	return x == v.x && y == v.y;
}
bool Vector::operator==(const std::vector<float>& v) const{
	return v.size() == 2 && x == v[0] && y == v[1];
}
bool Vector::operator==(const sf::Vector2f& v) const{
	return x == v.x && y == v.y;
}

Vector Vector::operator*(const float& f) const{
	return Vector(x * f, y * f);
}
void Vector::operator*=(const float& f){
	x = x * f;
	y = y * f;
}

Vector Vector::operator/(const float& f) const{
	return Vector(x / f, y / f);
}
void Vector::operator/=(const float& f){
	x = x / f;
	y = y / f;
}

Vector Vector::operator+(const Vector& v) const{
	return Vector(x + v.x, y + v.y);
}
void Vector::operator+=(const Vector& v){
	x += v.x;
	y += v.y;
}

Vector Vector::operator-(const Vector& v) const{
	return Vector(x - v.x, y - v.y);
}
void Vector::operator-=(const Vector& v){
	x -= v.x;
	y -= v.y;
}
