#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include <Plant.h>

class Sunflower : public Plant {
private:
    
    unsigned int sunProduction;
    double productionInterval;
    


public:
    Sunflower(unsigned int row, unsigned int column);
    void update(double deltaTime);
    unsigned int produceSun();



};









#endif// SUNFLOWER_H