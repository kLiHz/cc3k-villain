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
    int         floor_max_num = 5;
    bool        playing   = false;
    bool        color_output = false;
    void        welcome();
    void        show_help();
    bool        usr_command();
    bool        generate_player();
    void        generate_floor();
public:
    Game( std::string _seed = "" ) : seed(_seed) {}
    void initialize() {
        // WELCOME PAGE
        welcome();
        // CHOOSE PLAYER
        if (player) { delete player; player = nullptr; }
        while (!generate_player());
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
        while (playing) {
            display->draw(floor);
            display->show(player);
            while(!usr_command());
            if (floor->at_stair()) {
                ++floor_num;
                if (floor_num > floor_max_num) {
                    std::cout << "You've reached the top! Congratulations!" << std::endl;
                    playing = false;
                }
                else {
                    std::cout << "You've entered Floor " << floor_num << "! " << std::endl;
                    generate_floor();
                }
            }
            floor->do_something(); // floor->budge();
            if (!player->is_alive()) lose_game();
        }
        goodbye(); 
    }
    //void load_ranks();
    void lose_game() {
        bool play_again = true;
        std::cout << "You lost the game!" << std::endl;
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
    void view_ranks();
    void goodbye() {
        view_ranks();
        std::cout << "Thanks for playing the game!" << std::endl;
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
