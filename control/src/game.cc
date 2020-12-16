#include "../game.hpp"

void Game::welcome() {
    std::cout << "Welcome to play the game of Chamber Crawler 3000 - villain!" << std::endl;
    show_help();
}

void Game::show_help()
{
    std::cout << std::endl;
    std::cout << "Help: \n";
    std::cout << "  h               : show help\n";
    std::cout << "  <direction>     : e.g. n(o) s(o) e(a) w(e) ne nw se sw \n\n";
    std::cout << "    - giving a direction instructs the PC to roam towards it, and they would\n";
    std::cout << "      automatically attack anyone hostile in their way or pick up any gold.\n\n";
    std::cout << "  a <direction>   : attack given direction\n";
    std::cout << "  u <direction>   : use sth. at given direction\n";
    std::cout << "  q               : quit the game\n";
    std::cout << "  r               : restart the game\n";
    std::cout << std::endl;
}

void Game::generate_floor() {
    if (floor) { delete floor; floor = nullptr; }
    player->debuff();
    if (player) floor = new Floor(player, floor_num);
    // else throw exception
}

void Game::view_ranks() {
    std::cout << "You've gained " << player->gold_amount() << " pieces of gold. " << std::endl;
}

bool Game::generate_player() {
    std::cout << "Choose a race to begin (s, d, v, t, g): " << std::endl;
    // Todo: race introduction;
    std::string usr_input;
    std::cin >> usr_input; // get user choice;
    auto i = usr_input.begin();
    while ( i != usr_input.end() && (*i == ' ' || *i == '\t') ) ++i;
    Character * t_ch = nullptr;
    switch ( *i ) {
    case 's': case 'S': t_ch = new Shade() ; break; // Shade
    case 'd': case 'D': t_ch = new Drow() ; break; // Drow
    case 'v': case 'V': t_ch = new Vampire() ; break; // Vampire
    case 't': case 'T': t_ch = new Troll() ; break; // Troll
    case 'g': case 'G': t_ch = new Goblin() ; break; // Goblin
    case 'q': case 'Q': playing = false; return true; break;
    default:
        std::cout << "Wrong choice. Please Try again.\n";
        return false;
        break;
    }
    playing = true;
    player = new PlayerCharacter( t_ch );
    return true;
}

bool Game::usr_command() {
    std::string usr_cmd;
    while ( usr_cmd.empty() ) {
        std::getline(std::cin, usr_cmd);
    }
    Point move_offset(0,0);
    enum PCAction { ROAM, ATTACK, USE, FREEZE, QUIT, RESTART };
    PCAction going_to_do = PCAction::ROAM;
    auto i = usr_cmd.begin();
    while ( i != usr_cmd.end() && (*i == ' ' || *i == '\t') ) ++i; // ignore spaces
    // if the command input phase is going to be simplified in the future,
    // probabaly i'll store PC's previous 'offset' and do the op again
    // functions like getch() might also be use.
    if ( i == usr_cmd.end() ) return false; 
    switch (*i) // first parse: get possible command
    {
    case 'h': 
        show_help(); ++i; 
        return false; // get PC's command again.
        break;
    case 'q': 
        quit_game(); ++i; 
        going_to_do = QUIT;
        break;
    case 'r': 
        restart(); ++i; 
        going_to_do = RESTART;
        break;
    case 'f':
        going_to_do = FREEZE; ++i;
        break;
    case 'a': case 'A':
        going_to_do = ATTACK; ++i;
        break;
    case 'u': case 'U':
        going_to_do = USE; ++i;
        break;
    default: 
        // do nothing here...
        break;
    }
    while ( i != usr_cmd.end() && (*i == ' ' || *i == '\t') ) ++i;
    if ( i != usr_cmd.end() ) switch (*i) // second phase: get direction
    {
    case 'n': case 'N':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'w': case 'W': move_offset = Point(-1, -1); break;
            case 'e': case 'E': move_offset = Point(+1, -1); break;
            case 'o': case 'O': move_offset = Point(0, -1); break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'nx'
                std::cout << "Illegal command! \n";
                return false; 
                break;
            }
        } else move_offset = Point(0, -1);
        break;
    case 's': case 'S':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'w': case 'W': move_offset = Point(-1, +1); break;
            case 'e': case 'E': move_offset = Point(+1, +1); break;
            case 'o': case 'O': move_offset = Point(0, +1); break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'sx'
                std::cout << "Illegal command! \n";
                return false; 
                break;
            }
        } else move_offset = Point(0, +1);
        break;
    case 'w': case 'W':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'e': case 'E': move_offset = Point(-1, 0); break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'sx'
                std::cout << "Illegal command! \n";
                return false; 
                break;
            }
        } else move_offset = Point(-1, 0);
        break;
    case 'e': case 'E':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'a': case 'A': move_offset = Point(+1, 0); break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'sx'
                std::cout << "Illegal command! \n";
                return false; 
                break;
            }
        } else move_offset = Point(+1, 0);
        break;
    default: // either not command nor direction -> illegal input
        std::cout << "Illegal command! \n";
        return false; 
        break;
    }
    switch(going_to_do) {
    case ROAM:
        floor->player_go( player->get_position() + move_offset );
        break;
    case ATTACK:
        floor->player_attack( player->get_position() + move_offset );
        break;
    case USE:
        floor->player_use( player->get_position() + move_offset );
        break;
    case FREEZE: 
        floor->frozen(); 
        break;
    default: break;
    }
    return true;
}
