#ifndef EFFECT_HPP
#define EFFECT_HPP

struct Effect
{
    int hp_change;
    int atk_buff;
    int def_buff;
    Effect(int h_change = 0, int atk_buff = 0, int def_buff = 0)
    : hp_change(h_change)
    , atk_buff(atk_buff)
    , def_buff(def_buff) {}
};

#endif
