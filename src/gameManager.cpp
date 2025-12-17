#include "../include/gameManager.h"
#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

// --- Constructor ---
GameManager::GameManager(const std::string& mapFile) : gameMaze(mapFile) {
    init();
}

// --- Destructor ---
GameManager::~GameManager() {
    for (hero* h : heroes) delete h;
    for (trap* t : traps) delete t;
    endwin();
}

// --- Game Initialization ---
void GameManager::init() {
    initscr();
    noecho();
    curs_set(0);
    srand(time(0));

    gameKey.placeRandomly(gameMaze);

    heroes = { new hero('G'), new hero('S') };
    heroes[0]->placeRandomly(gameMaze);

    do {
        heroes[1]->placeRandomly(gameMaze);
    } while (std::abs(heroes[0]->getX() - heroes[1]->getX()) < 7 ||
             std::abs(heroes[0]->getY() - heroes[1]->getY()) < 7);

    traps = { new trap(), new trap() };
    for (trap* t : traps) t->placeRandomly(gameMaze);
}

// --- Main Game Loop ---
void GameManager::run() {
    for (turn = 0; turn < 1000; ++turn) {
        checkGameOver();

        clear();

        if (!terrainPurged && heroesHaveMet()) {
            terrainPurged = true;
            gameMaze.clearInnerWalls();
            for (trap* t : traps) t->deactivate();
        }

        gameMaze.drawMap();
        for (trap* t : traps) t->draw();
        if (!gameKey.isPickedUp()) gameKey.draw();

        if (!together && heroesHaveMet()) {
            together = true;
            stairs = gameMaze.findStairs();
        }

        // Movement
        if (together) {
            for (hero* h : heroes) {
                int dx = stairs.first - h->getX();
                int dy = stairs.second - h->getY();
                if (dx != 0) dx /= std::abs(dx);
                if (dy != 0) dy /= std::abs(dy);
                int nx = h->getX() + dx;
                int ny = h->getY() + dy;
                if (gameMaze.isWalkable(nx, ny)) h->setPosition(nx, ny);
            }
        } else {
            for (hero* h : heroes) h->move(gameMaze);
        }

        for (hero* h : heroes) {
            h->tryPickUp(gameKey);
            if (!h->isTrapped()) h->draw();
        }

        for (trap* t : traps) t->checkTrigger(heroes);
	//for (trap* t : traps) t->checkFalseCapture(heroes);

        // Rescue logic
        for (hero* h1 : heroes) {
            if (!h1->isTrapped() && h1->hasRescueKey()) {
                for (hero* h2 : heroes) {
                    if (h1 != h2 && h2->isTrapped()) {
                        for (trap* t : traps)
                            t->tryUnlock(*h1, *h2);
                    }
                }
            }
        }

        refresh();
        napms(200);
    }

    showLoseScreen("Time ran out. The dungeon prevails!\n");
}
bool GameManager::heroesHaveMet() const {
    if (heroes.size() < 2) return false;
    int dx = std::abs(heroes[0]->getX() - heroes[1]->getX());
    int dy = std::abs(heroes[0]->getY() - heroes[1]->getY());
    return (dx <= 1 && dy <= 1 &&
            !heroes[0]->isTrapped() &&
            !heroes[1]->isTrapped());
}

bool GameManager::allHeroesAtStairs() const {
    for (hero* h : heroes)
        if (h->getX() != stairs.first || h->getY() != stairs.second)
            return false;
    return true;
}

bool GameManager::keyHolderTrapped() const {
    for (hero* h : heroes)
        if (h->hasRescueKey() && h->isTrapped() && gameKey.isPickedUp())
            return true;
    return false;
}

bool GameManager::allHeroesTrapped() const {
    for (hero* h : heroes)
        if (!h->isTrapped())
            return false;
    return true;
}

void GameManager::checkGameOver() {
    if (together && allHeroesAtStairs()) {
        showWinScreen();
        exit(0);
    }

    if (keyHolderTrapped() && gameKey.isPickedUp()) {
        showLoseScreen("The hero with the key was trapped!\n");
        exit(0);
    }

    if (allHeroesTrapped()) {
        showLoseScreen("All heroes are trapped!\n");
        exit(0);
    }
}

void GameManager::showWinScreen() {
    clear();
    mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "  ~~~ YOU WIN! ~~~");
    mvprintw(LINES / 2,     (COLS - 38) / 2, "The heroes escaped the dungeon together!");
    mvprintw(LINES / 2 + 2, (COLS - 26) / 2, "Press any key to exit...\n");
    refresh();
    getch();
}

void GameManager::showLoseScreen(const std::string& reason) {
    clear();
    mvprintw(LINES / 2 - 1, (COLS - 13) / 2, "  GAME OVER  ");
    mvprintw(LINES / 2,     (COLS - reason.size()) / 2, "%s", reason.c_str());
    mvprintw(LINES / 2 + 2, (COLS - 26) / 2, "Press any key to exit...\n");
    refresh();
    getch();
}

