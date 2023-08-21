#include "Point.h"

Point::Point()
{
	Point(0, 0);
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point Point::operator+(const Point& other)
{
	Point result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	return result;
}

Point Point::operator-(const Point& other)
{
	Point result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	return result;
}

Point Point::operator*(const float coeficient)
{
	Point result;
	result.x = this->x * coeficient;
	result.y = this->y * coeficient;
	return result;
}

void Point::print()
{
	std::cout << (int)x << ":" << (int)y;
}