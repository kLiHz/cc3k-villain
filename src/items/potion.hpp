#ifndef _POTION_HPP_
#define _POTION_HPP_

#include "item.hpp"
#include <vector>
#include <string>

class Potion : public Item {
public:
    enum PotionType {RH = 0, BA, BD, PH, WA, WD};
    PotionType potion_type;
    static std::vector<std::string> potion_strings;
    Potion(PotionType p_type) : potion_type(p_type), Item(POTION) { category_type = p_type; }
    virtual Effect get_effect() {
        Effect t_effect;
        switch (potion_type) {
            case RH: t_effect.hp_change = 10;   break;
            case BA: t_effect.atk_buff = 5;     break;
            case BD: t_effect.def_buff = 5;     break;
            case PH: t_effect.hp_change = -10;  break;
            case WA: t_effect.atk_buff = -5;    break;
            case WD: t_effect.def_buff = -5;    break;
        }
        return t_effect;
    }
};


/*
class RestoreHealth : public Potion {

};

class BoostAtk : public Potion {

};

class BoostDef : public Potion {

};

class PoisonHealth : public Potion {

};

class WoundAtk : public Potion {

};

class WoundDef : public Potion {

};*/

#endif 
