#include <iostream>
#include <string>
bool flag = true;
void usr_command() {
    std::string usr_cmd;
    while ( usr_cmd.empty() ) {
        std::getline(std::cin, usr_cmd);
    }
    //Point move_offset(0,0);
    enum PCAction { ROAM, ATTACK, USE, FREEZE, QUIT, RESTART };
    PCAction going_to_do = PCAction::ROAM;
    auto i = usr_cmd.begin();
    while ( i != usr_cmd.end() && (*i == ' ' || *i == '\t') ) ++i; // ignore spaces
    // if the command input phase is going to be simplified in the future,
    // probabaly i'll store PC's previous 'offset' and do the op again
    // functions like getch() might also be use.
    if ( i == usr_cmd.end() ) return usr_command(); 
    switch (*i) // first parse: get possible command
    {
    case 'h': 
        std::cout << "help\n"; ++i; 
        return usr_command(); // get PC's command again.
        break;
    case 'q': 
        std::cout<<"quit\n"; ++i; 
        going_to_do = QUIT; flag = false; return;
        break;
    case 'r': 
        std::cout<<"restart\n"; ++i; 
        going_to_do = RESTART; return;
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
            case 'w': case 'W': std::cout << "north west\n"; break;
            case 'e': case 'E': std::cout << "north east\n"; break;
            case 'o': case 'O': std::cout << "north \n";     break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'nx'
                std::cout << "Illegal command! \n";
                return usr_command(); 
                break;
            }
        } else std::cout << "north\n";
        break;
    case 's': case 'S':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'w': case 'W': std::cout << "south west\n"; break;
            case 'e': case 'E': std::cout << "south east\n"; break;
            case 'o': case 'O': std::cout << "south \n";     break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'sx'
                std::cout << "Illegal command! \n";
                return usr_command(); 
                break;
            }
        } else std::cout << "south\n";
        break;
    case 'w': case 'W':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'e': case 'E': std::cout << "west \n";     break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'sx'
                std::cout << "Illegal command! \n";
                return usr_command(); 
                break;
            }
        } else std::cout << "west \n";
        break;
    case 'e': case 'E':
        ++i;
        if ( i != usr_cmd.end() ) {
            switch(*i) {
            case 'a': case 'A': std::cout << "east \n";     break;
            case ' ': case '\t': break; //ignore space;
            default: // illegal input, e.g. 'sx'
                std::cout << "Illegal command! \n";
                return usr_command(); 
                break;
            }
        } else std::cout << "east \n";
        break;
    default: // either not command nor direction -> illegal input
        std::cout << "Illegal command! \n";
        return usr_command(); 
        break;
    }
    switch(going_to_do) {
    case ROAM:
        std::cout << "roam\n";
        break;
    case ATTACK:
        std::cout << "attack\n";
        break;
    case USE:
        std::cout << "use\n";
        break;
    case FREEZE: 
        std::cout << "freeze\n";
        break;
    default: break;
    }
}
int main()
{
    while (flag)
    {
        usr_command();
    }
}