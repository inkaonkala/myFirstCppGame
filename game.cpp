#include "practise.h"

void Game::init_var()
{
	this->window = nullptr;

	this->points = 0;
	this->enemySpawnTimer = 0.f;
	this->enemySpawnTimerMax = 10.f;
	this->maxEnemies = 5;
	this->maxCats = 5;
	this->catSpawnTimer = 0.f;
	this->catSpawnTimerMax = 10.f;
}

void Game::init_win()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "This is a test", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initCats()
{
	std::string catFiles[3] = {"kisu1.png", "kisu2.png", "kisu3.png"};
	for (const auto& file : catFiles)
	{
		sf::Texture texture;
		if(!texture.loadFromFile(file))
		{
			std::cout << "Error: Could not find the Cat texture!" << std::endl;
		}
		else
		{
			this->catTexture.push_back(texture);
		}
	}
}

void Game::init_enemies()
{
	if (!this->enemyTexture.loadFromFile("pisara.png"))
	{
		std::cout << "Error: Could not find the enemy texture!" << std::endl;
	}
	this->enemy.setTexture(this->enemyTexture);
	//check if this is the correct scale!
//	this->enemy.setScale(0.5f, 0.5f); 
	/*
	//this is for simple enemy
	this->enemy.setPosition(20.f, 20.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	//or resize with this->enemy.setScale(Vector2f(0.5f, 0.5,));
	this->enemy.setFillColor(sf::Color::Magenta);
//	this->enemy.setOutlineColor(sf::Color::Red);
//	this->enemy.setOutlineThickness(2.f);
	*/
}

void Game::spawnEnemy()
{
	/*
		set new enemy color and position
		-random pos and color (use srand SEED)
		-spawn enemy to vector
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - (this->enemy.getGlobalBounds().width))),
		//static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - (this->enemy.getSize().y)))
		0.f
		);

	//this->enemy.setFillColor(sf::Color::Magenta);

	this->enemies.push_back(this->enemy);
}

void Game::spawnCat()
{
	int randomIndex = rand() % this->catTexture.size();
	this->cat.setTexture(this->catTexture[randomIndex]);
	this->cat.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - (this->cat.getGlobalBounds().width))),
		0.f
	);
	this->cats.push_back(this->cat);
}

//Construtors and destructors
Game::Game()
{
	this->init_var();
	this->init_win();
	this->init_enemies();
	this->initCats();
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
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWin);
	//std::cout << "Mouse is here: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
}

void Game::updateCat()
{
	if (this->cats.size() < this->maxCats)
	{
		if (this->catSpawnTimer >= this->catSpawnTimerMax)
		{
			this->spawnCat();
			this->catSpawnTimer = 0.f;
		}
		else
			this->catSpawnTimer += 1.f;
	}
	for (int i = 0; i < this->cats.size(); i++)
	{
		bool deleted = false;
		this->cats[i].move(0.f, 1.f);
		if (this->cats[i].getGlobalBounds().contains(this->mousePosView))
		{
			deleted = true;
			this->points += 10;
		}	
		if (this->cats[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}
		if (deleted)
			this->cats.erase(this->cats.begin() + i);
	}

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
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 1.f);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;
				this->points -= 10;
			}
		}
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}
		if (deleted)
			this->enemies.erase(this->enemies.begin() + i);
	}
	//move enemies
	/*
	//this was the practise loop, using e
	for (auto &e : this->enemies)
	{
		e.move(0.f, 5.f);
	}
	*/
}

void Game::update()
{
	this->pollEvents();
	this->updateMousePos();
	this->updateEnem();
	this->updateCat();
}

void Game::renderCat()
{
	for (auto &e : this->cats)
	{
		this->window->draw(e);
	}
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
	this->renderCat();
//	this->window->draw(this->enemy);
//	this->window->draw(this->cat);
	this->window->display();
}
