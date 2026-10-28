CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O0 -g
INCLUDES = 	-Iinclude \
			-Iinclude/plants \
			-Iinclude/zombies \
			-Iinclude/projectiles \
			-Iinclude/game \
			-Iinclude/enum

TARGET = pvz
SOURCES = 	src/main.cpp \
			src/zombies/Zombie.cpp \
			src/zombies/Normal_Zombie.cpp \
			src/zombies/Conehead_Zombie.cpp \
			src/zombies/Gargantuar_Zombie.cpp \
			src/projectiles/Projectile.cpp \
			src/plants/Plant.cpp \
			src/projectiles/Pea.cpp \
			src/plants/Peashooter.cpp \
			src/projectiles/Cabbage.cpp \
			src/plants/Cabbage_Pult.cpp \
			src/plants/Wall_Nut.cpp \
			src/plants/Sunflower.cpp \
			src/plants/Potato_Mine.cpp \
			src/game/Board.cpp \
			src/game/LawnMower.cpp \
			src/game/Game.cpp 
			
.PHONY: compile run clean

compile:
			
			$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)



clean:
			rm -f $(TARGET)


run:

			./$(TARGET)