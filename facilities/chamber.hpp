#pragma once

#include <list>
#include "../basic/types.hpp"
#include "../characters/races.hpp"
#include "../characters/player_character.hpp"
#include "../items/item.hpp"
#include "../items/gold.hpp"
#include "../items/potion.hpp"
#include "./port.hpp"
#include "./path.hpp"

class Chamber 
{
    Rect                    region;
    Rect                    inside;
    std::list<Character*>   characters; // chracters are managed by 'Chamber', while PC is managed by 'Game'
    std::list<Item*>        items; // items are managed by chamber
    std::list<Port*>        ports; // ports are managed by chamber
    void player_try_attack(PlayerCharacter * player, const Point & dst, bool intended = false);
    void player_try_use(PlayerCharacter * player, const Point & dst, bool intended = false);
public:
    friend class Display;
    Chamber(Rect _region, const std::list<Port*> & _ports);
    ~Chamber();
    const std::list<Port*> &    get_ports() { return ports; };
    const Rect &                get_region() { return region; };
    void print();
    bool contains(const Point & pos) {
        return inside.contains(pos);
    }
    bool is_neighbor(Character * a, Character * b);
    bool is_available(const Point & pos);
    Port * at_port(const Point & pos);
    void do_something(PlayerCharacter * player);
    void player_go(PlayerCharacter * player, const Point & dst);
    void player_attack(PlayerCharacter * player, const Point & dst);
    void player_use(PlayerCharacter * player, const Point & dst);
    Point get_available_random_pos();
    bool push(Character * ch);
    bool push(Item * item, Point assign_pos = Point(-1,-1));
};