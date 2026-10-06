#include "Plant.h"


Plant::Plant(unsigned int health, unsigned int price, unsigned int row, 
             unsigned int column, double timerPlant){
    this->health = health;
    this->price = price;
    this->row = row;
    this->column = column;
    this->timerPlant = timerPlant;

             }


    void Plant::setHealth(unsigned int health) {
    this->health = health;
    }

    void Plant::setTimerPlant(double timerPlant) {
    this->timerPlant = timerPlant;
    }

    unsigned int Plant::getHealth() {
        return health;
    }

    unsigned int Plant::getPrice() {
        return price;
    }

    unsigned int Plant::getRow() {
        return row;
    }

    unsigned int Plant::getColumn() {
        return column;
    }

    double Plant::getTimerPlant() {
        return timerPlant;
    }

    bool Plant::isAlive() {
        return health > 0;
    }

    void Plant::takeDamage(unsigned int damage) {
        if (damage >= health) {
            health = 0;
        } else {
            health -= damage;
        }
    }

    void Plant::update(double deltaTime) {
        timerPlant += deltaTime;
    }