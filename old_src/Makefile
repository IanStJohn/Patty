CXX = g++ -std=c++17
LDFLAGS =  -LC:/Libraries/SDL2-2.0.12_mingw/lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -LC:/Libraries/glew-2.1.0/lib -lglew32 -lglu32 -lopengl32
CXXFLAGS = -IC:/Libraries/SDL2-2.0.12_mingw/include/ -IC:/Libraries/glew-2.1.0/include/ -IC:/Libraries/glm/ -IC:/Libraries/mathtool/ -IC:/Libraries/dirent/

SRC = main.cpp Game.cpp Object.cpp Mesh.cpp Model.cpp Scene.cpp Time.cpp Input.cpp Camera.cpp Player.cpp Coin.cpp
OBJ = $(SRC:.cc=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -g -o $@ $(OBJ) $(LDFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC)