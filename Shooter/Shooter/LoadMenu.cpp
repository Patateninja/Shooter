#include "LoadMenu.hpp"

void ReloadMenu::Update(Player& _player, Window& _window)
{
	this->m_InputTimer += Time::GetDeltaTime();
	
	this->m_Rect.setFillColor(Color::LightGrey);

	this->m_Rect.setPosition(_window.RelativePos(sf::Vector2f(10.f, 65.f)));
	
	this->m_BirdShot.SetPosition(_window,_window.RelativePos(sf::Vector2f(20.f, 75.f)));

	this->m_BuckShot.SetPosition(_window, _window.RelativePos(sf::Vector2f(20.f, 135.f)));
	this->m_BuckShot.UpdateText(std::to_string(_player.GetBuckshot()));

	this->m_DragonBreath.SetPosition(_window, _window.RelativePos(sf::Vector2f(20.f, 195.f)));
	this->m_DragonBreath.UpdateText(std::to_string(_player.GetDragonBreath()));

	this->m_Slug.SetPosition(_window, _window.RelativePos(sf::Vector2f(20.f, 255.f)));
	this->m_Slug.UpdateText(std::to_string(_player.GetSlug()));

	if (RscMana::Get<sf::Sound>("ButtonClicked").getStatus() == sf::Sound::Playing)
	{
		RscMana::Get<sf::Sound>("ButtonClicked").stop();
	}
	if (RscMana::Get<sf::Sound>("ButtonHover").getStatus() == sf::Sound::Playing)
	{
		RscMana::Get<sf::Sound>("ButtonHover").stop();
	}

	if (this->m_BirdShot.Update(_window) && !_player.GetShotgun().Full() && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		RscMana::Get<sf::Sound>("Reload").play();
		if (!_player.GetBmgEnabled())
		{
			_player.GetShotgun().Load(1);
		}
		else
		{
			_player.GetShotgun().Load(5);
		}
	}
	if (this->m_BuckShot.Update(_window) && !_player.GetShotgun().Full() && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (_player.GetBuckshot() != 0)
		{
			RscMana::Get<sf::Sound>("Reload").play();
			if (!_player.GetBmgEnabled())
			{
				--_player.GetBuckshot();
				_player.GetShotgun().Load(2);
			}
			else
			{
				_player.GetShotgun().Load(5);
			}
		}
		else
		{
			RscMana::Get<sf::Sound>("Reload_Denied").play();
		}
	}
	if (this->m_DragonBreath.Update(_window) && !_player.GetShotgun().Full() && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (_player.GetDragonBreath() != 0)
		{
			RscMana::Get<sf::Sound>("Reload").play();
			if (!_player.GetBmgEnabled())
			{
				--_player.GetDragonBreath();
				_player.GetShotgun().Load(3);
			}
			else
			{
				_player.GetShotgun().Load(5);
			}
		}
		else
		{
			RscMana::Get<sf::Sound>("Reload_Denied").play();
		}
	}
	if (this->m_Slug.Update(_window) && !_player.GetShotgun().Full() && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (_player.GetSlug() != 0)
		{
			RscMana::Get<sf::Sound>("Reload").play();
			if (!_player.GetBmgEnabled())
			{
				--_player.GetSlug();
				_player.GetShotgun().Load(4);
			}
			else
			{
				_player.GetShotgun().Load(5);
			}
		}
		else
		{
			RscMana::Get<sf::Sound>("Reload_Denied").play();
		}

	}
}

void ReloadMenu::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	this->m_BirdShot.Display(_window);
	this->m_BuckShot.Display(_window);
	this->m_DragonBreath.Display(_window);
	this->m_Slug.Display(_window);
}