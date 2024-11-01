#include "practise.h"

void Game::init_var()
{
	this->window = nullptr;
}

void Game::init_win()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "This is a test", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
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

void Game::update()
{
	this->pollEvents();

	//update mouse position
	std::cout << "Mouse is here: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
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
	this->window->draw(this->enemy);
	this->window->display();
}
