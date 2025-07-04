#include "Shotgun.hpp"

//////////////////////////////////////////////////

Shotgun::~Shotgun()
{
	this->EmptyMagazine();
}

void Shotgun::Modify(Muzzle& _muzzle, Grip& _grip, Magazine& _magazine, Stock& _stock)
{
	this->m_MuzzleAttachement = _muzzle;
	this->m_GripAttachement = _grip;
	this->m_MagazineAttachement = _magazine;
	this->m_Stock = _stock;
}

void Shotgun::Load(int _input)
{
	if (int(this->m_Magazine.size()) < this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity())
	{
		switch (_input)
		{
			case 1 :
				this->m_Magazine.push_back(std::make_unique<BirdShot>(this->m_MuzzleAttachement.GetSpreadMod(), this->m_MuzzleAttachement.GetRangeMod(), this->m_MuzzleAttachement.GetVelocityMod()));
				break;
			case 2 :
				this->m_Magazine.push_back(std::make_unique<BuckShot>(this->m_MuzzleAttachement.GetSpreadMod(), this->m_MuzzleAttachement.GetRangeMod(), this->m_MuzzleAttachement.GetVelocityMod()));
				break;
			case 3 :
				this->m_Magazine.push_back(std::make_unique<DragonBreath>(this->m_MuzzleAttachement.GetSpreadMod(), this->m_MuzzleAttachement.GetRangeMod(), this->m_MuzzleAttachement.GetVelocityMod()));
				break;
			case 4 :
				this->m_Magazine.push_back(std::make_unique<Slug>(this->m_MuzzleAttachement.GetSpreadMod(), this->m_MuzzleAttachement.GetRangeMod(), this->m_MuzzleAttachement.GetVelocityMod()));
				break;
			case 5 :
				this->m_Magazine.push_back(std::make_unique<BMG>(this->m_MuzzleAttachement.GetSpreadMod(), this->m_MuzzleAttachement.GetRangeMod(), this->m_MuzzleAttachement.GetVelocityMod()));
		}
	}
}
void Shotgun::Unload(int& _buckshot, int& _dragonbreath, int& _slug, int& _maxammo)
{
	for (const std::unique_ptr<Shell>& shell : this->m_Magazine)
	{
		if (dynamic_cast<BuckShot*>(shell.get()))
		{
			if (_buckshot < _maxammo)
			{
				++_buckshot;
			}
		}
		else if (dynamic_cast<DragonBreath*>(shell.get()))
		{
			if (_dragonbreath < _maxammo)
			{
				++_dragonbreath;
			}
		}
		else if (dynamic_cast<Slug*>(shell.get()))
		{
			if (_slug < _maxammo)
			{
				++_slug;
			}
		}
	}

	this->EmptyMagazine();
}
void Shotgun::Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _playerAngle, Window& _window)
{
	if (!this->m_Magazine.empty())
	{
		RscMana::Get<sf::Sound>("Player_Shot").play();
		this->m_Magazine.front()->Shot(_playerPos, _playerVel, _playerAngle + Tools::DegToRad(Tools::Random(3,-3) / this->GetAccuracyMultiplier()), this->m_Recoil, _window);
		this->m_Magazine.erase(this->m_Magazine.begin());

		this->m_Recoil += 0.5f * this->GetRecoilModifier();
		if (this->m_Recoil > 2.f)
		{
			this->m_Recoil = 2.f;
		}
	}
	else
	{
		RscMana::Get<sf::Sound>("EmptyMag").play();
	}
}
void Shotgun::EmptyMagazine()
{
	while (!this->m_Magazine.empty())
	{
		this->m_Magazine.front().reset();
		this->m_Magazine.erase(this->m_Magazine.begin());
	}

	this->m_Magazine.clear();
}

void Shotgun::ReduceRecoil()
{
	if (this->m_Recoil > 1)
	{
		this->m_Recoil -= Time::GetDeltaTime() * 0.3f;
	}
	else
	{
		this->m_Recoil = 1;
	}
}


void Shotgun::DisplayMagazine(Window& _window)
{
	this->m_Renderer.setSize(sf::Vector2f((this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity()) * 135.f + 20.f, 50.f));
	this->m_Renderer.setTexture(nullptr);
	this->m_Renderer.setPosition(_window.RelativePos(sf::Vector2f(10.f, 10.f)));
	this->m_Renderer.setFillColor(Color::Grey);
	_window.Draw(this->m_Renderer);

	this->m_Renderer.setTexture(&RscMana::Get<sf::Texture>("Ammo"));
	this->m_Renderer.setFillColor(sf::Color::White);
	for (int i = 0; i < this->m_Magazine.size(); ++i)
	{
		this->m_Renderer.setSize(sf::Vector2f(126.f, 45.f));
		this->m_Renderer.setPosition(_window.RelativePos(sf::Vector2f(i * 126.f + (i + 1) * 10.f + 10.f, 12.5)));

		if (dynamic_cast<BirdShot*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setTextureRect(sf::IntRect(140, 0, 70, 25));
		}
		else if (dynamic_cast<BuckShot*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setTextureRect(sf::IntRect(70,0,70,25));
		}
		else if (dynamic_cast<DragonBreath*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setTextureRect(sf::IntRect(0, 0, 70, 25));
		}
		else if (dynamic_cast<Slug*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setTextureRect(sf::IntRect(210, 0, 70, 25));
		}
		else if (dynamic_cast<BMG*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setTextureRect(sf::IntRect(280, 0, 70, 25));
		}

		_window.Draw(this->m_Renderer);
	}
}

//////////////////////////////////////////////////