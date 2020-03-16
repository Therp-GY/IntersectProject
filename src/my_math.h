#ifndef MATH_H
#define MATH_H
#include <ostream>
#include <iostream>
#include <functional>	

class Point;
class Line;
class Circle;
class Ray;

class Point {
	double x_;
	double y_;
public:
	Point(double x, double y);
	Point();
	double get_x()const;
	double get_y()const;
	double distance(const Point& point)const;
	bool operator==(const Point& point) const;
	bool operator<(const Point& point) const;  //	ÒÔx´óÐ¡ÅÅÐò
	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	Point operator*(const double& d) const;
	Point operator/(const double& d) const;
	friend void operator<<(std::ostream &os,  Point &point);
};

typedef Point Vector;



class Line {
protected:
	double a;
	double b;
	double c;
	//	ax + by + c = 0
public:
	Line(const Point& p1, const  Point& p2);
	Line(const double& a_, const double& b_, const double& c_);
	Line(const double& a_, const double& b_, const Point &point);
	virtual int find_intersection(const Line &line, Point *p) const; 	
	virtual int find_intersection(const Circle& circle, Point* p) const;
	double get_a()const;
	double get_b()const;
	double get_c()const;
	Vector get_directionVector()const;
	bool operator==(const Line& line)const;
	friend void operator<<(std::ostream& os, Line& line);
};

class Circle {
	Point o;
	double r;
public:
	Circle(const Point& point, const double r_);
	Circle();
	int find_intersection(const Line& line , Point *p)const;
	int find_intersection(const Circle& circle, Point* p)const;
	double get_r()const;
	Point get_o()const;

};


class Ray:public Line {
private:
	Point start_point;
	int x_change;
	int y_change;
public:

};
bool equal(const double& a, const double& b);



#endif