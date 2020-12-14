#include "../character.hpp"
#include "../strategies.hpp"

std::vector<std::string>
Character::character_strings = {
    "Player", "Shade", "Drow", "Vampire", "Troll", "Goblin", 
    "Merchant", "Human", "Dragon", "Dwarf", "Elf", "Orc", "Halfling"
};

Character::~Character()  { delete strategy; }

void 
Character::receive(const Attack & attack) {
    strategy->receive(attack);
    // add outputs here or in the attack or maybe in the strategy
}

void 
Character::attack(Character * target) {
    strategy->attack(target);
}

void 
Character::debuff() {
    CStatus _status = this->default_status();
    _status.health = this->current_status().health;
    delete strategy;
    strategy = new DefaultStrategy(_status, this);
}


CStatus     Character::default_status() { return CStatus(default_hp, default_atk, default_def); }
CStatus     Character::current_status() { return strategy->current_status(); }
CharacterStrategy * Character::get_strategy() { return strategy; }
bool        Character::is_alive()   { return strategy->current_status().health > 0; }
char        Character::get_denote() { return '$'; } 
Point       Character::get_position() { return position; }
bool        Character::is_hostile() { return attitude == HOSTILE; } 
void        Character::move_to(const Point & dst) { position = dst; }
void        Character::use_potion(Item * item) { strategy->consume(item); } 
void        Character::one_turn() {
    Character * aim = strategy->get_target();
    if (aim != nullptr) strategy->attack(aim);
};
Character *  Character::get_target() { return strategy->get_target(); }
void         Character::set_target(Character * ch) { strategy->set_target(ch); }
Item *       Character::drop_reward() { return nullptr; }
//void Character::assign_strategy(CStrategy * _new_strategy) 
