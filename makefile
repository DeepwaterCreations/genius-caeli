all:
	g++ main.cpp OpenGLHelper.cpp GeniusCaeli.cpp -lGL -lGLEW -lglfw -lSOIL -std=c++11 -Wall -g