#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <ctime>

#include "./display.hpp"
#include "../facilities/floor.hpp"

typedef PlayerCharacter PC;

class Game
{
    std::string seed;
    Display *   display   = nullptr;
    Floor *     floor     = nullptr;
    PC *        player    = nullptr;
    int         floor_num = 1;
    bool        playing   = false;
    bool        color_output = false;
    void        welcome();
    void        show_help();
    void        usr_command();
    void        generate_player();
    void        generate_floor();
public:
    Game( std::string _seed = "" ) : seed(_seed) {}
    void initialize() {
        // WELCOME PAGE
        welcome();
        // CHOOSE PLAYER
        generate_player();
        // GENERATE FLOOR
        generate_floor();
        if (display) delete display;
        display = new Display();
        playing = true;
    };
    void play() {
        if (seed.empty()) srand(time(0));
        else {
            int _seed;
            try { 
                _seed = std::stod(seed); // parse seed
                srand(_seed);
            } 
            catch (std::exception & except) {
                std::cerr << except.what();
                srand(0);
            }
        }
        initialize();
        display->draw(floor);
        display->show(player);
        while (playing) {
            usr_command();
            if (floor->at_stair()) {
                ++floor_num;
                generate_floor();
            }
            //floor->budge();
            floor->do_something();
            display->draw(floor);
            display->show(player);
            if (!player->is_alive()) lose_game();
        }
        goodbye(); 
    }
    //void load_ranks();
    void lose_game() {
        bool play_again = true;
        // Todo: Would you like to try again?
        if (play_again) { // Yes
            view_ranks();
            initialize(); 
        } else {
            playing = false;
        }
    }
    void quit_game() {
        if (player->is_alive()) {
            // Todo: Possible Game Saving
        }
        playing = false;
    }
    void view_ranks() {
    }
    void goodbye() {
        view_ranks();
        // GOODBYE PAGE: THANKS FOR PLAYING!
    }
    void restart() {
        bool if_restart = true;
        // SURE
        if (if_restart) {
            initialize();
        }
        else return; // do nothing
    }
    ~Game() {
        delete floor;
        delete player;
    }
};

#endif