#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include "basic/types.hpp"

class Item {
public:
    enum ItemType {POTION = 0, GOLD};
    Item(ItemType _type) : type(_type) {}
    virtual void    set_pos(const Point & p) { pos = p; } 
    virtual Point   get_pos() { return pos; };
    virtual Effect  get_effect() { return Effect(0,0,0); }
    virtual int     get_value() { return 0; }

    ItemType type;
    int category_type;
private:
    Point pos;
};

#endif
