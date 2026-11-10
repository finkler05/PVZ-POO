#include <Sunflower.h>


Sunflower::Sunflower(unsigned int row, unsigned column) : Plant(300, 50, row, column, 0.0), sunProduction(50), productionInterval(12.0), firstProduction(false)
{
}

void Sunflower::update(double deltaTime){
    setTimerPlant(getTimerPlant() + deltaTime);

}

unsigned int Sunflower::produceSun(){
    if(!firstProduction){
        if(getTimerPlant() >= 5.0){
            firstProduction = true;
            setTimerPlant(0.0);

            return sunProduction;
        }
    }   else{
        if(getTimerPlant() >= productionInterval){
        setTimerPlant(0.0);
        
        return sunProduction;
    }
    

    }
    return 0;
}