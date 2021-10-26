#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <iostream>
#include "characters/races.hpp"
#include "characters/player_character.hpp"
#include "basic/canvas.hpp"
#include "facilities/floor.hpp"
#include "facilities/chamber.hpp"
#include "facilities/path.hpp"

#include <queue>

class Display {
private:
    Canvas * screen; //default 25*79
public:
    Display() {
        screen = new Canvas(25, 79); // height * width: 25 * 79
    };
    ~Display() { delete screen; }
    //void draw();
    void show(PlayerCharacter * player, int floor_num);
    void draw(Floor * _floor);
    void draw(Chamber * _chamber);
    void draw(Character * _character);
    void draw(Item * _item);
    void draw(Path * _path);
    Canvas * get_canvas() {
        return screen;
    }
    //void push_msg(Message * msg) {
    //    msg_quque.push(msg);
    //};
};

#endif
