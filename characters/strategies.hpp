#ifndef STRATEGIES
#define STRATEGIES

#include "./strategy_interface.hpp"

#include <iostream>

// Default strategy for character; Concrete class 
class DefaultStrategy : public CharacterStrategy
{
protected:
    Character * self;
    Character * target = nullptr;
    int current_health;
    int current_atk;
    int current_def;
public:
    DefaultStrategy(CStatus init_status, Character * ch = nullptr) 
    : self(ch) 
    , current_health(init_status.health)
    , current_atk(init_status.atk)
    , current_def(init_status.def) {}
    virtual ~DefaultStrategy() {}
    virtual Attack      attack(Character * target) {
        if (!target) return Attack(self, 0);
        int current_atk = current_status().atk;
        auto atk = Attack(self, current_atk);
        // All characters has a possibility to miss its target.
        int miss = rand() % 1;
        if (miss) atk.atk_points = 0;
        target->receive(atk); 
        return atk;
    };
    virtual void        receive(const Attack & attack) {
        int current_def = current_status().def;
        current_health -= attack.atk_points * ( 100 / (100 + current_def));
    };
    virtual void        consume(Item * item) {
        if (item->type == Item::POTION) this->apply(item->get_effect());
    }
    virtual void        apply(const Effect & effect) {
        Effect final_effect = effect;
        if (effect.hp_change != 0) {
            int default_hp = self->default_status().health;
            if (current_status().health + final_effect.hp_change > default_hp) 
                final_effect.hp_change = default_hp - current_health;
        }
        current_atk += final_effect.atk_buff;
        current_def += final_effect.def_buff;
    }
    virtual CharacterStrategy * previous() { return this; };
    virtual CStatus     current_status() {
        return CStatus(current_health, current_atk, current_def); 
    };
    virtual Point       get_move_offset() { 
        return Point(rand() % 1, rand() % 1); // random move; may chase its target (e.g. Player) in the future
    }; 
    virtual Character * get_target()              { return target; }
    virtual void        set_target(Character * p) { target = p; }
    virtual Character * get_self()                { return self; }
};

class NoHealthLimit : public DefaultStrategy {
public:
    NoHealthLimit(CStatus init_status, Character * ch = nullptr) 
    : DefaultStrategy( init_status, ch) {}
    virtual ~NoHealthLimit() {}
    virtual void        apply(const Effect & effect) {
        current_health += effect.hp_change;
        current_atk += effect.atk_buff;
        current_def += effect.def_buff;
    }
    virtual CharacterStrategy * previous() { return this; };
};

//class NerverMissBut : public DefaultStrategy {
//    Character::CharacterType disturbance;
//public:
//    NerverMissBut(Character::CharacterType _disturbance, CStatus init_status, Character * ch = nullptr)
//    : DefaultStrategy(init_status, ch), disturbance(_disturbance) {}
//    virtual Attack      attack(Character * target) {
//        if (!target) return Attack(self, 0);
//        int current_atk = current_status().atk;
//        auto atk = Attack(self, current_atk);
//        int miss = rand() % 1;
//        if (target->get_type() == disturbance && miss) atk.atk_points = 0;
//        target->receive(atk); 
//        return atk;
//    };
//};

class StrategyDecorator : public CharacterStrategy
{
protected:
    CStrategy * pre_strategy;
public:
    StrategyDecorator(CStrategy * s) : pre_strategy(s) {}
    ~StrategyDecorator() { delete pre_strategy; }

    virtual Attack          attack(Character * target)      = 0; //{ return pre_strategy->attack(target); }
    virtual void            receive(const Attack & attack)  = 0; //{ return pre_strategy->receive(attack); }
    virtual void            apply(const Effect & effect)    = 0; //{ return pre_strategy->receive(effect); }
    virtual void            consume(Item * item)            = 0;
    virtual CStatus         current_status()                = 0; //{ return pre_strategy->current_status(); }
    virtual Point           get_move_offset()               = 0; //{ return pre_strategy->current_status(); }
    //virtual 
    virtual CharacterStrategy *         previous() {
        CStrategy * t = pre_strategy; 
        pre_strategy = nullptr; 
        return t; 
    }
    Character *         get_target()              { return pre_strategy->get_target(); }
    void                set_target(Character * p) { pre_strategy->set_target(p); }
    Character *         get_self()                { return pre_strategy->get_self(); }
};

class RestoreHPbyAttak : public StrategyDecorator {
public:
    RestoreHPbyAttak(CStrategy * s) : StrategyDecorator(s) {}
    virtual Attack          attack(Character * target) { 
        this->apply(Effect(5,0,0));
        return pre_strategy->attack(target);    
    }
    virtual void            receive(const Attack & attack) { return pre_strategy->receive(attack); }
    virtual void            apply(const Effect & effect) { return pre_strategy->apply(effect); }
    virtual void            consume(Item * item) { pre_strategy->consume(item); }
    virtual CStatus         current_status() { return pre_strategy->current_status(); }
    virtual Point           get_move_offset() { return pre_strategy->get_move_offset(); }
};

// PotionEnhance: Decorator
class PotionEnhance : public StrategyDecorator {
private:
    double multiplier;
public:
    PotionEnhance(CStrategy * s, double _c) : StrategyDecorator(s), multiplier(_c) {}
    virtual void            apply(const Effect & effect) { pre_strategy->apply(effect); }
    virtual void            consume(Item * item) { 
        if (item->type == Item::POTION) {
            Effect potion_effect = item->get_effect();
            Effect enhanced(
                potion_effect.hp_change * multiplier,
                potion_effect.atk_buff * multiplier,
                potion_effect.def_buff * multiplier
            );
            this->apply(enhanced);
        }
    }
    virtual Attack          attack(Character * target) { return pre_strategy->attack(target); }
    virtual void            receive(const Attack & attack) { return pre_strategy->receive(attack); } 
    virtual CStatus         current_status() { return pre_strategy->current_status(); }
    virtual Point           get_move_offset() { return pre_strategy->get_move_offset(); }
};

class GoldbyAttack : public StrategyDecorator {
public: 
    GoldbyAttack(CStrategy * s) : StrategyDecorator(s) {}
    virtual Attack attack(Character * target) {
        pre_strategy->get_self()->gold_change(+5);
        return pre_strategy->attack(target);
    }
    virtual void            receive(const Attack & attack) { return pre_strategy->receive(attack); } 
    virtual void            apply(const Effect & effect) { return pre_strategy->apply(effect); }
    virtual void            consume(Item * item) { pre_strategy->consume(item); }
    virtual CStatus         current_status() { return pre_strategy->current_status(); }
    virtual Point           get_move_offset() { return pre_strategy->get_move_offset(); }
};

class StayStill : public StrategyDecorator {
public: 
    StayStill(CStrategy * s) : StrategyDecorator(s) {}
    virtual Attack          attack(Character * target) { return pre_strategy->attack(target); }
    virtual void            receive(const Attack & attack) { return pre_strategy->receive(attack); } 
    virtual void            apply(const Effect & effect) { return pre_strategy->apply(effect); }
    virtual void            consume(Item * item) { pre_strategy->consume(item); }
    virtual CStatus         current_status() { return pre_strategy->current_status(); }
    virtual Point get_move_offset() { return Point(0,0); }
};

class Allergic : public StrategyDecorator {
private:
    Character::CharacterType allergen;
public:
    Allergic(CStrategy * s, Character::CharacterType allergic_to)
    : StrategyDecorator(s), allergen(allergic_to) {}
    virtual void            receive(const Attack & atk) {
        if (atk.attacker->get_type() == allergen) this->apply( Effect(-5,0,0) );
        // Allergic, lost Health Points
        pre_strategy->receive(atk);
    }
    virtual void            apply(const Effect & effect) { pre_strategy->apply(effect); }
    virtual void            consume(Item * item) { pre_strategy->consume(item); }
    virtual Attack          attack(Character * target) {
        if (target->get_type() == allergen) this->apply( Effect(-5,0,0) );
        // Allergic, lost Health Points
        return pre_strategy->attack(target);
    }
    virtual CStatus         current_status() { return pre_strategy->current_status(); }
    virtual Point           get_move_offset() { return pre_strategy->get_move_offset(); }    
};

class PronetoHurt : public StrategyDecorator {
    Character::CharacterType object;
public:
    PronetoHurt(CStrategy * s, Character::CharacterType ch )
    : StrategyDecorator(s), object(ch) {}
    virtual Attack          attack(Character * target) { return pre_strategy->attack(target); }
    virtual void            receive(const Attack & atk) { 
        if (atk.attacker->get_type() == object) pre_strategy->receive(
            Attack( atk.attacker, atk.atk_points * 1.5 )
        ); 
        return pre_strategy->receive(atk);
    } 
    virtual void            apply(const Effect & effect) { pre_strategy->apply(effect); }
    virtual void            consume(Item * item) { pre_strategy->consume(item); }
    virtual CStatus         current_status() { return pre_strategy->current_status(); }
    virtual Point           get_move_offset() { return pre_strategy->get_move_offset(); }   
};

//class BuffDecorator : public StrategyDecorator {
//private:
//    int this_hp_change;
//    int this_atk_buff;
//    int this_def_buff;
//public:
//    BuffDecorator(CStrategy * s, const Effect & effect);
//    virtual Effect          receive(const Effect & effect) { return pre_strategy->receive(effect); }
//    virtual CStrategy *     apply_effect(const Effect & final_effect);
//    virtual CStatus         current_status();
//    //virtual 
//};



#endif
