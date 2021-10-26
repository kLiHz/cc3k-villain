#include "path.hpp"

Path::Path() {}

bool Path::contains(const Point & pos) {
    for (auto passage : passages) if (passage.contains(pos)) return true;
    //for (auto p : ports) if (p->position == pos) return true;
    return false;
}

Port * Path::at_port(const Point & pos) {
    for (auto i : ports) {
        if (pos == i->position) return i;
    }
    return nullptr;
}
