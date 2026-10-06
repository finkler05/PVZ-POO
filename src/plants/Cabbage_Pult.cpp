#include <Cabbage_Pult.h>
#include <Cabbage.h>

Cabbage_Pult::Cabbage_Pult(unsigned int row, unsigned column) : Plant(300, 100, row, column, 0.0) {
    damage = 40;
    attackInterval = 3.0;
    range = 4;
}

Cabbage Cabbage_Pult::shoot(double targetColumn){
    setTimerPlant(0.0);

    return Cabbage(getRow(), getColumn(), targetColumn);
}

void Cabbage_Pult::update(double deltaTime){
    Plant::update(deltaTime);
}

double Cabbage_Pult::getAttackInterval(){
    return attackInterval;
}

unsigned int Cabbage_Pult::getRange(){
    return range;
}