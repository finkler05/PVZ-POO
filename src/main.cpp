#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include <Game.h>

PlantType choosePlant(choice){


    switch(choice){

        case 1: 
            return PlantType::Sunflower;
    
        case 2: 
            return PlantType::Peashooter;
            
        case 3:
            return PlantType::Wall_Nut;

        case 4:
            return PlantType::Cabbage_Pult;
            
        case 5: 
            return PlantType::Potato_Mine;        

        default: 
            return PlantType::Sunflower;   
    } 
}


int main(){

    srand(time(nullptr));

    Game game;

    game.startWave();

    game.buyPlant(PlantType::SUNFLOWER, 0 , 0);

    std::cout << "Jogo Iniciado!" << std::endl;

    std::cout << "Sois Restantes: " << game.getSun() << std::endl;

    

    auto lastTime =std::chrono::steady_clock::now();

    while(!game.isGameOver() && !game.hasWon()){

        auto currentTime = std::chrono::steady_clock::now();

        double deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();

        lastTime = currentTime;

        game.update(deltaTime);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
        if(game.hasWon()){
            std::cout << "Você venceu!" << std::endl;

        }   else{
            std::cout << "Você perdeu!" << std::endl;
        }


        










    
    return 0;
}