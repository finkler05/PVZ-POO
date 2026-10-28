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

GRAPHICS_TARGET = pvz_graphics

GRAPHICS_SOURCES = $(filter-out src/main.cpp,$(SOURCES)) src/graphics_test.cpp

SFML_CFLAGS = -DSFML_STATIC $(shell PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config --cflags sfml-graphics)

SFML_LIBS = /usr/local/lib/libsfml-graphics-s.a /usr/local/lib/libsfml-window-s.a /usr/local/lib/libsfml-system-s.a $(shell PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config --libs --static sfml-graphics | sed 's/-lsfml-graphics//g; s/-lsfml-window//g; s/-lsfml-system//g')
SFML_LIBS += -lX11 -lXrandr -lXcursor -lXi -ludev

.PHONY: compile run clean

compile:
			
			$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)



clean:
			rm -f $(TARGET)


run:

			./$(TARGET)

graphics:

			$(CXX) $(CXXFLAGS) $(INCLUDES) $(GRAPHICS_SOURCES) $(SMFL_CFLAGS) -o $(GRAPHICS_TARGET) $(SFML_LIBS)



run-graphics:
			./$(GRAPHICS_TARGET)