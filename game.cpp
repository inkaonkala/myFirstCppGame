#include "practise.h"

void Game::init_var()
{
	this->window = nullptr;

	this->points = 0;
	this->enemySpawnTimer = 0.f;
	this->enemySpawnTimerMax = 1000.f;
	this->maxEnemies = 5;
}

void Game::init_win()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "This is a test", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::init_enemies()
{
	this->enemy.setPosition(20.f, 20.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	//or resize with this->enemy.setScale(Vector2f(0.5f, 0.5,));
	this->enemy.setFillColor(sf::Color::Magenta);
	this->enemy.setOutlineColor(sf::Color::Red);
	this->enemy.setOutlineThickness(2.f);
}

void Game::spawnEnemy()
{
	/*
		set new enemy color and position
		-random pos and color (use srand SEED)
		-spawn enemy to vector
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - (this->enemy.getSize().x))),
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - (this->enemy.getSize().y)))
		0.f
		);

	this->enemy.setFillColor(sf::Color::Magenta);

	this->enemies.push_back(this->enemy);
}

//Construtors and destructors
Game::Game()
{
	this->init_var();
	this->init_win();
	this->init_enemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors

const bool Game::whilstRunning() const
{
	return this->window->isOpen();
}

//FUNCTIONS

// All the game logic

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break ;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::updateMousePos()
{
	// vector2i(int x, int y)
	this->mousePosWin = sf::Mouse::getPosition(*this->window);
	//std::cout << "Mouse is here: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
}

void Game::updateEnem()
{
	if(this->enemies.size() < this->maxEnemies)
	{
	//spawn and update
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	//move enemies
	for (auto &e : this->enemies)
	{
		e.move(0.f, 5.f);
	}
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePos();
	this->updateEnem();
}

void Game::renderEnemy()
{
	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}	
}

// all the drawing
void Game::render()
{
	/*
		-clear old
		-render objct 
		-display frames in window
	*/

	this->window->clear();

	//will draw game objct
	this->renderEnemy();
	this->window->draw(this->enemy);
	this->window->display();
}
