#include <iostream>
#include <ncurses.h>
#include "../include/trap.h"

void trap::checkTrigger(std::vector<hero*>& heroes) {
    if(!active){return;}
    for (hero* h : heroes) {
        if (!triggered && h->getX() == x && h->getY() == y) {
            symbol = 'C';
            triggered = true;
            locked = true;
            h->freeze();
        }
    }
}

void trap::checkFalseCapture(std::vector<hero*>& heroes){
    for (hero* h : heroes){
	    if(triggered && h->getX() != x && h->getY() != y){
		    symbol = 'T';
		    triggered = false;
		    locked = false;
		    mvaddch(y, x, symbol);	    
	    }
    }
}

void trap::tryUnlock(hero& rescuer, hero& victim) {
    if (!locked || !triggered || !victim.isTrapped() || !rescuer.hasRescueKey())
        return;

    int dx = std::abs(rescuer.getX() - x);
    int dy = std::abs(rescuer.getY() - y);

    if ((dx <= 1 && dy <= 1) && !(rescuer.getX() == x && rescuer.getY() == y)) {
        locked = false;
        triggered = false;
	active = false;
        victim.unfreeze();
	victim.setPosition(x, y);
        rescuer.loseKey();
    }
}

void trap::deactivate() {
    active = false;
    triggered = false;
    locked = false;
    symbol = ' ';
}


void trap::draw() const {
    if (!active) return;

    if (triggered && locked)
        mvaddch(y, x, 'C');  
    else
        mvaddch(y, x, symbol); 
}

void trap::move(const maze& maze) {}

