#ifndef _GOLD_HPP_
#define _GOLD_HPP_

#include "./item.hpp"
#include <vector>
#include <string>

class Gold : public Item 
{
public:
    enum GoldType {SMALL = 0, NORMAL, MERCHANT_HOARD, DRAGON_HOARD};
    static std::vector<std::string> gold_strings;
    Gold(GoldType _type) : Item(Item::GOLD), gold_type(_type) { category_type = _type; }
    virtual int     get_value(){
        //int gold_amount;
        switch(gold_type) {
            case SMALL:             return 1;
            case NORMAL:            return 2;
            case MERCHANT_HOARD:    return 4;
            case DRAGON_HOARD:      return 6;
            default:                return 0;
        }
        return 0;
    }
    GoldType gold_type;
};

#endif
