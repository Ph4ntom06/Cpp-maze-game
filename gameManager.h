#pragma once
#include <vector>
#include <string>
#include "maze.h"
#include "hero.h"
#include "trap.h"
#include "key.h"

class GameManager {
public:
    GameManager(const std::string& mapFile);
    ~GameManager();
    void run();

private:
    void init();
    void update();
    void draw();
    void checkGameOver();
    void showWinScreen();
    void showLoseScreen(const std::string& reason);
    bool heroesHaveMet() const;
    bool allHeroesAtStairs() const;
    bool keyHolderTrapped() const;
    bool allHeroesTrapped() const;

    maze gameMaze;
    key gameKey;
    std::vector<hero*> heroes;
    std::vector<trap*> traps;
    std::pair<int, int> stairs;

    bool terrainPurged = false;
    bool together = false;
    int turn = 0;
};

