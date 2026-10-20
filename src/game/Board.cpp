#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

#include <Sunflower.h>
#include <Peashooter.h>
#include <Cabbage_Pult.h>
#include <Wall_Nut.h>
#include <Potato_Mine.h>
#include <Board.h>
#include <Cabbage.h>
#include <Pea.h>

#include <Normal_Zombie.h>
#include <Conehead_Zombie.h>
#include <Gargantuar_Zombie.h>


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

    if(row >= rows || column >= columns){
        throw std::out_of_range("Posição fora dos limites do Tabuleiro!");
    }

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
    delete plants[row][column];

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
            Cabbage* cabbage = dynamic_cast<Cabbage*>(projectile);
            if(cabbage != nullptr){
                if(cabbage->getColumn() >= cabbage->getTargetColumn()){
                    
                    for(Zombie* zombie : zombies)
                    {
                        if(zombie == nullptr || !zombie->isAlive())
                    {
                        continue;
                    }
                    if(zombie->getRow() == cabbage->getRow() && zombie->getColumn() >= cabbage->getTargetColumn() - 0.5 && zombie->getColumn() <= cabbage->getTargetColumn() + 0.5){
                        zombie->takeDamage(cabbage->getDamage());
                        break;
                    }
                    }
                cabbage->deactivate();
                }
            
        }   else{
            for(Zombie* zombie : zombies){
                if(zombie == nullptr || !zombie->isAlive()){
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

            if(mower->isActive() && zombie->getColumn() >= mower->getColumn() - 0.5 && zombie->getColumn() <= mower->getColumn() + 0.5){

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

    for(unsigned int row = 0; row < rows; row++){
        for(unsigned int col = 0; col < columns; col++){
            if(plants[row][col] != nullptr){
                plants[row][col]->update(deltaTime);

                Peashooter* peashooter = dynamic_cast<Peashooter*>(plants[row][col]);
                if(peashooter != nullptr){
                    if(peashooter->getTimerPlant() >= peashooter->getAttackInterval()){
                        
                        addProjectile(new Pea(peashooter->shoot()));

                        peashooter->setTimerPlant(0.0);
                    }
                }
                Cabbage_Pult* cabbagePult = dynamic_cast<Cabbage_Pult*>(plants[row][col]);
                if(cabbagePult != nullptr){
                    if(cabbagePult->getTimerPlant() >= cabbagePult->getAttackInterval()){
                        Zombie* target = nullptr;

                        for(Zombie* zombie : zombies){
                            if(zombie == nullptr || !zombie->isAlive()){
                                continue;
                            }
                            if(zombie->getRow() != row){
                                continue;
                            }
                            double distance = zombie->getColumn() - col;

                            if(distance >= 0 && distance <= cabbagePult->getRange()){
                                if(target == nullptr || zombie->getColumn() < target->getColumn()){
                                    target = zombie;
                                }
                            }
                        }
                        if(target != nullptr){
                            addProjectile(new Cabbage(cabbagePult->shoot(target->getColumn())));
                        }
                    }
                }
                
            }
        }
    }

        for(Zombie* zombie : zombies){
            if(zombie != nullptr && zombie->isAlive()){

                zombie->update(deltaTime);

                unsigned int row = zombie->getRow();
                double column = zombie->getColumn();

                bool attacking = false;

                if(row < rows && column >= 0 && column < columns){
                    unsigned int col = static_cast<unsigned int>(column);

                    if(plants[row][col] != nullptr){

                        Potato_Mine* mine = dynamic_cast<Potato_Mine*>(plants[row][col]);
                        if(mine != nullptr && mine->isArmed()){
                            zombie->takeDamage(mine->getDamamge());
                            removePlant(row, col);
                            attacking = true;

                        }   else{
                            zombie->attack(*plants[row][col]);

                                if(!plants[row][col]->isAlive()){
                                removePlant(row, col);
                                }
                            
                                attacking = true;
                            }
                        }
                        
                        
                        
                }
                if(!attacking){
                    zombie->setColumn(zombie->getColumn() - zombie->getSpeed() * deltaTime);
                    
                }

                
            }
        }

    for(Projectile* projectile : projectiles){
        if(projectile != nullptr && projectile->isActive()){

            projectile->update(deltaTime);

            if(projectile->getColumn() >= columns){
               projectile->deactivate();
            }
        }
    }
    

    for(unsigned int i = 0; i < rows; i++){
        if(lawnMowers[i] != nullptr && lawnMowers[i]->isActive()){
            lawnMowers[i]->update(deltaTime);
        }
    }
    checkProjectileCollisions();
    checkLawnMowerCollisions();


    zombies.erase(
        std::remove_if(zombies.begin(), zombies.end(), [](Zombie* zombie)-> bool{
        
            if(zombie == nullptr){
            return true;
        }
        
            if(!zombie->isAlive()){
            delete zombie;
            return true;
        }
        return false;
    }
),
    zombies.end()








);
}    

void Board::display()const{

    std::cout << "\n             0 1 2 3 4 5 6\n";

    for(unsigned int row = 0; row < 3; row++){

        std::cout << "Linha " << row << " ";

        if(lawnMowers[row] != nullptr && !lawnMowers[row]->isUsed()){
            std::cout << "LM ";

        }   else{
            std::cout << "-- ";
        }

        for(unsigned int column = 0; column < 7; column++){

            LawnMower* mower = lawnMowers[row];
            if(mower != nullptr && mower->isActive()){
                if(static_cast<unsigned int>(mower->getColumn()) == column){

                    std::cout << "LM";
                    continue;
                }
            }


            char zombieSymbol = ' ';

            for(Zombie* zombie : zombies){
                if(zombie != nullptr && zombie->isAlive()){
                    if(zombie->getRow() == row && zombie->getColumn() >= column && zombie->getColumn() < column + 1){
                        if(dynamic_cast<Gargantuar_Zombie*>(zombie) != nullptr){
                            zombieSymbol = 'G';
                        }   else if(dynamic_cast<Conehead_Zombie*>(zombie) != nullptr){
                            zombieSymbol = 'C';

                        }   else{
                            zombieSymbol = 'Z';
                        }
                        break;
                    }
                }
            }
            if(zombieSymbol != ' '){
                std::cout << zombieSymbol << " ";
                continue;
            }
            
            char projectileSymbol = ' ';

            for(Projectile* projectile : projectiles){


                if(projectile != nullptr && projectile->isActive()){
                    if(projectile->getRow() == row && projectile->getColumn() >= column && projectile->getColumn() < column + 1){
                        if(dynamic_cast<Cabbage*>(projectile) != nullptr){
                            projectileSymbol = 'O';
                        }   else{
                            projectileSymbol = 'o';
                        }
                        break;
                    }
                }
            }    




            if(projectileSymbol != ' '){
                std::cout << projectileSymbol << " ";
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

                    }else if(Potato_Mine* mine = dynamic_cast<Potato_Mine*>(plant)){
                        if(mine->isArmed()){
                            std::cout << "M ";
                        }   else{
                            std::cout << "m ";
                        }


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

unsigned int Board::collectSun(){
    unsigned int totalSun = 0;

    for(unsigned int row = 0; row < rows; row++){
        for(unsigned int col = 0; col < columns; col++){
            Sunflower* sunflower = dynamic_cast<Sunflower*>(plants[row][col]);
            if(sunflower != nullptr){
                totalSun += sunflower->produceSun();

            }
        }
    }
    return totalSun;
}