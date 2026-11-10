#ifndef CONEHEAD_ZOMBIE_H
#define CONEHEAD_ZOMBIE_H

#include <Zombie.h>


class Conehead_Zombie : public Zombie {
private:

unsigned int coneHealth;


public:

Conehead_Zombie(unsigned int row);
ZombieType getType() const override {
    return ZombieType::CONEHEAD_ZOMBIE;
}

void takeDamage(unsigned int damage) ;

};


#endif