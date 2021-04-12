#ifndef STRATEGY_INTERFACE_HPP
#define STRATEGY_INTERFACE_HPP

#include "characters/character.hpp"

// All attack and effect from other character should be handled by the character's strategy
class CharacterStrategy
{
protected:
    // 'apply_effect()' applies a FINAL "Effect" to the character
public:
    enum StrategyType {DEFAULT, BUFFED};
    CharacterStrategy() = default;
    virtual ~CharacterStrategy() = default;
    // when the character receive an attack, the current "Strategy" should handle it
    // and returns a FINAL "Effect" which should be exerted directly on the character
    virtual void                receive(const Attack & attack) = 0;
    // when the character use a potion, the current "Strategy" should handle and modify it
    // and returns a FINAL "Effect" which should be applied directly by the character
    virtual void                consume(Item * item) = 0;
    virtual void                apply(const Effect & effect) = 0;
    // return the "Attack" of current strategy
    virtual Attack              attack(Character * ch) = 0; 
    // get player move offset; random roaming for default
    virtual Point               get_move_offset() = 0;
    //virtual Effect get_buff() = 0;
    // 'previous()' return the strategy before last modified.
    virtual CharacterStrategy * previous() = 0;
    virtual CStatus             current_status() = 0;
    virtual Character *         get_target() = 0;
    virtual void                set_target(Character * p) = 0;
    virtual Character *         get_self() = 0;
};
typedef CharacterStrategy CStrategy;

#endif
