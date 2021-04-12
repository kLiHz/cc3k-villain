#include "basic/figures.hpp"

Point Point::operator+(const Point & p) const 
{
    return Point(this->x + p.x, this->y + p.y);
}

Point Point::operator-(const Point & p) const 
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

//bool Point::operator<(const Point & p) const
//{
//    auto a = this->x * this->y;
//    auto b = p.x * p.y;
//    if (a < b) return true; // e.g. Point(2,6) < Point (6,3)
//    if (b > a) return false;
//    if (*this == p) return false; // e.g. Point(1, 1) == Point(1, 1)
//    return (1000 * x + y) < (1000 * p.x + p.y); // e.g. Point(1,5) < Point(5,1)
//}

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

Point Rect::tl() const
{
    return Point(base.x, base.y);
}
Point Rect::br() const
{
    return Point(base.x + width + 1, base.y + height + 1);
}

bool Rect::contains(const Point & p) const {
    //return (!(p < base)) && (p < this->br());
    return base.x <= p.x && p.x < base.x + width 
        && base.y <= p.y && p.y < base.y + height;
}

int Rect::area() const { return width * height; }

bool Line::cross(const Point & p) const {
    int dx1 = p.x - begin.x;
    int dy1 = p.y - begin.y;
    int dx2 = end.x - begin.x;
    int dy2 = end.y - begin.y;
    return dy1 * dx2 == dy2 * dx1;
}

// horizontal/vertical line supported only!
bool Line::contains(const Point & p) const {
    return this->cross(p) &&
        this->bounding_rect().contains(p);
}

Rect Line::bounding_rect() const {
    if (begin.x * begin.y < end.x * end.y) {
        return Rect(begin, end + Point(1,1));
    }
    else return Rect(end, begin + Point(1,1));
}