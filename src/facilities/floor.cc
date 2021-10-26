#include "floor.hpp"

std::shared_ptr<std::mt19937> Floor::rand_gen;

void Floor::GenerateSampleFloorTerrain() {
    // std::map use to avoid redefinition
    std::map<std::string, Port *> existing_ports;
    existing_ports["(6,5)"  ] = new Port(6,5);
    existing_ports["(10,5)" ] = new Port(10,5);
    existing_ports["(25,10)"] = new Port(25,10);
    existing_ports["(12,18)"] = new Port(12,18);
    existing_ports["(30,10)"] = new Port(30,10);
    existing_ports["(32,13)"] = new Port(32,13);
    existing_ports["(51,12)"] = new Port(51,12);
    existing_ports["(67,9)" ] = new Port(67,9);
    existing_ports["(14,21)"] = new Port(14,21);
    existing_ports["(32,20)"] = new Port(32,20);
    chambers.push_back(
        new Chamber(
            Rect(Point(1,1),10,6), 
            { existing_ports["(6,5)"] }
        )
    );
    chambers.push_back(
        new Chamber(
            Rect(Point(10,4), 15, 16), 
            { existing_ports["(10,5)"], existing_ports["(25,10)"], existing_ports["(12,18)"] }
        )
    );
    chambers.push_back(
        new Chamber (
            Rect(Point(14,20), 4, 24),
            { existing_ports["(14,21)"], existing_ports["(32,20)"] }

        )
    );
    chambers.push_back(
        new Chamber (
            Rect(Point(30,1), 13, 22), 
            { existing_ports["(30,10)"], existing_ports["(32,13)"], existing_ports["(51,12)"] }
        )
    );
    chambers.push_back(
        new Chamber(
            Rect(Point(63,3), 7, 15),
            { existing_ports["(67,9)" ] }
        )
    );
    Path * p;
    p = new Path(); 
    p->add_line( Line(Point(6,5), Point(10,5)) );
    p->add_port( existing_ports["(6,5)"] );
    p->add_port( existing_ports["(10,5)"] );
    path.push_back(p);
    p = new Path();
    p->add_line( Line( Point(12,18), Point(12,21) ) );
    p->add_line( Line( Point(12,21), Point(14,21) ) );
    p->add_port( existing_ports["(12,18)"] );
    p->add_port( existing_ports["(14,21)"] );
    path.push_back(p);
    p = new Path();
    p->add_line( Line( Point(25,10), Point(30,10) ) );
    p->add_port( existing_ports["(25,10)"] );
    p->add_port( existing_ports["(30,10)"] );
    path.push_back(p);
    p = new Path();
    p->add_line( Line( Point(32,13), Point(32,20) ) );
    p->add_port( existing_ports["(32,13)"] );
    p->add_port( existing_ports["(32,20)"] );
    path.push_back(p);
    p = new Path();
    p->add_line( Line( Point(51,12), Point(67,12) ) );
    p->add_line( Line( Point(67,12), Point(67,9)  ) );
    p->add_port( existing_ports["(51,12)"] );
    p->add_port( existing_ports["(67,9)" ] );
    path.push_back(p);
}

void Floor::initialize() {
    // 1. Generate terrain, chambers & paths;
    GenerateSampleFloorTerrain();
    // 2. Generate characters, push'em into each chamber;
    Character * t_ch;
    std::uniform_int_distribution<> rand_room_num_uni_distrib(0, chambers.size() - 1);
    std::uniform_int_distribution<> rand_character_type_uni_distrib(0, 7);
    for (int i = 0; i < 2; ++i ) {
        t_ch = new Elf();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
        t_ch = new Orc();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
        t_ch = new Merchant();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
        t_ch = new Halfling();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
    }
    for (int i = 0; i < 3; ++i ) {
        t_ch = new Human();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
        t_ch = new Dwarf();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
        t_ch = new Halfling();
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
    }
    t_ch = new Human();
    while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_ch));
    // 3. Generate potion & gold
    Item * t_potion;
    for (int i = 0; i < 10; ++i) {
        t_potion = new Potion( Potion::PotionType(rand() % 6) );
        while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_potion));
    }
    Item * t_gold;
    for (int i = 0; i < 10; ++i) {
        int rand_num = rand_character_type_uni_distrib(*(this->rand_gen));
        int room_num;
        bool dragon_spawn = false, hoard_spawn = false;
        Point dragon_pos, hoard_pos;
        switch (rand_num) {
        case 0: case 1: case 2: case 3: case 4: 
            t_gold = new Gold(Gold::GoldType::NORMAL);
            while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_gold));
            break;
        case 5: case 6:
            t_gold = new Gold(Gold::GoldType::SMALL);
            while (!chambers[rand_room_num_uni_distrib(*(this->rand_gen))]->push(t_gold));
            break;
        case 7:
            while (!dragon_spawn || !hoard_spawn) {
                while (!dragon_spawn) {
                    room_num = rand_room_num_uni_distrib(*(this->rand_gen));
                    dragon_pos = chambers[room_num]->get_available_random_pos();
                    if ( !(dragon_pos == Point(-1,-1)) ) dragon_spawn = true;
                }
                for (int i = -1; i <= 1; ++i ) {
                    if (hoard_spawn) break;
                    for (int j = -1; j <= 1; ++j ) {
                        if ( i == 0 && j == 0) continue;
                        hoard_pos = dragon_pos + Point(i,j); // gold should be spawn next to the dragon
                        if (chambers[room_num]->is_available(hoard_pos)) {
                            hoard_spawn = true;
                            t_ch = new Dragon( hoard_pos );
                            chambers[room_num]->push(t_ch);
                            t_ch->move_to(dragon_pos);
                            chambers[room_num]->push(new Gold(Gold::DRAGON_HOARD), hoard_pos);
                            break;
                        }
                    }
                }
                // if dragon hoard fails to be spawned, then dragon pos is invalidated
                if (!hoard_spawn) dragon_spawn = false; 
            } 
        }
    }
    // 3. Generate stair.
    while (true) {
        int room_num = rand_room_num_uni_distrib(*(this->rand_gen));
        auto stair_pos = chambers[room_num]->get_available_random_pos();
        if ( !(stair_pos == Point(-1,-1)) ) {
            stairs = new Port(stair_pos);
            break;
        };
    }
    // 4. Put Character
    while (true) {
        int room_num = rand_room_num_uni_distrib(*(this->rand_gen));
        auto player_pos = chambers[room_num]->get_available_random_pos();
        if ( !(stairs->position == player_pos) ) {
            the_chamber = chambers[room_num];
            player->move_to(player_pos);
            break;
        };
    }
}

// regular update each turn
void Floor::do_something() {
    player->one_turn();
    for (auto chamber : chambers) {
        if (!is_frozen) chamber->do_something(player);
    }
};

void Floor::player_go(const Point & dst)
{
    switch (player_where) 
    {
    case CHAMBER:
        the_chamber->player_go(player, dst);
        the_port = the_chamber->at_port(player->get_position());
        if ( the_port ) {
            player_where = PORT;
            the_chamber = nullptr;
        }
        break;
    case PORT: 
        if (the_port->the_chamber->contains(dst)) {
            player_where = CHAMBER;
            the_chamber = the_port->the_chamber;
            the_port = nullptr;
            player->move_to(dst);
        }
        else if (the_port->the_path->contains(dst)) {
            player_where = PATH;
            the_path = the_port->the_path;
            the_port = nullptr;
            player->move_to(dst);
        }
        else {
            // TODO: blocked; illegal move;
        }
        break;
    case PATH:
        if (the_path->contains(dst)) {
            //player_where = PATH;
            player->move_to(dst);
        } 
        else {
            // TODO: blocked; illegal move;
        }
        // similar to 'the_path->player_go()', refers to 'the_chamber->player_go()'
        the_port = the_path->at_port(dst);
        if (the_port) {
            player_where = PORT;
            the_path = nullptr;
        }
        break;
    default: break;
    }
}

void Floor::player_attack(const Point & dst) {
    if (the_chamber) the_chamber->player_attack(player, dst);
    else {} // there's nobody to attack
};
void Floor::player_use(const Point & dst) {
    if (the_chamber) the_chamber->player_use(player, dst);
    else {} // there's nothing to use
};
bool Floor::at_stair() { return player->get_position() == stairs->position; }

