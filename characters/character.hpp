#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER

#include "./character_interface.hpp"

#include "../items/item.hpp"
#include "../items/potion.hpp"
#include "../items/gold.hpp"

class CharacterStrategy;

class Character : public CharacterInterface
{
public:
    friend class Display;
    enum CharacterType { 
        PLAYER, SHADE, DROW, VAMPIRE, TROLL, GOBLIN, 
        MERCHANT, HUMAN, DRAGON, DWARF, ELF, ORCS, HALFLING
    };
    enum Attitude { 
        ALLY, NEUTRAL, HOSTILE
    }; 
    static std::vector<std::string> character_strings;

    virtual ~Character();
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
    CharacterStrategy * get_strategy();
    virtual bool        is_hostile();
    virtual void        move_to(const Point & dst);
    virtual Item*       drop_reward();
    virtual void        one_turn();
    virtual void        debuff();

    CharacterType   type;
    CStatus         org_status;
    int             gold_in_hand;
protected:
    Attitude        attitude;
    Point           position;
    int             default_hp;     // default health points; HP, stands for Health Points or Hit Points
    int             default_atk;    // default atk points
    int             default_def;    // default def points
    CharacterStrategy * strategy; // reset to default when floor changed.
    //CharacterStrategy::StrategyType strategy_type = CharacterStrategy::DEFAULT;
    // Note: adding buff to a character can also be designed as a decorator

    Character(int _hp, int _atk, int _def, CharacterType _type)
    : default_hp(_hp), default_atk(_atk), default_def(_def), type(_type), strategy(nullptr) {
        gold_in_hand = 0;
    }
};


#endif
