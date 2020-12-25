#include "../chamber.hpp"

Chamber::Chamber(Rect _region, const std::list<Port*> & _ports)
{
    region = _region;
    inside = Rect(
        _region.base + Point(1,1),
        region.height - 2,
        region.width - 2
    );
    ports = _ports;
    for (auto p : ports) p->the_chamber = this; // link port and chamber
}

Chamber::~Chamber() 
{
    for (auto p : ports) delete p; 
    for (auto ch : characters) delete ch;
    for (auto i : items) delete i;
}

bool Chamber::is_neighbor(Character * a, Character * b) {
    Point distance = a->get_position() - b->get_position();
    return abs(distance.x) <= 1 && abs(distance.y) <= 1;
}

bool Chamber::is_available(const Point & pos) {
    if (!(inside.contains(pos))) return false; // Walls encountered
    for (auto ch : characters) if (ch->get_position() == pos) return false;
    for (auto it : items) if (it->get_pos() == pos) return false;
    return true;
}

Port * Chamber::at_port(const Point & pos) {
    for (auto i : ports) {
        if (pos == i->position) return i;
    }
    return nullptr;
}

void Chamber::do_something(PlayerCharacter * player)
{
    for (auto ch : characters) {
        if (ch->is_hostile() && is_neighbor(player, ch) || (ch->get_type() == Character::DRAGON && is_neighbor(player, ch)))
            ch->set_target((Character*)player);
        else ch->set_target(nullptr);
        ch->one_turn(); // self restoring, etc.
        Point new_pos, ch_pos = ch->get_position();
        new_pos = ch_pos + ch->get_strategy()->get_move_offset();
        if (new_pos == ch_pos || this->is_available(new_pos)) ch->move_to(new_pos);
    }
}

void Chamber::player_go(PlayerCharacter * player, const Point & dst)
{
    bool blocked = !(contains(dst) || at_port(dst) != nullptr); // walls encountered
    if (blocked) {
        // Todo: unable to move; blocked
        return;
    }
    player_try_attack(player, dst, false);
    //blocked = !is_available(dst);
    //if (blocked) return; // round ended;
    player_try_use(player, dst, false);
    if (is_available(dst) || at_port(dst) != nullptr) {
        blocked = false;
        player->move_to(dst);
    }
}

void Chamber::player_attack(PlayerCharacter * player, const Point & dst) {
    player_try_attack(player, dst, true); // intended
}

void Chamber::player_use(PlayerCharacter * player, const Point & dst) {
    player_try_use(player, dst, true); // intended
}

void Chamber::player_try_attack(PlayerCharacter * player, const Point & dst, bool intended)
{
    auto i = characters.begin();
    for (auto ch : characters) {
        if (dst == ch->get_position()) {
            if (ch->is_hostile() || intended) player->attack(ch);
            if (!ch->is_alive()) {
                player->messages.push(
                    RealCharacter::character_strings[ch->get_type()] 
                    + " was killed by PC: " 
                    + RealCharacter::character_strings[player->get_type()]
                    + ". \n"
                );
                if (player->get_type() == Character::GOBLIN) player->gold_change(+5);
                this->push(ch->drop_reward()); // Todo: DROP REWARD;
                auto g = new Gold(Gold::NORMAL);
                player->use_item( g );
                delete g;
                // The gold is immediately picked up by Player.
                delete ch;
                characters.erase(i);
                // Attention: there is something to take care of when using 'std::list<T>::erase()'
            }
            else {} // Todo: unable to move
            break; // attack finished, return.
        }
        ++i;
    }
    // attack nothing
}

void Chamber::player_try_use(PlayerCharacter * player, const Point & dst, bool intended) {
    bool got_item = false;
    auto i = items.begin();
    for (auto item : items) {
        if (dst == item->get_pos()) {
            got_item = true;
            if (item->type == Item::GOLD) {
                // walks across gold, automatically pick it up
                player->use_item(item);
                delete item;
                items.erase(i);
            }
            else if (intended) {
                player->use_item(item); // player use potion;
                delete item;
                items.erase(i);
                // or the character can pick up it;
                // implement in the future when inventory system finished
                // Todo: print potion info.
            }
            break;
        }
        ++i;
    }
    // todo: there's nothing to use in the direction
    if (intended && !got_item) player->messages.push("There's nothing to use in this direction. \n");
    // there's nothing to use
}

Point Chamber::get_available_random_pos() {
    if ( characters.size() + items.size() > inside.area() ) return Point(-1,-1);
    // todo: throw exception
    while (true) {
        int x_bias = rand() % inside.width;
        int y_bias = rand() % inside.height;
        Point dst = inside.base + Point(x_bias, y_bias);
        if (this->is_available(dst)) return dst;
    }
    return Point(-1,-1);
}

bool Chamber::push(Character * ch)
{
    auto dst = this->get_available_random_pos();
    if (dst == Point(-1,-1)) return false; // todo: throw exception: the room is full
    ch->move_to(dst);
    characters.push_back(ch);
    return true;
}

bool Chamber::push(Item * item, Point assign_pos) {
    if (item == nullptr) return false;
    Point dst;
    if (assign_pos == Point(-1,-1)) // default argument
        dst = this->get_available_random_pos();
    else dst = assign_pos;
    if (dst == Point(-1,-1)) return false; // todo: throw exception
    item->set_pos(dst);
    items.push_back(item);
    return true;
}
