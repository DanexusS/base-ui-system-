#pragma once

struct Vector2 {
private:
	double _x, _y;

	void setValues(double x, double y);
	void addValues(double dx, double dy);
public:
	Vector2() { setValues(0, 0); }
	Vector2(double x, double y) { setValues(x, y); }

	Vector2(const Vector2 &other);
	Vector2(Vector2 &other);

	
	Vector2& operator=(double value);
	Vector2& operator=(const Vector2& other);
	

	Vector2& operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& other);

	// NOTE: WIP
	double& operator[](unsigned int index);
	const double& operator[](unsigned int index) const;
};
