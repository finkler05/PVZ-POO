#include <LawnMower.h>


LawnMower::LawnMower(unsigned int row) : row(row), column(0.0), speed(4.0), active(false), used(false){


}

void LawnMower::activate(){

    if(!used){
        active = true;
        used = true;
    }   
}

bool LawnMower::isActive(){

    return active;

}

bool LawnMower::isUsed(){

    return used;

}

void LawnMower::hitZombie(Zombie& zombie){

    zombie.setHealth(0);

}

void LawnMower::update(double deltaTime){
    if(active){
        column += speed * deltaTime;
        
        if(column <= 7.0){
            active = false;
        }
    }
}


double LawnMower::getColumn(){
    
    return column;

}

unsigned int LawnMower::getRow(){
    
    return row;
}