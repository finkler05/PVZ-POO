#include <Conehead_Zombie.h>


Conehead_Zombie::Conehead_Zombie(unsigned int row) : Zombie(row, 7.0) {

    setHealth(270);
    setDamage(100);
    setAttackInterval(1.0);
    setSpeed(1.0 / 4.7);
    coneHealth = 370;

}


void Conehead_Zombie::takeDamage(unsigned int damage) {

    if (coneHealth > 0) {

        if (damage >= coneHealth) {
            unsigned int remainingDamage = damage - coneHealth;

            coneHealth = 0;

            Zombie::takeDamage(remainingDamage);
        }
        else {
            coneHealth -= damage;
        }

    }
    else {
        Zombie::takeDamage(damage);
    }
}


