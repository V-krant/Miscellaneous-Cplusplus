//Class Inheritance

#include <iostream>
#include <vector>
#include<math.h>
#include <algorithm>
using namespace std;

class Point {
public:
	float x;
	float y;
	Point() { x = 0; y = 0; };
	Point(float i, float j) { x = i; y = j; };
	void operator=(Point &P) {
		x = P.x;
		y = P.y;
	}
	Point(const Point &P) {
		x = P.x;
		y = P.y;
	}
	void displayPt() {
		cout << "X co-ordinate is : " << x << endl;
		cout << "Y co-ordinate is : " << y << endl;
	}
};

class Shape {
protected:
	vector<Point> corners;
	float area;
	float perimeter;
	Shape() { area = 0; perimeter = 0; }
	Shape(const Shape& S) {
		area = S.area;
		perimeter = S.perimeter;
		for (size_t i = 0; i < S.corners.size(); i++)
		{
			corners.push_back(S.corners[i]);
		}
	}
	void operator=(Shape &S) {
		area = S.area;
		perimeter = S.perimeter;
		for (size_t i = 0; i < S.corners.size(); i++)
		{
			corners[i].x=S.corners[i].x;
			corners[i].y = S.corners[i].y;
		}
	}
	virtual void displayShapeData() {
		cout << "The vertices of this shape are at:" << endl;
		for (int i = 0; i < corners.size(); i++) {
			cout << "( " << corners[i].x << " , " << corners[i].y << " )";
		}
		cout << "The area of shape is : " << area;
		cout << "The perimeter of shape is : " << perimeter;
	}
	virtual void calArea() = 0;
	virtual void calPerimeter() = 0;
};

class Triangle :private Shape {
	float side[3];
	void calSides() {
		if (corners[0].x == corners[1].x && corners[1].x == corners[2].x || corners[0].y == corners[1].y && corners[1].y == corners[2].y) {
			side[0] = side[1] = side[2] = 0;
			return;
		}
		side[0] = sqrt(pow((corners[1].x - corners[0].x), 2) + pow((corners[1].y - corners[0].y), 2));
		side[1] = sqrt(pow((corners[2].x - corners[1].x), 2) + pow((corners[2].y - corners[1].y), 2));
		side[2] = sqrt(pow((corners[0].x - corners[2].x), 2) + pow((corners[0].y - corners[2].y), 2));
		if (side[0] == 0 | side[1] == 0 | side[2] == 0)
			side[0] = side[1] = side[2] = 0;
	}
public:
	Triangle(Point a, Point b, Point c) {
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		calSides();
	}
	Triangle(Point a, Point b) {
		Point c(a.x+1,a.y+1);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		calSides();
	}
	Triangle(Point a) {
		Point b(a.x, a.y+1);
		Point c(a.x+1, a.y);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		calSides();
	}
	Triangle() {
		Point a(0, 0);
		Point b(0, 1);
		Point c(1, 0);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		calSides();
	}
	Triangle(const Triangle &T):Shape(T) {
		for (size_t i = 0; i < 3; i++)
		{
			side[i] = T.side[i];
		}
	}
	void operator=(Triangle &T) {
		Shape::operator=(T);
		for (size_t i = 0; i < 3; i++)
		{
			side[i] = T.side[i];
		}
	}
	void displayShapeData() {
		cout << "The vertices of this triangle are at: ";
		for (int i = 0; i < 3; i++) {
			cout << "( " << corners[i].x << " , " << corners[i].y << " ) ";
		}
		if (side[0] == 0) {
			cout <<endl<< "The given points are co-linear and cannot form a triangle" << endl;
			return;
		}
		cout << endl << "This triangle has sides of length: " << side[0] << " , " << side[1] << " , " << side[2] << endl;
		cout << "The area of this triangle is : " << area << endl;
		cout << "The perimeter of this triangle is : " << perimeter << endl;
	}
	void calArea() {
		float s = (side[0] + side[1] + side[2]) / 2;
		area = sqrt(s*(s - side[0])*(s - side[1])*(s - side[2]));
	}
	void calPerimeter() {
		perimeter = side[0] + side[1] + side[2];
	}
};

class Rectangle :protected Shape {
protected:
	float length;
	float breadth;
	void calLengthBreadth() {
		vector<float> temp;
		float diag1 = 0, diag2 = 0;
		temp.push_back(sqrt(pow((corners[1].x - corners[0].x), 2) + pow((corners[1].y - corners[0].y), 2)));
		temp.push_back(sqrt(pow((corners[2].x - corners[0].x), 2) + pow((corners[2].y - corners[0].y), 2)));
		temp.push_back(sqrt(pow((corners[3].x - corners[0].x), 2) + pow((corners[3].y - corners[0].y), 2)));
		if (temp[0] == 0 || temp[1] == 0 || temp[2] == 0) {
			length = breadth = 0;
			return;
		}
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (diag1 <= temp[i])
				diag1 = temp[i];
		}
		temp.erase(remove(temp.begin(), temp.end(), diag1));
		for (size_t i = 0; i < temp.size(); i++)
		{
			if (diag2 <= temp[i])
				diag2 = temp[i];
		}
		length = diag2;
		temp.erase(remove(temp.begin(), temp.end(), diag2));
		breadth = temp[0];
		if (abs((diag1*diag1) - ((length*length) + (breadth*breadth)))>0.01) {
			length = breadth = 0;
			return;
		}
	}
public:
	Rectangle(Point a, Point b, Point c, Point d) {
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		corners.push_back(d);
		calLengthBreadth();
	}
	Rectangle(Point a, Point b, Point c) {
		Point d(0,0);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		corners.push_back(d);
		calLengthBreadth();
	}
	Rectangle(Point a, Point b) {
		Point c(-a.x, -a.y);
		Point d(-b.x, -b.y);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		corners.push_back(d);
		calLengthBreadth();
	}
	Rectangle(Point a) {
		Point b(a.x, a.y + 1);
		Point c(a.x + 1, a.y);
		Point d(a.x + 1, a.y + 1);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		corners.push_back(d);
		calLengthBreadth();
	}
	Rectangle() {
		Point a(0, 0);
		Point b(0, 1);
		Point c(1, 0);
		Point d(1, 1);
		corners.push_back(a);
		corners.push_back(b);
		corners.push_back(c);
		corners.push_back(d);
		calLengthBreadth();
	}
	Rectangle(const Rectangle &R) :Shape(R) {
		length = R.length;
		breadth = R.breadth;
	}
	void operator=(Rectangle &R) {
		Shape::operator=(R);
		length = R.length;
		breadth = R.breadth;
	}
	void displayShapeData() {
		cout << "The vertices of this Rectangle are at: ";
		for (int i = 0; i < 4; i++) {
			cout << "( " << corners[i].x << " , " << corners[i].y << " ) ";
		}
		if (length == 0) {
			cout <<endl<< "The given points do not form a Rectangle" << endl;
			return;
		}
		cout << endl << "The length of this rectangle is : " << length<< endl;
		cout << "The breadth of this rectangle is : " << breadth << endl;
		cout << "The area of this rectangle is : " << area << endl;
		cout << "The perimeter of this rectangle is : " << perimeter << endl;
	}
	void calArea() {
		area = length*breadth;	
	}
	void calPerimeter() {
		perimeter = (2 * length) + (2 * breadth);
	}
};

class Square :private Rectangle {
	float side;
public:
	Square(Point a, Point b, Point c, Point d):Rectangle(a,b,c,d) {
		calLengthBreadth();
		if (length == breadth)
			side = length;
		else
			side = 0;
	}
	Square(Point a, Point b, Point c) :Rectangle(a, b, c) {
		calLengthBreadth();
		if (length == breadth)
			side = length;
		else
			side = 0;
	}
	Square(Point a, Point b) :Rectangle(a, b) {
		calLengthBreadth();
		if (length == breadth)
			side = length;
		else
			side = 0;
	}
	Square(Point a) :Rectangle(a) {
		calLengthBreadth();
		if (length == breadth)
			side = length;
		else
			side = 0;
	}
	Square() :Rectangle() {
		calLengthBreadth();
		if (length == breadth)
			side = length;
		else
			side = 0;
	}
	Square(const Square &S) :Rectangle(S) {
		side = S.side;
	}
	void operator=(Square &S) {
		Rectangle::operator=(S);
		side = S.side;
	}
	void displayShapeData() {
		cout << "The vertices of this Square are at: ";
		for (int i = 0; i < 4; i++) {
			cout << "( " << corners[i].x << " , " << corners[i].y << " ) ";
		}
		if (length == 0) {
			cout <<endl<< "The given points do not form a Square" << endl;
			return;
		}
		cout << endl << "The length of each side of this square is : " << length << endl;
		cout << "The area of this square is : " << area << endl;
		cout << "The perimeter of this square is : " << perimeter << endl;
	}
	void calArea() {
		area = side*side;
	}
	void calPerimeter() {
		perimeter = 4 * side;
	}
};

int main() {
	Point p1(1,1),p2(3,1),p3(1,4),p4(3,4),p5(4,1),p6(4,4);
	p2.displayPt();
	Point p7 = p3;
	Triangle T1(p1,p2,p7);
	T1.calArea();				//Calculate Area
	T1.calPerimeter();			//Calculate Perimeter
	T1.displayShapeData();		//Display vertices,sides,area,perimeter
	Triangle T2 = T1;
	T2.displayShapeData();
	Rectangle R1(p3, p5);
	R1.calArea();
	R1.calPerimeter();
	R1.displayShapeData();
	Rectangle R2;
	R2 = R1;
	R2.displayShapeData();
	Square S1(p6);
	Square S2(S1);
	S1.calArea();
	S1.calPerimeter();
	S1.displayShapeData();
	S2.calArea();
	S2.calPerimeter();
	S2.displayShapeData();
	getchar();
	getchar();
	return 0;
}
