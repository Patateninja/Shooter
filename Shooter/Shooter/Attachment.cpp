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

//////////////////////////////////////////////////