#include "../include/entity.h"
#include <iostream>
#include <cstdlib>
#include <ncurses.h>

entity::entity(char s) : x(0), y(0), symbol(s){}

void entity::placeRandomly(const maze& maze){

 do {
  x = rand() % maze.getWidth();
  y = rand() % maze.getHeight();
 } while (!maze.isWalkable(x, y));


}

void entity::draw() const {

 mvaddch(y, x, symbol);

}

int entity::getX() const {return x;}
int entity::getY() const {return y;}
