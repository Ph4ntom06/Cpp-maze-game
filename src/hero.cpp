#include "hero.h"
#include <cstdlib>
#include <ncurses.h>

void hero::freeze(){
 isFrozen = true;
}

void hero::move(const maze& gameMaze) {
    rememberCurrentTile();

    std::vector<std::pair<int, int>> directions = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };

    std::vector<std::pair<int, int>> candidates;

    for (auto [dx, dy] : directions) {
        int nx = x + dx, ny = y + dy;
        if (gameMaze.isWalkable(nx, ny) && visited.count({nx, ny}) == 0) {
            std::pair<int, int> next = {nx, ny};
            if (next != lastPosition) candidates.push_back({dx, dy});
        }
    }

 
    if (candidates.empty()) {
        for (auto [dx, dy] : directions) {
            int nx = x + dx, ny = y + dy;
            if (gameMaze.isWalkable(nx, ny)) {
                candidates.push_back({dx, dy});
            }
        }
    }

    if (!candidates.empty()) {
        auto [dx, dy] = candidates[rand() % candidates.size()];
        lastPosition = {x, y};
        x += dx;
        y += dy;
    }
}


void hero::tryPickUp(key& k) {
    if (!hasKey && !k.isPickedUp() && x == k.getX() && y == k.getY()) {
        hasKey = true;
	k.pickUp();

    }
}

bool hero::hasRescueKey() const{
 return hasKey;
}

void hero::loseKey(){
 hasKey = false;
}


