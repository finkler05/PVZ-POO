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
            if(mower->isUsed() && zombie->getColumn() <= 0.0){

                mower->activate();

            }
            if(mower->isActive() && mower->getColumn() >= zombie->getColumn()){

                mower->hitZombie(*zombie);

            }
        }
    }

}

bool Board::hasZombies(){

    return !zombies.empty();
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