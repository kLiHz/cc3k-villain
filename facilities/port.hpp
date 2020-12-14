#pragma once

#include "../basic/types.hpp"

class Path;
class Chamber;

class Port {
public:
    Chamber * the_chamber;
    Path * the_path;
    Point position;
    Port() {}
    ~Port() {}
    Port(int _row, int _col) : position(_row, _col) {}
    Port(const Point & pos) : position(pos) {}
};
