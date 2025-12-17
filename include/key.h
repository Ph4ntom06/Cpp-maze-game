#ifndef KEY_H
#define KEY_H
#include "entity.h"
#include "maze.h"

class key : public entity{
 bool pickedUp = false;

 public:
 key() : entity('K') {};
 void placeRandomly(const maze& maze);
 bool isPickedUp() const;
 void pickUp();
 void move(const maze& maze) override;

};

#endif
