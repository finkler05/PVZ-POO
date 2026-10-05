#ifndef PLANT_H
#define PLANT_H

class Plant {
    private:
    unsigned int health;
    unsigned int price;
    unsigned int row;
    unsigned int column;
    double timerPlant;

    public:
    Plant(unsigned int health, unsigned int price, unsigned int row, unsigned int column, double timerPlant);

    void update(double deltaTime);
    void takeDamage(unsigned int damage);
    bool isAlive();

    unsigned int setHealth(unsigned int health);
    unsigned int setTimerPlant(double timerPlant);
    
    unsigned int getHealth();
    unsigned int getPrice();
    unsigned int getRow();
    unsigned int getColumn();
    double getTimerPlant();



};



#endif // PLANT_H