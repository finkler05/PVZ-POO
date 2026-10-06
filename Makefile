CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
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
			src/projectiles/Pea.cpp \
			src/plants/Plant.cpp

		  	# src/game/Game.cpp \
		  	# src/game/Board.cpp \
		  	# src/game/LawnMower.cpp \ 
		  	# src/plants/Sunflower.cpp \
		  	# src/plants/Peashooter.cpp \
		  	# src/plants/Wallnut.cpp \
		  	# src/plants/Cabbage_Pult.cpp \
		  	# src/plants/Potato_Mine.cpp \

		  	#src/projectiles/Cabbage.cpp \

			
			
			
			
			
compile:
			$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)



clean:
		

run: