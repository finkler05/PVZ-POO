#include <Normal_Zombie.h>


Normal_Zombie::Normal_Zombie(unsigned int row) : Zombie(row, 7.0) {


    setHealth(270);
    setDamage(100);
    setAttackInterval(1.0);
    setSpeed(1.0 / 4.7);

}