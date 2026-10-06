#ifndef LawnMower_H
#define LawnMower_H

#include <Zombie.h>

class LawnMower {
private:
    unsigned int row;
    double column;
    double speed;
    bool active;
    bool used;

public:
    LawnMower(unsigned int row);
    void activate();
    void update(double deltaTime);
    bool isActive();
    bool isUsed();
    void hitZombie(Zombie& zombie);

};
    


#endif // LawnMower_H