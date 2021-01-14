#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <curses.h>
#include "winsys.h"
#include <vector>
#include <unistd.h>
enum direction {UP,DOWN,LEFT,RIGHT};
class CSnake:public CFramedWindow
{
public:
  CSnake(CRect r, char _c = ' ');

    void snake_update();
    void make_fruit();
    void restart_game();

    void fruit_paint();
    void paint();
    void s_paint();
    void paint_help();
    void paint_level();
    void paint_game_over();

    bool handleEvent(int c);
    bool check_game_over();
    bool check_fruit_eat();


private:
    int level;
    bool help;
    std::vector<CPoint> s;
    bool pause;
    int curr_dir;
    unsigned int clock;
    bool game_over;
    bool game_start;
    CPoint fruit;
};

#endif

