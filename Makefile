CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++17
LDFLAGS = -Llib -lraylib -lwinmm -lgdi32 -lopengl32

SRC = main.cpp Player.cpp Projectile.cpp enemies/DiveBomber.cpp enemies/Enemy.cpp enemies/DogFighter.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = spacefighters.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o *.exe 2>nul || exit 0