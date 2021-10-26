#ifndef FLOOR_HPP
#define FLOOR_HPP

#include <list>
#include <map>
#include <vector>
#include <memory>
#include <random>

#include "chamber.hpp"
#include "path.hpp"

class Floor
{
public:
    friend class Display;

    static std::shared_ptr<std::mt19937> rand_gen;

    Floor(PlayerCharacter * _player, int _num = 1) : player(_player), floor_num(_num) {
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
    int  get_num() { return floor_num; } 
private:
    PlayerCharacter *       player      = nullptr;
    std::vector<Chamber *>  chambers;   // managed by 'floor'
    std::list<Path *>       path;       // managed by 'floor'
    Chamber *               the_chamber = nullptr;    
    Path *                  the_path    = nullptr;       
    Port *                  the_port    = nullptr;       
    Port *                  stairs;     // managed by 'floor'
    bool                    is_frozen   = false;
    int                     floor_num   = 1;
    enum Where {CHAMBER, PORT, PATH};
    Where player_where = Where::CHAMBER;
};

#endif // FLOOR_HPP
