#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <queue>
#include "./races.hpp"

// Decorate Class: PlayerCharacter
class PlayerCharacter : public Character
{
    Character * character;
public:
    std::queue<std::string> messages;
    PlayerCharacter(Character * ch) : Character(*ch), character(ch) {}
    ~PlayerCharacter();
    //void receive(const Item &);
    int gold_amount();
    void use_item(Item * item);
    char get_denote() { return '@'; }
    void do_something();
    void attack(Character * target);
    void receive(Attack attack);
    
    CStatus     default_status() ;
    CStatus     current_status() ;
    //CharacterStrategy * get_strategy() ;
    bool        is_alive()  ;
    void        debuff();
    Point       get_position();
    bool        is_hostile() ;
    void        move_to(const Point & dst);
    void        use_potion(Item * item);
    Item*       drop_reward();
    CStrategy * get_strategy();
};

#endif
