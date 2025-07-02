CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++17
LDFLAGS = -Llib -lraylib -lwinmm -lgdi32 -lopengl32

ADDITIONAL_PROJECTILES = projectiles/Projectile.cpp projectiles/BasicProjectile.cpp projectiles/ExplosiveProjectile.cpp
ADDITIONAL_ENEMIES = enemies/DiveBomber.cpp enemies/Enemy.cpp enemies/DogFighter.cpp enemies/Bomber.cpp enemies/HeavyFighter.cpp

SRC = main.cpp Player.cpp $(ADDITIONAL_PROJECTILES) $(ADDITIONAL_ENEMIES)
OBJ = $(SRC:.cpp=.o)

TARGET = spacefighters.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o *.exe 2>nul || exit 0