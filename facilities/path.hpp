#pragma once

#include "./port.hpp"

#include <list>

class Path {
public:
    friend class Display;
    std::list<Line> passages;
    std::list<Port*> ports; // 'ports' stores ptr to ports, which are stored by class 'Chamber'
    Path();
    void add_line(const Line & passage) { passages.push_back(passage); } ;
    void add_port(Port * port) { port->the_path = this; ports.push_back(port); };
    bool contains(const Point & pos) {
        for (auto passage : passages) if (passage.cross(pos)) return true;
        //for (auto p : ports) if (p->position == pos) return true;
        return false;
    }
    Port * at_port(const Point & pos) {
        for (auto i : ports) {
            if (pos.x == i->position.x && pos.y == i->position.y) return i;
        }
        return nullptr;
    }
};