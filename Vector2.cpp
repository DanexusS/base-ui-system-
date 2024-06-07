#include <stdexcept>

#include "Vector2.h"

/// <summary>
/// Set _value1 to val1 and _value2 to val2.
/// </summary>
void Vector2::setValues(double x, double y) {
	this->_x = x;
	this->_y = y;
}

/// <summary>
/// Increase _value1 by dval1 and _value2 by dval2.
/// </summary>
void Vector2::addValues(double dx, double dy) {
	this->_x += dx;
	this->_y += dy;
}

Vector2::Vector2(const Vector2 &other)
{
	setValues(other._x, other._y);
}

Vector2::Vector2(Vector2 &other)
{
	*this = other;
	other = Vector2( 0, 0 );
}

Vector2& Vector2::operator=(double value) {
	this->_x = value;
	this->_y = value;

	return *this;
}

Vector2 &Vector2::operator=(const Vector2 &other)
{
	if (this == &other)
		return *this;

	setValues(other._x, other._y);
	return *this;
}

Vector2& Vector2::operator+(const Vector2& other) {
	setValues(this->_x + other._x, this->_y + other._y);
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other) {
	if (this == &other)
		return *this;

	this->_x += other._x;
	this->_y += other._y;
	return *this;
}

double& Vector2::operator[](unsigned int index) {
	if (index > 1)
		throw std::out_of_range("Provided index is out of range. Allowed index's values are (0, 1).");

	if (index == 0)
		return _x;
	return _y;
}

const double& Vector2::operator[](unsigned int index) const {
	if (index > 1)
		throw std::out_of_range("Provided index is out of range. Allowed index's values are (0, 1).");

	if (index == 0)
		return _x;
	return _y;
}
