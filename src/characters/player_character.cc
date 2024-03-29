#include "player_character.hpp"

PlayerCharacter::~PlayerCharacter() { delete its_character; }

void PlayerCharacter::use_item(Item * item) { 
    if (item->type == Item::POTION) {
        its_character->use_potion(item);
        messages.push(
            "The Player consumed " 
            + Potion::potion_strings[item->category_type]
            + " Potion. \n"
        );
        // Todo: Output potion info.
    } 
    if (item->type == Item::GOLD) {
        its_character->gold_change(item->get_value());
        messages.push(
            "The Player picked up a(n) "
            + Gold::gold_strings[item->category_type]
            + ".\n"
        );
    }
    // TODO: this item cannot be used.
}

void PlayerCharacter::attack(Character * target) {
    auto prestatus = target->current_status();
    messages.push(
        std::string("Player hit the ")
        + RealCharacter::character_strings[target->get_type()] 
        + " (" + std::to_string(target->current_status().health) + " HP). "
    );
    bool miss = false; // Character has 100% hit accuracy,
    std::uniform_int_distribution<> distrib(0, 1);
    if (target->get_type() == Character::HALFLING && distrib(*(Character::rand_gen)) == 0) miss = true; // but only a half when attacking halflings
    if (!miss) {
        its_character->get_strategy()->attack(target);
        auto afterstatus = target->current_status();
        messages.push(
            RealCharacter::character_strings[target->get_type()]
            + " lost " + std::to_string(prestatus.health - afterstatus.health) + " HP. \n"
        );
    }
    else {
        messages.push(
            std::string("Player missed the ")
            + RealCharacter::character_strings[target->get_type()] + ". \n"
        );
    }
}

void PlayerCharacter::receive(const Attack & attack) {
    auto prestatus = its_character->current_status();
    if (!(its_character->is_alive())) return; // no longer able to receive attak
    if (attack.atk_points > 0)
    {
        messages.push(
            "The " + RealCharacter::character_strings[attack.attacker->get_type()] 
            + '(' + std::to_string(attack.attacker->current_status().health) + " HP)"
            + " hit the Player. " 
        );
        its_character->receive(attack);
        auto afterstatus = its_character->current_status();
        messages.push( "Player lost " + std::to_string(prestatus.health - afterstatus.health) + " HP. \n" );
        if (!(its_character->is_alive())) messages.push(
            "Player was killed by " 
            + RealCharacter::character_strings[attack.attacker->get_type()]
            + ". \n"
        ); // dying message
    }
    else {
        messages.push(
            "The " + RealCharacter::character_strings[attack.attacker->get_type()] 
            + '(' + std::to_string(attack.attacker->current_status().health) + " HP)"
            + " missed the Player. \n" 
        );
    }
}

int PlayerCharacter::gold_amount() { return its_character->gold_amount(); }
void PlayerCharacter::gold_change(int amount) { its_character->gold_change(amount); }
void PlayerCharacter::set_target(Character * target) { return its_character->set_target(target); }
Character * PlayerCharacter::get_target() { return its_character->get_target(); }
Character::CharacterType PlayerCharacter::get_type() { return its_character->get_type(); }

void PlayerCharacter::one_turn() {
    static int turns = 0;
    ++turns;
    if (its_character->get_type() == Character::TROLL) 
        its_character->get_strategy()->apply(Effect(5,0,0));
    if (turns % 5 == 0) {
        its_character->get_strategy()->apply(Effect(3,0,0));
        turns = 0;
    }
}

//void        PlayerCharacter::debuff() { its_character->debuff();}
CStatus     PlayerCharacter::default_status() { return its_character->default_status(); }
CStatus     PlayerCharacter::current_status() { return its_character->current_status(); }
CStrategy * PlayerCharacter::get_strategy() { return its_character->get_strategy(); }
bool        PlayerCharacter::is_alive()   { return its_character->is_alive(); }
Point       PlayerCharacter::get_position() { return its_character-> get_position(); }
bool        PlayerCharacter::is_hostile() { return its_character->is_hostile();}
void        PlayerCharacter::move_to(const Point & dst) { its_character->move_to(dst);}
void        PlayerCharacter::use_potion(Item * item){ its_character->use_potion(item);}
Item *      PlayerCharacter::drop_reward() { return its_character->drop_reward();}
void        PlayerCharacter::debuff() { return its_character->debuff(); }
