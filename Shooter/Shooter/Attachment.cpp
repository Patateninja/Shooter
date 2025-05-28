#include "Attachment.hpp"

//////////////////////////////////////////////////

Muzzle::Muzzle()
{
	this->m_Name = "Default";
	this->m_UnlockLevel = 0;

	this->m_SpreadModifier = 1;
	this->m_VelocityModifier = 1;
	this->m_RangeModifier = 1;
}

Muzzle::Muzzle(std::string _name, int _level, float _spread, float _velocity, float _range)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_SpreadModifier = _spread;
	this->m_VelocityModifier = _velocity;
	this->m_RangeModifier = _range;
}

Muzzle::Muzzle(const Muzzle& _muzzle)
{
	this->m_Name = _muzzle.m_Name;
	this->m_UnlockLevel = _muzzle.m_UnlockLevel;

	this->m_RangeModifier = _muzzle.m_RangeModifier;
	this->m_SpreadModifier = _muzzle.m_SpreadModifier;
	this->m_VelocityModifier = _muzzle.m_VelocityModifier;
}

//////////////////////////////////////////////////

Magazine::Magazine()
{
	this->m_Name = "Default";
	this->m_UnlockLevel = 0;

	this->m_Capacity = 0;
}

Magazine::Magazine(std::string _name, int _level, int _capacity)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_Capacity = _capacity;
}

Magazine::Magazine(const Magazine& _magazine)
{
	this->m_Name = _magazine.m_Name;
	this->m_UnlockLevel = _magazine.m_UnlockLevel;

	this->m_Capacity = _magazine.m_Capacity;
}

//////////////////////////////////////////////////

Grip::Grip()
{
	this->m_Name = "Default";
	this->m_UnlockLevel = 0;

	this->m_AimSpeedModifier = 1;
	this->m_RecoilModifier = 1;
	this->m_RateOfFireModifier = 1;
}

Grip::Grip(std::string _name, int _level, float _aim, float _recoil, float _rof)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_AimSpeedModifier = _aim;
	this->m_RecoilModifier = _recoil;
	this->m_RateOfFireModifier = _rof;
}

Grip::Grip(const Grip& _grip)
{
	this->m_Name = _grip.m_Name;
	this->m_UnlockLevel = _grip.m_UnlockLevel;

	this->m_AimSpeedModifier = _grip.m_AimSpeedModifier;
	this->m_RecoilModifier = _grip.m_RecoilModifier;
	this->m_RateOfFireModifier = _grip.m_RateOfFireModifier;
}

//////////////////////////////////////////////////

Stock::Stock()
{
	this->m_Name = "Default";
	this->m_UnlockLevel = 0;

	this->m_AimSpeedModifier = 1.f;
	this->m_RecoilModifier = 1.f;
	this->m_WalkSpeedModifier = 1.f;
}

Stock::Stock(std::string _name, int _level, float _aim, float _recoil, float _walk)
{
	this->m_Name = _name;
	this->m_UnlockLevel = _level;

	this->m_AimSpeedModifier = _aim;
	this->m_RecoilModifier = _recoil;
	this->m_WalkSpeedModifier = _walk;
}

Stock::Stock(const Stock& _stock)
{
	this->m_Name = _stock.m_Name;
	this->m_UnlockLevel = _stock.m_UnlockLevel;

	this->m_AimSpeedModifier = _stock.m_AimSpeedModifier;
	this->m_RecoilModifier = _stock.m_RecoilModifier;
	this->m_WalkSpeedModifier = _stock.m_WalkSpeedModifier;
}

//////////////////////////////////////////////////