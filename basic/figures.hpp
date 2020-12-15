#ifndef _FIGURES_HPP_
#define _FIGURES_HPP_

#include <cmath>
#include <algorithm>

struct Point {
public:
    int x; // x indicates which column (horizontal position)
    int y; // y indicates which row (vertical position)
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    Point operator+(const Point & p);
    Point operator-(const Point & p);
    Point& operator+=(const Point & p);
    Point& operator-=(const Point & p);
    //bool operator<(const Point & p) const;
    bool operator==(const Point & p) const;
};

class Rect {
public:
    Point base; // top left point (or the nearest point to (0,0)) of the rect
    int width;  // width is horizontal
    int height; // height is vertical
    Rect();
    Rect(const Point& a, const Point& b);
    Rect(const Point& _tl, int _height, int _width);
    //Rect operator = (const Rect &);
    Point tl();
    Point br();
    bool contains(const Point & p);
    int area();
};

class Line {
public:
    Point begin;
    Point end;
    Line();
    Line(const Point& a, const Point& b) : begin(a), end(b) {}
    bool cross(const Point& p);
};

#endif
