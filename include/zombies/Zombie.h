#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <Plant.h>

class Zombie {
private:
    unsigned int health;
    unsigned int damage;
    double attackInterval;
    unsigned int row;
    double column;
    double speed;
    double timerZombie;

public:
    Zombie(unsigned int row, double column);
    void update(double deltaTime);
    void takeDamage(unsigned int damage);
    void attack(Plant& plant);
    bool isAlive();

    void setColumn(double);
    void setHealth(unsigned int health);
    void setDamage(unsigned int damage);
    void setAttackInterval(double attackInterval);
    void setSpeed(double speed);
    void setTimerZombie(double timerZombie);
    
    unsigned int getHealth();
    unsigned int getRow();
    double getColumn();
    double getTimerZombie();
    double getSpeed();




};






#endif // ZOMBIE_H