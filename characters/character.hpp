#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER

#include "characters/character_interface.hpp"

#include "items/item.hpp"
#include "items/potion.hpp"
#include "items/gold.hpp"

class CharacterStrategy;

class RealCharacter : public Character
{
public:
    friend class Display;

    static std::vector<std::string> character_strings;

    virtual ~RealCharacter();
    virtual CStatus     default_status();
    virtual CStatus     current_status();
    virtual bool        is_alive();
    virtual void        use_potion(Item * item);
    virtual void        receive(const Attack & attack);
    virtual void        attack(Character * target);  
    virtual char        get_denote(); 
    virtual Point       get_position();  
    virtual void        set_target(Character * target);
    virtual Character * get_target();
    virtual CharacterStrategy * get_strategy();
    virtual bool        is_hostile();
    virtual void        move_to(const Point & dst);
    virtual Item*       drop_reward();
    virtual void        one_turn();
    virtual void        debuff();
    virtual CharacterType get_type();
    virtual int         gold_amount();
    virtual void        gold_change(int amount);
protected:
    CStatus         org_status;
    CharacterType   type;
    int             my_gold;
    Attitude        attitude;
    Point           position;
    int             default_hp;     // default health points; HP, stands for Health Points or Hit Points
    int             default_atk;    // default atk points
    int             default_def;    // default def points
    CharacterStrategy * strategy; // reset to default when floor changed.
    //CharacterStrategy::StrategyType strategy_type = CharacterStrategy::DEFAULT;
    // Note: adding buff to a character can also be designed as a decorator

    RealCharacter(int _hp, int _atk, int _def, CharacterType _type)
    : default_hp(_hp), default_atk(_atk), default_def(_def), type(_type), strategy(nullptr) {
        my_gold = 0;
    }
};


#endif
