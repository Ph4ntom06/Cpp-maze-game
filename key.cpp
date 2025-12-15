#include "key.h"
#include <ncurses.h>

bool key::isPickedUp() const{
 return pickedUp;
}

void key::placeRandomly(const maze& maze) {
    do {
        x = rand() % maze.getWidth();
        y = rand() % maze.getHeight();
    } while (!maze.isWalkable(x, y));
}

void key::pickUp(){
 pickedUp = true;
 symbol = ' ';
 x = -1;
 y = -1;
}

void key::move(const maze&) {
   
}

