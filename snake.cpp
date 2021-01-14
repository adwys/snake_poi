#include "snake.h"
#include "screen.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
CSnake::CSnake(CRect r, char _c /*=' '*/):
  CFramedWindow(r, _c)
{
    s.push_back(CPoint(geom.topleft.y+5,10));
    s.push_back(CPoint(geom.topleft.y+4,10));
    s.push_back(CPoint(geom.topleft.y+3,10));
    level = 1;
    help = true;
    pause = true;
    curr_dir = RIGHT;
    clock = 18000;
    game_over = false;
    game_start = false;
    make_fruit();
}

void CSnake::paint() {

    CFramedWindow::paint();
    if(game_over){
        paint_game_over();
    }

    if(help)paint_help();
    s_paint();
    fruit_paint();
    paint_level();

}

void CSnake::s_paint(){

    for(int i=0;i<s.size();i++){
        gotoyx(geom.topleft.y+s[i].y,geom.topleft.x+s[i].x);
        if(i == 0)printl("o");
        else printl("x");
    }

}

bool CSnake::check_game_over(){

    for(int i = 1;i<s.size();i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y){
            return true;
        }
    }
    return false;


}
bool CSnake::check_fruit_eat(){
    if(fruit.x == s[0].x && fruit.y == s[0].y){
        level++;
        make_fruit();
        return true;
    }
    return false;
}

void CSnake::paint_game_over(){
    gotoyx(geom.topleft.y + 2, geom.topleft.x + 5);
    printl("GAME OVER, result: %d",level);
}


void CSnake::snake_update(){
    if(curr_dir == UP) {
        if(s[0].y - 1 + geom.topleft.y == geom.topleft.y){
            s.insert(s.begin(), CPoint(s[0].x, geom.size.y - 2 ));
        }
        else s.insert(s.begin(), CPoint(s[0].x, s[0].y - 1));
        if(check_game_over()){
            paint_game_over();
            game_over = true;
            pause = true;
        }
        if(!check_fruit_eat())
            s.pop_back();
        usleep(clock * 7.5);
    }
    if(curr_dir == DOWN) {
        if(s[0].y+1 + geom.topleft.y  == geom.size.y + geom.topleft.y - 1){
            s.insert(s.begin(), CPoint(s[0].x, 1));
        }
        else s.insert(s.begin(), CPoint(s[0].x, s[0].y + 1));
        if(check_game_over()){
            paint_game_over();
            game_over = true;
            pause = true;
        }
        if(!check_fruit_eat())
            s.pop_back();
        usleep(clock*7.5);
    }
    if(curr_dir == LEFT) {
        if(s[0].x - 1 + geom.topleft.x  == geom.topleft.x ){
            s.insert(s.begin(), CPoint(geom.size.x - 2, s[0].y));
        }
        else s.insert(s.begin(), CPoint(s[0].x - 1, s[0].y));
        if(check_game_over()){
            paint_game_over();
            game_over = true;
            pause = true;
        }
        if(!check_fruit_eat())
            s.pop_back();
        usleep(clock * 2.5);
    }
    if(curr_dir == RIGHT) {
        if(s[0].x + 1 + geom.topleft.x  == geom.size.x + geom.topleft.x -1){
            s.insert(s.begin(), CPoint(1, s[0].y));
        }
        else s.insert(s.begin(), CPoint(s[0].x + 1, s[0].y));
        if(check_game_over()){
            paint_game_over();
            game_over = true;
            pause = true;
        }
        if(!check_fruit_eat())
            s.pop_back();
        usleep(clock * 2.5);
    }
}
void CSnake::fruit_paint(){
    gotoyx(geom.topleft.y+fruit.y,geom.topleft.x+fruit.x);
    printl("@");
}

void CSnake::make_fruit(){
    srand(time(0));
    bool end=false;
    while(!end) {
         end=true;
         fruit.x = rand() % (geom.size.x-2) + 1;
         fruit.y = rand() % (geom.size.y-2) + 1;
         for(int i=0;i<s.size();i++){
             if(fruit.x == s[i].x && fruit.y == s[i].y)end=false;
         }
    }
}
void CSnake::paint_help(){
    gotoyx(geom.topleft.y + 2, geom.topleft.x + 5);
    printl("h - toggle help information");
    gotoyx(geom.topleft.y + 3, geom.topleft.x + 5);
    printl("p - toggle pause/play mode");
    gotoyx(geom.topleft.y + 4, geom.topleft.x + 5);
    printl("r - restart");
    gotoyx(geom.topleft.y + 5, geom.topleft.x + 5);
    printl("arrows - move snake");
}

void CSnake::paint_level(){
    gotoyx(geom.topleft.y - 1, geom.topleft.x );
    printl("| LEVEL: %d  |",level);
}

void CSnake::restart_game(){

    s.clear();
    CFramedWindow::paint();
    s.push_back(CPoint(geom.topleft.y+5,10));
    s.push_back(CPoint(geom.topleft.y+4,10));
    s.push_back(CPoint(geom.topleft.y+3,10));
    s_paint();
    level = 1;
    help = true;
    pause = true;
    curr_dir = RIGHT;
    clock = 18000;
    game_over = false;
    game_start = false;
    make_fruit();
    paint_help();
}

bool CSnake::handleEvent(int c){

    if(c == 114){
        restart_game();
    }

    if(c == 112){
        if(!help)
            pause = !pause;
        return false;
    }
    if(c == 104){
        help = !help;
        if(!pause && help){
            pause= true;
            return true;
        }
        pause = false;
        return false;
    }

    if(c == KEY_DOWN && !pause){
        if(!game_start)game_start = true;
        if(curr_dir != UP){
            curr_dir = DOWN;
            snake_update();
        }
        return true;
    }
    if(c == KEY_LEFT && !pause){
        if(!game_start)game_start = true;
        if(curr_dir != RIGHT){
            curr_dir = LEFT;
            snake_update();
        }
        return true;
    }
    if(c == KEY_RIGHT && !pause){
        if(!game_start)game_start = true;
        if(curr_dir != LEFT){
            curr_dir = RIGHT;
            snake_update();
        }
        return true;
    }
    if(c == KEY_UP && !pause){
        if(!game_start)game_start = true;
        if(curr_dir != DOWN){
            curr_dir = UP;
            snake_update();
        }
        return true;
    }
    if(game_start && !pause) {
        snake_update();
        return true;
    }
    if(CWindow::handleEvent(c)){
        return true;
    }
    return false;
}