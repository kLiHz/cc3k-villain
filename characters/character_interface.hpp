#ifndef CHARCTER_HPP
#define CHARCTER_HPP

#include "../basic/types.hpp"
#include "../items/item.hpp"

#include <vector>
#include <string>

struct Attack;

class CharacterInterface {
public:

    friend class CharacterStrategy;

    virtual CStatus     default_status() = 0;
    virtual CStatus     current_status() = 0;
    virtual bool        is_alive() = 0;
    virtual void        use_potion(Item *) = 0;
    virtual void        receive(const Attack & attack) = 0;
    //virtual void        attack(CharacterInterface * target) = 0;
    virtual char        get_denote() = 0;
    virtual Point       get_position() = 0;
    //virtual void        set_target(CharacterInterface * target) = 0;
    //virtual void        get_target() = 0;
    virtual bool        is_hostile() = 0;
    virtual void        move_to(const Point & dst) = 0;
    virtual Item*       drop_reward() = 0;
    virtual void        one_turn() = 0;
};

class Character;

struct Attack
{
    Character * attacker;
    int atk_points;
    Attack(Character * p, int _atk) 
    : attacker(p)
    , atk_points(_atk) {};
};

#endif
