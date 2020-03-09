#include "my_math.h"
#define max(a,b) a>=b?a:b
#define min(a,b) a<=b?a:b
double eps = 0.00000001;

Point::Point(double x, double y) {
	x_ = x;
	y_ = y;
}
Point::Point()
{
	x_ = INFINITY;
	y_ = INFINITY;
}
bool Point::operator==(const Point& point) const 
{
	if (x_ == point.x_ && y_ == point.y_)
		return true;
	if (equal(x_, point.x_) && equal(y_, point.y_))
	{
		return true;
	}
	return false;
}

bool Point::operator<(const Point& point) const
{
	if (equal(x_, point.x_) && equal(y_, point.y_)) {
		return false;
	}
	if (!equal(x_, point.x_)) {
		return x_ < point.x_;
	}
	else {
		return y_ < point.y_;
	}
}

Point Point::operator+(const Point& point) const
{	
	return Point(x_ + point.x_, y_ + point.y_);
}

Point Point::operator-(const Point& point) const
{
	return Point(x_ - point.x_, y_ - point.y_);
}

Point Point::operator*(const double& d) const
{
	return Point(x_ * d, y_ * d);
}

Point Point::operator/(const double& d) const
{
	return Point(x_ / d, y_ / d);
}

double Point::get_x()const {
	return x_;
}
 
double Point::get_y()const {
	return y_;
}

double Point::distance(const Point& point) const
{
	return sqrt(pow((x_ - point.x_),2)+pow((y_ - point.y_),2));
}


void operator<<(std::ostream& os, Point& point)
{
	os << "x is " << point.x_ << " and " << " y is " << point.y_ << "\n";
}

Line::Line(const Point& p1, const Point& p2)
{
	double x_1 = p1.get_x();
	double y_1 = p1.get_y();
	double x_2 = p2.get_x();
	double y_2 = p2.get_y();
	a = y_2 - y_1;
	b = x_1 - x_2;
	c = x_2 * y_1 - x_1 * y_2;
}

Line::Line(const double& a_, const double& b_, const double& c_) {
	a = a_;
	b = b_;
	c = c_;
}

Line::Line(const double& a_, const double& b_, const Point& point)
{
	a = a_;
	b = b_;
	c = -a * point.get_x() - b * point.get_y();
}

Point Line::find_intersection(const Line& line)
{
	if (*this == line) {
		std::cout << "两条线重合， 无数个交点" << std::endl;
		abort();
	}
	else {
		if (b * line.a - a * line.b == 0) {
			return Point();
		}
		else {
			double x;
			double y;
			y = (a * line.c - c * line.a) / (b * line.a - a * line.b);
			if (a != 0) {
				x = (- c - b * y) / a;
			}
			else {
				x = (-line.c - line.b * y) / line.a;
			}
			return Point(x, y);
		}
	}
	
}

bool Line::operator==(const Line& line)
{
	if (equal(a, line.a) && equal(b, line.b) && equal(c, line.c)) {
		return true;
	}
	return false;
}


double Line::get_a()const
{
	return a;
}

double Line::get_b()const
{
	return b;
}
double Line::get_c()const
{
	return c;
}

Vector Line::get_directionVector() const
{
	return Vector(b/sqrt(pow(b,2)+ pow(a, 2)), -a / sqrt(pow(b, 2) + pow(a, 2)));
}

void operator<<(std::ostream& os, Line& line)
{
	os << "a is " << line.a << " and b is "  << line.b << " and c is " << line.c << "\n";
}

bool equal(const double &a, const double &b) {
	if (abs(a - b) < eps) {
		return true;
	}
	else {
		return false;
	}
}

Circle::Circle(const Point& point, const double r_)
{
	o = point;
	r = r_;
}

Circle::Circle()
{
	Point o(INFINITY, INFINITY);
	r = 0;
}

int Circle::find_intersection(const Line& line, Point* p)
{
	int n;	//	交点个数
	Vector line_vector = line.get_directionVector();	//	line 的单位向量
	Line line_h(-line.get_b(), line.get_a(), o); // 和 line 垂直且过圆心的垂线 line_h
	Point i1 = line_h.find_intersection(line);	// l_h 和 line 的交点 i1
	double d = i1.distance(o);	//	i1 到 圆心 o 的 距离
	double l = sqrt(pow(r, 2) - pow(d, 2));	//  sqrt(r^2 - d^2)
	Vector v = line_vector* l;
	*p = i1 + line_vector * l;
	*(p+1) = i1 - line_vector * l;

	if (d > r) {
		n = 0;
		return n;
	}
	else if (abs(d - r) <= eps) n = 1;
	else n = 2;
	return n;
}

int Circle::find_intersection(const Circle& circle, Point* p)
{
	if (o == circle.o && (r - circle.r) < eps) {
		std::cout << "两圆重合，无数个交点" << std::endl;
		abort();
	}

	//	交点个数
	int n;

	//	分大小圆
	Circle big;
	Circle small;
	if (r >= circle.r) {
		big = *this;
		small = circle;
	}
	else {
		big = circle;
		small = *this;
	}

	//	判断交点个数
	double d = big.o.distance(small.o);
	if (d > (big.r + small.r) || d < big.r - small.r) {
		n = 0;
		return n;
	}
	else if (abs(d - (big.r + small.r)) <= eps) {	//	小圆外切
		n = 1;
		Vector v1 = small.o - big.o;	//	大圆圆心射向小圆圆心的向量
		v1 = v1 * (big.r / (big.r + small.r));
		*p = big.o + v1;
		return n;
	}
	else if (abs(d - (big.r - small.r)) <= eps) {	//	小圆内切
		n = 1;
		Vector v1 = small.o - big.o;	//	大圆圆心射向小圆圆心的向量
		v1 = v1 / big.o.distance(small.o) * big.r;
		*p = big.o + v1;
		return n;
	}
	else  {	// 2个交点  d ，r1，r2形成三角形 
		n = 2;
		Vector v1 = small.o - big.o;
		v1 = v1 / big.o.distance(small.o);	//	单位向量
		double x = (pow(big.r, 2) - pow(small.r, 2) + pow(d, 2)) / (2 * d);
		v1 = v1 *  x;
		Point cross = big.o + v1;
		Line l(v1.get_x(), v1.get_y(), cross);
		big.find_intersection(l, p);
		return n;
	}
	return 0;
}

double Circle::get_r() const
{
	return r;
}

Point Circle::get_o() const
{
	return o;
}
