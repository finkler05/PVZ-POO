#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include <Zombie.h>
#include <Projectile.h>
#include <Plant.h>
#include <LawnMower.h>

class Board {
private:
    unsigned int rows;
    unsigned int columns;
    std::vector<Zombie*> zombies;
    std::vector<Projectile*> projectiles;
    Plant* plants[3][7];
    LawnMower* lawnMowers[3];
    bool gameOver;

public:
    Board();
    bool isEmpty(unsigned int row, unsigned int column);
    bool placePlant(Plant* plant);
    void removePlant(unsigned int row, unsigned int column);
    void addZombie(Zombie* zombie);
    void addProjectile(Projectile* projectile);
    void checkProjectileCollisions();
    void checkLawnMowerCollisions();
    bool hasZombies();
    bool isGameOver();
    void update(double deltaTime);




};



#endif