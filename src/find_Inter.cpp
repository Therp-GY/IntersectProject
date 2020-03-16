#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <set>
#include<fstream>
#include "my_math.h"
using namespace std;

template<typename T1, typename T2>
void find(T1& c, vector<T2>& c_list, set<Point>& p_set);

int main(int argc, char* argv[]) {

	set<Point>point_set;
	vector<Line> line_list;
	vector<Line>::iterator line_it;
	vector<Circle>circle_list;
	vector<Circle>::iterator circle_it;

	//ofstream fout;
	//ifstream cin;
	//for (int i = 1; i < argc; i++) {
	//	if ((string)argv[i] == "-i") {
	//		cin.open(argv[i + 1]);
	//	}
	//	if ((string)argv[i] == "-o") {
	//		fout.open(argv[i + 1]);
	//	}
	//}

	//	去重方法
	/*line_list.erase(unique(line_list.begin(), line_list.end()), line_list.end);*/
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
			find(l, line_list, point_set);
			find(l, circle_list, point_set);
			line_list.push_back(l);

		}
		else if (type == 'C') {
			cin >> x1;
			cin >> y1;
			Point p1(x1, y1);
			cin >> r;
			Circle circle(p1, r);
			find(circle, line_list, point_set);
			/*find(circle, circle_list, point_set);*/
			circle_list.push_back(circle);

		}
		else {
			cout << "wrong input" << endl;
			cin.ignore(100, '\n');
			i--;
		}
	}
	cout << point_set.size() << endl;
	//for (point_it = point_set.begin(); point_it != point_set.end(); point_it++) {	
	//	fout << point_it ->first.get_x() << "," << point_it->first.get_y() << endl;
	//}

}



template<typename T1, typename T2>
void find(T1& c, vector<T2>& c_list, set<Point>& p_set) {
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