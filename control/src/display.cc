#include "control/display.hpp"

void Display::show(PlayerCharacter * player, int floor_num) {
    //std::cout << "\ec"; // clear terminal
    std::cout << "\e[H\e[J"; // '\e[H': move cursor to the upper left
    // Show Screen
    screen->display();
    // Show Player Character's Status
    std::cout << "Race: " << RealCharacter::character_strings[player->get_type()];
    std::cout << "\tGold: " << player->gold_amount() << "\t\t\t\t\t\tFloor " << floor_num;
    std::cout << '\n';
    auto status = player->current_status();
    std::cout << "HP: " << status.health << '\n';
    std::cout << "Atk: " << status.atk << '\n';
    std::cout << "Def: " << status.def << '\n';
    // Show Messages per Round
    std::queue<std::string> & msg_quque  = player->messages;
    std::cout << "Action: ";
    int msg_cnt = 0;
    while (!msg_quque.empty()) {
        if (msg_cnt > 0 && *(msg_quque.front().rbegin()) != '\n') std::cout << '\t';
        std::cout << msg_quque.front();
        if (*(msg_quque.front().rbegin()) == '\n') ++msg_cnt;
        msg_quque.pop();
    }
    if (msg_cnt == 0) std::cout << '\n';
    if (player->is_alive()) std::cout << "> ";
}

void Display::draw(Floor * _floor) {
    // 1. print floor region
    screen->draw(Rect(Point(0,0),25,79));
    // 2. print path
    for (auto p : _floor->path)             this->draw(p);
    // 3. print chambers
    for (auto chamber : _floor->chambers)   this->draw(chamber);
    // 4. draw player
    this->draw(_floor->player);
    // 5. draw stairs
    screen->draw(_floor->stairs->position, '\\');
}

void Display::draw(Chamber * _chamber) {
    // 1. print region
    screen->draw(_chamber->region);
    // 2. print floor
    screen->fill(_chamber->inside, '.');
    // 3. print ports
    for (auto i : _chamber->ports) {
        screen->draw(i->position, '+');
    }
    // 4. print characters
    for (auto ch : _chamber->characters) {
        this->draw(ch);
    }
    // 5. print items
    for (auto i : _chamber->items) {
        this->draw(i);
    }
}

void Display::draw(Item * _item) {
    switch(_item->type) {
    case Item::GOLD:
        screen->draw(_item->get_pos(), 'G');
        break;
    case Item::POTION:
        screen->draw(_item->get_pos(), 'P'); 
        break;
    };
}

void Display::draw(Character * _character) {
    screen->draw(_character->get_position(), _character->get_denote());
}

void Display::draw(Path * _path) {
    for (auto line : _path->passages) screen->draw(line); 
}
