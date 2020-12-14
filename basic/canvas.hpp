#ifndef _CANVAS_HPP_
#define _CANVAS_HPP_

#include <iostream>
#include <cstring>
#include <algorithm>
#include "./figures.hpp"

class Canvas {
    int c_width;
    int c_height;
    char ** canvas; 
public:
    Canvas(int height, int width);
    ~Canvas();
    void display();
    void empty_canvas();
    void draw(const Point & pt, char c = '*');
    void draw(const Rect & rt, char c = '*');
    void draw(const Line & ln, char c = '#');
    void fill(const Rect &, char c = ' ');
};

#endif
