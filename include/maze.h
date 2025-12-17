#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <vector>

class maze{

 std::vector<std::string> grid;
 int width, height;

public:
 maze(const std::string& filename);
 bool isWalkable(int x, int y) const;
 void drawMap() const;
 void clearInnerWalls();
 std::pair<int, int> findStairs() const;

 

 int getWidth() const;
 int getHeight() const;
 char getChar(int x, int y) const;

};

#endif
