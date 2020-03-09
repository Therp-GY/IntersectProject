#ifndef MATH_H
#define MATH_H
#include <ostream>
#include <iostream>
#include <functional>	

template<typename t>
inline void hash_combine(std::size_t& seed, const t& val)
{
	seed ^= std::hash<t>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename t>
inline void hash_val(std::size_t& seed, const t& val)
{
	hash_combine(seed, val);
}

template<typename t, typename... types>
inline void hash_val(std::size_t& seed, const t& val, const types& ... args)
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}

template<typename... types>
inline std::size_t hash_val(const types& ...args)
{
	std::size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

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
	bool operator<(const Point& point) const;  //	以x大小排序
	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	Point operator*(const double& d) const;
	Point operator/(const double& d) const;
	friend void operator<<(std::ostream &os,  Point &point);
};

typedef Point Vector;

namespace std
{
	template<>
	struct hash<Point>
	{
		size_t operator() (const Point& s) const noexcept
		{
			return hash_val(s.get_x(), s.get_y());
		}
	}; // 间接调用原生Hash.
}



class Line {
	double a;
	double b;
	double c;
	//	ax + by + c = 0
public:
	Line(const Point& p1, const  Point& p2);
	Line(const double& a_, const double& b_, const double& c_);
	Line(const double& a_, const double& b_, const Point &point);
	Point find_intersection(const Line &line);	
	double get_a()const;
	double get_b()const;
	double get_c()const;
	Vector get_directionVector()const;
	bool operator==(const Line& line);
	friend void operator<<(std::ostream& os, Line& line);
};

class Circle {
	Point o;
	double r;
public:
	Circle(const Point& point, const double r_);
	Circle();
	int find_intersection(const Line& line , Point *p);
	int find_intersection(const Circle& circle, Point* p);
	double get_r()const;
	Point get_o()const;

};

bool equal(const double& a, const double& b);



#endif