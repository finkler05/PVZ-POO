#ifndef CABBAGE_H
#define CABBAGE_H

#include <Projectile.h>

class Cabbage : public Projectile {
private:
    double height;
    double verticalSpeed;
    double targetColumn;


public:
   Cabbage(unsigned int row, double column);
   void update(double deltaTime);
};

#endif // CABBAGE_H