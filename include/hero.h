#ifndef HERO_H
#define HERO_H

#include "entity.h"
#include "maze.h"
#include "key.h"
#include <set>

class hero : public entity {

 bool isFrozen;
 bool hasKey = false;
 std::set<std::pair<int, int>> visited;
 std::pair<int, int> lastPosition = {-1, -1};

 public:
  hero(char s) : entity(s), isFrozen(false) {}
  void move(const maze& maze) override;
  void freeze();
  void tryPickUp(key& k);
  bool hasRescueKey() const;
  void loseKey();
  bool isTrapped() const { return isFrozen; }
  void unfreeze() { isFrozen = false; }
  void setPosition(int newX, int newY) {
    x = newX;
    y = newY;
  }
  void rememberCurrentTile() {
    visited.insert({x, y});
  }



};

#endif
