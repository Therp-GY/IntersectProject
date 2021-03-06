﻿#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <set>
#include<fstream>
#include "my_math.h"
using namespace std;

void find_intersection_l_l(Line& l, vector<Line>& l_list, set<Point>& p_set);
void find_intersection_l_c(Line& l, vector<Circle>& c_list, set<Point>& p_set);
void find_intersection_c_l(Circle& c, vector<Line>& l_list, set<Point>& p_set);
void find_intersection_c_c(Circle& c, vector<Circle>& c_list, set<Point>& p_set);




int main(int argc, char *argv[]) {
	ofstream fout;
	ifstream fin;
	set<Point>point_set;
	vector<Line> line_list;
	vector<Line>::iterator line_it;
	vector<Circle>circle_list;
	vector<Circle>::iterator circle_it;

	for(int i = 1; i < argc; i++) {
		if ((string)argv[i] == "-i") {
			fin.open(argv[i + 1]);
		}
		if ((string)argv[i] == "-o") {
			fout.open(argv[i + 1]);
		}
	}

	//	去重方法
	/*line_list.erase(unique(line_list.begin(), line_list.end()), line_list.end);*/
	int n;
	fin >> n;
	for (int i = 0; i < n; i++) {
		char type;
		double x1, y1, x2, y2, r;
		fin >> type;
		if (type == 'L') {
			fin >> x1;
			fin >> y1;
			Point p1(x1, y1);
			fin >> x2;
			fin >> y2;
			Point p2(x2, y2);
			Line l(p1, p2);
			find_intersection_l_l(l, line_list, point_set);
			find_intersection_l_c(l, circle_list, point_set);
			line_list.push_back(l);

		}
		else if(type == 'C'){
			fin >> x1;
			fin >> y1;
			Point p1(x1, y1);
			fin >> r;
			Circle circle(p1, r);
			find_intersection_c_l(circle, line_list, point_set);
			find_intersection_c_c(circle, circle_list, point_set);
			circle_list.push_back(circle);

		}
		else {
			fout << "wrong input" << endl;
			fin.ignore(100, '\n');
			i--;
		}
	}
	fout << point_set.size() << endl;
	//for (point_it = point_set.begin(); point_it != point_set.end(); point_it++) {	
	//	fout << point_it ->first.get_x() << "," << point_it->first.get_y() << endl;
	//}

}

void find_intersection_l_l(Line &l,vector<Line> &l_list, set<Point>&p_set) {
	for (unsigned int i = 0; i < l_list.size(); i++) {
		Point p;
		Point nopoint(INFINITY, INFINITY);
		p = l_list[i].find_intersection(l);
		if (p == nopoint)continue;
		p_set.insert(p);
	}
}

void find_intersection_l_c(Line &l, vector<Circle>& c_list, set<Point>& p_set) {
	for (unsigned int i = 0; i < c_list.size(); i++) {
		Point p[2];
		int n;
		n = c_list[i].find_intersection(l, p);
		if (n == 0)continue;
		else if (n == 1) {
			p_set.insert(p[0]);
		}
		else {
			p_set.insert(p[0]);
			p_set.insert(p[1]);
		}
	}
}

void find_intersection_c_l(Circle &c, vector<Line>& l_list, set<Point>& p_set) {
	for (unsigned int i = 0; i < l_list.size(); i++) {
		Point p[2];
		int n;
		n = c.find_intersection(l_list[i], p);
			if (n == 0)continue;
		else if (n == 1) {
			p_set.insert(p[0]);
		}
		else {
			p_set.insert(p[0]);
			p_set.insert(p[1]);	
		}
	}
}


void find_intersection_c_c(Circle &c, vector<Circle>& c_list, set<Point>& p_set) {
	for (unsigned int i = 0; i < c_list.size(); i++) {
		Point p[2];
		int n;
		n = c_list[i].find_intersection(c, p);
		if (n == 0)continue;
		else if (n == 1) {
			p_set.insert(p[0]);	
		}
		else {
			p_set.insert(p[0]);
			p_set.insert(p[1]);
		}
	}
}