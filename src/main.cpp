#include <iostream>
#include <cstdlib>
#include <ctime> // Funções utilitárias (srand() e rand())
#include <chrono> // Medir intervalos de tempo (calcular deltaTime)
#include <thread> // Atualizar o jogo e receber comandos
#include <functional> // Ferramentas para funções e referencias (std::ref(game))
#include <mutex> // Sincronizar acesso a dados compartilhados (Proteger o objeto(game))
#include <atomic> // Variaveis com operações atomicas (inputRunning)


#include <Game.h>






PlantType choosePlant(int choice){


    switch(choice){

        case 1: 
            return PlantType::SUNFLOWER;
    
        case 2: 
            return PlantType::PEASHOOTER;
            
        case 3:
            return PlantType::WALL_NUT;

        case 4:
            return PlantType::CABBAGE_PULT;
            
        case 5: 
            return PlantType::POTATO_MINE;        

        default: 
            return PlantType::SUNFLOWER;   
    } 
}

std::mutex gameMutex;
std::atomic<bool> inputRunning{true};
std::atomic<bool> playerTyping{false};



bool gameIsRunning(Game& game){

    std::lock_guard<std::mutex> lock(gameMutex);

    return !game.isGameOver() && !game.hasWon();
}

void playerTurn(Game& game){

    while(inputRunning && gameIsRunning(game)){
        int choice;
        unsigned int row, column;
        playerTyping = true;

        std::cout << "Selecione uma planta desejada: " << std::endl;
        std::cout << "1 = Sunflower / 2 = Peashooter / 3 = Wall-Nut / 4 = Cabbage-Pult / 5 = Potato Mine" << std::endl;
        if(!(std::cin >> choice)){
            break;
            
        } // Verifica e encerra o while, para caso entrada inválida.

        if(choice == 0){
            break;
        }

        if(!inputRunning || !gameIsRunning(game)){
            break;
        }

        PlantType selectedPlant = choosePlant(choice);

        std::cout << "Selecione a linha onde deseja plantar: " << std::endl;
        if(!(std::cin >> row)){
            break;
        }
        if(!inputRunning || !gameIsRunning(game)){
            break;
        }

        std::cout << "Selecione a coluna onde deseja plantar: " << std::endl;
        if(!(std::cin >> column)){
            break;
        }
        if(!inputRunning || !gameIsRunning(game)){
            break;
        }

    
        {std::lock_guard<std::mutex> lock(gameMutex);
            if(!game.isGameOver() && !game.hasWon()){
                game.buyPlant(selectedPlant, row, column);
            }
        }
        playerTyping = true;
    }
}

void renderGame(Game& game){
    std::lock_guard<std::mutex> lock(gameMutex);

    std::cout << "\033[s";
    std::cout << "\033[H";

    for(int i = 0; i < 8; i++){
        std::cout << "\033[2K";
        if(i < 7){
            std::cout << "\033[1B";

        }
    }
    std::cout << "\033[H";

    game.display();
    std::cout << "\033[u";
    std::cout.flush();
}







int main(){

    srand(time(nullptr));

    Game game;

    game.startWave();

    std::cout << "\033[2J\033[H";
    for(int i = 0; i < 8; i++){
        std::cout << std::endl;
    }

    std::cout << "Jogo Iniciado!" << std::endl;
    std::cout << "Sois Restantes: " << game.getSun() << std::endl;

    renderGame(game);
    std::thread inputThread(playerTurn, std::ref(game));

    

    auto lastTime = std::chrono::steady_clock::now();

    double displayTimer = 0.0;

    while(gameIsRunning(game)){

        auto currentTime = std::chrono::steady_clock::now();

        double deltaTime = std::chrono::duration<double>(currentTime - lastTime).count();

        lastTime = currentTime;

        {std::lock_guard<std::mutex> lock(gameMutex);

        game.update(deltaTime);
        displayTimer += deltaTime;

        if(displayTimer >= 1.0 && !playerTyping.load()){

            renderGame(game);

            displayTimer = 0.0;
        }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    inputRunning = false;

    std::cout << "\nJogo Encerrado!" << std::endl;
    std::cout << "Se houver uma pergunta pendente, digite um numero e pressione Enter para finalizar." << std::endl;

    if(inputThread.joinable()){

        inputThread.join();

    }
        if(game.hasWon()){
            std::cout << "Você venceu!" << std::endl;

        }   else{
            std::cout << "Você perdeu!" << std::endl;
        }


        










    
    return 0;
}