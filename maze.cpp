#include "maze.h"
#include <fstream>
#include <ncurses.h>

maze::maze(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    height = grid.size();
    width = grid.empty() ? 0 : grid[0].size();
}

bool maze::isWalkable(int x, int y) const {
    if (y < 0 || y >= height || x < 0 || x >= width)
        return false;
    char c = grid[y][x];
    return c == ' ' || c == 'L';
}

void maze::drawMap() const {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            mvaddch(y, x, grid[y][x]);
        }
    }
}


int maze::getWidth() const { return width; }
int maze::getHeight() const { return height; }
char maze::getChar(int x, int y) const { 
 if (y < 0 || y >= height || x < 0 || x >= width)
  return ' '; 
 return grid[y][x]; 
}

void maze::clearInnerWalls() {
    int rows = grid.size();
    int cols = grid[0].size();

    for (int y = 1; y < rows - 1; ++y) {
        for (int x = 1; x < cols - 1; ++x) {
            if (grid[y][x] == '*') {
                grid[y][x] = ' ';
            }
        }
    }
}

std::pair<int, int> maze::findStairs() const {
    for (int y = 0; y < grid.size(); ++y)
        for (int x = 0; x < grid[y].size(); ++x)
            if (grid[y][x] == 'L') return {x, y};
    return {-1, -1};
}


