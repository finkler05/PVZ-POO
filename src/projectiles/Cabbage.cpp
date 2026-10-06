#include <Cabbage.h>

Cabbage::Cabbage(unsigned int row, double column, double targetColumn) : Projectile(40, row, column, 600.0){

    height = 0.0;
    this->targetColumn = targetColumn; 
    verticalSpeed = 400.0;
    startColumn = column;
}

void Cabbage::update(double deltaTime){
    Projectile::update(deltaTime);
double middle = (startColumn + targetColumn / 2.0);

if(getColumn() < middle){
    height += verticalSpeed * deltaTime;

}   else {
    height -= verticalSpeed * deltaTime;
    }


    if(height < 0){
        height = 0;
    }
} 

