#include "../player_character.hpp"

void PlayerCharacter::use_item(Item * item) { 
    if (item->type == Item::POTION) {
        character->use_potion(item);
        messages.push(
            "The Player consumed " 
            + Potion::potion_strings[item->category_type]
            + "potion. \n"
        );
        // Todo: Output potion info.
    } 
    if (item->type == Item::GOLD) {
        character->gold_in_hand += item->get_value();
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
    bool miss = false;
    if (target->type == Character::HALFLING && rand() % 1) miss = true;
    if (!miss) character->attack(target);
    auto afterstatus = target->current_status();
    // Character has 100% hit accuracy. 
    messages.push(
        std::string("Player (")
        + std::to_string(this->current_status().health) + " HP)"
        + " hit the " + Character::character_strings[target->type] + ". "
    );
    messages.push(
        Character::character_strings[target->type]
        + " lost " + std::to_string(prestatus.health - afterstatus.health) + " HP. \n"
    );
}

void PlayerCharacter::receive(Attack attack) {
    auto prestatus = character->current_status();
    messages.push(
        "The" + Character::character_strings[attack.attacker->type] 
        + '(' + std::to_string(attack.attacker->current_status().health) + " HP)"
        + " hit the Player. " 
    );
    //character->receive(attack);
    if (attack.atk_points < 0)
    {
        messages.push(
            "The" + Character::character_strings[attack.attacker->type] 
            + '(' + std::to_string(attack.attacker->current_status().health) + " HP)"
            + " hit the Player. " 
        );
        character->receive(attack);
        auto afterstatus = character->current_status();
        messages.push( "Player lost " + std::to_string(prestatus.health - afterstatus.health) + "HP. " );
    }
    else {
        messages.push(
            "The" + Character::character_strings[attack.attacker->type] 
            + '(' + std::to_string(attack.attacker->current_status().health) + " HP)"
            + " missed the Player. " 
        );
    }
}

PlayerCharacter::~PlayerCharacter() { delete character; }

int PlayerCharacter::gold_amount() { return gold_in_hand; }

void PlayerCharacter::do_something(){
    if (type == Character::TROLL) strategy->apply(Effect(5,0,0));
}

CStatus     PlayerCharacter::default_status() { return character->default_status(); }
CStatus     PlayerCharacter::current_status() { return character->current_status(); }
CStrategy * PlayerCharacter::get_strategy() { return character->get_strategy(); }
bool        PlayerCharacter::is_alive()   { return character->is_alive(); }
void        PlayerCharacter::debuff() { character->debuff();}
Point       PlayerCharacter::get_position() { return character-> get_position(); }
bool        PlayerCharacter::is_hostile() { return character->is_hostile();}
void        PlayerCharacter::move_to(const Point & dst) { character->move_to(dst);}
void        PlayerCharacter::use_potion(Item * item){ character->use_potion(item);}
Item *      PlayerCharacter::drop_reward() { return character->drop_reward();}