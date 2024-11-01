#include <iostream>

#include "practise.h"

// using namespace sf;

int main()
{
	// init the little engine <3
	Game game;
	//Gameloop AKA Event polling
	while (game.whilstRunning())
	{
		game.update();

		game.render();


		/*
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break ;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			default:
				break;
			}
		}

		// Updates

		//Render
		window.clear(sf::Color(173, 216, 230)); // clear first
		// draw the game here!
		window.display(); //tells program that drawing is done
		*/
	}	

	return (0);
}