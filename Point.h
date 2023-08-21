#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>

class Point
{
public:
	float x;
	float y;

	Point();
	Point(float x, float y);

	Point operator+(const Point& other);
	Point operator-(const Point& other);
	Point operator*(const float coeficient);
	void print();

	float getLengthSquared() { return x * x + y * y; }

};

#endif //__POINT_H__