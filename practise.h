#ifndef PRACTISE_H
#define PRACTISE_H

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


// The little game engine class <3

class Game
{
private:

	sf::RenderWindow *window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Game objects
	//sf::Sprite	piggy;
	sf::RectangleShape enemy;

	void init_var();
	void init_win();
	void init_enemies();
	void initPiggy();

public:
	//constructors and distractors
	 Game();
	 virtual ~Game();

	 //accessors
	 const bool whilstRunning() const;

	 //functions
	 void pollEvents();
	 void update();
	 void render();
};

#endif