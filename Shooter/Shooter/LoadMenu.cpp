#include "LoadMenu.hpp"

void ReloadMenu::Update(Player& _player, Window& _window)
{
	this->m_InputTimer += Time::GetDeltaTime();
	
	this->m_Rect.setFillColor(Color::LightGrey);

	this->m_Rect.setPosition(_window.RelativePos(sf::Vector2f(10.f, 65.f)));
	
	this->m_BirdShot.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 75.f))));
	this->m_BuckShot.UpdateText("Infinite");
	this->m_BuckShot.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 135.f))));
	this->m_BuckShot.UpdateText(std::to_string(_player.GetBuckshot()));
	this->m_DragonBreath.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 195.f))));
	this->m_DragonBreath.UpdateText(std::to_string(_player.GetDragonBreath()));
	this->m_Slug.SetPosition(sf::Vector2f(_window.RelativePos(sf::Vector2f(20.f, 255.f))));
	this->m_Slug.UpdateText(std::to_string(_player.GetSlug()));

	if (this->m_BirdShot.Update(_window, 0) && !_player.GetShotgun().Full() && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
		if (!_player.GetBmgEnabled())
		{
			_player.GetShotgun().Load(1);
		}
		else
		{
			_player.GetShotgun().Load(5);
		}
	}
	if (this->m_BuckShot.Update(_window, 0) && !_player.GetShotgun().Full() && _player.GetBuckshot() != 0 && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
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
	if (this->m_DragonBreath.Update(_window, 0) && !_player.GetShotgun().Full() && _player.GetDragonBreath() != 0 && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
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
	if (this->m_Slug.Update(_window, 0) && !_player.GetShotgun().Full() && _player.GetSlug() != 0 && this->m_InputTimer > 0.3f)
	{
		this->m_InputTimer = 0.f;
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
}

void ReloadMenu::Display(Window& _window)
{
	_window.Draw(this->m_Rect);
	this->m_BirdShot.Display(_window);
	this->m_BuckShot.Display(_window);
	this->m_DragonBreath.Display(_window);
	this->m_Slug.Display(_window);
}