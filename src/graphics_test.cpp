#include <vector>
#include <algorithm>
#include <iostream>

#include <SFML/Graphics.hpp>


struct CabbageData {
        float x;
        float y;
        float startX;
        float startY;
        float targetX;
        int row;
};

struct PeaData {
        float x;
        float y;
};

enum class GameState {
        Playing,
        Won, 
        Lost

};

struct LawnMowerData{
        float x;
        int row;
        bool active = false;
        bool used = false;

    
};
enum class ZombieType { 
        Normal,
        ConeHead,
        Gargantuar
};

struct ZombieData {
        float x;
        int row;
        float health;
        ZombieType type;

        float coneHealth = 0.0f;
        float attackTimer = 0.0f;
};

    int main(){

        sf::RenderWindow window(sf::VideoMode({800, 600}), "Plants vs Zombies");
        window.setVisible(true);
        window.requestFocus();
        


        std::cout << "Janela criada" << std::endl;

        const int rows = 3;
        const int columns = 7;

        const float cellSize = 90.0f;
        const float startX = 85.0f;
        const float startY = 150.0f;
        int plants[3][7] = {};
        float plantsHealth[3][7] = {};
        float sunflowerTimer[3][7] = {};
        float sunflowerGlow[3][7] = {};
        float potatoTimer[3][7] = {};
        int selectedPlant = 1;
        int suns = 150;
        const int plantCosts[6] = {0, 50, 100, 50, 100, 25};
        int currentWave = 1;
        GameState gameState = GameState::Playing;
        const int maxWaves = 10;
        std::vector<ZombieData> zombies = {{startX + 6 * cellSize + 20.0f, 0, 270.0f, ZombieType::Normal}, {startX + 6 * cellSize + 20.0f, 1, 270.0f, ZombieType::ConeHead, 370.0f}, {startX + 6 * cellSize + 20.0f, 2, 3000.0f, ZombieType::Gargantuar}};

        std::vector<PeaData> peas;
        std::vector<CabbageData> cabbages;
        std::vector<LawnMowerData> lawnMowers;
        for(int row = 0; row < rows; row++){
            lawnMowers.push_back({startX - 65.0f, row, false, false});
        }

        float cabbageTimer[3][7] = {};
        float shootTimer[3][7] = {};
        sf::Clock clock;
        sf::Font font;

        if(!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")){
        
            return 1;
        }
        
        while(window.isOpen()){
            float deltaTime = clock.restart().asSeconds();
            if(gameState != GameState::Playing){
                deltaTime = 0.0f;
            }
            for(int row = 0; row < rows; row++){
                for(int column = 0; column < columns; column++){
                    if(plants[row][column] == 5){
                        if(potatoTimer[row][column] < 14.0f){
                            potatoTimer[row][column] += deltaTime;

                        }
                    }   else{
                        potatoTimer[row][column] = 0.0f;
                    }
                }
            }
            for(int row = 0; row < 3; row++){
                for(int column = 0; column < 7; column++){
                    if(sunflowerGlow[row][column] > 0.0f){
                        sunflowerGlow[row][column] -= deltaTime;
                    }
                    if(plants[row][column] == 1){
                        sunflowerTimer[row][column] += deltaTime;
                        if(sunflowerTimer[row][column] >= 12.0f){
                            suns += 50;
                            sunflowerTimer[row][column] -= 12.0f;
                            sunflowerGlow[row][column] = 0.5f;
                        }
                    }   else{
                        sunflowerTimer[row][column] = 0.0f;
                    }
                }
            }
            for(int row = 0; row < rows; row++){
                for(int column = 0; column < columns; column++){
                    if(plants[row][column] == 2){
                        shootTimer[row][column] += deltaTime;
                        if(shootTimer[row][column] >= 1.5f){
                            peas.push_back({startX + column * cellSize + 65.0f, startY + row * cellSize + 35.0f});
                            shootTimer[row][column] -= 1.5f;
                        }
                    }
                }
            }
            for(int row = 0; row < rows; row++){
                for(int column = 0; column < columns; column ++){
                    if(plants[row][column] == 4){
                        cabbageTimer[row][column] += deltaTime;
                        if(cabbageTimer[row][column] >= 3.0f){
                            float x = startX + column * cellSize + 65.0f;
                            float y = startY + row * cellSize + 35.0f;

                            cabbages.push_back({x, y, x, y, x + 2 * cellSize - 20.0f, row});
                            cabbageTimer[row][column] -= 3.0f;

                        }
                    }   else{
                        cabbageTimer[row][column] = 0.0f;
                    }
                }
            }
            for(auto& pea : peas){
                pea.x += 200.0f * deltaTime;
            } 
            for(auto& cabbage : cabbages){
                cabbage.x += 200.0f * deltaTime;
                float distance = cabbage.targetX - cabbage.startX;
                float progress = (cabbage.x - cabbage.startX) / distance;

                if(progress > 1.0f){
                    progress = 1.0f;
                }
                cabbage.y = cabbage.startY - 100.0f * 4.0f * progress * (1.0f - progress);
            }
            for(auto& cabbage : cabbages){
                if(cabbage.x >= cabbage.targetX){
                    for(auto& zombie : zombies){
                        if(zombie.health <= 0 || zombie.row != cabbage.row){
                            continue;
                        }
                        if(cabbage.x + 28.0f >= zombie.x && cabbage.x <= zombie.x + 50.0f){
                            zombie.health -= 40.0f;
                            break;
                        }
                    }
                }
            }
            cabbages.erase(std::remove_if(cabbages.begin(), cabbages.end(), [] (const CabbageData& cabbage){
                return cabbage.x >= cabbage.targetX;
            }),
            cabbages.end()
        );
            for(auto& pea : peas){
                for(auto& zombie : zombies){
                    float zombieY = startY + zombie.row * cellSize + 10.0f;
                        if(zombie.health > 0 && pea.y + 22.0f > zombieY && pea.y < zombieY + 70.0f && pea.x + 22.0f >= zombie.x && pea.x <= zombie.x + 50.0f){
                            zombie.health -= 50.0f;
                            pea.x = 900.0f;
                            break;
                        }
                }
            }
            peas.erase(std::remove_if(peas.begin(), peas.end(), [](const PeaData& pea){
                return pea.x > 800.0f;

            }),
            peas.end()
        );

            for(auto& zombie : zombies){
                if(zombie.health > 0){
                    for(int column = 0; column < columns; column++){
                        if(plants[zombie.row][column] == 5 && potatoTimer[zombie.row][column] >= 14.0f){
                             float potatoX = startX + column * cellSize;
                             if(zombie.x < potatoX + cellSize && zombie.x + 50.0f > potatoX){
                                zombie.health -= 1000.0f;

                                plants[zombie.row][column] = 0;
                                plantsHealth[zombie.row][column] = 0.0f;
                                potatoTimer[zombie.row][column] = 0.0f;

                                break;
                             }
                        }
                    }
                    if(zombie.health <= 0){
                        continue;

                    }
                
                int zombieColumn = (zombie.x - startX) / cellSize;
                if(zombieColumn >= 0 && zombieColumn < columns){
                    if(plants[zombie.row][zombieColumn] == 0){
                        zombie.x -= 30.f * deltaTime;
                    }   else{
                        plantsHealth[zombie.row][zombieColumn] -= 100.0f * deltaTime;
                        if(plantsHealth[zombie.row][zombieColumn] <= 0){
                            plantsHealth[zombie.row][zombieColumn] = 0;
                            plants[zombie.row][zombieColumn] = 0;
                        }
                        }
                    }   else{   
                        zombie.x -= 30.0f * deltaTime;
                        }
                }   
            }
            if(gameState == GameState::Playing){
                for(const auto& zombie : zombies){
                    if(zombie.health > 0.0f && zombie.x <= startX - 50.0f){
                        gameState = GameState::Lost;
                        break;
                    }
                }
            }
            while(const auto event = window.pollEvent()){
                if(event->is<sf::Event::Closed>()){
                    window.close();
                }
                if(const auto* key = event->getIf<sf::Event::KeyPressed>()){
                    if(key->code == sf::Keyboard::Key::Num1){
                        selectedPlant = 1;
                    }   else if(key->code == sf::Keyboard::Key::Num2){
                        selectedPlant = 2;
                    }   else if(key->code == sf::Keyboard::Key::Num3){
                        selectedPlant = 3;
                    }   else if(key->code == sf::Keyboard::Key::Num4){
                        selectedPlant = 4;
                    }   else if(key->code == sf::Keyboard::Key::Num5){
                        selectedPlant = 5;
                    }
                    if(key->code == sf::Keyboard::Key::V){
                        gameState = GameState::Won;
                    }
                    if(key->code == sf::Keyboard::Key::L){
                        gameState = GameState::Lost;
                    }
                    if(key->code == sf::Keyboard::Key::Escape){
                        window.close();
                    }
                }

                if(const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()){
                    if(mouse->button == sf::Mouse::Button::Left && gameState == GameState::Playing){
                        int column = (mouse->position.x - startX) / cellSize;
                        int row = (mouse->position.y - startY) / cellSize;
                        if(mouse->position.x >= startX && mouse->position.y >= startY && column >= 0 && column < columns && row >= 0 && row < rows){
                            if(plants[row][column] == 0 && suns >= plantCosts[selectedPlant]){
                                plants[row][column] = selectedPlant;
                                suns -= plantCosts[selectedPlant];

                                if(selectedPlant == 3){
                                    plantsHealth[row][column] = 4000.0f;

                                }   else{
                                    plantsHealth[row][column] = 300.0f;
                                }
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color(34, 100, 34));
            sf::RectangleShape panel({800.0f, 100.0f});
            panel.setFillColor(sf::Color(25, 70, 35));
            panel.setPosition({0.0f, 0.0f});
            window.draw(panel);
            
            sf::Text sunText(font, std::to_string(suns), 28);
            sunText.setFillColor(sf::Color::Yellow);
            sunText.setPosition({90.0f, 30.0f});
            window.draw(sunText);

            sf::Text waveText(font, "Wave " + std::to_string(currentWave) + "/" + std::to_string(maxWaves), 26);
            waveText.setFillColor(sf::Color::White);
            waveText.setPosition({550.0f, 30.0f});
            window.draw(waveText);

            for(int row = 0; row < rows; row++){
                for(int column = 0; column < columns; column++){

                    sf::RectangleShape cell({cellSize - 2, cellSize - 2});

                    cell.setPosition({startX + column * cellSize, startY + row * cellSize});

                    if((row + column) % 2 == 0){
                        cell.setFillColor(sf::Color(100, 180, 80));

                    }   else{
                        cell.setFillColor(sf::Color(80, 160, 65));

                    }
                    window.draw(cell);
                }
            }
            
        for(int row = 0; row < rows; row++){

            for(int column = 0; column < columns; column++){

                if(plants[row][column]){

                    sf::CircleShape plant(30.0f);
                    

                    if(plants[row][column] == 1){
                        plant.setPointCount(8);
                        plant.setFillColor(sf::Color(160, 90, 30));
                        plant.setOutlineColor(sf::Color(255, 210, 40));
                        plant.setOutlineThickness(12.0f);

                        if(sunflowerGlow[row][column] > 0.0f){
                            plant.setOutlineThickness(15.0f);
                            plant.setOutlineColor(sf::Color(255, 255, 150));
                        }

                    }   else if(plants[row][column] == 2){
                        plant.setFillColor(sf::Color(80, 190, 65));
                        plant.setOutlineColor(sf::Color(35, 110, 35));
                        plant.setOutlineThickness(2.0f);

                    }   else if(plants[row][column] == 3){
                        plant.setFillColor(sf::Color(180, 110, 55));
                        plant.setOutlineColor(sf::Color(100, 55, 25));
                        plant.setOutlineThickness(3.0f);
                        plant.setScale({0.85f, 1.15f});




                    }   else if(plants[row][column] == 4){
                        plant.setFillColor(sf::Color(100, 165, 55));
                        plant.setOutlineColor(sf::Color(45, 100, 35));
                        plant.setOutlineThickness(3.0f);
                    }   else if(plants[row][column] == 5){
                        if(potatoTimer[row][column] >= 14.0f){
                            plant.setFillColor(sf::Color::Red);
                        }   else{
                            plant.setFillColor(sf::Color(139, 69, 19));
                        }
                        
                    }

                    if(plantsHealth[row][column] <= 100.0f){
                        plant.setFillColor(sf::Color(100, 100, 100));
                    }
                    plant.setPosition({
                        startX + column * cellSize + 15.0f,
                        startY + row * cellSize + 15.0f
                    });

                if(plants[row][column] != 5){
                        window.draw(plant);
                }
                if(plants[row][column] == 1){
                    
                    float x = startX + column * cellSize;
                    float y = startY + row * cellSize;

                    sf::RectangleShape stem({9.0f, 24.0f});
                    stem.setFillColor(sf::Color(45, 135, 45));
                    stem.setPosition({x + 40.0f, y + 57.0f});
                    window.draw(stem);

                    sf::CircleShape leftLeaf(12.0f, 3);
                    leftLeaf.setFillColor(sf::Color(50, 160, 45));
                    leftLeaf.setRotation(sf::degrees(-35.0f));
                    leftLeaf.setPosition({x + 22.0f, y + 65.0f});
                    window.draw(leftLeaf);

                    sf::CircleShape rightLeaf(12.0f, 3);
                    rightLeaf.setFillColor(sf::Color(50, 160, 45));
                    rightLeaf.setRotation(sf::degrees(35.0f));
                    rightLeaf.setPosition({x + 48.0f, y + 65.0f});
                    window.draw(rightLeaf);

                    sf::CircleShape leftEye(4.0f);
                    leftEye.setFillColor(sf::Color(35, 25, 15));
                    leftEye.setPosition({x + 30.0f, y + 37.0f});
                    window.draw(leftEye);
                    
                    
                    sf::CircleShape rightEye(4.0f);
                    rightEye.setFillColor(sf::Color(35, 25, 15));
                    rightEye.setPosition({x + 52.0f, y + 37.0f});
                    window.draw(rightEye);

                    sf::CircleShape smile(9.0f);
                    smile.setScale({1.2f, 0.55f});
                    smile.setFillColor(sf::Color(85, 45, 20));
                    smile.setPosition({x + 34.0f, y + 47.0f});
                    window.draw(smile);

                    sf::RectangleShape smileCover({24.0f, 6.0f});
                    smileCover.setFillColor(sf::Color(160, 90, 30));
                    smileCover.setPosition({x + 34.0f, y + 47.0f});
                    window.draw(smileCover);

                }

                if(plants[row][column] == 3){
                    float x = startX + column * cellSize;
                    float y = startY + row * cellSize;

                    sf::CircleShape leftEye(5.0f);
                    leftEye.setFillColor(sf::Color::Black);
                    leftEye.setPosition({x + 31.0f, y + 35.0f});
                    window.draw(leftEye);

                    sf::CircleShape rightEye(5.0f);
                    rightEye.setFillColor(sf::Color::Black);
                    rightEye.setPosition({x + 51.0f, y + 35.0f});
                    window.draw(rightEye);

                    if(plantsHealth[row][column] <= 300.0f){
                        sf::CircleShape mouth(7.0f);
                        mouth.setScale({0.8f, 1.3f});
                        mouth.setFillColor(sf::Color(70, 35, 20));
                        mouth.setPosition({x + 38.0f, y + 54.0f});
                        window.draw(mouth);

                    }   else{
                        
                            sf::RectangleShape mouth({14.0f, 3.0f});
                            mouth.setFillColor(sf::Color(90, 45, 25));
                            mouth.setPosition({x + 38.0f, y + 58.0f});
                            window.draw(mouth);
                        }
                }
                if(plants[row][column] == 2){
                    float x = startX + column * cellSize;
                    float y = startY + row * cellSize;

                    sf::RectangleShape stem({10.0f, 25.0f});
                    stem.setFillColor(sf::Color(40, 125, 35));
                    stem.setPosition({x + 40.0f, y + 55.0f});
                    window.draw(stem);

                    sf::CircleShape leftLeaf(12.0f, 3);
                    leftLeaf.setFillColor(sf::Color(50, 155, 45));
                    leftLeaf.setRotation(sf::degrees(-35.0f));
                    leftLeaf.setPosition({x + 22.0f, y + 65.0f});
                    window.draw(leftLeaf);

                    sf::CircleShape rightLeaf(12.0f, 3);
                    rightLeaf.setFillColor(sf::Color(50, 155, 45));
                    rightLeaf.setRotation(sf::degrees(35.0f));
                    rightLeaf.setPosition({x + 48.0f, y + 65.0f});
                    window.draw(rightLeaf);

                    sf::RectangleShape cannon({30.0f, 22.0f});
                    cannon.setFillColor(sf::Color(65, 160, 50));
                    cannon.setOutlineColor(sf::Color(35, 100, 30));
                    cannon.setOutlineThickness(2.0f);
                    cannon.setPosition({x + 50.0f, y + 32.0f});
                    window.draw(cannon);

                    sf::CircleShape opening(9.0f);
                    opening.setFillColor(sf::Color(25, 85, 25));
                    opening.setPosition({x + 70.0f, y + 32.0f});
                    window.draw(opening);
                }
                if(plants[row][column] == 4){
                    sf::RectangleShape stem({12.0f, 25.0f});
                    stem.setFillColor(sf::Color(50, 120, 40));
                    stem.setPosition({startX + column * cellSize + 39.0f, startY + row * cellSize + 55.0f});
                    window.draw(stem);

                    sf::CircleShape leaf(13.0f, 3);
                    leaf.setFillColor(sf::Color(65, 145, 45));
                    leaf.setRotation(sf::degrees(35.0f));
                    leaf.setPosition({startX + column * cellSize + 48.0f, startY + row * cellSize + 55.0f});
                    window.draw(leaf);
                }
                if(plants[row][column] == 5){
                    float x = startX + column * cellSize;
                    float y = startY + row * cellSize;

                    bool armed  = potatoTimer[row][column] >= 14.0f;

                    sf::CircleShape potato(25.0f);
                    potato.setScale({1.35f, 0.75f});

                    if(armed){
                        potato.setFillColor(sf::Color(200, 75, 45));
                        potato.setScale({1.3f, 0.75f});

                    }   else{
                        potato.setFillColor(sf::Color(160, 100, 55));
                    }

                    potato.setOutlineColor(sf::Color(90, 50, 25));
                    potato.setOutlineThickness(3.0f);
                    potato.setPosition({x + 12.0f, y + 38.0f});
                    window.draw(potato);

                    sf::RectangleShape antenna({5.0f, 20.0f});
                    antenna.setFillColor(sf::Color(75, 75, 75));
                    antenna.setPosition({x + 42.0f, y + 23.0f});
                    window.draw(antenna);

                    sf::CircleShape light(7.0f);
                    if(armed){
                        light.setFillColor(sf::Color::Red);
                    }   else{
                        light.setFillColor(sf::Color(100, 100, 100));
                    }
                    light.setPosition({x + 37.5f, y + 14.0f});
                    window.draw(light);

                    sf::CircleShape leftEye(4.0f);
                    leftEye.setFillColor(sf::Color::Black);
                    leftEye.setPosition({x + 30.0f, y + 51.0f});
                    window.draw(leftEye);

                    
                    sf::CircleShape rightEye(4.0f);
                    rightEye.setFillColor(sf::Color::Black);
                    rightEye.setPosition({x + 51.0f, y + 51.0f});
                    window.draw(rightEye);

                                  
                
                }
            }
            }
        }
        for(const auto& mower : lawnMowers){
            if(mower.used && !mower.active){
                continue;
            }
            float x  = mower.x;
            float y = startY + mower.row * cellSize + 30.0f;

            sf::RectangleShape body({48.0f, 28.0f});
            body.setFillColor(sf::Color(200, 35, 25));
            body.setPosition({x, y});
            window.draw(body);

            sf::RectangleShape engine({25.0f, 25.0f});
            engine.setFillColor(sf::Color(80, 80, 80));
            engine.setPosition({x + 4.0f, y + 20.0f});
            window.draw(engine);

            sf::CircleShape backWheel(9.0f);
            backWheel.setFillColor(sf::Color::Black);
            backWheel.setPosition({x + 4.0f, y + 20.0f});
            window.draw(backWheel);

            sf::CircleShape frontWheel(9.0f);
            frontWheel.setFillColor(sf::Color::Black);
            frontWheel.setPosition({x + 32.0f, y + 20.0f});
            window.draw(frontWheel);

            sf::RectangleShape handle({5.0f, 32.5f});
            handle.setFillColor(sf::Color::Black);
            handle.setRotation(sf::degrees(-25.0f));
            handle.setPosition({x + 5.0f, y - 25.0f});
            window.draw(handle);
        }

        for(const auto& pea : peas){
            sf::CircleShape peaShape(11.0f);
            peaShape.setFillColor(sf::Color(0, 255, 0));
            peaShape.setPosition({pea.x, pea.y});
            window.draw(peaShape);

        }
        for(const auto& cabbage : cabbages){
            sf::CircleShape cabbageShape(14.0f);
            cabbageShape.setFillColor(sf::Color(128, 186, 66));
            cabbageShape.setOutlineColor(sf::Color(53, 107, 41));
            cabbageShape.setOutlineThickness(2.0f);
            cabbageShape.setPosition({cabbage.x, cabbage.y});
            window.draw(cabbageShape);

            sf::CircleShape leaf(8.0f);
            leaf.setFillColor(sf::Color::Transparent);
            leaf.setOutlineColor(sf::Color(65, 125, 50));
            leaf.setOutlineThickness(1.5f);
            leaf.setPosition({cabbage.x + 5.0f, cabbage.y + 5.0f});
            window.draw(leaf);
        }
        
        for(const auto& zombie : zombies){
            if(zombie.health <= 0.0f){
                continue;
            }

            float x = zombie.x;
            float y = startY + zombie.row * cellSize;

            if(zombie.type == ZombieType::Normal || zombie.type == ZombieType::ConeHead){

            sf::RectangleShape leftLeg({10.0f, 24.0f});
            leftLeg.setFillColor(sf::Color(55, 65, 100));
            leftLeg.setPosition({x + 13.0f, y + 60.0f});
            window.draw(leftLeg);

            sf::RectangleShape rightLeg({10.0f, 24.0f});
            rightLeg.setFillColor(sf::Color(55, 65, 100));
            rightLeg.setPosition({x + 30.0f, y + 60.0f});
            window.draw(rightLeg);

            sf::RectangleShape body({35.0f, 35.0f});
            body.setFillColor(sf::Color(100, 75, 60));
            body.setPosition({x + 10.0f, y + 32.0f});
            window.draw(body);

             sf::RectangleShape tie({5.0f, 19.0f});
            tie.setFillColor(sf::Color(170, 35, 35));
            tie.setPosition({x + 26.0f, y + 36.0f});
            window.draw(tie);

            sf::RectangleShape leftArm({12.0f, 30.0f});
            leftArm.setFillColor(sf::Color(105, 150, 105));
            leftArm.setRotation(sf::degrees(65.0f));
            leftArm.setPosition({x + 12.0f, y + 38.0f});
            window.draw(leftArm);   
            
             sf::RectangleShape rightArm({12.0f, 30.0f});
            rightArm.setFillColor(sf::Color(105, 150, 105));
            rightArm.setRotation(sf::degrees(-65.0f));
            rightArm.setPosition({x + 43.0f, y + 38.0f});
            window.draw(rightArm);

            sf::CircleShape head(19.0f);
            head.setScale({1.0f, 1.15f});
            head.setFillColor(sf::Color(125, 170, 115));
            head.setPosition({x + 10.0f, y + 5.0f});
            window.draw(head);

        
            sf::CircleShape leftEye(5.0f);
            leftEye.setFillColor(sf::Color::White);
            leftEye.setPosition({x + 17.0f, y + 18.0f});
            window.draw(leftEye);

            sf::CircleShape rightEye(5.0f);
            rightEye.setFillColor(sf::Color::White);
            rightEye.setPosition({x + 34.0f, y + 18.0f});
            window.draw(rightEye);

            sf::CircleShape pupil(2.0f);
            pupil.setFillColor(sf::Color::Black);
            pupil.setPosition({x + 17.0f, y + 20.0f});
            window.draw(pupil);

            pupil.setPosition({x + 34.0f, y + 20.0f});
            window.draw(pupil);

            sf::RectangleShape mouth({17.0f, 5.0f});
            mouth.setFillColor(sf::Color(55, 45, 40));
            mouth.setPosition({x + 23.0f, y + 36.0f});
            window.draw(mouth);


            if(zombie.type == ZombieType::ConeHead &&
            zombie.coneHealth > 0.0f){

                sf::CircleShape cone(23.0f, 3);
                cone.setFillColor(sf::Color(245, 125, 25));
                cone.setOutlineColor(sf::Color(180, 75, 10));
                cone.setOutlineThickness(2.0f);
                cone.setPosition({x + 8.0f, y - 28.0f});
                window.draw(cone);

                sf::RectangleShape stripe({32.0f, 5.0f});
                stripe.setFillColor(sf::Color::White);
                stripe.setPosition({x + 15.0f, y + 4.0f});
                window.draw(stripe);
            }
        }   else if(zombie.type == ZombieType::Gargantuar){

                sf::RectangleShape leftLeg({19.0f, 30.0f});
                leftLeg.setFillColor(sf::Color(65, 65, 85));
                leftLeg.setPosition({x + 5.0f, y + 55.0f});
                window.draw(leftLeg);

                sf::RectangleShape rightLeg({19.0f, 30.0f});
                rightLeg.setFillColor(sf::Color(65, 65, 85));
                rightLeg.setPosition({x + 35.0f, y + 55.0f});
                window.draw(rightLeg);

                sf::RectangleShape body({58.0f, 48.0f});
                body.setFillColor(sf::Color(85, 95, 85));
                body.setPosition({x, y + 22.0f});
                window.draw(body);

                sf::CircleShape head(24.0f);
                head.setFillColor(sf::Color(115, 145, 110));
                head.setPosition({x + 5.0f, y - 15.0f});
                window.draw(head);

                sf::CircleShape leftEye(5.0f);
                leftEye.setFillColor(sf::Color(235, 220, 170));
                leftEye.setPosition({x + 16.0f, y + 1.0f});
                window.draw(leftEye);

                sf::CircleShape rightEye(5.0f);
                rightEye.setFillColor(sf::Color(235, 220, 170));
                rightEye.setPosition({x + 39.0f, y + 1.0f});
                window.draw(rightEye);

                sf::RectangleShape mouth({25.0f, 8.0f});
                mouth.setFillColor(sf::Color(45, 35, 35));
                mouth.setPosition({x + 17.0f, y + 23.0f});
                window.draw(mouth);

                sf::RectangleShape arm({18.0f, 45.0f});
                arm.setFillColor(sf::Color(115, 145, 110));
                arm.setRotation(sf::degrees(-35.0f));
                arm.setPosition({x + 50.0f, y + 28.0f});
                window.draw(arm);

                sf::RectangleShape club({13.0f, 65.0f});
                club.setFillColor(sf::Color(105, 65, 35));
                club.setOutlineColor(sf::Color(65, 40, 25));
                club.setOutlineThickness(2.0f);
                club.setRotation(sf::degrees(25.0f));
                club.setPosition({x + 70.0f, y - 25.0f});
                window.draw(club);
            
                    }
                    
                }
                
                if(gameState != GameState::Playing){
                    sf::RectangleShape overlay({800.0f, 600.0f});
                    overlay.setFillColor(sf::Color(0, 0, 0, 210));
                    overlay.setPosition({0.0f, 0.0f});
                    window.draw(overlay);

                    std::string message;
                    sf::Color messageColor;
                    if(gameState == GameState::Won){
                        message = "VOCE VENCEU!";
                        messageColor = sf::Color(255, 220, 70);

                    }   else{
                        message = "VOCE PERDEU!";
                        messageColor = sf::Color(255, 90, 90);
                    }

                    sf::Text resultText(font, message, 58);
                    resultText.setFillColor(messageColor);
                    resultText.setStyle(sf::Text::Bold);

                    sf::FloatRect bounds = resultText.getLocalBounds();
                    resultText.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});

                    resultText.setPosition({400.0f, 270.0f});
                    window.draw(resultText);

                    sf::Text exitText(font, "Pressione ESC para sair", 23);
                    exitText.setFillColor(sf::Color::White);
                    sf::FloatRect exitBounds = exitText.getLocalBounds();

                    exitText.setOrigin({exitBounds.position.x + exitBounds.size.x / 2.0f, exitBounds.position.y + exitBounds.size.y / 2.0f});
                    window.draw(exitText);

                }
            window.display();
        }









        return 0;
    }
    