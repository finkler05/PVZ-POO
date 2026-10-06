#ifndef POTATO_MINE_H
#define POTATO_MINE_H

#include <Plant.h>

class Potato_Mine : public Plant {
private:
   unsigned int damage;
   double armTime;
   bool armed;

public:
   Potato_Mine(unsigned int row, unsigned int column);
   void explode();
   bool isArmed();
   void update(double deltaTime);

};

#endif// POTATO_MINE_H