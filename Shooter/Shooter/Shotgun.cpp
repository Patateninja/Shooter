#include "Shotgun.hpp"

//////////////////////////////////////////////////

Shotgun::Shotgun()
{
	this->m_Magazine.clear();
	this->m_MaxCapacity = 4;
}
Shotgun::~Shotgun()
{
	this->m_Magazine.clear();
}

void Shotgun::DisplayMagazine(Window& _window, ResourceManager& _rscmana)
{
	sf::RectangleShape bg(sf::Vector2f(1135.f, 100.f));
	bg.setPosition(sf::Vector2f(10.f, 10.f));
	bg.setFillColor(sf::Color(100, 100, 100, 255));
	_window.Draw(bg);

	for (int i = 0; i < this->m_Magazine.size(); ++i)
	{
		sf::RectangleShape shell(sf::Vector2f(250.f, 75.f));
		shell.setPosition(sf::Vector2f(i * 250.f + (i + 1) * 25.f + 10.f, 22.5f));

		if (dynamic_cast<BirdShot*>(this->m_Magazine[i].get()))
		{
			shell.setFillColor(sf::Color(0, 255, 0, 255));
		}
		else if (dynamic_cast<BuckShot*>(this->m_Magazine[i].get()))
		{
			shell.setTexture(&RscMana::Get<sf::Texture>("Red_Shell"));
		}
		else if (dynamic_cast<DragonBreath*>(this->m_Magazine[i].get()))
		{
			shell.setFillColor(sf::Color(255, 125, 0, 255));
		}
		else if (dynamic_cast<Slug*>(this->m_Magazine[i].get()))
		{
			shell.setFillColor(sf::Color(255, 255, 0, 255));
		}

		_window.Draw(shell);
	}
}

void Shotgun::Load(int _input)
{
	if (this->m_Magazine.size() < this->m_MaxCapacity)
	{
		switch (_input)
		{
			case 1:
				this->m_Magazine.push_back(std::make_unique<BirdShot>());
				break;
			case 2:
				this->m_Magazine.push_back(std::make_unique<BuckShot>());
				break;
			case 3:
				this->m_Magazine.push_back(std::make_unique<DragonBreath>());
				break;
			case 4:
				this->m_Magazine.push_back(std::make_unique<Slug>());
				break;
		}
	}
}
void Shotgun::Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel)
{
	if (!this->m_Magazine.empty())
	{
		this->m_Magazine.front()->Shot(_playerPos, _playerVel);
		this->m_Magazine.erase(this->m_Magazine.begin());
	}
}

//////////////////////////////////////////////////