#include "LoadMenu.hpp"

void LoadMenu::Update(int& _buckshot, int& _dragonbreath, int& _slug, bool _bmg, Window& _window, Shotgun& _shotgun)
{
	this->m_Rect.setFillColor(Color::LightGrey);

	this->m_InputTimer += Time::GetDeltaTime();

	this->m_Text.setString(this->infinite + "\n" + std::to_string(_buckshot) + "\n" + std::to_string(_dragonbreath) + "\n" + std::to_string(_slug));

	if (this->m_BirdShot.Update(_window, 0) && !_shotgun.Full() && this->m_InputTimer > 0.5f)
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
	if (this->m_BuckShot.Update(_window, 0) && !_shotgun.Full() && _buckshot != 0 && this->m_InputTimer > 0.5f)
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
	if (this->m_DragonBreath.Update(_window, 0) && !_shotgun.Full() && _dragonbreath != 0 && this->m_InputTimer > 0.5f)
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
	if (this->m_Slug.Update(_window,0) && !_shotgun.Full() && _slug != 0 && this->m_InputTimer > 0.5f)
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
	this->m_Rect.setPosition(_window.RelativePos(sf::Vector2f(10.f, 50.f)));
	_window.Draw(this->m_Rect);

	this->m_BirdShot.Display(_window);
	this->m_BuckShot.Display(_window);
	this->m_DragonBreath.Display(_window);
	this->m_Slug.Display(_window);

	this->m_Text.setPosition(_window.RelativePos(sf::Vector2f(11.f, 51.f)));
	_window.Draw(this->m_Text);
}