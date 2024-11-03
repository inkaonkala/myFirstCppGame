#include <iostream>

#include "practise.h"

// using namespace sf;

int main()
{
	//init seed for randomizing
	std::srand(static_cast<unsigned>(time(NULL)));

	// init the little engine <3
	Game game;
	//Gameloop AKA Event polling
	while (game.whilstRunning())
	{
		game.update();

		game.render();

	}	

	return (0);
}