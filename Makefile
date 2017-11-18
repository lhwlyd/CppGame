pang.o: Game.h Game.cpp stdafx.h stdafx.cpp
	g++ -c pang.cpp

SplashScreen.o: SplashScreen.h SplashScreen.cpp stdafx.h stdafx.cpp
	g++ -c SpalshScreen.cpp

MainMenu.o: MainMenu.h MainMenu.cpp
	g++ -c MainMenu.cpp

VisibleGameObject.o: stdafx.h stdafx.cpp
	g++ -c VisibleGameObject.cpp

PlayerPaddle.o: VisibleGameObject.o
	g++ -c PlayerPaddle.cpp

play: pang.o Game.o stdafx.o MainMenu.o SplashScreen.o PlayerPaddle.o
	g++ pang.o Game.o stdafx.o MainMenu.o SplashScreen.o PlayerPaddle.o VisibleGameObject.o -o play -lsfml-graphics -lsfml-window -lsfml-system
