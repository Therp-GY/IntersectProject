#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "my_math.h"
using namespace std;

void find_intersection_l_l(Line& l, vector<Line>& l_list, unordered_map<Point, int>& p_unordered_map);
void find_intersection_l_c(Line& l, vector<Circle>& c_list, unordered_map<Point, int>& p_unordered_map);
void find_intersection_c_l(Circle& c, vector<Line>& l_list, unordered_map<Point, int>& p_unordered_map);
void find_intersection_c_c(Circle& c, vector<Circle>& c_list, unordered_map<Point, int>& p_unordered_map);




int main() {
	unordered_map<Point, int>point_unordered_map;
	unordered_map<Point, int>::iterator point_it;
	vector<Line> line_list;
	vector<Line>::iterator line_it;
	vector<Circle>circle_list;
	vector<Circle>::iterator circle_it;

	//	ȥ�ط���
	/*line_list.erase(unique(line_list.begin(), line_list.end()), line_list.end);*/
	cout << "how many inputs ?" << endl;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char type;
		double x1, y1, x2, y2, r;
		cin >> type;
		if (type == 'L') {
			cin >> x1;
			cin >> y1;
			Point p1(x1, y1);
			cin >> x2;
			cin >> y2;
			Point p2(x2, y2);
			Line l(p1, p2);
			find_intersection_l_l(l, line_list, point_unordered_map);
			find_intersection_l_c(l, circle_list, point_unordered_map);
			line_list.push_back(l);

		}
		else if(type == 'C'){
			cin >> x1;
			cin >> y1;
			Point p1(x1, y1);
			cin >> r;
			Circle circle(p1, r);
			find_intersection_c_l(circle, line_list, point_unordered_map);
			find_intersection_c_c(circle, circle_list, point_unordered_map);
			circle_list.push_back(circle);

		}
		else {
			cout << "wrong input" << endl;
			cin.ignore(100, '\n');
			i--;
		}
	}
	cout << point_unordered_map.size() << endl;
	//for (point_it = point_unordered_map.begin(); point_it != point_unordered_map.end(); point_it++) {	
	//	cout << point_it ->first.get_x() << "," << point_it->first.get_y() << endl;
	//}

}

void find_intersection_l_l(Line &l,vector<Line> &l_list, unordered_map<Point, int>&p_unordered_map) {
	for (unsigned int i = 0; i < l_list.size(); i++) {
		Point p;
		Point nopoint(INFINITY, INFINITY);
		p = l_list[i].find_intersection(l);
		if (p == nopoint)continue;
		p_unordered_map.insert(pair<Point, int>(p, 1));
	}
}

void find_intersection_l_c(Line &l, vector<Circle>& c_list, unordered_map<Point, int>& p_unordered_map) {
	for (unsigned int i = 0; i < c_list.size(); i++) {
		Point p[2];
		int n;
		n = c_list[i].find_intersection(l, p);
		if (n == 0)continue;
		else if (n == 1) {
			p_unordered_map.insert(pair<Point, int>(p[0], 1));
		}
		else {
			p_unordered_map.insert(pair<Point, int>(p[0], 1));
			p_unordered_map.insert(pair<Point, int>(p[1], 1));
		}
	}
}

void find_intersection_c_l(Circle &c, vector<Line>& l_list, unordered_map<Point, int>& p_unordered_map) {
	for (unsigned int i = 0; i < l_list.size(); i++) {
		Point p[2];
		int n;
		n = c.find_intersection(l_list[i], p);
			if (n == 0)continue;
		else if (n == 1) {
			p_unordered_map.insert(pair<Point, int>(p[0], 1));
		}
		else {
			p_unordered_map.insert(pair<Point, int>(p[0], 1));
			p_unordered_map.insert(pair<Point, int>(p[1], 1));	
		}
	}
}


void find_intersection_c_c(Circle &c, vector<Circle>& c_list, unordered_map<Point, int>& p_unordered_map) {
	for (unsigned int i = 0; i < c_list.size(); i++) {
		Point p[2];
		int n;
		n = c_list[i].find_intersection(c, p);
		if (n == 0)continue;
		else if (n == 1) {
			p_unordered_map.insert(pair<Point, int>(p[0], 1));	
		}
		else {
			p_unordered_map.insert(pair<Point, int>(p[0], 1));
			p_unordered_map.insert(pair<Point, int>(p[1], 1));
		}
	}
}