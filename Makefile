CXX=g++
CXXFLAGS=-g -std=c++11 -Wall
SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system
#BIN=prog

OBJS=pang.o SplashScreen.o MainMenu.o VisibleGameObject.o PlayerPaddle.o GameObjectManager.o GameBall.o Game.o

all: play

pang.o: Game.h Game.cpp stdafx.h stdafx.cpp
	g++ -c pang.cpp

Game.o: Game.h
	g++ -c Game.cpp

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

play: $(OBJS)
	$(CXX) $(OBJS) -o play $(SFML_FLAGS)

.PHONY: clean
clean:
	rm -f *.o
	@echo clean done
