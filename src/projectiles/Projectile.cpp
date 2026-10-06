#include <Projectile.h>

Projectile::Projectile(unsigned int damage, unsigned int row, double column, double speed){
    this->damage = damage;
    this->row = row;
    this->column = column;
    this->speed = speed;
    active = true;
}

unsigned int Projectile::getDamage(){
    return damage;

}

double Projectile::getColumn(){
    return column;
}

unsigned int Projectile::getRow(){
    return row;
}

bool Projectile::isActive(){
    return active;
}

void Projectile::deactivate(){
    active = false;
}

void Projectile::update(double deltaTime){
    column += speed * deltaTime;
}

