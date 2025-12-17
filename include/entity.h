#ifndef ENTITY_H
#define ENTITY_H
#include "maze.h"

class entity{

 protected:
  
  int x, y;
  char symbol;
 
 public:
  
   entity(char s);
   virtual void move(const maze& ) = 0;
   virtual void draw() const;
   void placeRandomly(const maze&);
   int getX() const;
   int getY() const;   
};

#endif

