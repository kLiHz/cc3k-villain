// December, 2020.
//
//   _____ _                     _                
//  / ____| |                   | |               
// | |    | |__   __ _ _ __ ___ | |__   ___ _ __  
// | |    | '_ \ / _` | '_ ` _ \| '_ \ / _ \ '__| 
// | |____| | | | (_| | | | | | | |_) |  __/ |    
//  \_____|_| |_|\__,_|_| |_| |_|_.__/ \___|_|    
//               _____                    _           
//              / ____|                  | |          
//             | |     _ __ __ ___      _| | ___ _ __ 
//             | |    | '__/ _` \ \ /\ / / |/ _ \ '__|
//             | |____| | | (_| |\ V  V /| |  __/ |   
//              \_____|_|  \__,_| \_/\_/ |_|\___|_|   
//                              ____   ___   ___   ___  
//                             |___ \ / _ \ / _ \ / _ \ .
//                               __) | | | | | | | | | |
//                              |__ <| | | | | | | | | |
//                              ___) | |_| | |_| | |_| |
//                             |____/ \___/ \___/ \___/ 
//
// From: http://patorjk.com/software/taag/#p=display&f=Big&t=Chamber%20Crawler%203000
// Also see: https://fsymbols.com/generators/carty/

#include <iostream>
#include <vector>
#include "control/game.hpp"

int main(int argc, char * argv[] ) 
{
    bool seed_found = false;
    Game * inst;
    std::vector <std::string> tokens;
    for ( int i = 1; i < argc; ++i ) {
        tokens.push_back(std::string(argv[i]));
    }
    for (auto t : tokens) {
        if (std::isdigit(t[0])) {
            if (seed_found) continue;
            seed_found = true;
            inst = new Game(t);
            continue;
        }
    }
    if (!seed_found) inst = new Game();
    inst->play();
    delete inst;
    return 0;
}