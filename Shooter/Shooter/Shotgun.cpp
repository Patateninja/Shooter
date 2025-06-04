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
	if (this->m_Magazine.size() < this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity())
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
void Shotgun::Shoot(sf::Vector2f& _playerPos, sf::Vector2f& _playerVel, float _playerAngle, Window& _window)
{
	if (!this->m_Magazine.empty())
	{
		RscMana::Get<sf::Sound>("Shot").play();
		this->m_Magazine.front()->Shot(_playerPos, _playerVel, _playerAngle + Tools::DegToRad(Tools::Random(10,-5) / this->GetAccuracyMultiplier()), this->m_Recoil, _window);
		this->m_Magazine.erase(this->m_Magazine.begin());

		this->m_Recoil += 0.5f * this->GetRecoilModifier();
		if (this->m_Recoil > 2.f)
		{
			this->m_Recoil = 2.f;
		}
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
	this->m_Renderer.setSize(sf::Vector2f((this->m_DefaultCapacity + this->m_MagazineAttachement.GetCapacity()) * 145.f , 50.f));
	this->m_Renderer.setTexture(nullptr);
	this->m_Renderer.setPosition(_window.RelativePos(sf::Vector2f(10.f, 10.f)));
	this->m_Renderer.setFillColor(Color::Grey);
	_window.Draw(this->m_Renderer);

	for (int i = 0; i < this->m_Magazine.size(); ++i)
	{
		this->m_Renderer.setSize(sf::Vector2f(125.f, 37.5f));
		this->m_Renderer.setPosition(_window.RelativePos(sf::Vector2f(i * 125.f + (i + 1) * 12.5f + 5.f, 16.25f)));
		this->m_Renderer.setTexture(nullptr);
		this->m_Renderer.setFillColor(sf::Color::White);

		if (dynamic_cast<BirdShot*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setFillColor(sf::Color::Green);
		}
		else if (dynamic_cast<BuckShot*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setTexture(&RscMana::Get<sf::Texture>("Red_Shell"));
		}
		else if (dynamic_cast<DragonBreath*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setFillColor(Color::Flamming);
		}
		else if (dynamic_cast<Slug*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setFillColor(sf::Color::Yellow);
		}
		else if (dynamic_cast<BMG*>(this->m_Magazine[i].get()))
		{
			this->m_Renderer.setFillColor(sf::Color::Cyan);
		}

		_window.Draw(this->m_Renderer);
	}
}

//////////////////////////////////////////////////