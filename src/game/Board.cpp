#include <iostream>

#include <Sunflower.h>
#include <Peashooter.h>
#include <Cabbage_Pult.h>
#include <Wall_Nut.h>
#include <Potato_Mine.h>
#include <Board.h>


Board::Board() : rows(3), columns(7), gameOver(false){

    for(unsigned int row = 0; row < rows; row++){
        for(unsigned int column = 0; column < columns; column++){
            plants[row][column] = nullptr;
        }
        lawnMowers[row] = new LawnMower(row);
    }
}

bool Board::isEmpty(unsigned int row, unsigned int column){
    if(row >= rows || column >= columns){
        return false;
    }
    return plants[row][column] == nullptr;

}


bool Board::placePlant(Plant* plant){
    if(plant == nullptr){
        return false;
    }
    unsigned int row = plant->getRow();
    unsigned int column = plant->getColumn();

    if(!isEmpty(row, column)){
        return false;
    }
    plants[row][column] = plant;

    return true;
}


void Board::removePlant(unsigned int row, unsigned int column){

    if(row >= rows || column >= columns){
        return;
    }

    plants[row][column] = nullptr;
}

void Board::addZombie(Zombie* zombie){
    if(zombie != nullptr){
        zombies.push_back(zombie);
    }
}

void Board::addProjectile(Projectile* projectile){

    if(projectile != nullptr){

        projectiles.push_back(projectile);
    }
}

void Board::checkProjectileCollisions()
{
    for(Projectile* projectile : projectiles)
    {
        if(projectile == nullptr || !projectile->isActive())
        {
            
            continue;
        }

    for(Zombie* zombie : zombies)
    {
        if(zombie == nullptr || !zombie->isAlive())
        {
            continue;
        }

        if(projectile->getRow() == zombie->getRow() && projectile->getColumn() >= zombie->getColumn()){
                zombie->takeDamage(projectile->getDamage());
                projectile->deactivate();
                break;
            }
        }
    }
}

void Board::checkLawnMowerCollisions(){
    
    for(unsigned int i = 0; i < rows; i++){
        
        LawnMower* mower = lawnMowers[i];

        if(mower == nullptr){

            continue;
            
        }
        for(Zombie* zombie : zombies){

            if(zombie == nullptr || !zombie->isAlive()){
                
                continue;

            }
            if(zombie->getRow() != mower->getRow()){

                continue;

            }
            if(!mower->isUsed() && zombie->getColumn() <= 0.0){

                mower->activate();

            }else if(mower->isUsed() && !mower->isActive() && zombie->getColumn() <= 0.0){
                gameOver = true;

            }

            if(mower->isActive() && mower->getColumn() >= zombie->getColumn()){

                mower->hitZombie(*zombie);

            }
        }
    }

}

bool Board::hasZombies(){

    for(Zombie* zombie : zombies){
        if(zombie != nullptr && zombie->isAlive()){
            return true;
        }
    }
    return false;   
}

bool Board::isGameOver(){

    return gameOver;
}

void Board::update(double deltaTime){

    for(Zombie* zombie : zombies){
        if(zombie != nullptr && zombie->isAlive()){

            zombie->update(deltaTime);
            zombie->setColumn(zombie->getColumn() - zombie->getSpeed() * deltaTime);
        }
    }

    for(Projectile* projectile : projectiles){
        if(projectile != nullptr && projectile->isActive()){

            projectile->update(deltaTime);
        }
    }
    for(unsigned int i = 0; i < rows; i++){
        if(lawnMowers[i] != nullptr && lawnMowers[i]->isActive()){
            lawnMowers[i]->update(deltaTime);
        }
    }
    checkProjectileCollisions();
    checkLawnMowerCollisions();
}

void Board::display()const{

    std::cout << "\n     0 1 2 3 4 5 6\n";

    for(unsigned int row = 0; row < 3; row++){

        std::cout << "Linha " << row << " ";

        for(unsigned int column = 0; column < 7; column++){

            bool hasZombies = false;

            for(Zombie* zombie : zombies){

                if(zombie != nullptr && zombie->isAlive()){
                    if(zombie->getRow() == row && zombie->getColumn() >= column && zombie->getColumn() < column + 1){
                        hasZombies = true;
                        break;

                    }
                }
            }
            if(hasZombies){
                std::cout << "Z ";
                continue;
            }

            if(plants[row][column] != nullptr){
                
                Plant* plant = plants[row][column];

                if(dynamic_cast<Sunflower*>(plant)){
                    std::cout << "S ";

                }else if(dynamic_cast<Peashooter*>(plant)){
                    std::cout << "P ";

                }else if(dynamic_cast<Wall_Nut*>(plant)){
                    std::cout << "W ";

                }else if(dynamic_cast<Potato_Mine*>(plant)){
                    std::cout << "M ";

                } else if(dynamic_cast<Cabbage_Pult*>(plant)){
                    std::cout << "C ";

                }else{
                    std::cout << "? ";
                }
            }else {
                std::cout << ". ";
            }

        }
        std::cout << std::endl;
    }




}