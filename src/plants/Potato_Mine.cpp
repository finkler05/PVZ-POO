#include <Potato_Mine.h>

Potato_Mine::Potato_Mine(unsigned int row, unsigned int column) : Plant(300, 25, row, column, 0.0), damage(1000), armTime(14.0), armed(false){

}

void Potato_Mine::update(double deltaTime){

    if(!armed){
        setTimerPlant(getTimerPlant() + deltaTime);
        if(getTimerPlant() >= armTime){
            armed = true;
        }
    }
}

bool Potato_Mine::isArmed(){
    return armed;

}

void Potato_Mine::explode(){
    
}