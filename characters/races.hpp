#ifndef RACES_HPP
#define RACES_HPP

#include "characters/character.hpp"
#include "characters/strategies.hpp"

class Shade : public RealCharacter
{
public:
    Shade() : RealCharacter(125,25,25, SHADE) {
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'S'; }
};

class Drow : public RealCharacter
{
public:
    Drow() : RealCharacter(150, 25, 15, DROW) {
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

class Vampire : public RealCharacter
{
public:
    Vampire() : RealCharacter(50, 25, 25, VAMPIRE) {
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

class Troll : public RealCharacter
{
public:
    Troll() : RealCharacter(120, 25, 15, TROLL) {
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'T'; }
};

class Goblin : public RealCharacter
{
public:
    Goblin() : RealCharacter(110, 15, 20, GOBLIN) {
        strategy = new DefaultStrategy(this->default_status(), this);
        strategy = new PronetoHurt(strategy, RealCharacter::ORCS);
    }
    char get_denote() { return 'L'; }
    void debuff() {
        CStatus _status = this->default_status();
        _status.health = this->current_status().health;
        delete strategy;
        strategy = new DefaultStrategy(_status, this);
        strategy = new PronetoHurt(strategy, RealCharacter::ORCS);
    }
};

class Dwarf : public RealCharacter
{
public:
    Dwarf() : RealCharacter(100, 20, 30, DWARF) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'W'; }
};

class Elf : public RealCharacter
{
public:
    Elf() : RealCharacter(140, 30, 10, ELF) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    void attack(Character * p) {
        if (p->get_type() != DROW) strategy->attack(p);
        strategy->attack(p);
    } 
    char get_denote() { return 'E'; }
};

class Orc : public RealCharacter
{
public:
    Orc() : RealCharacter(180, 30, 25, ORCS) {
        attitude = HOSTILE; 
        strategy = new DefaultStrategy(this->default_status(), this);
        
    }
    char get_denote() { return 'O'; }
};

class Halfling : public RealCharacter
{
public:
    Halfling() : RealCharacter(100, 15, 20, HALFLING) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    char get_denote() { return 'L'; }
};

class Human : public RealCharacter 
{
public:
    Human() : RealCharacter(140, 20, 20, HUMAN) {
        attitude = HOSTILE;
        strategy = new DefaultStrategy(this->default_status(), this);
    }
    ~Human() {
        // Generate Gold (2 * Normal Pile)
    }
    char get_denote() { return 'H'; }
    Item * drop_reward();
};

class Merchant : public RealCharacter
{
public:
    Merchant() : RealCharacter(30, 70, 5, MERCHANT) {
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

class Dragon : public RealCharacter
{
private:
public:
    Point hoard_position;
    Dragon( Point _hoard ) : RealCharacter(150, 20, 20, DRAGON), hoard_position(_hoard) {
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

