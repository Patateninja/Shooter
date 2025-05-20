#include "Shotgun.hpp"

//////////////////////////////////////////////////

Shotgun::Shotgun()
{
	this->m_Magazine.clear();
	this->m_MaxCapacity = 4;
}
Shotgun::~Shotgun()
{
	this->EmptyMagazine();
}

void Shotgun::DisplayMagazine(Window& _window)
{
	sf::RectangleShape bg(sf::Vector2f(1135.f, 100.f));
	bg.setPosition(_window.RelativePos(sf::Vector2f(10.f, 10.f)));
	bg.setFillColor(Color::Grey);
	_window.Draw(bg);

	for (int i = 0; i < this->m_Magazine.size(); ++i)
	{
		sf::RectangleShape shell(sf::Vector2f(250.f, 75.f));
		shell.setPosition(_window.RelativePos(sf::Vector2f(i * 250.f + (i + 1) * 25.f + 10.f, 22.5f)));

		if (dynamic_cast<BirdShot*>(this->m_Magazine[i].get()))
		{
			shell.setFillColor(sf::Color::Green);
		}
		else if (dynamic_cast<BuckShot*>(this->m_Magazine[i].get()))
		{
			shell.setTexture(&RscMana::Get<sf::Texture>("Red_Shell"));
		}
		else if (dynamic_cast<DragonBreath*>(this->m_Magazine[i].get()))
		{
			shell.setFillColor(Color::Flamming);
		}
		else if (dynamic_cast<Slug*>(this->m_Magazine[i].get()))
		{
			shell.setFillColor(sf::Color::Yellow);
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
void Shotgun::Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, Window& _window)
{
	if (!this->m_Magazine.empty())
	{
		RscMana::Get<sf::Sound>("Shot").play();
		this->m_Magazine.front()->Shot(_playerPos, _playerVel, _window);
		this->m_Magazine.erase(this->m_Magazine.begin());
	}
}

void Shotgun::EmptyMagazine()
{
	for (std::unique_ptr<Shell>& shell : this->m_Magazine)
	{
		shell.release();
	}

	this->m_Magazine.clear();
}

//////////////////////////////////////////////////