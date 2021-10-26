#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <utility>
#include <random>
#include <memory>

#include "display.hpp"
#include "facilities/floor.hpp"

using PC = PlayerCharacter;

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
    static void     welcome();
    static void     show_help();
    bool            usr_command();
    bool            generate_player();
    void            generate_floor();

public:
    std::shared_ptr<std::mt19937> rand_gen;

    Game(const std::string & seed_ = "") : seed(seed_) {}
    void initialize() {
        // WELCOME PAGE
        welcome();
        // CHOOSE PLAYER
        if (player) { delete player; player = nullptr; }
        while (!generate_player());
        if (!playing) return;
        // GENERATE FLOOR
        generate_floor();
        delete display;
        display = new Display();
        playing = true;
    };
    void play() {
        try {
            int s = std::stol(seed); // parse seed
            rand_gen = std::make_shared<std::mt19937>(s);
        }
        catch (std::exception & except) { // unable to parse string
            std::cerr << except.what();
            std::random_device rd;
            rand_gen = std::make_shared<std::mt19937>(rd());
        }
        Character::rand_gen = rand_gen;
        Floor::rand_gen = rand_gen;
        initialize();
        while (playing) {
            display->draw(floor);
            display->show(player, floor_num);
            while(!usr_command());
            if (!playing) break;
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
        display->draw(floor);
        display->show(player, floor_num);
        bool play_again = true;
        std::cout << "You lost the game!" << std::endl;
        view_ranks();
        // Todo: Would you like to try again?
        std::cout << "Would you like to try again? (Y/N) " << std::endl;
        int choice = ' ';
        while (choice == ' ') {
            choice = getchar();
            getchar(); // take '\n' away
            switch (choice)
            {
            case 'y': case 'Y': play_again = true; break;
            case 'n': case 'N': play_again = false; break;
            default: 
                std::cout << "Wrong choice. Try again." << std::endl;
                choice = ' '; break;
            }
        }
        if (play_again) { // Yes
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
        if (player) view_ranks();
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
