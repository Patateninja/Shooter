#include "LoadMenu.hpp"

void LoadMenu::Update(int& _buckshot, int& _dragonbreath, int& _slug, bool _bmg, Window& _window, Shotgun& _shotgun)
{
	this->m_Rect.setFillColor(Color::LightGrey);

	this->m_InputTimer += Time::GetDeltaTime();

	this->m_Rect.setPosition(_window.RelativePos(sf::Vector2f(10.f, 65.f)));
	
	this->m_BirdShot.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 75.f))));
	this->m_BuckShot.UpdateText("Infinite");
	this->m_BuckShot.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 135.f))));
	this->m_BuckShot.UpdateText(std::to_string(_buckshot));
	this->m_DragonBreath.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 195.f))));
	this->m_DragonBreath.UpdateText(std::to_string(_dragonbreath));
	this->m_Slug.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 255.f))));
	this->m_Slug.UpdateText(std::to_string(_slug));

	if (this->m_BirdShot.Update(_window, 0) && !_shotgun.Full() && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (!_bmg)
		{
			_shotgun.Load(1);
		}
		else
		{
			_shotgun.Load(5);
		}
	}
	if (this->m_BuckShot.Update(_window, 0) && !_shotgun.Full() && _buckshot != 0 && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (!_bmg)
		{
			--_buckshot;
			_shotgun.Load(2);
		}
		else
		{
			_shotgun.Load(5);
		}
	}
	if (this->m_DragonBreath.Update(_window, 0) && !_shotgun.Full() && _dragonbreath != 0 && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (!_bmg)
		{
			--_dragonbreath;
			_shotgun.Load(3);
		}
		else
		{
			_shotgun.Load(5);
		}
	}
	if (this->m_Slug.Update(_window, 0) && !_shotgun.Full() && _slug != 0 && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (!_bmg)
		{
			--_slug;
			_shotgun.Load(4);
		}
		else
		{
			_shotgun.Load(5);
		}
	}
}

void LoadMenu::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	this->m_BirdShot.Display(_window);
	this->m_BuckShot.Display(_window);
	this->m_DragonBreath.Display(_window);
	this->m_Slug.Display(_window);
}