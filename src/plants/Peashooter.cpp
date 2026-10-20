#include <iostream>


#include <Pea.h>
#include <Peashooter.h>

Peashooter::Peashooter(unsigned int row, unsigned int column) : Plant(300, 100, row, column, 0.0){
    damage = 20;
    attackInterval = 1.5;

}

Pea Peashooter::shoot(){
    Pea pea(getRow(), getColumn());
    return pea;


}

void Peashooter::update(double deltaTime){
    Plant::update(deltaTime);

}

double Peashooter::getAttackInterval(){
    return attackInterval;
}