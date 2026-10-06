#include <Gargantuar_Zombie.h>


Gargantuar_Zombie::Gargantuar_Zombie(unsigned int row) : Zombie(row, 7.0) {
    setHealth(3000);
    smashDamage = 2000;
    setAttackInterval(4.0);
    setSpeed(1.0 / 4.7);

}

void Gargantuar_Zombie::attack(Plant& plant) {
    if(getTimerZombie() >= 4.0) {
    plant.takeDamage(smashDamage);
    setTimerZombie(0.0);
    }
}