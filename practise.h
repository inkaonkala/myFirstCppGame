#ifndef PRACTISE_H
#define PRACTISE_H

#include <iostream>
#include <vector> //for enemies
#include <ctime> // for randomizing

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

	//mouse stuff
	sf::Vector2i mousePosWin;
	sf::Vector2f mousePosView;

	//Game logic stuff
	int		points;

	float	enemySpawnTimer;
	float	enemySpawnTimerMax;
	int		maxEnemies;

	float	catSpawnTimer;
	float	catSpawnTimerMax;
	int		maxCats;

	//Game objects stuff

	std::vector<sf::Texture> catTexture;
	std::vector<sf::Sprite> cats;
	sf::Sprite cat;

	sf::Texture enemyTexture;
	std::vector<sf::Sprite> enemies;
	sf::Sprite enemy;

	//this is for the simple version
	//std::vector<sf::RectangleShape> enemies;
	//sf::RectangleShape enemy;

	void init_var();
	void init_win();
	void initCats();
	void init_enemies();
//	void initKisu();

public:
	//constructors and distractors
	 Game();
	 virtual ~Game();

	 //accessors
	 const bool whilstRunning() const;

	 //functions
	 void pollEvents();
	 void updateMousePos();
	 
	 void spawnEnemy();
	 void updateEnem();
	 void renderEnemy();
	 
	 void spawnCat();
	 void updateCat();
	 void renderCat();

	 void update();
	 void render();
};

#endif