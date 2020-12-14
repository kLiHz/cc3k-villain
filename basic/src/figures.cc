#include "../figures.hpp"

Point Point::operator+(const Point & p) 
{
    return Point(this->x + p.x, this->y + p.y);
}

Point Point::operator-(const Point & p) 
{
    return Point(this->x - p.x, this->y - p.y);
}

Point& Point::operator+=(const Point& p) 
{
    this->x += p.x;
    this->y += p.y;
    return *this;
}

Point& Point::operator-=(const Point& p) 
{
    this->x -= p.x;
    this->y -= p.y;
    return *this;
}

bool Point::operator<(const Point & p) const
{
    return this->x < p.x && this->y < p.y;
    //return (abs(this->x) + abs (this->y)) < (abs(p.x) + abs(p.y));
}

bool Point::operator==(const Point & p) const {
    return this->x == p.x && this->y == p.y;
}

Rect::Rect() {
    base = Point(0,0);
    width = 0;
    height = 0;
}

Rect::Rect(const Point & a, const Point & b) {
    base.x = std::min(a.x, b.x);
    base.y = std::min(a.y, b.y);
    //width  = std::abs(a.x - b.x);
    //height = std::abs(a.y - b.y);
    width = std::max(a.x, b.x) - base.x;
    height = std::max(a.y, b.y) - base.y;
}

Rect::Rect(const Point & _tl, int _height, int _width)
: base(_tl), height(_height), width(_width) {}

/*Rect Rect::operator = (const Rect & r) 
{
    base = r.base;
    width = r.width;
    height = r.height;
    return * this;
}*/

Point Rect::tl()
{
    return Point(base.x, base.y);
}
Point Rect::br()
{
    return Point(base.x + width + 1, base.y + height + 1);
}

bool Rect::contains(const Point & p) {
    return (!(p < base)) && (p < this->br());
    //return base.x <= p.x && p.x <= base.x + width 
    //    && base.y <= p.y && p.y <= base.y + height;
}

int Rect::area() { return width * height; }

bool Line::cross(const Point & p) {
    int dx1 = p.x - begin.x;
    int dy1 = p.y - begin.y;
    int dx2 = end.x - begin.x;
    int dy2 = end.y - begin.y;
    return dy1 * dx2 == dy2 * dx1;
}

