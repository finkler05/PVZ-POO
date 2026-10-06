#include <Zombie.h>

Zombie::Zombie(unsigned int row, double column) : row(row), column(column) {
    health = 0;
    damage = 0;
    attackInterval = 0;
    speed = 0;
    timerZombie = 0;
}

    void Zombie::setHealth(unsigned int health) {
    this->health = health;
    }

    void Zombie::setDamage(unsigned int damage) {
    this->damage = damage;
    }

    void Zombie::setAttackInterval(double attackInterval) {
    this->attackInterval = attackInterval;
    }

    void Zombie::setSpeed(double speed) {
    this->speed = speed;
    }

    unsigned int Zombie::getHealth() {
    return health;
    }

    unsigned int Zombie::getRow() {
    return row;
    }

    double Zombie::getColumn() {
    return column;
    }

    bool Zombie::isAlive() {
    return health > 0;
    }   

    void Zombie::takeDamage(unsigned int damage) {
    if (damage >= health) {
        health = 0;
    } else {
        health -= damage;
    }
    }

    void Zombie::update(double deltaTime) {
    timerZombie += deltaTime;
    }

    void Zombie::attack(Plant& plant) {
        if (timerZombie >= attackInterval) {
            plant.takeDamage(damage);
            timerZombie = 0;
        }
    }

    double Zombie::getTimerZombie(){
        return timerZombie;
    }

    void Zombie::setTimerZombie(double timerZombie){
        this->timerZombie = timerZombie;
    }
