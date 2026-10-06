#ifndef GARGANTUAR_ZOMBIE_H
#define GARGANTUAR_ZOMBIE_H

#include <Zombie.h>



class Gargantuar_Zombie : public Zombie {
private:
    unsigned int smashDamage;


public:
    Gargantuar_Zombie(unsigned int row);
    void attack(Plant& plant);
};

#endif