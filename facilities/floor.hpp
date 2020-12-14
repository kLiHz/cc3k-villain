#pragma once

#include <list>
#include <map>
#include <vector>
#include "./chamber.hpp"
#include "./path.hpp"

class Floor
{
public:
    friend class Display;
    Floor(PlayerCharacter * _player) : player(_player) {
        initialize();
    }
    ~Floor() {
        for (auto c : chambers) delete c;
        for (auto p : path)     delete p;
        delete stairs;
    }
    void GenerateSampleFloorTerrain();
    void initialize();
    // regular update each turn
    void do_something();
    // restrict elements on the floor to update;
    // switch between two states for each calling.
    void frozen() { is_frozen = !is_frozen; } 
    void player_go(const Point & dst);
    void player_attack(const Point & dst);
    void player_use(const Point & dst);
    bool at_stair();
private:
    PlayerCharacter *       player = nullptr;
    std::vector<Chamber *>  chambers;       // managed by 'floor'
    std::list<Path *>       path;           // managed by 'floor'
    Chamber *               the_chamber;    
    Path *                  the_path;       
    Port *                  the_port;       
    Port *                  stairs;         // managed by 'floor'
    bool                    is_frozen = false;
    enum Where {CHAMBER, PORT, PATH};
    Where player_where = Where::CHAMBER;
};
