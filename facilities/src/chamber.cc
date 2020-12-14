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
    if (inside.contains(pos) == false) return false; // Walls encountered
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
        if (ch->is_hostile() || (ch->type == Character::DRAGON && is_neighbor(player, ch)))
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
    bool blocked = false;
    if (!contains(dst)) blocked = true; 
    for (auto port : ports) {
        if (dst == port->position) {
            blocked = false;
            break;
        }
    }
    if (blocked) {
        // Todo: unable to move; blocked
        return;
    }
    auto i = characters.begin();
    for (auto ch : characters) {
        if (dst == ch->get_position()) {
            blocked = true;
            if (ch->is_hostile()) player->attack(ch);
            if (!ch->is_alive()) {
                delete ch;
                // ToDO: DROP GOLD;
                characters.erase(i); 
                // Attention: there is something to take care of when using 'std::list<T>::erase()'
            }
            else {} // Todo: unable to move
            break;
        }
        ++i;
    }
    auto j = items.begin();
    for (auto item : items) {
        if (dst == item->get_pos()) {
            if (item->type == Item::GOLD) {
                blocked = false;
                player->use_item(item);
                items.erase(j);
            }
            else {
                blocked = true;
                // or the character can pick up it;
                // implement in the future when inventory system finished
                // Todo: print potion info.
            }
            break;
        }
        ++j;
    }
    if (!blocked) player->move_to(dst);
}

void Chamber::player_attack(PlayerCharacter * player, const Point & dst)
{
    auto i = characters.begin();
    for (auto ch : characters) {
        if (dst == ch->get_position()) {
            player->attack(ch);
            if (!ch->is_alive()) {
                delete ch;
                player->messages.push(
                    Character::character_strings[ch->type] 
                    + " was killed by PC: " 
                    + Character::character_strings[player->type]
                    + ". \n"
                );
                if (player->type == Character::GOBLIN) player->gold_in_hand += 5;
                this->push(ch->drop_reward()); // Todo: DROP REWARD;
                auto g = new Gold(Gold::NORMAL);
                player->use_item( g );
                delete g;
                // The gold is immediately picked up by Player.
                characters.erase(i);
            }
            break; // attack finished, return.
        }
        ++i;
    }
}

void Chamber::player_use(PlayerCharacter * player, const Point & dst) {
    auto i = items.begin();
    for (auto item : items) {
        if (dst == item->get_pos()) {
            player->use_item(item); // player use potion;
            items.erase(i);
            break;
        }
        ++i;
    }
    // todo: there's nothing to use in the direction
    player->messages.push("There's nothing to use in this direction. \n");
    // there's nothing to use
}

Point Chamber::get_available_random_pos() {
    if ( ports.size() + characters.size() + items.size() > inside.area() ) return Point(-1,-1);
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
