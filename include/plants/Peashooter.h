#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <Plant.h>
#include <Pea.h>


class Peashooter : public Plant {
private:
    unsigned int damage;
    double attackInterval;


public:
    Peashooter(unsigned int row, unsigned int column);
    Pea shoot();
    void update(double deltaTime);


};

#endif// PEASHOOTER_H