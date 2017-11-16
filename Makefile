pang.o: Game.h Game.cpp stdafx.h stdafx.cpp
	g++ -c pang.cpp

play: pang.o Game.o stdafx.o
	g++ pang.o Game.o stdafx.o -o play -lsfml-graphics -lsfml-window -lsfml-system
