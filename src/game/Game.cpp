#include <Game.h>
#include <cstdlib>

#include <Normal_Zombie.h>
#include <Conehead_Zombie.h>
#include <Gargantuar_Zombie.h>

#include <Cabbage_Pult.h>
#include <Peashooter.h>
#include <Potato_Mine.h>
#include <Wall_Nut.h>
#include <Sunflower.h>


Game::Game() : sun(150), wave(0), maxWaves(10), waveInterval(45.0), waveTimer(0.0), gameOver(false), victory(false), spawnTimer(0.0), spawnInterval(0.0), zombiesToSpawn(0), normalToSpawn(0), coneheadToSpawn(0), gargantuarToSpawn(0)
{




}

bool Game::canBuyPlant(unsigned int price){
    
    return sun >= price;

}

void Game::spendSun(unsigned int amount){

    if(sun >= amount){
        sun -= amount;
    }

}

void Game::addSun(unsigned int amount){

    sun += amount;

}

unsigned int Game::getSun(){

    return sun;

}

bool Game::buyPlant(PlantType type, unsigned int row, unsigned int column){

    Plant* plant = nullptr;

    switch(type){
    
        case PlantType::SUNFLOWER: 
        plant = new Sunflower(row, column);
        break;

        case PlantType::PEASHOOTER:

        plant = new Peashooter(row, column);
        break;

        case PlantType::CABBAGE_PULT:

        plant = new Cabbage_Pult(row, column);
        break;

        case PlantType::POTATO_MINE:

        plant = new Potato_Mine(row, column);
        break;

        case PlantType::WALL_NUT:

        plant = new Wall_Nut(row, column);
        break;
}

    if(!canBuyPlant(plant->getPrice())){
        delete plant;
        return false;
    }

    if(!board.placePlant(plant)){
        delete plant;
        return false;
    }
    spendSun(plant->getPrice());
    return true;
}

void Game::spawnZombie(ZombieType type){

    unsigned int row = rand() % 3;

    switch(type){

        case ZombieType::NORMAL_ZOMBIE:
            board.addZombie(new Normal_Zombie(row));
            break;
        
        case ZombieType::CONEHEAD_ZOMBIE:
            board.addZombie(new Conehead_Zombie(row));
            break;
            
        case ZombieType::GARGANTUAR_ZOMBIE:
            board.addZombie(new Gargantuar_Zombie(row));
            break;    
    }
}

void Game::startWave(){

    switch(wave){
    
        case 1: 
            normalToSpawn = 2;
            break;
        
        case 2:
            normalToSpawn = 3;
            break;

        case 3:
            normalToSpawn = 4;
            break;
            
        case 4:
            normalToSpawn = 4;
            coneheadToSpawn = 1;
            break;
                 
        case 5:
            normalToSpawn = 4;
            coneheadToSpawn = 2;
            break;
            
        case 6:
            normalToSpawn = 4;
            coneheadToSpawn = 3;
            break;
            
        case 7:
            normalToSpawn = 3;
            coneheadToSpawn = 5;
            break;
            
        case 8:
            normalToSpawn = 4;
            coneheadToSpawn = 4;
            gargantuarToSpawn = 1;
            break;
            
        case 9:
            normalToSpawn = 4;
            coneheadToSpawn = 5;
            gargantuarToSpawn = 1;
            break;
            
        case 10:
            normalToSpawn = 5;
            coneheadToSpawn = 5;
            gargantuarToSpawn = 2;
            break;            
    }
    zombiesToSpawn = normalToSpawn + coneheadToSpawn + gargantuarToSpawn;
}

void Game::update(double deltaTime){

    if(gameOver){
        return;
    }

    board.update(deltaTime);

    waveTimer += deltaTime;
    spawnTimer += deltaTime;

    if(zombiesToSpawn > 0 && spawnTimer >= spawnInterval){
        if(gargantuarToSpawn > 0){
            spawnZombie(ZombieType::GARGANTUAR_ZOMBIE);
            gargantuarToSpawn--;
        } else if(coneheadToSpawn > 0){
            spawnZombie(ZombieType::CONEHEAD_ZOMBIE);
            coneheadToSpawn--;

        } else if(normalToSpawn > 0){
            spawnZombie(ZombieType::NORMAL_ZOMBIE);
            normalToSpawn--;
        }
        zombiesToSpawn--;

        spawnTimer = 0.0;
        spawnInterval = 4.0 +(rand() % 4);

        if(waveTimer >= waveInterval || (zombiesToSpawn == 0 && !board.hasZombies()))
        {

            if(wave < maxWaves)
            {
                
                startWave();

            } 
        }
            checkGameOver();
            checkVictory();
        }

    }



bool Game::isGameOver(){

    return gameOver;

}

bool Game::hasWon(){

    return victory;

}

unsigned int Game::getWave(){
    
    return wave;

}

Board& Game::getBoard(){

    return board;

}

void Game::checkGameOver(){

    if(board.isGameOver()){
        gameOver = true;
        victory = false;
    }
}

void Game::checkVictory(){

    if(wave == maxWaves && zombiesToSpawn == 0 && !board.hasZombies()){
        victory = true;
        gameOver = false;
    }
}