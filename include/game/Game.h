#ifndef GAME_H
#define GAME_H

#include <Board.h>
#include <enum.h>

class Game {
private:
    Board board;
    unsigned int sun;
    unsigned int wave;
    unsigned int maxWaves;
    double waveInterval;
    double waveTimer;
    bool gameOver;
    bool victory;
    double spawnTimer;
    double spawnInterval;
    unsigned int zombiesToSpawn;
    unsigned int normalToSpawn;
    unsigned int coneheadToSpawn;
    unsigned int gargantuarToSpawn;

    
public:
    Game();
    void update(double deltaTime);
    void spawnZombie(ZombieType type);
    void startWave();
    bool canBuyPlant(unsigned int price);
    void spendSun(unsigned int amount);
    void addSun(unsigned int amount);
    void checkGameOver();
    void checkVictory();
    bool isGameOver();
    bool hasWon();
    bool buyPlant(PlantType type, unsigned int row, unsigned int column);
    
    unsigned int getSun();
    
};

#endif