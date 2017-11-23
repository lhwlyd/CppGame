CXX=g++
CXXFLAGS=-g -std=c++11 -Wall 
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
#BIN=prog

#SRC=$(wildcard *.cpp)
#OBJ=$(SRC:%.cpp=%.o)

pang.o: Game.h Game.cpp stdafx.h stdafx.cpp
	g++ -c pang.cpp

SplashScreen.o: SplashScreen.h SplashScreen.cpp stdafx.h stdafx.cpp
	g++ -c SplashScreen.cpp

MainMenu.o: MainMenu.h MainMenu.cpp
	g++ -c MainMenu.cpp

VisibleGameObject.o: stdafx.h stdafx.cpp
	g++ -c VisibleGameObject.cpp

PlayerPaddle.o: VisibleGameObject.o
	g++ -c PlayerPaddle.cpp

GameObjectManager.o: GameObjectManager.h GameObjectManager.cpp
	g++ -c GameObjectManager.cpp

GameBall.o: GameBall.h GameBall.cpp
	g++ -c GameBall.cpp

play: pang.o Game.o stdafx.o MainMenu.o SplashScreen.o PlayerPaddle.o GameObjectManager.o GameBall.o
	$(CXX) pang.o Game.o stdafx.o MainMenu.o SplashScreen.o PlayerPaddle.o VisibleGameObject.o GameObjectManager.o GameBall.o -o play -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o
