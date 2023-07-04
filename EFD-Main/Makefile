source_path = ./src/source/
files = main.cpp ${source_path}/Map.cpp
all:
	g++ -std=c++11 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -I ./include/raylib.h ./lib/libraylib.a ./src/${files} -o ./build/Game
	./build/Game

