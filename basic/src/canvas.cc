#include "../canvas.hpp"

Canvas::Canvas(int height, int width) : c_height(height), c_width(width)
{
    canvas = nullptr;
    canvas = new char* [c_height]; 
    for (int i = 0; i < c_height; ++i) {
        canvas[i] = new char [c_width + 1];
        memset(canvas[i], ' ', sizeof(char)*c_width);
        canvas[i][c_width] = '\0'; 
    }
}

Canvas::~Canvas() 
{
    for (int i = 0; i < c_height; ++i) {
        delete canvas[i];
    }
    delete canvas;
}

void Canvas::display()
{
    for (int i = 0; i < c_height; ++i) {
        //for (int j = 0; j < c_width; ++j) {
        //    std::cout << canvas[i][j];
        //}
        std::cout << canvas[i] << std::endl;
    }
}

void Canvas::empty_canvas() 
{
    for (int i = 0; i < c_height; ++i) {
        memset(canvas[i], ' ', sizeof(char)*c_width);
    }
}

void Canvas::fill(const Rect & rt, char c) 
{
    for (int i = rt.base.y; i < rt.base.y + rt.height; ++i) {
        if (i >= c_height || i < 0) continue;
        for (int j = rt.base.x; j < rt.base.x + rt.width; ++j) {
            if (j >= c_width || j < 0) continue;
            canvas[i][j] = c;
        }
    }
}

void Canvas::draw(const Point & pt, char c)
{
    if (pt.x >= c_width || pt.x < 0 || pt.y >= c_height || pt.y < 0) return;
    canvas[pt.y][pt.x] = c;
}

void Canvas::draw(const Rect & rt, char c)
{
    char row_char = '-';
    char col_char = '|';
    if (c != '*') {
        row_char = c;
        col_char = c;
    }

        int row_begin_1 = rt.base.y, row_begin_2 = rt.base.y + rt.height - 1;
        int col_begin_1 = rt.base.x, col_begin_2 = rt.base.x + rt.width - 1;
        if (row_begin_1 >= 0 && row_begin_1 < c_height) { // see if the starting point is valid
            for (int i = col_begin_1 + 1; i < col_begin_2; ++i) { // draw a rect's upper horizontal line
                if (i >= c_width || i < 0) continue; // break if go out of the margin
                canvas[row_begin_1][i] = row_char;
            }
        }
        if (row_begin_2 >= 0 && row_begin_2 < c_height) { 
            for (int i = col_begin_1 + 1; i < col_begin_2; ++i) {  // draw lower horizontal line
                if (i >= c_width || i < 0) continue;
                canvas[row_begin_2][i] = row_char;
            }
        }
        if (col_begin_1 >= 0 && col_begin_1 < c_width) {
            for (int i = row_begin_1; i <= row_begin_2; ++i) {
                if (i >= c_height || i < 0) continue;
                canvas[i][col_begin_1] = col_char;
            }
        }
        if (col_begin_2 >= 0 && col_begin_2 < c_width) {
            for (int i = row_begin_1; i <= row_begin_2; ++i) {
                if (i >= c_height || i < 0) continue;
                canvas[i][col_begin_2] = col_char;
            }
        }
}

void Canvas::draw(const Line & ln, char c)
{
    if (ln.begin.x == ln.end.x) { //vertical
        int begin_y = std::min(ln.begin.y, ln.end.y);
        int end_y = std::max(ln.begin.y, ln.end.y);
        for (int i = begin_y; i < end_y; ++i) 
            canvas[i][ln.begin.x] = c;
    }
    else if (ln.begin.y == ln.end.y) { // horizontal
        int begin_x = std::min(ln.begin.x, ln.end.x);
        int end_x = std::max(ln.begin.x, ln.end.x);
        for (int i = begin_x; i <= end_x; ++i)
            canvas[ln.begin.y][i] = c;
    } 
    else {} // not implemented
}