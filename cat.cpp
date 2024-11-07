
#include "practise.h"

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

void Game::renderCat()
{
	for (auto &e : this->cats)
	{
		this->window->draw(e);
	}
}