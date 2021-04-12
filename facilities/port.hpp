#ifndef PORT_HPP
#define PORT_HPP

#include "basic/types.hpp"

class Path;
class Chamber;

class Port {
public:
    Chamber * the_chamber = nullptr;
    Path * the_path = nullptr;
    Point position;
    Port() = default;
    ~Port() = default;
    Port(int _row, int _col) : position(_row, _col) {}
    Port(const Point & pos) : position(pos) {}
};

#endif PORT_HPP
