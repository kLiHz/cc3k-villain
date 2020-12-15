#include "../character.hpp"
#include "../strategies.hpp"

std::vector<std::string>
RealCharacter::character_strings = {
    "Player", "Shade", "Drow", "Vampire", "Troll", "Goblin", 
    "Merchant", "Human", "Dragon", "Dwarf", "Elf", "Orc", "Halfling"
};

RealCharacter::~RealCharacter()  { delete strategy; }

void 
RealCharacter::receive(const Attack & attack) {
    strategy->receive(attack);
    // add outputs here or in the attack or maybe in the strategy
}

Character::CharacterType
RealCharacter::get_type() { return type; }

int
RealCharacter::gold_amount() { return my_gold; }

void
RealCharacter::gold_change( int amount ) {
    my_gold += amount;
    //if (my_gold < 0) my_gold = 0;
}

void 
RealCharacter::attack(Character * target) {
    // All characters has a possibility to miss its target.
    int miss = rand() % 2;
    if (!miss) strategy->attack(target);
    else target->receive(Attack(this, 0));
}

void 
RealCharacter::debuff() {
    CStatus _status = this->default_status();
    _status.health = this->current_status().health;
    delete strategy;
    strategy = new DefaultStrategy(_status, this);
}


CStatus     RealCharacter::default_status() { return CStatus(default_hp, default_atk, default_def); }
CStatus     RealCharacter::current_status() { return strategy->current_status(); }
CharacterStrategy * RealCharacter::get_strategy() { return strategy; }
bool        RealCharacter::is_alive()   { return strategy->current_status().health > 0; }
char        RealCharacter::get_denote() { return '$'; } 
Point       RealCharacter::get_position() { return position; }
bool        RealCharacter::is_hostile() { return attitude == HOSTILE; } 
void        RealCharacter::move_to(const Point & dst) { position = dst; }
void        RealCharacter::use_potion(Item * item) { strategy->consume(item); } 
void        RealCharacter::one_turn() {
    Character * aim = strategy->get_target();
    if (aim != nullptr) strategy->attack(aim);
};
Character *  RealCharacter::get_target() { return strategy->get_target(); }
void         RealCharacter::set_target(Character * ch) { strategy->set_target(ch); }
Item *       RealCharacter::drop_reward() { return nullptr; }
//void RealCharacter::assign_strategy(CStrategy * _new_strategy) 
