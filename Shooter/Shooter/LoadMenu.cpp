#include "LoadMenu.hpp"

void ReloadMenu::SwitchButtonMode(bool _bmg)
{
	if (_bmg)
	{
		this->m_BirdShot.SetPopUpText("Insanely strong ammo not even meant for this shotgun.\nStill fits however, and will kill everything it touches.");
		this->m_BirdShot.SetPopUpTexture("Bmg");

		this->m_BuckShot.SetPopUpText("Insanely strong ammo not even meant for this shotgun.\nStill fits however, and will kill everything it touches.");
		this->m_BuckShot.SetPopUpTexture("Bmg");

		this->m_DragonBreath.SetPopUpText("Insanely strong ammo not even meant for this shotgun.\nStill fits however, and will kill everything it touches.");
		this->m_DragonBreath.SetPopUpTexture("Bmg");

		this->m_Slug.SetPopUpText("Insanely strong ammo not even meant for this shotgun.\nStill fits however, and will kill everything it touches.");
		this->m_Slug.SetPopUpTexture("Bmg");
	}
	else
	{
		this->m_BirdShot.SetPopUpText("A small lead filled cartrige with not a lot of fire power.\nLuckly you have plenty of this.");
		this->m_BirdShot.SetPopUpTexture("Bird");

		this->m_BuckShot.SetPopUpText("A volley of pellets for whatever you're aiming at.\nPretty efficient at close range.");
		this->m_BuckShot.SetPopUpTexture("Buck");

		this->m_DragonBreath.SetPopUpText("A special firery ammunition, setting everything ablaze.\nSet enemies on fire, dealing damage over time.");
		this->m_DragonBreath.SetPopUpTexture("Dragon");

		this->m_Slug.SetPopUpText("A powefull single ammo, wich shreads everything in its path.\nPierce through both human and shield.");
		this->m_Slug.SetPopUpTexture("Slug");
	}
}

void ReloadMenu::Update(Player& _player, EnemyList& _enemyList, Window& _window)
{
	this->m_InputTimer += Time::GetDeltaTime();
	
	if (this->m_BMG != _player.GetBmgEnabled())
	{
		this->m_BMG = _player.GetBmgEnabled();
		this->SwitchButtonMode(this->m_BMG);
	}
	if (this->m_ShotgunHasAmmo != !_player.GetShotgun().Empty())
	{
		this->m_ShotgunHasAmmo = !_player.GetShotgun().Empty();
		if (this->m_ShotgunHasAmmo)
		{
			this->m_Rect.setSize(sf::Vector2f(160.f, 310.f));
		}
		else
		{
			this->m_Rect.setSize(sf::Vector2f(160.f, 250.f));
		}
	}

	this->m_Rect.setFillColor(Color::LightGrey);

	this->m_Rect.setPosition(_window.RelativePos(sf::Vector2f(10.f, 65.f)));
	
	this->m_BirdShot.SetPosition(_window,_window.RelativePos(sf::Vector2f(20.f, 75.f)));

	this->m_BuckShot.SetPosition(_window, _window.RelativePos(sf::Vector2f(20.f, 135.f)));
	if (this->m_BMG)
	{
		this->m_BuckShot.UpdateText("");
	}
	else
	{
		this->m_BuckShot.UpdateText(std::to_string(_player.GetBuckshot()));
	}

	this->m_DragonBreath.SetPosition(_window, _window.RelativePos(sf::Vector2f(20.f, 195.f)));
	if (this->m_BMG)
	{
		this->m_DragonBreath.UpdateText("");
	}
	else
	{
		this->m_DragonBreath.UpdateText(std::to_string(_player.GetDragonBreath()));
	}

	this->m_Slug.SetPosition(_window, _window.RelativePos(sf::Vector2f(20.f, 255.f)));
	if (this->m_BMG)
	{
		this->m_Slug.UpdateText("");
	}
	else
	{
		this->m_Slug.UpdateText(std::to_string(_player.GetSlug()));
	}


	if (this->m_ShotgunHasAmmo)
	{
		this->m_Ready.SetPosition(_window.RelativePos(sf::Vector2f(20.f, 315.f)));
		if (this->m_Ready.Update(_window) && this->m_InputTimer > 0.3f)
		{
			this->m_InputTimer = 0.f;
			_player.Ready();
			_enemyList.Activate();
		}
	}
	
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

	if (this->m_ShotgunHasAmmo)
	{
		this->m_Ready.Display(_window);
	}
}