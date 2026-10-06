#ifndef CABBAGE_PULT_H
#define CABBAGE_PULT_H

#include <Plant.h>
#include <Cabbage.h>

class Cabbage_Pult : public Plant {
private:
    unsigned int damage;
    double attackInterval;
    unsigned int range;

public:
    Cabbage_Pult(unsigned int row, unsigned int column);
    void update(double deltaTime);
    Cabbage shoot(double targetColumn);    
    double getAttackInterval();
    unsigned int getRange();




};




#endif