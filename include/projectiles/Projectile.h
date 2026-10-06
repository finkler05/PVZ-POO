#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile {
private:

    unsigned int damage;
    unsigned int row;
    double column;
    double speed;
    bool active;

public:
    Projectile(unsigned int damage, unsigned int row, double column, double speed);
    void update(double deltaTime);
    bool isActive();
    void deactivate();

    unsigned int getDamage();
    unsigned int getRow();
    double getColumn();





};





#endif // PROJECTILE_H