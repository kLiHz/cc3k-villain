#ifndef RACES_HPP
#define RACES_HPP

#include "./character.hpp"
#include "./strategies.hpp"

class Shade : public Character
{
public:
    Shade() : Character(125,25,25, SHADE) {
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'S'; }
};

class Drow : public Character
{
public:
    Drow() : Character(150, 25, 15, DROW) {
        auto s = new DefaultStrategy(this->default_status(), this);
        strategy = new PotionEnhance(s, 1.5);
    }
    char get_denote() { return 'R'; }
    void debuff() {
        CStatus _status = this->default_status();
        _status.health = this->current_status().health;
        delete strategy;
        strategy = new DefaultStrategy(_status, this);
        strategy = new PotionEnhance(strategy, 1.5);
    }
};

class Vampire : public Character
{
public:
    Vampire() : Character(50, 25, 25, VAMPIRE) {
        CharacterStrategy * s = new NoHealthLimit(this->default_status(), this);
        s = new Allergic(s, DROW);
        strategy = new RestoreHPbyAttak(s);
    }
    char get_denote() { return 'V'; }
    void debuff() {
        CStatus _status = this->default_status();
        _status.health = this->current_status().health;
        delete strategy;
        strategy = new NoHealthLimit(_status, this);
        strategy = new Allergic(strategy, DROW);
        strategy = new RestoreHPbyAttak(strategy);
    }
};

class Troll : public Character
{
public:
    Troll() : Character(120, 25, 15, TROLL) {
        auto s = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'T'; }
};

class Goblin : public Character
{
public:
    Goblin() : Character(110, 15, 20, GOBLIN) {
        strategy = new DefaultStrategy(this->default_status(), this);
        strategy = new PronetoHurt(strategy, Character::ORCS);
    }
    char get_denote() { return 'L'; }
    void debuff() {
        CStatus _status = this->default_status();
        _status.health = this->current_status().health;
        delete strategy;
        strategy = new DefaultStrategy(_status, this);
        strategy = new PronetoHurt(strategy, Character::ORCS);
    }
};

class Dwarf : public Character
{
public:
    Dwarf() : Character(100, 20, 30, DWARF) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'W'; }
};

class Elf : public Character
{
public:
    Elf() : Character(140, 30, 10, ELF) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    void attack(Character * p) {
        if (p->type != DROW) strategy->attack(p);
        strategy->attack(p);
    } 
    char get_denote() { return 'E'; }
};

class Orc : public Character
{
public:
    Orc() : Character(180, 30, 25, ORCS) {
        attitude = HOSTILE; 
        strategy = new DefaultStrategy(this->default_status(), this);
        
    }
    char get_denote() { return 'O'; }
};

class Halfling : public Character
{
public:
    Halfling() : Character(100, 15, 20, HALFLING) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'L'; }
};

class Human : public Character 
{
public:
    Human() : Character(140, 20, 20, HUMAN) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    ~Human() {
        // Generate Gold (2 * Normal Pile)
    }
    char get_denote() { return 'H'; }
    Item * drop_reward();
};

class Merchant : public Character
{
public:
    Merchant() : Character(30, 70, 5, MERCHANT) {
        attitude = NEUTRAL;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    ~Merchant() {
        // Generate Gold (Merchant Hoard)
    }
    char get_denote() { return 'M'; }
    Item * drop_reward();
    void receive(const Attack & attack) {
        attitude = HOSTILE;
        strategy->receive(attack);
    } 
};

class Dragon : public Character
{
private:
public:
    Point hoard_position;
    Dragon( Point _hoard ) : Character(150, 20, 20, DRAGON), hoard_position(_hoard) {
        strategy = new DefaultStrategy(this->default_status(), this);
        strategy = new StayStill(strategy);
    }
    ~Dragon() {
        // Generate Gold (Dragon Hoard)
    }
    char get_denote() {
        //display->get_canvas()->draw(position, 'D');
        //display->get_canvas()->draw(hoard_position, 'G');
        return 'D';
    }
    Item * drop_reward();
};

#endif

