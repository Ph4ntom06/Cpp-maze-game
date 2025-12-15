#ifndef TRAP_H
#define TRAP_H

#include <vector>
#include "entity.h"
#include "hero.h"

class trap : public entity {
    bool triggered;
    bool locked;
    bool active;

public:
    trap() : entity('T'), triggered(false), locked(false), active(true) {}

    void checkTrigger(std::vector<hero*>& heroes);
    void checkFalseCapture(std::vector<hero*>&heroes);
    void tryUnlock(hero& rescuer, hero& victim); 
    bool isActive(){ return active;}

    void draw() const override;
    void move(const maze& maze) override;
    void deactivate();

    bool isTriggered() const { return triggered; }
    bool isLocked() const { return locked; }
};

#endif

